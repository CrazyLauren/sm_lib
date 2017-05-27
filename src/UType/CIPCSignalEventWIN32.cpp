// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CIPCSignalEventWIN32.cpp
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 24.06.2016
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */   
#ifdef _WIN32
#include <deftype>
#include <UType/CIPCSignalEvent.h>

namespace NSHARE
{
extern size_t get_unique_name(char const* aPreifix,uint8_t* aTo,size_t aSize);

size_t CIPCSignalEvent::sMRequredBufSize()
{
	return CIPCSignalEvent::eReguredBufSize;
}

struct CIPCSignalEvent::CImpl
{
	HANDLE FSignalEvent;
	eOpenType FType;
	NSHARE::CText FName;
	CImpl() :
			FSignalEvent(INVALID_HANDLE_VALUE),FType(E_UNDEF)
	{

	}
	bool MInit(uint8_t* aBuf, size_t aSize, eOpenType aIsNew)
	{
		if(aSize<eReguredBufSize)
		{
			LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<< eReguredBufSize;
			return false;
		}
		void *const _p=memchr(aBuf,'\0',aSize);
		bool const _is_empty=_p== NULL || _p==aBuf;

		if(aIsNew==E_UNDEF && _is_empty)
		{
			VLOG(2)<<"The buffer is empty. Create the mutex";
			aIsNew=E_HAS_TO_BE_NEW;
		}

		switch (aIsNew)
		{
			case E_HAS_TO_BE_NEW:
			{
				get_unique_name("cv",aBuf, aSize);
				break;
			}
			case E_UNDEF:
			{
				break;
			}
			case E_HAS_EXIST:
			{
				if(_is_empty)
				{
					LOG(ERROR)<<"The buffer is empty.";
					return false;
				}
				break;
			}
		}

		FSignalEvent = ::CreateEvent(NULL, FALSE, FALSE, (char*)aBuf);
		if (FSignalEvent == INVALID_HANDLE_VALUE)
			return false;

		DWORD const _last_error = GetLastError();
		LOG_IF(FATAL,FSignalEvent==INVALID_HANDLE_VALUE)
																	<< "CreateEvent failed. signalEvent:"
																	<< FSignalEvent
																	<< " error:"
																	<< _last_error;

		LOG_IF(DFATAL,_last_error == ERROR_ALREADY_EXISTS && aIsNew==E_HAS_TO_BE_NEW)
																								<< "The signalEvent  "
																								<< (char*)aBuf
																								<< " is exist.";
		VLOG_IF(2,_last_error != ERROR_ALREADY_EXISTS) << "The New signalEvent "
																<< (char*)aBuf
																<< " has been created.";
		VLOG_IF(2,_last_error == ERROR_ALREADY_EXISTS) << "The signalEvent "
																<< (char*)aBuf
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
				LOG(ERROR)<<"The mutex is not to be a new, but it's not true.";
				CloseHandle(FSignalEvent);
				return false;
			}
			return true;
		}
		case E_UNDEF:
		{
			if (_is_new)
				aIsNew = E_HAS_TO_BE_NEW;
			else
				aIsNew = E_HAS_EXIST;

			break;
		}
		}
		FType=aIsNew;
		FName=(char*)aBuf;
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
CIPCSignalEvent::CIPCSignalEvent(uint8_t* aBuf, size_t aSize, eOpenType aIsNew) :
		FPImpl(new CImpl)
{
	MInit(aBuf,aSize, aIsNew);
}
bool CIPCSignalEvent::MInit(uint8_t* aBuf, size_t aSize, eOpenType aHasToBeNew)
{
	CHECK_NOTNULL(FPImpl);
	return FPImpl->MInit(aBuf,aSize, aHasToBeNew);
}
void CIPCSignalEvent::MFree()
{
	CHECK_NOTNULL(FPImpl);
	if (FPImpl->FSignalEvent != INVALID_HANDLE_VALUE)
	{
		VLOG(2) << "Event " << FPImpl->FName << " is freed.";
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
	CHECK_NOTNULL(FPImpl);
	VLOG(2) << "Event " << FPImpl->FName << " is waited for.";
	LOG_IF(DFATAL,FPImpl->FSignalEvent==INVALID_HANDLE_VALUE) << "Event "
																		<< FPImpl->FName
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
	VLOG(2) << "Event " << FPImpl->FName << " has been singaled.";
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
	VLOG(2) << "Event " << FPImpl->FName << " is signaled.";
	return SetEvent(FPImpl->FSignalEvent) != FALSE;
}
NSHARE::CText const& CIPCSignalEvent::MName() const
{
	return FPImpl->FName;
}
void CIPCSignalEvent::MUnlink()
{
	;
}
bool CIPCSignalEvent::MIsInited() const
{
	return FPImpl->FSignalEvent != INVALID_HANDLE_VALUE ;
}
CIPCSignalEvent::eOpenType CIPCSignalEvent::MGetType() const
{
	return FPImpl->FType;
}
} /* namespace NSHARE */
#endif
