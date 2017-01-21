/*
 * CIPCSignalEventPosix.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 24.06.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#if   defined(__QNX__)||defined(unix)
#include <deftype>
#include <UType/CIPCSignalEvent.h>
#include <semaphore.h>
#include <fcntl.h>
namespace NSHARE
{
extern void add(struct timespec* aTo, double const& aFrom); //s

struct CIPCSignalEvent::CImpl
{
	mutable sem_t* FSignalEvent;

	CImpl() :
			FSignalEvent(SEM_FAILED)
	{

	}
	bool MInit(char const* aName, eOpenType aIsNew)
	{
		int oflags = O_CREAT | O_EXCL;

		switch (aIsNew)
		{
		case E_HAS_TO_BE_NEW:
		{
			break;
		}
		case E_HAS_EXIST:
			oflags = 0;
			break;
		case E_UNDEF:
			oflags = O_CREAT;
			break;
		}

		if(oflags&O_CREAT)
			FSignalEvent= sem_open(aName, oflags, 0666, 0);
		else
			FSignalEvent= sem_open(aName, oflags);

		if (FSignalEvent == SEM_FAILED )
		{
			LOG(ERROR)<<aName<< " has not created as error "<<strerror(errno)<<"("<<errno<<")";
			if(errno==EEXIST)
			{
				CHECK(aIsNew==E_HAS_TO_BE_NEW);
				VLOG(2)<<"The IPC mutex "<< aName << " is exist.";
			}
			return false;
		}
		return true;
	}
	~CImpl()
	{
		if (FSignalEvent != SEM_FAILED)
			sem_close(FSignalEvent);
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
	if (FName[0] != '/')
		FName.insert(FName.begin(), '/');
	else if (FName[0] != '\\')
		FName[0] = '/';
	VLOG(2) << "Event " << FName << " is initialized.";
	return FPImpl->MInit(FName.c_str(), aHasToBeNew);
}
void CIPCSignalEvent::MFree()
{
	CHECK_NOTNULL(FPImpl);
	if(FPImpl->FSignalEvent== SEM_FAILED)
		return;
	CHECK_NE(FPImpl->FSignalEvent, SEM_FAILED);
	bool _is = sem_destroy(FPImpl->FSignalEvent) == 0;
	VLOG(2) << "Event " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;
	FPImpl->FSignalEvent= SEM_FAILED;
}
void CIPCSignalEvent::MUnlink()
{
	if(!FName.empty())
			sem_unlink(FName.c_str());
}
CIPCSignalEvent::~CIPCSignalEvent()
{
	delete FPImpl;
}
//bool CIPCSignalEvent::MTimedwait(CIPCSem * aMutex, const struct timespec* aVal)
//{
//	VLOG(2) << "Event " << FName << " is waited for.";
//	CHECK_NOTNULL(FPImpl);
//	LOG_IF(DFATAL,FPImpl->FSignalEvent==INVALID_HANDLE_VALUE) << "Event "
//																		<< FName
//																		<< " is not init.";
//	if (FPImpl->FSignalEvent == INVALID_HANDLE_VALUE)
//		return false;
//	unsigned msec = INFINITE;
//	if (aVal)
//	{
//		msec = aVal->tv_sec * 1000 + aVal->tv_nsec / 1000 / 1000;
//	}
//	aMutex->MPost();
//	DWORD ret;
//	bool _is_timeout = false;
//	for (HANG_INIT;;HANG_CHECK)
//	{
//		ret = ::WaitForSingleObject(FPImpl->FSignalEvent, msec);
//		_is_timeout=ret == WAIT_TIMEOUT;
//		if(ret == WAIT_OBJECT_0 ||ret == WAIT_TIMEOUT)
//		break;
//	}
//	bool _is = aMutex->MWait();
//	CHECK(_is);
//	(void) _is;
//	VLOG(2) << "Event " << FName << " has been singaled.";
//	return !_is_timeout;
//}
bool CIPCSignalEvent::MTimedwait(CIPCSem * aMutex, const struct timespec* aVal)
{
	if(aVal)
		return MTimedwait(aMutex,aVal->tv_sec+((double)aVal->tv_nsec)/1000.0/1000.0/1000.0);
	VLOG(2) << "Event " << FName<< " is waited for.";

	CHECK_NOTNULL(FPImpl);
	CHECK_NE(FPImpl->FSignalEvent, SEM_FAILED);


	aMutex->MPost();
	bool _is = sem_wait(FPImpl->FSignalEvent) == 0;
	aMutex->MWait();

	VLOG(2) << "Sem " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem *aMutex, double const aTime)
{
	CHECK_GE(aTime,0);
	CHECK_LE(aTime,std::numeric_limits<unsigned>::max());
	VLOG(2) << "Event  TimedWait " << FName<<" Time = "<<aTime;
	struct timespec tm;
	if (clock_gettime(CLOCK_REALTIME, &tm) < 0)
	{
		LOG(DFATAL)<<"Clock reatime error "<<errno;
		return false;
	}
	add(&tm, aTime);
	CHECK_NOTNULL(FPImpl);
	CHECK_NE(FPImpl->FSignalEvent, SEM_FAILED);

	aMutex->MPost();
	bool _is = sem_timedwait(FPImpl->FSignalEvent,&tm) == 0;
	aMutex->MWait();

	VLOG(2) << "Sem " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Event Wait error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}

bool CIPCSignalEvent::MSignal()
{
	CHECK_NOTNULL(FPImpl);
	VLOG(2) << "Event " << FName << " will signaled.";
	bool _is = sem_post(FPImpl->FSignalEvent) == 0;
	VLOG(2) << "Event " << FName << " is singaled.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
NSHARE::CText const& CIPCSignalEvent::MName() const
{
	return FName;
}
bool CIPCSignalEvent::MIsInited() const
{
	return FPImpl->FSignalEvent != SEM_FAILED ;
}
} /* namespace NSHARE */
#endif



