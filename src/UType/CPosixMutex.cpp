/*
 * CPosixMutex.cpp
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
namespace NSHARE
{
bool CMutexEmpty::MLock(void)
{
	if (FNumber)
		MASSERT(FNumber, thread_id());

	FNumber = thread_id();
	return true;
}
bool CMutexEmpty::MUnlock(void)
{
	MASSERT(FNumber, thread_id());
	FNumber = 0;
	return true;
}
struct CMutex::CImpl
{

	mutable pthread_mutex_t FPMutex;
	pthread_mutexattr_t FAttr;
	unsigned FCounter;
	volatile unsigned FId;
};

 CMutex::CMutex(eMutexType aVal) :
		FFlags(aVal)
{
	FImpl=new CImpl;
	FImpl->FId=0;
	FImpl->FCounter=0;
	pthread_mutexattr_init(&FImpl->FAttr);

#ifdef __QNX__
	if (FFlags == MUTEX_RECURSIVE)
		pthread_mutexattr_settype(&FImpl->FAttr, PTHREAD_MUTEX_RECURSIVE);
#else
	if (FFlags == MUTEX_RECURSIVE)
		pthread_mutexattr_settype(&FImpl->FAttr, PTHREAD_MUTEX_RECURSIVE);
	else
		pthread_mutexattr_settype(&FImpl->FAttr, PTHREAD_MUTEX_ERRORCHECK);
#endif
	pthread_mutex_init(&FImpl->FPMutex, &FImpl->FAttr);
}
 CMutex::~CMutex()
{
	pthread_mutex_destroy(&FImpl->FPMutex);
	pthread_mutexattr_destroy(&FImpl->FAttr);
	CHECK_EQ(FImpl->FId ,0u);
	delete FImpl;
}
 unsigned CMutex::MThread() const
 {
 	return FImpl->FId;
 }
 bool CMutex::MLock()
{
	bool _rval = !pthread_mutex_lock(&FImpl->FPMutex);
	++FImpl->FCounter;
	FImpl->FId = CThread::sMThreadId();
	return _rval;
}
 bool CMutex::MUnlock()
{
	if(--FImpl->FCounter==0)
		FImpl->FId = 0;
	return !pthread_mutex_unlock(&FImpl->FPMutex);
}
 bool CMutex::MCanLock()
{
	bool _is= !pthread_mutex_trylock(&FImpl->FPMutex);
	if(_is)
	{
		++FImpl->FCounter;
		FImpl->FId = CThread::sMThreadId();
	}
	return _is;
}
 void* CMutex::MGetPtr() const
{
	return &FImpl->FPMutex;
}
}
#endif
