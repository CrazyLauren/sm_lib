/*
 * CIPCSignalEventWIN32.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 24.06.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */   
#ifdef _WIN32
#include <deftype>
#include <UType/CIPCSignalEvent.h>

namespace NSHARE
{
struct CIPCSignalEvent::CImpl
{
	HANDLE FSignalEvent;

	CImpl() :
			FSignalEvent(INVALID_HANDLE_VALUE)
	{

	}
	bool MInit(char const* aName, eOpenType aIsNew)
	{
		FSignalEvent = ::CreateEvent(NULL, FALSE, FALSE, aName);
		DWORD const _last_error = GetLastError();
		LOG_IF(FATAL,FSignalEvent==INVALID_HANDLE_VALUE)
																	<< "CreateEvent failed. signalEvent:"
																	<< FSignalEvent
																	<< " error:"
																	<< _last_error;

		LOG_IF(DFATAL,_last_error == ERROR_ALREADY_EXISTS && aIsNew==E_HAS_TO_BE_NEW)
																								<< "The signalEvent  "
																								<< aName
																								<< " is exist.";
		VLOG_IF(2,_last_error != ERROR_ALREADY_EXISTS) << "The New signalEvent "
																<< aName
																<< " has been created.";
		VLOG_IF(2,_last_error == ERROR_ALREADY_EXISTS) << "The signalEvent "
																<< aName
																<< " is exist.";

		bool _is_new = _last_error != ERROR_ALREADY_EXISTS;
		switch (aIsNew)
		{
		case E_HAS_TO_BE_NEW:
		{
			if (!_is_new)
			{
				CloseHandle(FSignalEvent);
				return false;
			}
			return true;
			break;
		}
		case E_HAS_EXIST:
		{
			if (_is_new)
			{
				CloseHandle(FSignalEvent);
				return false;
			}
			return true;
		}
		case E_UNDEF:
			break;
		}
		return true;
	}
	~CImpl()
	{
		if (FSignalEvent != INVALID_HANDLE_VALUE)
			CloseHandle(FSignalEvent);
	}
};
CIPCSignalEvent::CIPCSignalEvent() :
		FPImpl(new CImpl)
{

}
CIPCSignalEvent::CIPCSignalEvent(char const* aName, eOpenType aIsNew) :
		FPImpl(new CImpl)
{
	MInit(aName, aIsNew);
}
bool CIPCSignalEvent::MInit(char const* aName, eOpenType aHasToBeNew)
{
	CHECK_NOTNULL(FPImpl);
	FName = aName;
	VLOG(2) << "Event " << FName << " is initialized.";
	return FPImpl->MInit(aName, aHasToBeNew);
}
void CIPCSignalEvent::MFree()
{
	CHECK_NOTNULL(FPImpl);
	if (FPImpl->FSignalEvent != INVALID_HANDLE_VALUE)
	{
		VLOG(2) << "Event " << FName << " is freed.";
		BOOL _is = CloseHandle(FPImpl->FSignalEvent);
		VLOG(2) << "Close handle return " << _is << " last error "
							<< (_is ? 0 : GetLastError());
		FPImpl->FSignalEvent = INVALID_HANDLE_VALUE;
	}
}
CIPCSignalEvent::~CIPCSignalEvent()
{
	delete FPImpl;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem * aMutex, const struct timespec* aVal)
{
	VLOG(2) << "Event " << FName << " is waited for.";
	CHECK_NOTNULL(FPImpl);
	LOG_IF(DFATAL,FPImpl->FSignalEvent==INVALID_HANDLE_VALUE) << "Event "
																		<< FName
																		<< " is not init.";
	if (FPImpl->FSignalEvent == INVALID_HANDLE_VALUE)
		return false;
	unsigned msec = INFINITE;
	if (aVal)
	{
		msec = static_cast<unsigned>(aVal->tv_sec * 1000.0 + aVal->tv_nsec / 1000.0 / 1000.0);
	}
	aMutex->MPost();
	DWORD ret;
	bool _is_timeout = false;
	for (HANG_INIT;;HANG_CHECK)
	{
		ret = ::WaitForSingleObject(FPImpl->FSignalEvent, msec);
		_is_timeout=ret == WAIT_TIMEOUT;
		if(ret == WAIT_OBJECT_0 ||ret == WAIT_TIMEOUT)
		break;
	}
	bool _is = aMutex->MWait();
	CHECK(_is);
	(void) _is;
	VLOG(2) << "Event " << FName << " has been singaled.";
	return !_is_timeout;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem *aMutex, double const aTime)
{
	LOG_IF(FATAL,aTime<0) << "Time is negative.";
	struct timespec _spec;
	_spec.tv_sec = static_cast<unsigned>(aTime);
	_spec.tv_nsec = static_cast<long>((aTime - _spec.tv_sec) * 1000.0 * 1000.0 * 100.0);
	return MTimedwait(aMutex, &_spec);
}

bool CIPCSignalEvent::MSignal()
{
	CHECK_NOTNULL(FPImpl);
	VLOG(2) << "Event " << FName << " is signaled.";
	return SetEvent(FPImpl->FSignalEvent) != FALSE;
}
NSHARE::CText const& CIPCSignalEvent::MName() const
{
	return FName;
}
void CIPCSignalEvent::MUnlink()
{
	;
}
bool CIPCSignalEvent::MIsInited() const
{
	return FPImpl->FSignalEvent != INVALID_HANDLE_VALUE ;
}
} /* namespace NSHARE */
#endif
