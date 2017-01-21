/*
 * CMutex.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 27.09.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef MUTEX_H_
#define MUTEX_H_

namespace NSHARE
{
extern "C" SHARE_EXPORT unsigned thread_id();
class SHARE_EXPORT CMutex: CDenyCopying
{
public:
	// Construction | Destruction
	enum eMutexType
	{
		MUTEX_NORMAL=1,
		MUTEX_RECURSIVE
	};
	explicit CMutex(eMutexType aType = MUTEX_RECURSIVE);
	~CMutex(void);
	// API
	bool MLock(void);
	bool MCanLock(void);
	bool MUnlock(void);
	eMutexType MGetMutexType() const
	{
		return FFlags.MGetMask();
	}
	void* MGetPtr() const;
	static bool sMUnitTest();
	unsigned MThread()const;
private:
	struct CImpl;

	CFlags<eMutexType,eMutexType> FFlags;
	CImpl *FImpl;

	friend class CCondvar;
};
template<> class  CRAII<CMutex> : public CDenyCopying
{
public:
	explicit CRAII(CMutex & aMutex) :
			FMutex(aMutex)
	{
		MLock();
	}
	~CRAII()
	{
		MUnlock();
	}
	inline void MUnlock()
	{
		FIsLock && FMutex.MUnlock();
		FIsLock = false;
	}
private:
	inline void MLock()
	{
		FIsLock = FMutex.MLock();
	}
	CMutex &FMutex;
	volatile bool FIsLock;
};
template<> class  CRAII<CMutex*>
{
public:
	explicit CRAII(CMutex* aMutex) :
			CRaii(*aMutex)
	{
	}
	~CRAII(void)
	{
	}
private:
	CRAII<CMutex> CRaii;
};
struct  CMutexEmpty: CDenyCopying
{

	CMutexEmpty()
	{
		FNumber = 0;
	}
	bool MLock(void);
	bool MCanLock(void)
	{
		return true;
	}
	bool MUnlock(void);
	volatile unsigned FNumber;
};

template<> struct SHARE_EXPORT CRAII<CMutexEmpty> : public CDenyCopying
{
public:
	explicit CRAII(CMutexEmpty const& aMutex)
	{

	}
};
} //namespace USHARE


#endif /*MUTEX_H_*/
