/*
 * CSafeDataPosix.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 23.12.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CSAFEDATAPOSIX_H_
#define CSAFEDATAPOSIX_H_

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
	}
	WAccess<_Y>& operator=(WAccess<_Y> const& aRhs)
	{
		return *this;
	}
	void MLock()
	{
		pthread_rwlock_wrlock(&FSafe.FImpl.FMutex);
		CHECK_EQ(FSafe.FImpl.FWritersLock,0);
		++FSafe.FImpl.FWritersLock;
	}

	void MUnlock()
	{
		if ((--FSafe.FImpl.FWritersLock) == 0)
			pthread_rwlock_unlock(&FSafe.FImpl.FMutex);

		CHECK_GE(FSafe.FImpl.FWritersLock , 0);
	}
	CSafeData<_T>& FSafe;
	friend class CSafeData<_T> ;
};

template<class _T>
template<class _Y>
inline CSafeData<_T>::WAccess<_Y>::~WAccess()
{
	MUnlock();
}
template<class _T>
template<class _Y>
inline CSafeData<_T>::WAccess<_Y>::WAccess(WAccess<_Y> const& aRhs) :
		FSafe(aRhs.FSafe)
{
	MASSERT_1(FSafe.FImpl.FWritersLock>0);
	++FSafe.FImpl.FWritersLock;
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
		pthread_rwlock_rdlock(&FSafe.FImpl.FMutex);
	}
	inline void MUnlock()
	{
		pthread_rwlock_unlock(&FSafe.FImpl.FMutex);
	}

	CSafeData<_T> const& FSafe;
	friend class CSafeData<_T> ;
};
} //namespace NSHARE




#endif /* CSAFEDATAPOSIX_H_ */
