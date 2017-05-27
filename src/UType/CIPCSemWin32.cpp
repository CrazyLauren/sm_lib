// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CIPCSemWin32.cpp
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

namespace NSHARE
{
extern size_t get_unique_name(char const* aPreifix,uint8_t* aTo,size_t aSize);
size_t CIPCSem::sMRequredBufSize()
{
	return CIPCSem::eReguredBufSize;
}
struct CIPCSem::CImpl
{
	CImpl() :
			FSem(INVALID_HANDLE_VALUE), FIs(false)
	{

	}
	mutable HANDLE FSem;
	bool FIs;
	NSHARE::CText FName;
};
int const CIPCSem::MAX_VALUE=std::numeric_limits<long>::max()/2;
CIPCSem::CIPCSem(uint8_t* aBuf, size_t aSize, unsigned int value,
		eOpenType const aHasToBeNew, int aInitvalue) :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	bool const _is=MInit(aBuf, aSize,value, aHasToBeNew,aInitvalue);
	(void)_is;
	CHECK(_is);
}
CIPCSem::CIPCSem() :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	;
}
bool CIPCSem::MInit(uint8_t* aBuf, size_t aSize, unsigned int value,
		eOpenType  aHasToBeNew, int aInitvalue)
{
	if (MIsInited())
	{
		LOG(ERROR)<<"Cannot init ipc sem";
		return false;
	}
	CHECK_NOTNULL(aBuf);
	if(aInitvalue<0)
		aInitvalue=value;

	VLOG(2)<<"Mutex  is initialized.";

	if(aSize<eReguredBufSize)
	{
		LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<< eReguredBufSize;
		return false;
	}
	void *const _p=memchr(aBuf,'\0',aSize);
	bool const _is_empty=_p== NULL || _p==aBuf;

	if(aHasToBeNew==E_UNDEF && _is_empty)
	{
		VLOG(2)<<"The buffer is empty. Create the mutex";
		aHasToBeNew=E_HAS_TO_BE_NEW;
	}

	switch (aHasToBeNew)
	{
		case E_HAS_TO_BE_NEW:
		{
			get_unique_name("cv",aBuf, aSize);		
			break;
		}
		case E_UNDEF:
		{
			VLOG(2)<<"Name of sem "<<aBuf;
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


	VLOG(2)<<"Sem "<< (char*)aBuf;

	FImpl->FSem = ::CreateSemaphore(NULL, aInitvalue, value, (char*)aBuf);

	DCHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);

	if (FImpl->FSem == INVALID_HANDLE_VALUE)
		return false;

	DWORD const _last_error = GetLastError();
	LOG_IF(DFATAL,_last_error == ERROR_ALREADY_EXISTS && aHasToBeNew==E_HAS_TO_BE_NEW)
																								<< "The mutex  "
																								<<  (char*)aBuf
																								<< " is exist.";
	VLOG_IF(2,_last_error != ERROR_ALREADY_EXISTS) << "The New IPC mutex "
															<<  (char*)aBuf
															<< " has been created.";
	VLOG_IF(2,_last_error == ERROR_ALREADY_EXISTS) << "The IPC mutex " <<  (char*)aBuf
															<< " is exist.";
	bool _is_new = _last_error != ERROR_ALREADY_EXISTS;

	switch (aHasToBeNew)
	{
		case E_UNDEF:
		{
			if (_is_new)
				aHasToBeNew = E_HAS_TO_BE_NEW;
			else
				aHasToBeNew = E_HAS_EXIST;

			break;
		}
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
	}
	FType = aHasToBeNew;
	FImpl->FIs = FImpl->FSem!= INVALID_HANDLE_VALUE;
	FImpl->FName=(char*)aBuf;
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
	CHECK_NOTNULL(FImpl);
	VLOG(2)<<"Wait for mutex(lock) "<<FImpl->FName;

	HANDLE const _handle = FImpl->FSem;
	LOG_IF(FATAL,FImpl->FSem== INVALID_HANDLE_VALUE)<<"Cannot wait of "<<FImpl->FName;
	bool _is = WaitForSingleObject(_handle, INFINITE) == WAIT_OBJECT_0;
	VLOG(2)<<"Sem "<<FImpl->FName<<" hold.";
	LOG_IF(ERROR,!_is) << "Look error " << GetLastError();
	return _is;
}
bool CIPCSem::MWait(double const aTime)
{
	CHECK_NOTNULL(FImpl);
	VLOG(2) << "Wait for mutex(lock) " << FImpl->FName << " Time = " << aTime;

	CHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	unsigned msec = static_cast<unsigned>(aTime*1000);


	bool _is = WaitForSingleObject(FImpl->FSem, msec) == WAIT_OBJECT_0;
	VLOG(2)<<"Sem "<<FImpl->FName<<" hold.";
	LOG_IF(ERROR,!_is) << "Look error " << GetLastError();
	return _is;
}
bool CIPCSem::MTryWait(void)
{
	CHECK_NOTNULL(FImpl);
	VLOG(2)<<"Try Wait for mutex "<<FImpl->FName;
	
	CHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	return ::WaitForSingleObject(FImpl->FSem, 0) == WAIT_OBJECT_0;
}
bool CIPCSem::MPost(void)
{
	CHECK_NOTNULL(FImpl);
	VLOG(2)<<"Post mutex(unlock) "<<FImpl->FName;

	CHECK_NE(FImpl->FSem, INVALID_HANDLE_VALUE);
	bool _is = ::ReleaseSemaphore(FImpl->FSem, 1, 0) != 0;
	VLOG(2)<<"Sem "<<FImpl->FName<<" released";
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
		VLOG(2)<<"free mutex "<<FImpl->FName;
		::CloseHandle(FImpl->FSem);
		FImpl->FSem = INVALID_HANDLE_VALUE;
		FType = E_UNDEF;
	}
}
NSHARE::CText const& CIPCSem::MName() const
{
	CHECK_NOTNULL(FImpl);
	return FImpl->FName;
}
} /* namespace NSHARE */
#endif
