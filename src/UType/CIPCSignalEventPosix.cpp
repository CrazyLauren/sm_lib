// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CIPCSignalEventPosix.cpp
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 24.06.2016
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#if   defined(__QNX__)||defined(unix)

#include <deftype>
#include <UType/CIPCSignalEvent.h>
#include <semaphore.h>
#include <fcntl.h>
#ifdef SE_USING_FUTEX
#	include <sys/syscall.h>
#	include <linux/futex.h>
#endif
namespace NSHARE
{
extern void add(struct timespec* aTo, double const& aFrom); //s
#ifdef SE_USING_SEM_INIT
SHARED_PACKED(struct _sem_t
{
	inline _sem_t();
	sem_t FSem;
	uint16_t FCount;
	uint16_t FIsUnlinked:1;
	uint16_t :15;
	uint32_t FId;

	inline bool MIsValid() const;
	inline void MInc();
	inline bool MDec();
	inline void MCreatedNew();
});
COMPILE_ASSERT((sizeof(_sem_t)+__alignof(sem_t))==CIPCSignalEvent::eReguredBufSize,InvalidSizeSem2_t);
_sem_t::_sem_t()
{
	memset(this,0,sizeof(*this));
}
bool _sem_t::MIsValid() const
{
	return FCount > 0 && !FIsUnlinked;
}
void _sem_t::MInc()
{
	++FCount;
}
bool _sem_t::MDec()
{
	return --FCount==0;
}
inline void _sem_t::MCreatedNew()
{
	FIsUnlinked=false;
	FCount=0;
	FId=get_uuid().MGetHash();
}
size_t CIPCSignalEvent::sMRequredBufSize()
{
	return sizeof(_sem_t);
}
struct CIPCSignalEvent::CImpl
{
	mutable _sem_t* FSignalEvent;
	eOpenType FType;
	CText FName;

	CImpl() :
			FSignalEvent(NULL),FType(E_UNDEF)
	{

	}
};
CIPCSignalEvent::CIPCSignalEvent() :
		FPImpl(new CImpl)
{

}
CIPCSignalEvent::CIPCSignalEvent(uint8_t* aBuf, size_t aSize, eOpenType aIsNew) :
		FPImpl(new CImpl)
{
	bool const _is=MInit(aBuf,aSize, aIsNew);
	if(!_is)
		MASSERT_1(false);
}
bool CIPCSignalEvent::MInit(uint8_t* aBuf, size_t aSize, eOpenType aHasToBeNew)
{
	CHECK_NOTNULL(FPImpl);
	if (MIsInited())
	{
		LOG(ERROR)<<"Cannot init ipc se";
		return false;
	}

	if(aSize<sMRequredBufSize())
	{
		LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<<sMRequredBufSize();
		return false;
	}

	CHECK_NOTNULL(aBuf);
	CHECK_EQ(FPImpl->FSignalEvent,NULL);
	FPImpl->FSignalEvent=(_sem_t*)(((uintptr_t)aBuf+__alignof(sem_t))& ~(__alignof(sem_t)-1));
	CHECK_LE((void*)(FPImpl->FSignalEvent+1),(void*)(aBuf+aSize));
	switch (aHasToBeNew)
	{
	case E_HAS_TO_BE_NEW:
	{

		if (FPImpl->FSignalEvent->MIsValid() || sem_init(&FPImpl->FSignalEvent->FSem, 1, 0)!=0)
		{
			if(FPImpl->FSignalEvent->MIsValid())
				errno=EEXIST;
			FPImpl->FSignalEvent = NULL;
			LOG(ERROR) <<"Signal event has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}else
			FPImpl->FSignalEvent->MCreatedNew();

		break;
	}
	case E_HAS_EXIST:
	{
		int _val = 0;
		//FImpl->FSem = ;//exist
		if ( !FPImpl->FSignalEvent->MIsValid() || sem_getvalue(&FPImpl->FSignalEvent->FSem, &_val)!=0)
		{
			if(!FPImpl->FSignalEvent->MIsValid())
				errno=ENOENT;
			FPImpl->FSignalEvent = NULL;
			LOG(ERROR)<<"Signal event has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}
		break;
	}

	case E_UNDEF:
	{
		aHasToBeNew = E_HAS_EXIST;
		int _val = 0;
		if (!FPImpl->FSignalEvent->MIsValid() || sem_getvalue(&FPImpl->FSignalEvent->FSem, &_val)!=0)
		{
			aHasToBeNew = E_HAS_TO_BE_NEW;

			if (sem_init(&FPImpl->FSignalEvent->FSem, 1, 0)!=0)
			{
				FPImpl->FSignalEvent = NULL;
				LOG(ERROR) << " Signal event  has not created as error " << strerror(errno) << "(" << errno << ")";
				return false;
			}else
				FPImpl->FSignalEvent->MCreatedNew();
		}
		break;
	}
	}
	FPImpl->FSignalEvent->MInc();
	FPImpl->FType=aHasToBeNew;
	char _str[16];
	sprintf(_str,"%u",FPImpl->FSignalEvent->FId);
	FPImpl->FName=_str;
	return true;
}
void CIPCSignalEvent::MFree()
{
	CHECK_NOTNULL(FPImpl);
	if(!MIsInited())
		return;
/*	bool _is = sem_close(FPImpl->FSignalEvent) == 0;
	VLOG(2) << "Event " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;*/
	if(FPImpl->FSignalEvent->MDec())
	{
		MUnlink();
	}

	{
		FPImpl->FSignalEvent = NULL;
		FPImpl->FType = E_UNDEF;
		FPImpl->FName.clear();
	}
}
void CIPCSignalEvent::MUnlink()
{
	CHECK_NOTNULL(FPImpl);
	if(!MIsInited())
		return;
	CHECK_NOTNULL(FPImpl->FSignalEvent);
	bool const _is = sem_destroy(&FPImpl->FSignalEvent->FSem) == 0;
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	if(_is)
		FPImpl->FSignalEvent->FIsUnlinked=true;
}
CIPCSignalEvent::~CIPCSignalEvent()
{
	MFree();
	delete FPImpl;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem * aMutex, const struct timespec* aVal)
{
	if(aVal)
		return MTimedwait(aMutex,aVal->tv_sec+((double)aVal->tv_nsec)/1000.0/1000.0/1000.0);
	VLOG(2) << "Event " << MName()<< " is waited for.";

	CHECK_NOTNULL(FPImpl);
	CHECK_NOTNULL(FPImpl->FSignalEvent);


	aMutex->MPost();
	bool _is = sem_wait(&FPImpl->FSignalEvent->FSem) == 0;
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	aMutex->MWait();

	VLOG(2) << "Sem " << MName() << " hold.";

	return _is;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem *aMutex, double const aTime)
{
	CHECK_GE(aTime,0);
	CHECK_LE(aTime,std::numeric_limits<unsigned>::max());
	VLOG(2) << "Event  TimedWait " << MName()<<" Time = "<<aTime;
	struct timespec tm;
	if (clock_gettime(CLOCK_REALTIME, &tm) < 0)
	{
		LOG(DFATAL)<<"Clock reatime error "<<errno;
		return false;
	}
	add(&tm, aTime);
	CHECK_NOTNULL(FPImpl);
	CHECK_NOTNULL(FPImpl->FSignalEvent);

	aMutex->MPost();
	bool _is = sem_timedwait(&FPImpl->FSignalEvent->FSem,&tm) == 0;
	aMutex->MWait();

	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Event Wait error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}

bool CIPCSignalEvent::MSignal()
{
	CHECK_NOTNULL(FPImpl);
	VLOG(2) << "Event " << MName() << " will signaled.";
	bool _is = sem_post(&FPImpl->FSignalEvent->FSem) == 0;
	VLOG(2) << "Event " << MName() << " is singaled.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
NSHARE::CText const& CIPCSignalEvent::MName() const
{
	CHECK_NOTNULL(FPImpl);
	return FPImpl->FName;
}
bool CIPCSignalEvent::MIsInited() const
{
	return FPImpl->FSignalEvent != NULL ;
}
#elif defined(SE_USING_FUTEX)
SHARED_PACKED(struct _sem_t
{
	inline _sem_t();
	int32_t FFutex;
	uint16_t FCount;
	uint16_t FIsUnlinked:1;
	uint16_t :15;
	uint32_t FId;

	inline bool MIsValid() const;
	inline void MInc();
	inline bool MDec();
	inline void MCreatedNew(int aVal);
});
COMPILE_ASSERT((sizeof(_sem_t)+__alignof(int32_t))==CIPCSignalEvent::eReguredBufSize,InvalidSizeSem2_t);
_sem_t::_sem_t()
{
	memset(this,0,sizeof(*this));
}
bool _sem_t::MIsValid() const
{
	return FCount > 0 && !FIsUnlinked;
}
void _sem_t::MInc()
{
	++FCount;
}
bool _sem_t::MDec()
{
	return --FCount==0;
}
inline void _sem_t::MCreatedNew(int aVal)
{
	FIsUnlinked=false;
	FCount=0;
	FId=get_uuid().MGetHash();
	FFutex=aVal;
}
size_t CIPCSignalEvent::sMRequredBufSize()
{
	return sizeof(_sem_t);
}
struct CIPCSignalEvent::CImpl
{
	mutable _sem_t* FSignalEvent;
	eOpenType FType;
	CText FName;

	CImpl() :
			FSignalEvent(NULL),FType(E_UNDEF)
	{

	}
};
CIPCSignalEvent::CIPCSignalEvent() :
		FPImpl(new CImpl)
{

}
CIPCSignalEvent::CIPCSignalEvent(uint8_t* aBuf, size_t aSize, eOpenType aIsNew) :
		FPImpl(new CImpl)
{
	bool const _is=MInit(aBuf,aSize, aIsNew);
	if(!_is)
		MASSERT_1(false);
}
bool CIPCSignalEvent::MInit(uint8_t* aBuf, size_t aSize, eOpenType aHasToBeNew)
{
	CHECK_NOTNULL(FPImpl);
	if (MIsInited())
	{
		LOG(ERROR)<<"Cannot init ipc se";
		return false;
	}

	if(aSize<sMRequredBufSize())
	{
		LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<<sMRequredBufSize();
		return false;
	}

	CHECK_NOTNULL(aBuf);
	CHECK_EQ(FPImpl->FSignalEvent,NULL);
	FPImpl->FSignalEvent=(_sem_t*)(((uintptr_t)aBuf+4)& ~(4-1));

	CHECK_EQ((uintptr_t)FPImpl->FSignalEvent%4,0);

	switch (aHasToBeNew)
	{
	case E_HAS_TO_BE_NEW:
	{

		if (FPImpl->FSignalEvent->MIsValid())
		{
			errno=EEXIST;
			LOG(ERROR) <<"Signal event has not created as error " << strerror(errno) << "(" << errno << ")";
			FPImpl->FSignalEvent = NULL;
			return false;
		}
		FPImpl->FSignalEvent->MCreatedNew(0);
		break;
	}
	case E_HAS_EXIST:
	{
		int _val = 0;
		//FImpl->FSem = ;//exist
		if ( !FPImpl->FSignalEvent->MIsValid())
		{
			errno=ENOENT;
			FPImpl->FSignalEvent = NULL;
			LOG(ERROR)<<"Signal event has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}
		break;
	}

	case E_UNDEF:
	{
		aHasToBeNew = E_HAS_EXIST;
		int _val = 0;
		if (!FPImpl->FSignalEvent->MIsValid())
		{
			aHasToBeNew = E_HAS_TO_BE_NEW;
			FPImpl->FSignalEvent->MCreatedNew(0);
		}
		break;
	}
	}
	FPImpl->FSignalEvent->MInc();
	FPImpl->FType=aHasToBeNew;
	char _str[16];
	sprintf(_str,"%u",FPImpl->FSignalEvent->FId);
	FPImpl->FName=_str;
	return true;
}
void CIPCSignalEvent::MFree()
{
	CHECK_NOTNULL(FPImpl);
	if(!MIsInited())
		return;
/*	bool _is = sem_close(FPImpl->FSignalEvent) == 0;
	VLOG(2) << "Event " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;*/
	if(FPImpl->FSignalEvent->MDec())
	{
		MUnlink();
	}

	{
		FPImpl->FSignalEvent = NULL;
		FPImpl->FType = E_UNDEF;
		FPImpl->FName.clear();
	}
}
void CIPCSignalEvent::MUnlink()
{
}
CIPCSignalEvent::~CIPCSignalEvent()
{
	MFree();
	delete FPImpl;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem * aMutex, const struct timespec* aVal)
{
	if(aVal)
		return MTimedwait(aMutex,aVal->tv_sec+((double)aVal->tv_nsec)/1000.0/1000.0/1000.0);
	VLOG(2) << "Event " << MName()<< " is waited for.";

	CHECK_NOTNULL(FPImpl);
	CHECK_NOTNULL(FPImpl->FSignalEvent);

	aMutex->MPost();
    int s=-1;
    bool  _is =false;
    do {

          /* Is the futex available? */

          if ((_is=__sync_bool_compare_and_swap(&FPImpl->FSignalEvent->FFutex, 1, 0)))
              break;      /* Yes */

          /* Futex is not available; wait */

          s = syscall(SYS_futex,&FPImpl->FSignalEvent->FFutex, FUTEX_WAIT, 0, NULL, NULL, 0);

    }while(!_is && (s != -1 || errno == EAGAIN));
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	aMutex->MWait();

	VLOG(2) << "Sem " << MName() << " hold.";

	return _is;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem *aMutex, double const aTime)
{
	CHECK_GE(aTime,0);
	CHECK_LE(aTime,std::numeric_limits<unsigned>::max());
	VLOG(2) << "Event  TimedWait " << MName()<<" Time = "<<aTime;
	struct timespec tm;
	if (clock_gettime(CLOCK_REALTIME, &tm) < 0)
	{
		LOG(DFATAL)<<"Clock reatime error "<<errno;
		return false;
	}
	add(&tm, aTime);
	CHECK_NOTNULL(FPImpl);
	CHECK_NOTNULL(FPImpl->FSignalEvent);

	aMutex->MPost();

    int s=-1;
    bool  _is =false;
    do {

          /* Is the futex available? */

          if ((_is=__sync_bool_compare_and_swap(&FPImpl->FSignalEvent->FFutex, 1, 0)))
              break;      /* Yes */

          /* Futex is not available; wait */

          s = syscall(SYS_futex,&FPImpl->FSignalEvent->FFutex, FUTEX_WAIT, 0, &tm, NULL, 0);

    }while(!_is && (s != -1 || errno == EAGAIN));



	aMutex->MWait();

	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Event Wait error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}

bool CIPCSignalEvent::MSignal()
{
	CHECK_NOTNULL(FPImpl);
	VLOG(2) << "Event " << MName() << " will signaled.";

	int s=0;

	if (__sync_bool_compare_and_swap(&FPImpl->FSignalEvent->FFutex, 0, 1)) {

		s = syscall(SYS_futex, &FPImpl->FSignalEvent->FFutex, FUTEX_WAKE, 1, NULL, NULL, 0);
	}

	bool _is = s != -1;
	VLOG(2) << "Event " << MName() << " is singaled.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
NSHARE::CText const& CIPCSignalEvent::MName() const
{
	CHECK_NOTNULL(FPImpl);
	return FPImpl->FName;
}
bool CIPCSignalEvent::MIsInited() const
{
	return FPImpl->FSignalEvent != NULL ;
}
#else
extern size_t get_unique_name(char const* aPreifix,uint8_t* aTo,size_t aSize);

size_t CIPCSignalEvent::sMRequredBufSize()
{
	return CIPCSem::eReguredBufSize;
}
struct CIPCSignalEvent::CImpl
{
	mutable sem_t* FSignalEvent;
	eOpenType FType;
	NSHARE::CText FName;
	CImpl() :
			FSignalEvent(SEM_FAILED),FType(E_UNDEF)
	{

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
	if (MIsInited())
	{
		LOG(ERROR)<<"Cannot init ipc sem";
		return false;
	}
	if(aSize<eReguredBufSize)
	{
		LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<< eReguredBufSize;
		return false;
	}
	CHECK_NOTNULL(aBuf);
	CHECK_EQ(FPImpl->FSignalEvent, SEM_FAILED);

	VLOG(2) << "Event is initialized.";

	void *const _p=memchr(aBuf,'\0',aSize);
	bool const _is_empty=_p== NULL || _p==aBuf;

	if(aHasToBeNew==E_UNDEF && _is_empty)
	{
		VLOG(2)<<"The buffer is empty. Create the mutex";
		aHasToBeNew=E_HAS_TO_BE_NEW;
	}

	int oflags = O_CREAT | O_EXCL;

	switch (aHasToBeNew)
	{
		case E_HAS_TO_BE_NEW:
		{
			get_unique_name("/ev",aBuf, aSize);


			FPImpl->FSignalEvent = sem_open((char*)aBuf, oflags, 0666, 0);
			if (FPImpl->FSignalEvent == SEM_FAILED)
			{
				LOG(ERROR) << aBuf << " has not created as error " << strerror(errno) << "(" << errno << ")";
				if (errno == EEXIST)
				{
					VLOG(2) << "The IPC mutex  is exist.";
				}
				return false;
			}
			break;
		}
		case E_HAS_EXIST:
		{
			if(_is_empty)
			{
				LOG(ERROR)<<"The buffer is empty.";
				return false;
			}
			oflags = 0;
			FPImpl->FSignalEvent= sem_open((char*)aBuf, oflags);
			if (FPImpl->FSignalEvent == SEM_FAILED)
			{
				LOG(ERROR) << aBuf << " has not created as error " << strerror(errno) << "(" << errno << ")";
				//CHECK_NE(errno, EEXIST);
				return false;
			}
			break;
		}
		case E_UNDEF:
		{
		aHasToBeNew = E_HAS_TO_BE_NEW;
		int oflags = O_CREAT | O_EXCL;
		FPImpl->FSignalEvent = sem_open((char*)aBuf, oflags, 0666, 0);
		if (FPImpl->FSignalEvent == SEM_FAILED && errno == EEXIST)
		{
			VLOG(2) << "It's exist";
			aHasToBeNew = E_HAS_EXIST;
			oflags = O_CREAT;
			FPImpl->FSignalEvent = sem_open((char*)aBuf, oflags, 0666, 0);
		}
		if (FPImpl->FSignalEvent == SEM_FAILED)
		{
			LOG(ERROR) << aBuf << " has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}
		break;
		}
	}
	FPImpl->FType = aHasToBeNew;
	FPImpl->FName=(char*)aBuf;
	return true;
}
void CIPCSignalEvent::MFree()
{
	CHECK_NOTNULL(FPImpl);
	if(FPImpl->FSignalEvent== SEM_FAILED)
		return;
	CHECK_NE(FPImpl->FSignalEvent, SEM_FAILED);
	bool _is = sem_close(FPImpl->FSignalEvent) == 0;
	VLOG(2) << "Event " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;
	FPImpl->FSignalEvent= SEM_FAILED;
	FPImpl->FName.clear();
}
void CIPCSignalEvent::MUnlink()
{
	if(!MName().empty())
		sem_unlink(MName().c_str());
}
CIPCSignalEvent::~CIPCSignalEvent()
{
	if(FPImpl->FSignalEvent!= SEM_FAILED)
		MFree();
	delete FPImpl;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem * aMutex, const struct timespec* aVal)
{
	if(aVal)
		return MTimedwait(aMutex,aVal->tv_sec+((double)aVal->tv_nsec)/1000.0/1000.0/1000.0);
	VLOG(2) << "Event " << MName()<< " is waited for.";

	CHECK_NOTNULL(FPImpl);
	CHECK_NE(FPImpl->FSignalEvent, SEM_FAILED);


	aMutex->MPost();
	bool _is = sem_wait(FPImpl->FSignalEvent) == 0;
	aMutex->MWait();

	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSignalEvent::MTimedwait(CIPCSem *aMutex, double const aTime)
{
	CHECK_GE(aTime,0);
	CHECK_LE(aTime,std::numeric_limits<unsigned>::max());
	VLOG(2) << "Event  TimedWait " << MName()<<" Time = "<<aTime;
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

	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Event Wait error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}

bool CIPCSignalEvent::MSignal()
{
	CHECK_NOTNULL(FPImpl);
	VLOG(2) << "Event " << MName() << " will signaled.";
	bool _is = sem_post(FPImpl->FSignalEvent) == 0;
	VLOG(2) << "Event " << MName() << " is singaled.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
NSHARE::CText const& CIPCSignalEvent::MName() const
{
	return FPImpl->FName;
}
bool CIPCSignalEvent::MIsInited() const
{
	return FPImpl->FSignalEvent != SEM_FAILED ;
}

#endif
} /* namespace NSHARE */
#endif



