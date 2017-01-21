/*
 * CIntrusived.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 20.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#include <deftype>
#include <boost/version.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <UType/CIntrusived.h>

#if (BOOST_VERSION / 100000 >=1) &&(BOOST_VERSION / 100 % 1000<=47)
using namespace boost::interprocess::detail;
#else
using namespace boost::interprocess::ipcdetail;
#endif

namespace NSHARE
{
struct CIntrusived::_w_counter_t
{
	_w_counter_t(CIntrusived* aPtr) :
			FCount(0), FWPtr(aPtr)
	{

	}

	_w_counter_t(_w_counter_t const& aRht):FWPtr(aRht.FWPtr)
	{
		//copy
		MRef();
	}

	int MRef() volatile
	{
		//todo first
		atomic_inc32(&FCount);
		return atomic_read32(&FCount);
	}
	int MUnref() volatile
	{
		atomic_dec32(&FCount);
		CHECK_LT(FCount, std::numeric_limits<unsigned>::max() / 2);
		if (atomic_read32(&FCount) == 0)
		{
			VLOG(2) << "Remove ";
			delete this;
			return 0;
		}
		else
			return atomic_read32(&FCount);
	}
	volatile mutable unsigned FCount;
	CIntrusived* FWPtr;
protected:
	~_w_counter_t()
	{

	}
	_w_counter_t& operator=(_w_counter_t const& aRht)
	{
		return *this;
	}
};

CIntrusived::w_counter_t::w_counter_t(CIntrusived* aP) :
		FWCounter(new _w_counter_t(aP))
{
	CHECK_NOTNULL(FWCounter);
	FWCounter->MRef();
}
CIntrusived::w_counter_t::w_counter_t(w_counter_t const & aRht) :
		FWCounter(aRht.FWCounter)
{
	CHECK_NOTNULL(FWCounter);
	if (FWCounter->MRef() == 0)
		FWCounter = NULL;
}
CIntrusived::w_counter_t& CIntrusived::w_counter_t::operator =(
		const w_counter_t& aRht)
{
	if (this != &aRht)
	{
		if (FWCounter && FWCounter->MUnref() == 0)
			FWCounter = NULL;
		FWCounter = aRht.FWCounter;
		CHECK_NOTNULL(FWCounter);
		if (FWCounter->MRef() == 0)
			FWCounter = NULL;
	}
	return *this;
}
CIntrusived* CIntrusived::w_counter_t::MGet() const
{
	CIntrusived* _ptr = FWCounter ? FWCounter->FWPtr : NULL;
	return _ptr;
}
CIntrusived::w_counter_t::~w_counter_t()
{
	if (FWCounter && FWCounter->MUnref() == 0)
		FWCounter = NULL;
}

CIntrusived::CIntrusived() :
		FCount(0), FReferedCount(0), FIsFirst(P_NOT_INITED), FWn(this)
{
	VLOG(2) << "Construct object " << this;
}
CIntrusived::CIntrusived(const CIntrusived& aRht) :
		FCount(0), FReferedCount(0), FIsFirst(P_NOT_INITED), FWn(this)
{
	VLOG(2) << "Constract object " << this;
	DCHECK(aRht.MCountRef() > 0);
}
CIntrusived::~CIntrusived()
{
	LOG_IF(DFATAL, MCountRef() != 0) << "Ref not null";
	VLOG(2) << "Destruct object " << this;
}
CIntrusived& CIntrusived::operator =(const CIntrusived& aVal)
{
	LOG(DFATAL)<< "operator = (" << this << ", " << (&aVal);
	return *this;
}

int CIntrusived::MRefImpl() const
{
	if (atomic_read32(&FIsFirst) == P_NOT_INITED)
	{
		atomic_write32(&FIsFirst, P_INITED);
		atomic_inc32(&FCount);
		atomic_inc32(&FReferedCount);
		return atomic_read32(&FCount);
	}
	else if (atomic_read32(&FCount) && //
			atomic_read32(&FIsFirst) == P_INITED && //
			atomic_inc32(&FCount) > 0 //
					)
	{
		atomic_inc32(&FReferedCount);
		return atomic_read32(&FCount);
	}
	else
	{
		return 0;
	}
}

int CIntrusived::MUnrefImpl() const
{
	if (atomic_read32(&FIsFirst) != P_INITED)
		return -1;
	atomic_dec32(&FCount);
	if (atomic_read32(&FCount) == 0)
	{
		atomic_write32(&FIsFirst, P_REMOVING);
		FWn.FWCounter->FWPtr = NULL;
		return 0;
	}
	return atomic_read32(&FCount);
}
int CIntrusived::MUnrefWithoutDelete() const
{
	VLOG(3) << "MUnrefWithoutDelete() " << this;
	atomic_dec32(&FCount);
	return atomic_read32(&FCount);
}
int CIntrusived::MCountRef() const
{
	return atomic_read32(&FCount);
}
unsigned CIntrusived::MReferedCount() const
{
	return atomic_read32(&FReferedCount);
}
void CIntrusived::MDelete() const
{
	VLOG(2) << "Delete object " << this;
	FWn.FWCounter->FWPtr = NULL;
	delete this;
}
}
