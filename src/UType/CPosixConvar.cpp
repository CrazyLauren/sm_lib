/*
 * CPosixConvar.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 27.09.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#if   defined(__QNX__)||defined(unix)
#include <deftype>
#include <pthread.h>                        // POSIX threads support
#include <errno.h>
#include <string.h>
namespace NSHARE
{
extern void add(struct timespec* aTo, double const& aFrom); //s

struct CCondvar::CImpl
{

	mutable pthread_cond_t FCondition;
	pthread_mutexattr_t FAttr;

	static void MConditionCleanup(void *arg)
	{
		pthread_mutex_t *mutex = static_cast<pthread_mutex_t *>(arg);
		pthread_mutex_unlock(mutex);
	}
};
 CCondvar::CCondvar()
{
	FPImpl = new CImpl;
	int _rval=pthread_cond_init(&FPImpl->FCondition, NULL);
	MASSERT(_rval, 0);
}
 CCondvar::~CCondvar()
{
int _rval=pthread_cond_destroy(&FPImpl->FCondition);
	MASSERT(_rval, 0);
	delete FPImpl;
}
bool CCondvar::MTimedwait(CMutex *aMutex, const struct timespec* aTime)
{
	if (!aTime)
		return MTimedwait(aMutex, -1);
	return MTimedwait(aMutex,
			aTime->tv_sec
					+ static_cast<double>(aTime->tv_nsec) / 1000.0 / 1000.0
							/ 1000.0);
}
/* bool CCondvar::MTimedwait(CMutex *aMutex, double const aTime)
{
	struct timespec _time =
	{ 0, 0 };
	add(&_time, aTime);
	return MTimedwait(aMutex, &_time);
}*/
bool CCondvar::MTimedwait(CMutex *aMutex, double const aTime)
{
	VLOG_IF(2,aTime>=0.0)
			<< "Condvar is Waited for  Mutex " << aTime << " sec.";
	VLOG_IF(2,aTime<0)
			<< "Condvar is Waited for  Mutex an infinitely long time";
//	aMutex->FIsForCondvar = true;
#ifdef __QNX__
	if (aMutex->MGetMutexType() != CMutex::MUTEX_NORMAL)
	{
		std::cerr << "The Condvar is not  working with recursive mutex."
				<< std::endl;
		LOG(FATAL)<<"The Condvar is not  working with recursive mutex.";
		return false;
	}
#endif
	int _status=-1;
	pthread_cleanup_push(CImpl::MConditionCleanup, aMutex->MGetPtr())
		;
		if (aTime > 0.0)
		{
			struct timespec tm;
			if (clock_gettime(CLOCK_REALTIME, &tm) < 0)
			{
				LOG(DFATAL)<<"Clock reatime error "<<errno;
				return false;
			}
			VLOG(2)<<"Wait for from "<<tm.tv_sec<<"."<<tm.tv_nsec;
			add(&tm, aTime);
			VLOG(2)<<"Wait for to "<<tm.tv_sec<<"."<<tm.tv_nsec;
			_status = pthread_cond_timedwait(&FPImpl->FCondition,
					static_cast<pthread_mutex_t*>(aMutex->MGetPtr()), &tm);
		}
		else
			_status = pthread_cond_wait(&FPImpl->FCondition,
					static_cast<pthread_mutex_t*>(aMutex->MGetPtr()));
		VLOG_IF(1,_status<0) << "Condvar error " << strerror(errno)<<"("<<errno<<")";
		pthread_cleanup_pop(0);
	return !_status;
}
 bool CCondvar::MSignal()
{
	return !pthread_cond_signal(&FPImpl->FCondition);
}
 bool CCondvar::MBroadcast()
{
	return !pthread_cond_broadcast(&FPImpl->FCondition);
}
}
#endif
