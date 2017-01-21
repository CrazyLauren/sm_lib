/*
 * CSafeData.hpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 15.09.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CSAFEDATA_HPP_
#define CSAFEDATA_HPP_

namespace NSHARE
{
template<class _T>
template<class _Y>
class CSafeData<_T>::WAccess
{
public:
	typedef _Y value_type;
	typedef _Y* pvalue_type;
	WAccess(WAccess<_Y> const& aRhs);
	~WAccess();

	value_type& operator*()
	{
		return FSafe.FData;
	}

	pvalue_type operator&() // never throws
	{
		return MGetPtr();
	}

	inline pvalue_type operator->()
	{
		return MGetPtr();
	}
	WAccess<value_type> & operator=(value_type const & aData)
	{
		FSafe.FData = aData;
		return *this;
	}
	operator value_type &()
	{
		return MGet();
	}
	inline value_type& MGet()
	{
		return FSafe.FData;
	}
	inline pvalue_type MGetPtr()
	{
		return &FSafe.FData;
	}
private:
	WAccess(CSafeData<_T>& aA) :
			FSafe(aA)
	{
		MLock();
#ifndef NDEBUG
		FPThread = new unsigned;
		*FPThread = CThread::sMThreadId();
#endif //NDEBUG
	}
	WAccess<_Y>& operator=(WAccess<_Y> const& aRhs)
	{
		return *this;
	}
	void MLock()
	{
		LOG_IF(FATAL,
				FSafe.FImpl.FMutex.MThread()
						== NSHARE::CThread::sMThreadId())
				<< "Dead lock for rw writer " << FSafe.FImpl.FMutex.MThread()
				<< " == " << NSHARE::CThread::sMThreadId();
		FIsLock=FSafe.FImpl.FMutex.MLock();
		++FSafe.FImpl.FWriters;
		for (; FSafe.FImpl.FReaders;)
		{
			bool _rval = FSafe.FImpl.FWriteSignal.MTimedwait(
					&FSafe.FImpl.FMutex);
			MASSERT_1(_rval);
		}
		CHECK_EQ(FSafe.FImpl.FWritersLock,0);
		++FSafe.FImpl.FWritersLock;
	}

	void MUnlock()
	{
		CHECK(FIsLock);
		CHECK(FSafe.FImpl.FWriters > 0);
		if ((--FSafe.FImpl.FWritersLock) == 0)
		{
			if ((--FSafe.FImpl.FWriters)!=0)
				FSafe.FImpl.FWriteSignal.MSignal();
			else
				FSafe.FImpl.FReadSignal.MBroadcast();

			if (FIsLock)
			{
				FIsLock = false;
				FSafe.FImpl.FMutex.MUnlock();
			}
		}
		CHECK_GE(FSafe.FImpl.FWritersLock, 0);
	}

	CSafeData<_T>& FSafe;
	volatile bool FIsLock;
#ifndef NDEBUG
	volatile unsigned *FPThread;
#endif //NDEBUG
	friend class CSafeData<_T> ;
};
template<class _T>
template<class _Y>
inline CSafeData<_T>::WAccess<_Y>::WAccess(WAccess<_Y> const& aRhs) :
		FSafe(aRhs.FSafe),FIsLock(aRhs.FIsLock)
{
#ifndef NDEBUG
	FPThread=aRhs.FPThread;
	MASSERT_1(CThread::sMThreadId() == *FPThread);
#endif //NDEBUG
	++FSafe.FImpl.FWritersLock;
}
template<class _T>
template<class _Y>
inline CSafeData<_T>::WAccess<_Y>::~WAccess()
{
#ifndef NDEBUG
	if (1 == FSafe.FImpl.FWritersLock)
		delete FPThread;
#endif //NDEBUG
	MUnlock();
}

template<class _T>
template<class _Y>
class CSafeData<_T>::RAccess
{
public:
	typedef _Y const value_type;
	typedef _Y const* pvalue_type;

	RAccess(RAccess<_Y> const& aRhs) :
			FSafe(aRhs.FSafe)
	{
		MASSERT_1(FSafe.FImpl.FReaders);
		MLock();
	}
	~RAccess()
	{
		MUnlock();
	}
	inline value_type& operator*() const
	{
		return MGet();
	}

	inline pvalue_type operator->() const
	{
		return MGetPtr();
	}
	inline operator value_type&() const
	{
		return MGet();
	}
	inline value_type& MGet() const
	{
		return FSafe.FData;
	}
	inline pvalue_type MGetPtr() const
	{
		return &FSafe.FData;
	}
private:
	RAccess(CSafeData<_T> const& aA) :
			FSafe(aA)
	{
		MLock();
	}
	RAccess<_Y>& operator=(RAccess<_Y> const& aRhs) const
	{
		return *this;
	}
	RAccess<_Y> & operator=(value_type & aData) const
	{
		return *this;
	}
	inline void MLock()
	{
		LOG_IF(FATAL,
				FSafe.FImpl.FMutex.MThread()
						== NSHARE::CThread::sMThreadId())
				<< "Dead lock for rw reader " << FSafe.FImpl.FMutex.MThread()
				<< " == " << NSHARE::CThread::sMThreadId();
		NSHARE::CRAII<CMutex> _block(FSafe.FImpl.FMutex);
		for (; FSafe.FImpl.FWriters;)
		{
			bool _rval = FSafe.FImpl.FReadSignal.MTimedwait(
					&FSafe.FImpl.FMutex);
			MASSERT_1(_rval);
		}
		++FSafe.FImpl.FReaders;
	}
	inline void MUnlock()
	{
		NSHARE::CRAII<CMutex> _block(FSafe.FImpl.FMutex);
		MASSERT_1(FSafe.FImpl.FReaders > 0);
		if (--FSafe.FImpl.FReaders == 0 && FSafe.FImpl.FWriters)
			FSafe.FImpl.FWriteSignal.MSignal();
	}

	CSafeData<_T> const& FSafe;
	friend class CSafeData<_T> ;
};
} //namespace NSHARE

#endif /* CSAFEDATA_HPP_ */
