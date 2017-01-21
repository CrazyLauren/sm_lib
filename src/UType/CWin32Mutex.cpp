/*
 * CWin32Mutex.cpp
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
#ifndef _Acquires_lock_
#	define _Acquires_lock_( a )
#endif
#ifndef _Releases_lock_
#	define _Releases_lock_( a )
#endif
namespace NSHARE
{
bool CMutexEmpty::MLock(void)
{
	if (FNumber)
		MASSERT(FNumber, CThread::sMThreadId());

	FNumber = CThread::sMThreadId();
	return true;
}
bool CMutexEmpty::MUnlock(void)
{
	MASSERT(FNumber, CThread::sMThreadId());
	FNumber = 0;
	return true;
}
struct CMutex::CImpl
{

	mutable CRITICAL_SECTION FCs;
	unsigned FCounter;
	volatile unsigned FId;
};
 CMutex::CMutex(eMutexType aVal) :
		FFlags(aVal)
{
	//CRITICAL_SECTION is always recursive -  ignoring aVal
	FImpl=new CImpl;
	FImpl->FId=0;
	FImpl->FCounter=0;
	InitializeCriticalSection(&FImpl->FCs);
}
 CMutex::~CMutex()
{
	DeleteCriticalSection(&FImpl->FCs);
	CHECK_EQ(FImpl->FId ,0u);
	delete FImpl;
}
 unsigned CMutex::MThread() const
 {
 	return FImpl->FId;
 }
 bool CMutex::MLock()
{
	_Acquires_lock_(FImpl->FCs);
	EnterCriticalSection(&FImpl->FCs);
	++FImpl->FCounter;
	FImpl->FId = CThread::sMThreadId();
	return true;
}
 bool CMutex::MCanLock()
{
	_Acquires_lock_(FImpl->FCs);
	bool const _is= TryEnterCriticalSection(&FImpl->FCs)!=0;
	if(_is)
	{
		++FImpl->FCounter;
		FImpl->FId = CThread::sMThreadId();
	}
	return _is;
}
 bool CMutex::MUnlock()
{
	_Releases_lock_(FImpl->FCs);
	if(--FImpl->FCounter==0)
		FImpl->FId = 0;
	LeaveCriticalSection(&FImpl->FCs);
	return true;
}
void* CMutex::MGetPtr() const
{
	return &FImpl->FCs;
}
}

#endif
