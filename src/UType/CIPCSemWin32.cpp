/*
 * CIPCSemWin32.cpp
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

namespace NSHARE
{
struct CIPCSem::CImpl
{
	CImpl() :
			FSem(INVALID_HANDLE_VALUE), FIs(false)
	{

	}
	mutable HANDLE FSem;
	bool FIs;
};
int const CIPCSem::MAX_VALUE=std::numeric_limits<long>::max()/2;
CIPCSem::CIPCSem(char const* aName, unsigned int value,
		eOpenType const aHasToBeNew, int aInitvalue) :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	bool const _is=MInit(aName, value, aHasToBeNew,aInitvalue);
	(void)_is;
	CHECK(_is);
}
CIPCSem::CIPCSem() :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	;
}
bool CIPCSem::MInit(char const* aName, unsigned int value,
		eOpenType  aHasToBeNew, int aInitvalue)
{
	if(aInitvalue<0)
		aInitvalue=value;
	FName=aName;
	VLOG(2)<<"Mutex "<<FName<<" is initialized.";
	CHECK_NOTNULL(FImpl);
	LOG_IF(FATAL,FImpl->FSem!= INVALID_HANDLE_VALUE)<<"Cannot init "<<aName<<" name="<<FName;
	FImpl->FSem = ::CreateSemaphore(NULL, aInitvalue, value, aName);
	DCHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	if (FImpl->FSem == INVALID_HANDLE_VALUE)
		return false;

	DWORD const _last_error = GetLastError();
	LOG_IF(DFATAL,_last_error == ERROR_ALREADY_EXISTS && aHasToBeNew==E_HAS_TO_BE_NEW)
																								<< "The mutex  "
																								<< aName
																								<< " is exist.";
	VLOG_IF(2,_last_error != ERROR_ALREADY_EXISTS) << "The New IPC mutex "
															<< aName
															<< " has been created.";
	VLOG_IF(2,_last_error == ERROR_ALREADY_EXISTS) << "The IPC mutex " << aName
															<< " is exist.";
	bool _is_new = _last_error != ERROR_ALREADY_EXISTS;
	switch (aHasToBeNew)
	{
		case E_HAS_TO_BE_NEW:
		{
			if (!_is_new)
			{
				MFree();
				return false;
			}

			break;
		}
		case E_HAS_EXIST:
		{
			if (_is_new)
			{
				LOG(ERROR)<<"The mutex is not to be a new, but it's not true.";
				MFree();
				return false;
			}
			break;
		}
		case E_UNDEF:
		{
			if (_is_new)
				aHasToBeNew = E_HAS_TO_BE_NEW;
			else
				aHasToBeNew = E_HAS_EXIST;
			break;
		}
	}
	FType = aHasToBeNew;
	FImpl->FIs = FImpl->FSem!= INVALID_HANDLE_VALUE;
	return true;
}
CIPCSem::~CIPCSem()
{
	if (FImpl)
	{
		MFree();
		delete FImpl;
	}
}
bool CIPCSem::MWait(void)
{
	VLOG(2)<<"Wait for mutex(lock) "<<FName;
	CHECK_NOTNULL(FImpl);
	HANDLE const _handle = FImpl->FSem;
	LOG_IF(FATAL,FImpl->FSem== INVALID_HANDLE_VALUE)<<"Cannot wait of "<<FName;
	bool _is = WaitForSingleObject(_handle, INFINITE) == WAIT_OBJECT_0;
	VLOG(2)<<"Sem "<<FName<<" hold.";
	LOG_IF(ERROR,!_is) << "Look error " << GetLastError();
	return _is;
}
bool CIPCSem::MWait(double const aTime)
{
	VLOG(2) << "Wait for mutex(lock) " << FName << " Time = " << aTime;
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	unsigned msec = static_cast<unsigned>(aTime*1000);


	bool _is = WaitForSingleObject(FImpl->FSem, msec) == WAIT_OBJECT_0;
	VLOG(2)<<"Sem "<<FName<<" hold.";
	LOG_IF(ERROR,!_is) << "Look error " << GetLastError();
	return _is;
}
bool CIPCSem::MTryWait(void)
{
	VLOG(2)<<"Try Wait for mutex "<<FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	return ::WaitForSingleObject(FImpl->FSem, 0) == WAIT_OBJECT_0;
}
bool CIPCSem::MPost(void)
{
	VLOG(2)<<"Post mutex(unlock) "<<FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	bool _is = ::ReleaseSemaphore(FImpl->FSem, 1, 0) != 0;
	VLOG(2)<<"Sem "<<FName<<" released";
	LOG_IF(FATAL,!_is) << "Look error " << GetLastError();
	return _is;
}
int CIPCSem::MValue() const
{
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	LONG v = -1;
	bool _is = ::ReleaseSemaphore(FImpl->FSem, 0, &v) && v > 0;
	LOG_IF(ERROR,!_is) << "Look error " << GetLastError();
	(void) _is;
	return v;
}
void CIPCSem::MUnlink(){
	;
}
bool CIPCSem::MIsInited() const
{
	return FImpl->FSem != INVALID_HANDLE_VALUE;
}
void CIPCSem::MFree()
{
	if (MIsInited())
	{
		VLOG(2)<<"free mutex "<<FName;
		::CloseHandle(FImpl->FSem);
		FImpl->FSem = INVALID_HANDLE_VALUE;
		FType = E_UNDEF;
	}
}
} /* namespace NSHARE */
#endif
