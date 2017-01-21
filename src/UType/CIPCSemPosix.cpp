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
namespace NSHARE
{
struct CIPCSem::CImpl
{
	CImpl() :
			FSem(SEM_FAILED ), FIs(false)
	{
	}
	mutable sem_t* FSem;
	bool FIs;
};
int const CIPCSem::MAX_VALUE=SEM_VALUE_MAX;
CIPCSem::CIPCSem(char const* aName, unsigned int value,
		eOpenType const aHasToBeNew, int aInitvalue) :
		FImpl(new CImpl),//
		FType(E_UNDEF)
{
	MInit(aName, value, aHasToBeNew, aInitvalue);
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
	if (aInitvalue < 0)
		aInitvalue = value;
	FName = aName;
	VLOG(2) << "Mutex " << FName << " is initialized.";
	CHECK_NOTNULL(FImpl);
	CHECK_NOTNULL(aName);
	CHECK_EQ(FImpl->FSem, SEM_FAILED);

	if (FName[0] != '/')
		FName.insert(FName.begin(), '/');
	else if (FName[0] != '\\')
		FName[0] = '/';
	
	CHECK_LE(value, SEM_VALUE_MAX);

	switch (aHasToBeNew)
	{
	case E_HAS_TO_BE_NEW:
	{
		int const oflags = O_CREAT | O_EXCL;
		FImpl->FSem = sem_open(FName.c_str(), oflags, 0666, aInitvalue);
		if (FImpl->FSem == SEM_FAILED)
		{
			LOG(ERROR) << FName << " has not created as error " << strerror(errno) << "(" << errno << ")";
			if (errno == EEXIST)
			{
				VLOG(2) << "The IPC mutex " << aName << " is exist.";
			}
			return false;
		}
		break;
	}
	case E_HAS_EXIST:
	{	
		int const 	oflags = 0;
		FImpl->FSem = sem_open(FName.c_str(), oflags);//exist
		if (FImpl->FSem == SEM_FAILED)
		{
			LOG(ERROR) << FName << " has not created as error " << strerror(errno) << "(" << errno << ")";
			CHECK_NE(errno, EEXIST);
			return false;
		}
		break;
	}

	case E_UNDEF:
	{
		aHasToBeNew = E_HAS_TO_BE_NEW;
		int oflags = O_CREAT | O_EXCL;
		FImpl->FSem = sem_open(FName.c_str(), oflags, 0666, aInitvalue);
		if (FImpl->FSem == SEM_FAILED && errno == EEXIST)
		{
			VLOG(2) << "It's exist";
			aHasToBeNew = E_HAS_EXIST;
			oflags = O_CREAT;
			FImpl->FSem = sem_open(FName.c_str(), oflags, 0666, aInitvalue);
		}
		if (FImpl->FSem == SEM_FAILED)
		{
			LOG(ERROR) << FName << " has not created as error " << strerror(errno) << "(" << errno << ")";
			return false;
		}
		break;
	}
	}

	//	for (; value != static_cast<unsigned>(aInitvalue); --value)
//	{
//		VLOG(2) << "Start sem post " << value;
//		sem_wait(FImpl->FSem);
//	}
	FType = aHasToBeNew;
	FImpl->FIs = true;
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
	VLOG(2) << "Wait for mutex(lock) " << FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	bool _is = sem_wait(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MWait(double const aTime)
{
	VLOG(2) << "Wait for mutex(lock) " << FName<<" Time = "<<aTime;
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
	VLOG(2) << "Sem " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MTryWait(void)
{
	VLOG(2) << "Try Wait for mutex " << FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	bool _is = sem_trywait(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
bool CIPCSem::MPost(void)
{
	VLOG(2) << "Post mutex(unlock) " << FName;
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	bool _is = sem_post(FImpl->FSem) == 0;
	VLOG(2) << "Sem " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is;
}
int CIPCSem::MValue() const
{
	CHECK_NOTNULL(FImpl);
	CHECK_NE(FImpl->FSem, SEM_FAILED);
	int __value = -1;
	bool _is = sem_getvalue(FImpl->FSem,&__value) == 0;
	VLOG(2) << "Sem " << FName << " hold.";
	LOG_IF(ERROR,!_is) << "Look error " << strerror(errno)<<"("<<errno<<")";
	return _is?__value:-1;
}
void CIPCSem::MUnlink()
{
	if(!FName.empty())
		sem_unlink(FName.c_str());
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
	VLOG(2) << "Sem " << FName << " freed.";
	LOG_IF(ERROR,!_is) << "Free error " << strerror(errno)<<"("<<errno<<")";
	(void)_is;
	FImpl->FSem= SEM_FAILED;
	FType = E_UNDEF;
}
} /* namespace NSHARE */

#endif
