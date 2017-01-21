/*
 * CWin32Condvar.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 27.09.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#if defined(_WIN32)
#include <deftype>
#include <windows.h>

#define InterlockedGet(x) InterlockedExchangeAdd(x,0)
namespace NSHARE
{
struct CCondvar::CImpl
{

	int FWaitNum; //waiters
	int FReleaseCount; //number of release thread
	int FWaitGenNum; // current "generation" - it don't allow
	//one thread to steal all the "releases" from the brodcast
	HANDLE FSignalEvent;
	CMutex FMutex;

	CImpl()
	{
		FWaitNum = 0;
		FReleaseCount = 0;
		FWaitGenNum = 0;
		FSignalEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		LOG_IF(FATAL,!FSignalEvent) << "CreateEvent failed. signalEvent:"
											<< FSignalEvent << " error:"
											<< GetLastError();
	}
	~CImpl()
	{
		::CloseHandle(FSignalEvent);
	}
	bool MWait(CMutex* _mutex, unsigned msec = INFINITE);
	bool MBroadcast(void);
	bool MSignal(void);
};

bool CCondvar::CImpl::MWait(CMutex* _mutex, unsigned msec)
{
	int _generation;
	{
		CRAII<CMutex> _block(FMutex);
		++FWaitNum;
		_generation = FWaitGenNum;
	}
	_mutex->MUnlock();
	DWORD ret;
	for (HANG_INIT;;HANG_CHECK)
	{
		ret = ::WaitForSingleObject(FSignalEvent, msec);
		VLOG(2) << "Ret = " << ret;

		CRAII<CMutex> _block(FMutex);
		{
			bool _wait_done=FReleaseCount>0 &&FWaitGenNum!=_generation;
			LOG_IF(DFATAL,((ret != WAIT_TIMEOUT) && (ret!= NO_ERROR)))<<" Error in WaitForSingleObject "<<ret;
			if(_wait_done ||ret == WAIT_TIMEOUT)
			{
				VLOG(2)<<"The condvar is unlocked. Number of Release "<<FReleaseCount//
						<<"; current 'generation' "<<FWaitGenNum//
						<<"; Gen="<<_generation;
				--FWaitNum;
				--FReleaseCount;
				if(FReleaseCount == 0)
					ResetEvent(FSignalEvent);
				break;
			}
			else
			{
				VLOG(1)<<"Does not for me. Number of Release "<<FReleaseCount	//
				<<"; current 'generation' "<<FWaitGenNum//
				<<"; Gen="<<_generation<<"; ret="<<ret<<"; msec="<<msec;
			}
		}
	}
	_mutex->MLock();
/*	bool _last;
	{
		CRAII<CMutex> _block(FMutex);
		--FWaitNum;
		--FReleaseCount;
		_last = FReleaseCount == 0;
	}
	if (_last)
		ResetEvent(FSignalEvent);*/
	return ret != WAIT_TIMEOUT;
}
bool CCondvar::CImpl::MSignal()
{
	CRAII<CMutex> _block(FMutex);
	if (FWaitNum > FReleaseCount)
	{
		VLOG(1) << "Do signal...";
		SetEvent(FSignalEvent);
		++FReleaseCount;
		++FWaitGenNum;
		return true;
	}
	VLOG(1) << "There is not expecting thread.";
	return false;
}
bool CCondvar::CImpl::MBroadcast(void)
{
	CRAII<CMutex> _block(FMutex);
	if (FWaitNum > 0)
	{
		VLOG(1) << "Do broadcast...";
		SetEvent(FSignalEvent);
		FReleaseCount = FWaitNum;
		++FWaitGenNum;
		return true;
	}
	VLOG(1) << "There is not expecting thread.";
	return false;
}
CCondvar::CCondvar()
{
	FPImpl = new CImpl();
}

CCondvar::~CCondvar()
{
	delete FPImpl;
}
bool CCondvar::MTimedwait(CMutex * aMutex, const struct timespec* aVal)
{
	if (!aVal)
		return FPImpl->MWait(aMutex);
	else
	{
		unsigned int _time =(unsigned int)( aVal->tv_sec * 1000 + aVal->tv_nsec / 1000 / 1000);
		return FPImpl->MWait(aMutex, _time);
	}
}
bool CCondvar::MTimedwait(CMutex *aMutex, double const aTime)
{
	LOG_IF(FATAL,aTime<0) << "Time is negative.";
	unsigned int const _time=(aTime<=0?INFINITE:(unsigned int)(aTime * 1000));
	return FPImpl->MWait(aMutex, _time);
}

bool CCondvar::MSignal()
{
	CHECK_NOTNULL(FPImpl);
	return FPImpl->MSignal();
}

bool CCondvar::MBroadcast()
{
	CHECK_NOTNULL(FPImpl);
	return FPImpl->MBroadcast();
}

}

#endif
