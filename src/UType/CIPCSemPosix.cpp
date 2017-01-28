// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CIPCSemPosix.cpp
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
#include <semaphore.h>
#include <fcntl.h>
#ifdef SEM_USING_FUTEX
#	include <sys/syscall.h>
#	include <linux/futex.h>
#endif

namespace NSHARE
{
#ifdef SM_USING_SEM_INIT
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
COMPILE_ASSERT((sizeof(_sem_t)+__alignof(sem_t))==CIPCSem::eReguredBufSize,InvalidSizeSem_t);
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
size_t CIPCSem::sMRequredBufSize()
{
	return sizeof(_sem_t);
}

struct CIPCSem::CImpl
{
	CImpl() :
			FSem(NULL)
	{
	}
	mutable _sem_t* FSem;
	NSHARE::CText  FName;
};
int const CIPCSem::MAX_VALUE=SEM_VALUE_MAX;
CIPCSem::CIPCSem(uint8_t* aBuf, size_t aSize, unsigned int value,
		eOpenType const aHasToBeNew, int aInitvalue) :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	bool const _is=MInit(aBuf,aSize, value, aHasToBeNew, aInitvalue);
	if(!_is)
		MASSERT_1(false);
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
	CHECK_NOTNULL(FImpl);
	if (MIsInited())
	{
		LOG(ERROR)<<"Cannot init ipc sem";
		return false;
	}

	if (aInitvalue < 0)
		aInitvalue = value;

	VLOG(2) << "Mutex  is initialized.";

	if(aSize<sMRequredBufSize())
	{
		LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<<sMRequredBufSize();
		return false;
	}

	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(aBuf);
	CHECK_EQ(FImpl->FSem, NULL);
	FImpl->FSem=(_sem_t*)(((uintptr_t)aBuf+__alignof(sem_t))& ~(__alignof(sem_t)-1));
	CHECK_LE((void*)(FImpl->FSem+1),(void*)(aBuf+aSize));

	CHECK_LE(value, SEM_VALUE_MAX);

	switch (aHasToBeNew)
	{
	case E_HAS_TO_BE_NEW:
	{

		if (FImpl->FSem->MIsValid() || sem_init(&FImpl->FSem->FSem, 1, aInitvalue)!=0)
		{
			if(FImpl->FSem->MIsValid())
				errno=EEXIST;
			FImpl->FSem = NULL;
			LOG(ERROR) << "Semaphore has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}else
			FImpl->FSem->MCreatedNew();
		break;
	}
	case E_HAS_EXIST:
	{
		int _val = 0;
		//FImpl->FSem = ;//exist
		if (!FImpl->FSem->MIsValid() ||sem_getvalue(&FImpl->FSem->FSem, &_val)!=0)
		{
			if(!FImpl->FSem->MIsValid())
				errno=ENOENT;
			FImpl->FSem = NULL;
			LOG(ERROR) << " Semaphore has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}
		break;
	}

	case E_UNDEF:
	{
		aHasToBeNew = E_HAS_EXIST;
		int _val = 0;
		if (!FImpl->FSem->MIsValid() || sem_getvalue(&FImpl->FSem->FSem, &_val)!=0)
		{
			aHasToBeNew = E_HAS_TO_BE_NEW;

			if (sem_init(&FImpl->FSem->FSem, 1, aInitvalue)!=0)
			{
				FImpl->FSem = NULL;
				LOG(ERROR) << "Semaphore has not created as error " << strerror(errno) << "(" << errno << ")";
				return false;
			}else
				FImpl->FSem->MCreatedNew();
		}
		break;
	}
	}

	//	for (; value != static_cast<unsigned>(aInitvalue); --value)
//	{
//		VLOG(2) << "Start sem post " << value;
//		sem_wait(FImpl->FSem);
//	}

	FImpl->FSem->MInc();
	FType = aHasToBeNew;
	char _str[16];
	sprintf(_str,"%u",FImpl->FSem->FId);
	FImpl->FName=_str;
	return true;
}
CIPCSem::~CIPCSem()
{
	MFree();
	delete FImpl;
}
bool CIPCSem::MWait(void)
{
	VLOG(2) << "Wait for mutex(lock) " << FImpl->FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
	int _rval=0;
	//HANG_INIT;
	//do
	{
		_rval=sem_wait(&FImpl->FSem->FSem);
	}//while(_rval!=0/*&& errno==EINVAL*/ && !FImpl->FSem->FIsUnlinked /*&& HANG_CHECK*/);

	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(DFATAL,_rval!=0) << "Look error "<<FImpl->FName<<" " << strerror(errno)<<"("<<errno<<")";
	return _rval==0;
}
bool CIPCSem::MWait(double const aTime)
{
	VLOG(2) << "Wait for mutex(lock) " << FImpl->FName<<" Time = "<<aTime;
	struct timespec tm;
	if (clock_gettime(CLOCK_REALTIME, &tm) < 0)
	{
		LOG(DFATAL)<<"Clock reatime error "<<errno;
		return false;
	}
	uint64_t _time=tm.tv_nsec+ static_cast<uint64_t>((aTime - (unsigned)aTime) * 1000.0 * 1000.0 * 100.0);

	static const unsigned _nano_time=1000*1000*1000;
	tm.tv_sec += static_cast<unsigned>(aTime)+(_time/_nano_time);
	tm.tv_nsec = (_time - (_time/_nano_time));
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);

	bool _is = sem_timedwait(&FImpl->FSem->FSem,&tm) == 0;
	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MTryWait(void)
{
	VLOG(2) << "Try Wait for mutex " << FImpl->FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
	bool _is = sem_trywait(&FImpl->FSem->FSem) == 0;
	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MPost(void)
{
	VLOG(2) << "Post mutex(unlock) " << FImpl->FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
	int _rval=0;
	//HANG_INIT;
	//do
	{
		_rval=sem_post(&FImpl->FSem->FSem);
	}//while(_rval!=0 /*&& errno==EINVAL*/&& !FImpl->FSem->FIsUnlinked /*&& HANG_CHECK*/);
	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(DFATAL,_rval!=0) << "Look error "<<FImpl->FName<<" " << strerror(errno)<<"("<<errno<<")";
	return _rval==0;
}
int CIPCSem::MValue() const
{
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
	int __value = -1;
	bool _is = sem_getvalue(&FImpl->FSem->FSem,&__value) == 0;
	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is?__value:-1;
}
void CIPCSem::MUnlink()
{
//	if(!FName.empty())
//		sem_unlink(FName.c_str());
	CHECK_NOTNULL(FImpl);
	if(!MIsInited())
			return;
	bool const _is = sem_destroy(&FImpl->FSem->FSem) == 0;
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	if(_is)
		FImpl->FSem->FIsUnlinked= true;
}
bool CIPCSem::MIsInited() const
{
	return FImpl->FSem != NULL;
}
void CIPCSem::MFree()
{
	CHECK_NOTNULL(FImpl);
	if(!MIsInited())
		return;
/*	bool _is = sem_close(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << FImpl->FName << " freed.";
	LOG_IF(ERROR,!_is) << "Free error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;*/
	if(FImpl->FSem->MDec())
	{
		MUnlink();
	}
	{
		FImpl->FSem = NULL;
		FType = E_UNDEF;
		FImpl->FName.clear();
	}
}
NSHARE::CText const& CIPCSem::MName() const
{
	CHECK_NOTNULL(FImpl);
	return FImpl->FName;
}
#elif defined(SEM_USING_FUTEX)
SHARED_PACKED(struct _sem_t
{
	inline _sem_t();
	volatile int32_t FFutex;
	uint16_t FCount;
	uint16_t FIsUnlinked:1;
	uint16_t :15;
	uint32_t FId;

	inline bool MIsValid() const;
	inline void MInc();
	inline bool MDec();
	inline void MCreatedNew(int aVal);
});
COMPILE_ASSERT((sizeof(_sem_t)+__alignof(int32_t))==CIPCSem::eReguredBufSize,InvalidSizeSem_t);
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
size_t CIPCSem::sMRequredBufSize()
{
	return sizeof(_sem_t);
}

struct CIPCSem::CImpl
{
	CImpl() :
			FSem(NULL)
	{
	}
	mutable _sem_t* FSem;
	NSHARE::CText  FName;
};
int const CIPCSem::MAX_VALUE=SEM_VALUE_MAX;
CIPCSem::CIPCSem(uint8_t* aBuf, size_t aSize, unsigned int value,
		eOpenType const aHasToBeNew, int aInitvalue) :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	bool const _is=MInit(aBuf,aSize, value, aHasToBeNew, aInitvalue);
	if(!_is)
		MASSERT_1(false);
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
	CHECK_NOTNULL(FImpl);
	if (MIsInited())
	{
		LOG(ERROR)<<"Cannot init ipc sem";
		return false;
	}
	
	if (aInitvalue < 0)
		aInitvalue = value;
	
	VLOG(2) << "Mutex  is initialized.";
	
	if(aSize<sMRequredBufSize())
	{
		LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<<sMRequredBufSize();
		return false;
	}
	
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(aBuf);
	CHECK_EQ(FImpl->FSem, NULL);
	FImpl->FSem=(_sem_t*)(((uintptr_t)aBuf+4)& ~(4-1));
	CHECK_EQ((uintptr_t)FImpl->FSem%4,0);

	CHECK_LE((void*)(FImpl->FSem+1),(void*)(aBuf+aSize));

	CHECK_LE(value, SEM_VALUE_MAX);

	switch (aHasToBeNew)
	{
	case E_HAS_TO_BE_NEW:
	{
		
		if (FImpl->FSem->MIsValid())
		{
			errno=EEXIST;
			FImpl->FSem = NULL;
			LOG(ERROR) << "Semaphore has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}else
			FImpl->FSem->MCreatedNew(aInitvalue);
		break;
	}
	case E_HAS_EXIST:
	{	
		//FImpl->FSem = ;//exist
		if (!FImpl->FSem->MIsValid())
		{
			errno=ENOENT;
			FImpl->FSem = NULL;
			LOG(ERROR) << " Semaphore has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}
		break;
	}

	case E_UNDEF:
	{
		aHasToBeNew = E_HAS_EXIST;
		if (!FImpl->FSem->MIsValid())
		{
			aHasToBeNew = E_HAS_TO_BE_NEW;
			FImpl->FSem->MCreatedNew(aInitvalue);
		}
		break;
	}
	}

	//	for (; value != static_cast<unsigned>(aInitvalue); --value)
//	{
//		VLOG(2) << "Start sem post " << value;
//		sem_wait(FImpl->FSem);
//	}
	
	FImpl->FSem->MInc();
	FType = aHasToBeNew;
	char _str[16];
	sprintf(_str,"%u",FImpl->FSem->FId);
	FImpl->FName=_str;
	return true;
}
CIPCSem::~CIPCSem()
{
	MFree();
	delete FImpl;
}
bool CIPCSem::MWait(void)
{
	VLOG(2) << "Wait for mutex(lock) " << FImpl->FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
    int _rval=-1;
    bool  _is =false;
    do {

          /* Is the futex available? */

          if ((_is=__sync_bool_compare_and_swap(&FImpl->FSem->FFutex, 1, 0)))
              break;      /* Yes */

          /* Futex is not available; wait */

          _rval = syscall(SYS_futex,&FImpl->FSem->FFutex, FUTEX_WAIT, 0, NULL, NULL, 0);

     }while(!_is && (_rval != -1 || errno == EAGAIN));

	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(DFATAL,!_is) << "Look error "<<FImpl->FName<<" " << strerror(errno)<<"("<<errno<<") rval="<<_rval;
	return _is;
}
bool CIPCSem::MWait(double const aTime)
{
	VLOG(2) << "Wait for mutex(lock) " << FImpl->FName<<" Time = "<<aTime;
	struct timespec tm;
	if (clock_gettime(CLOCK_REALTIME, &tm) < 0)
	{
		LOG(DFATAL)<<"Clock reatime error "<<errno;
		return false;
	}
	uint64_t _time=tm.tv_nsec+ static_cast<uint64_t>((aTime - (unsigned)aTime) * 1000.0 * 1000.0 * 100.0);

	static const unsigned _nano_time=1000*1000*1000;
	tm.tv_sec += static_cast<unsigned>(aTime)+(_time/_nano_time);
	tm.tv_nsec = (_time - (_time/_nano_time));
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);

	int _rval;
	bool  _is =false;
    do {

          /* Is the futex available? */

          if ((_is=__sync_bool_compare_and_swap(&FImpl->FSem->FFutex, 1, 0)))
              break;      /* Yes */

          /* Futex is not available; wait */

          _rval = syscall(SYS_futex,&FImpl->FSem->FFutex, FUTEX_WAIT, 0, &tm, NULL, 0);

    }while(!_is && (_rval != -1 || errno == EAGAIN));

	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MTryWait(void)
{
	VLOG(2) << "Try Wait for mutex " << FImpl->FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
	bool const _is = __sync_bool_compare_and_swap(&FImpl->FSem->FFutex, 1, 0);
	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MPost(void)
{
	VLOG(2) << "Post mutex(unlock) " << FImpl->FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
	int _rval=0;
	if (__sync_bool_compare_and_swap(&FImpl->FSem->FFutex, 0, 1))
	{

		_rval = syscall(SYS_futex, &FImpl->FSem->FFutex, FUTEX_WAKE, 1, NULL, NULL, 0);
	}
	VLOG(2) << "Sem " << FImpl->FName << " hold.";
	LOG_IF(DFATAL,_rval==-1) << "Look error "<<FImpl->FName<<" " << strerror(errno)<<"("<<errno<<")"<<" rval="<<_rval;
	return _rval != -1;
}
int CIPCSem::MValue() const
{
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(FImpl->FSem);
	return FImpl->FSem->FFutex;
}
void CIPCSem::MUnlink()
{
}
bool CIPCSem::MIsInited() const
{
	return FImpl->FSem != NULL;
}
void CIPCSem::MFree()
{
	CHECK_NOTNULL(FImpl);
	if(!MIsInited())
		return;
/*	bool _is = sem_close(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << FImpl->FName << " freed.";
	LOG_IF(ERROR,!_is) << "Free error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;*/
	if(FImpl->FSem->MDec())
	{
		MUnlink();
	}
	{
		FImpl->FSem = NULL;
		FType = E_UNDEF;
		FImpl->FName.clear();
	}
}
NSHARE::CText const& CIPCSem::MName() const
{
	CHECK_NOTNULL(FImpl);
	return FImpl->FName;
}
#else
extern size_t get_unique_name(char const* aPreifix,uint8_t* aTo,size_t aSize);

size_t CIPCSem::sMRequredBufSize()
{
	return CIPCSem::eReguredBufSize;
}
struct CIPCSem::CImpl
{
	CImpl() :
			FSem(SEM_FAILED )
	{
	}
	mutable sem_t* FSem;
	NSHARE::CText FName;
};
static int g_counter=0;
int const CIPCSem::MAX_VALUE=SEM_VALUE_MAX;
CIPCSem::CIPCSem(uint8_t* aBuf, size_t aSize, unsigned int value,
		eOpenType const aHasToBeNew, int aInitvalue) :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	MInit(aBuf,aSize, value, aHasToBeNew, aInitvalue);
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
	if (aInitvalue < 0)
		aInitvalue = value;

	VLOG(2) << "Mutex  is initialized.";
	if(aSize<eReguredBufSize)
	{
		LOG(DFATAL)<<"Invalid size of buf "<<aSize<<" min size "<< eReguredBufSize;
		return false;
	}
	CHECK_NOTNULL(FImpl);
	CHECK_EQ(FImpl->FSem, SEM_FAILED);

	void *const _p=memchr(aBuf,'\0',aSize);
	bool const _is_empty=_p== NULL || _p==aBuf;

	if(aHasToBeNew==E_UNDEF && _is_empty)
	{
		VLOG(2)<<"The buffer is empty. Create the mutex";
		aHasToBeNew=E_HAS_TO_BE_NEW;
	}

	CHECK_LE(value, SEM_VALUE_MAX);

	switch (aHasToBeNew)
	{
	case E_HAS_TO_BE_NEW:
	{

		get_unique_name("/sem",aBuf, aSize);

		int const oflags = O_CREAT | O_EXCL;
		FImpl->FSem = sem_open((char*)aBuf, oflags, 0666, aInitvalue);
		if (FImpl->FSem == SEM_FAILED)
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
		int const 	oflags = 0;
		FImpl->FSem = sem_open((char*)aBuf, oflags);//exist
		if (FImpl->FSem == SEM_FAILED)
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
		FImpl->FSem = sem_open((char*)aBuf, oflags, 0666, aInitvalue);
		if (FImpl->FSem == SEM_FAILED && errno == EEXIST)
		{
			VLOG(2) << "It's exist";
			aHasToBeNew = E_HAS_EXIST;
			oflags = O_CREAT;
			FImpl->FSem = sem_open((char*)aBuf, oflags, 0666, aInitvalue);
		}
		if (FImpl->FSem == SEM_FAILED)
		{
			LOG(ERROR) << aBuf << " has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}
		break;
	}
	}

	FType = aHasToBeNew;
	FImpl->FName=(char*)aBuf;
	return true;
}
CIPCSem::~CIPCSem()
{
	if(FImpl->FSem!= SEM_FAILED)
		MFree();
	delete FImpl;
}
bool CIPCSem::MWait(void)
{
	VLOG(2) << "Wait for mutex(lock) " << MName();
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	bool _is = sem_wait(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MWait(double const aTime)
{
	VLOG(2) << "Wait for mutex(lock) " << MName()<<" Time = "<<aTime;
	struct timespec tm;
	if (clock_gettime(CLOCK_REALTIME, &tm) < 0)
	{
		LOG(DFATAL)<<"Clock reatime error "<<errno;
		return false;
	}
	uint64_t _time=tm.tv_nsec+ static_cast<uint64_t>((aTime - (unsigned)aTime) * 1000.0 * 1000.0 * 100.0);

	static const unsigned _nano_time=1000*1000*1000;
	tm.tv_sec += static_cast<unsigned>(aTime)+(_time/_nano_time);
	tm.tv_nsec = (_time - (_time/_nano_time));
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);

	bool _is = sem_timedwait(FImpl->FSem,&tm) == 0;
	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MTryWait(void)
{
	VLOG(2) << "Try Wait for mutex " << MName();
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	bool _is = sem_trywait(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MPost(void)
{
	VLOG(2) << "Post mutex(unlock) " << MName();
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	bool _is = sem_post(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
int CIPCSem::MValue() const
{
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	int __value = -1;
	bool _is = sem_getvalue(FImpl->FSem,&__value) == 0;
	VLOG(2) << "Sem " << MName() << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is?__value:-1;
}
void CIPCSem::MUnlink()
{
	if(!MName().empty())
		sem_unlink(MName().c_str());
}
bool CIPCSem::MIsInited() const
{
	return FImpl->FSem != SEM_FAILED;
}
void CIPCSem::MFree()
{
	CHECK_NOTNULL(FImpl);
	if(!MIsInited())
		return;
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	bool _is = sem_close(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << MName() << " freed.";
	LOG_IF(ERROR,!_is) << "Free error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;
	FImpl->FSem= SEM_FAILED;
	FImpl->FName.clear();
	FType = E_UNDEF;
}
NSHARE::CText const& CIPCSem::MName() const
{
	CHECK_NOTNULL(FImpl);
	return FImpl->FName;
}
#endif
} /* namespace NSHARE */

#endif
