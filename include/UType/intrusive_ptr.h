/*
 * intrusive_ptr.h
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 12.01.2016
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef INTRUSIVE_PTR_H_
#define INTRUSIVE_PTR_H_

namespace NSHARE
{
template<class T>
class  intrusive_ptr
{
public:
	typedef T element_type;

	intrusive_ptr()
	{
		MSet(NULL);
		VLOG(5) << "Construct empty intrusive_ptr" << ":" << this;
	}
	explicit intrusive_ptr(T* ptr)
	{

		MSet(ptr /*? &ptr : NULL*/);
		if (MPtr() && (CIntrusived::sMRef(MPPtr()) == 0))
		{
			MSet(NULL);
			LOG(WARNING) << "Pointer is empty after Ref.";
		}
	}
	template<class U>
	explicit intrusive_ptr(U* ptr) //FIXME remove dynamic_cast, using is_parent
	{
		LOG_IF(WARNING,!ptr) << "Empty pointer in Constructor.";
		MSet(ptr);

		if (MPtr() && CIntrusived::sMRef(MPPtr()) == 0)
		{
			MSet(NULL);
			LOG(WARNING) << "Pointer is empty after Ref.";
		}
	}
	intrusive_ptr(const intrusive_ptr& aRht)
	{
		MSet(aRht.MPtr());
		if (MPtr()) //MRef cann't return 0;
			CIntrusived::sMRef (MPPtr());
		else
			VLOG(1) << "Empty pointer in Constructor.";
	}
	//наследники
	template<class U> intrusive_ptr(const intrusive_ptr<U>& aCopy)
	{
		MSet(aCopy.MPtr()); //FIXME remove dynamic_cast, using is_parent
		if (MPtr())
			CIntrusived::sMRef (MPPtr()); //MRef cann't return 0;
		else
			VLOG(1) << "Empty pointer in Constructor.";
	}
	~intrusive_ptr()
	{
		if (MPtr())
			MUnref();
	}

	inline intrusive_ptr& operator =(const intrusive_ptr& aRht)
	{
		MAssign(aRht);
		return *this;
	}

	template<class U>
	inline intrusive_ptr& operator =(const intrusive_ptr<U>& aRht)
	{
		MAssign(aRht);
		return *this;
	}
	inline intrusive_ptr& operator =(T* aP)
	{
		intrusive_ptr _tmp(aP);
		this->operator =(_tmp);
		return *this;
	}

	bool operator ==(const intrusive_ptr& aPht) const
	{
		return MPtr() == aPht.MPtr();
	}
	bool operator ==(const T* aPtr) const
	{
		return (MPtr() == aPtr);
	}
	friend bool operator ==(const T* aPtr, const intrusive_ptr& aRht)
	{
		return (aPtr == aRht.MPtr());
	}

	bool operator !=(const intrusive_ptr& aRht) const
	{
		return (MPtr() != aRht.MPtr());
	}
	bool operator !=(const T* aPtr) const
	{
		return MPtr() != aPtr;
	}
	friend bool operator !=(const T* aPtr, const intrusive_ptr& aRht)
	{
		return aPtr != aRht.MPtr();
	}

	bool operator <(const intrusive_ptr& aRht) const //Зачем?
	{
		return MPtr() <aRht.MPtr();
	}
	bool operator !() const
	{
		return !MIs();
	}
	operator bool() const
	{
		return MIs();
	}
	T& operator*() const
	{
		CHECK_NOTNULL (MPtr());
		return (*MPtr());
	}
	inline T const* MGetConst() const
	{
		//CHECK_NOTNULL (MPtr());
		return MPtr();
	}
	T * operator->() const
	{
		CHECK_NOTNULL (MPtr());
		return MPtr();
	}
	inline T * MGet() const
	{
		//CHECK_NOTNULL (MPtr());
		return MPtr();
	}

	inline bool MIs() const
	{
		return MPtr()!=NULL ;
	}

	T* MRelease()
	{
		VLOG(5) << "Release pointer :" << MPPtr() << ". :" << this;
		if (!MPtr())
			return NULL;
		T* _tmp = MPtr();
		if (MPtr())
			(MPtr())->MUnrefWithoutDelete();
		MSet( NULL);
		return _tmp;
	}

	void MSwap(intrusive_ptr& rp)
	{
		VLOG(5) << "Swap :" << MPtr() << " to " << rp.MPtr() << ". :" << this;
		T* _tmp = MPtr();
		FPtrBase = rp.MPtr();
		rp.FPtrBase = _tmp;
	}

private:

	template<class U> void MAssign(const intrusive_ptr<U>& aRht)
	{
//		T *_ptr = dynamic_cast<T*>(aRht.FPtr); ////FIXME remove dynamic_cast, using is_parent

//		CHECK_EQ(_ptr, aRht.FPtr);
		T* _ptr = static_cast<T*>(aRht.FPtrBase);
		if (FPtrBase == _ptr)
		{
			if (FPtrBase)
				LOG(WARNING) << "Self assignment:" << this;
			return;
		}
		//Был Баг когда FPtr удалялся(ref==0) раньше aP
		T* _kostil = FPtrBase;
		FPtrBase = _ptr;
		if (FPtrBase && CIntrusived::sMRef(MPPtr()) == 0)
			MSet( NULL);
		if (_kostil && CIntrusived::sMUnref(&_kostil) == 0)
			_kostil = NULL;
	}

	template<class U> friend class intrusive_ptr;
	template<class U> friend class w_ptr;

	inline T** MPPtr() const//fixme
	{
		return &FPtrBase;
	}
	inline T* MPtr() const//fixme
	{
		return FPtrBase;
	}
	template<class U>
	inline void MSet(U* aP)
	{
		FPtrBase = static_cast<T*>(aP);
	}
	inline void MSet(T* aP)
	{
		FPtrBase = aP;
	}
	void MUnref()
	{
		if (MPtr() && CIntrusived::sMUnref(MPPtr()) == 0)
			MSet(NULL);
	}
	mutable T* FPtrBase;
};
template<class T>
class w_ptr
{
	mutable NSHARE::CIntrusived::w_counter_t FWn;
public:
	typedef T element_type;
	w_ptr() :
			FWn(NULL)
	{
	}
	explicit w_ptr(const intrusive_ptr<element_type>& aVal) :
			FWn(NULL)
	{
		if (aVal.MIs())
			FWn = aVal->FWn;
	}
	explicit w_ptr(element_type* aVal) :
			FWn(aVal ? aVal->FWn : NULL)
	{
	}
	w_ptr(const w_ptr& wp) :
			FWn(wp.FWn)
	{
	}
	w_ptr& operator =(const w_ptr& wp)
	{
		if (&wp == this)
			return *this;

		FWn = wp.FWn;
		return *this;
	}
	w_ptr& operator =(const intrusive_ptr<element_type>& wp)
	{
		FWn = wp->FWn;
		return *this;
	}
	inline intrusive_ptr<T> MGet() const
	{
		if (MIsValid())
		{
			intrusive_ptr<T> _val(static_cast<T*>(FWn.MGet()));
			return _val;
		}

		return intrusive_ptr<T>();
	}
	inline CIntrusived* MGetDynamic() const
	{
		return FWn.MGet();
	}
	bool MIsValid() const
	{
		return FWn.MGet();
	}
	bool operator ==(const T* aPtr) const
	{
		if (MIsValid())
		{
			intrusive_ptr<T> _ptr(MGet());
			if (_ptr.MIs())
				return _ptr == aPtr;
		}
		else if (!MIsValid() && !aPtr)
			return true;
		return false;
	}
	bool operator ==(const w_ptr& wp) const
	{
		if (wp.MIsValid() && MIsValid())
		{
			intrusive_ptr<T> _ptr = MGet();
			return _ptr == wp;
		}
		else if (!wp.MIsValid() && !MIsValid()) //оба null
			return true;

		return false;
	}
};
}
namespace std
{
template<class T> inline
void swap(NSHARE::intrusive_ptr<T>& rp1, NSHARE::intrusive_ptr<T>& rp2)
{
	rp1.MSwap(rp2);
}
template<typename _Tp, typename _Tp1>
inline NSHARE::intrusive_ptr<_Tp> static_pointer_cast(
		const NSHARE::intrusive_ptr<_Tp1>& __r)
{
	return static_cast<_Tp*>(__r.get());
}

template<typename _Tp, typename _Tp1>
inline NSHARE::intrusive_ptr<_Tp> const_pointer_cast(
		const NSHARE::intrusive_ptr<_Tp1>& __r)
{
	return const_cast<_Tp*>(__r.get());
}

template<typename _Tp, typename _Tp1>
inline NSHARE::intrusive_ptr<_Tp> dynamic_pointer_cast(
		const NSHARE::intrusive_ptr<_Tp1>& __r)
{
	return dynamic_cast<_Tp*>(__r.get());
}
}
#endif /* INTRUSIVE_PTR_H_ */
