/*
 * CCommonAllocater.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 14.03.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */   
#ifndef CCOMMONALLOCATER_H_
#define CCOMMONALLOCATER_H_

#include <UType/IAllocater.h>
#include <UType/mallocallocater.h>
namespace NSHARE
{
template<template<class > class TAloc =malloc_allocater>
class CCommonAllocater: public IAllocater
{
public:
	typedef TAloc<uint8_t> common_allocater_t;

	CCommonAllocater();
	virtual ~CCommonAllocater();
	virtual void* MAllocate(size_type aSize, uint8_t aAlignment = 4,eAllocatorType =ALLOCATE_FROM_COMMON );
	virtual void* MReallocate(void* p,size_type aSize, uint8_t aAlignment = 4,eAllocatorType =ALLOCATE_FROM_COMMON);
	virtual void MDeallocate(void* p,size_type aSize);

	virtual size_type MMaxSize() const;

	virtual size_t MGetUsedMemory() const;

	virtual size_t MGetNumberOfAllocations() const;
	virtual bool MLock(void* p) const
	{
		return FMutex.MLock();
	}
	virtual bool MUnlock(void* p) const
	{
		return FMutex.MUnlock();
	}
protected:
	size_t FUsedMemory;
	size_t FAllocations;
	common_allocater_t FAllocater;
	mutable CMutex FMutex;
};
template<template<class > class TAloc>
inline CCommonAllocater<TAloc>::CCommonAllocater()
{
	FUsedMemory = 0;
	FAllocations = 0;
}
template<template<class > class TAloc>
inline CCommonAllocater<TAloc>::~CCommonAllocater()
{
	LOG_IF(ERROR,FUsedMemory!= 0)<<"The number of used memory "<<FUsedMemory;
	LOG_IF(ERROR,FAllocations!= 0)<<"The number of allocation "<<FAllocations;
}
template<template<class > class TAloc>
inline void* CCommonAllocater<TAloc>::MAllocate(size_type aSize,
		uint8_t aAlignment,eAllocatorType )
{
	++FAllocations;
	return FAllocater.allocate(aSize);
}
template<template<class > class TAloc>
inline void CCommonAllocater<TAloc>::MDeallocate(void* p,size_type aSize)
{
	--FAllocations;
	FAllocater.deallocate((typename common_allocater_t::pointer) p, 0);
}
template<template<class > class TAloc>
inline typename CCommonAllocater<TAloc>::size_type CCommonAllocater<TAloc>::MMaxSize() const
{
	return FAllocater.max_size();
}
template<template<class > class TAloc>
inline size_t CCommonAllocater<TAloc>::MGetUsedMemory() const
{
	return FUsedMemory;
}
template<template<class > class TAloc>
inline size_t CCommonAllocater<TAloc>::MGetNumberOfAllocations() const
{
	return FAllocations;
}
template<template<class > class TAloc>
inline void* CCommonAllocater<TAloc>::MReallocate(void* aP,size_type aSize, uint8_t aAlignment,eAllocatorType)
{
	void* _p=FAllocater.reallocate(aP,aSize);
	LOG_IF(WARNING, _p ==NULL) << "The reallocated pointer is NULL";
	if(!_p)
		return NULL;
	LOG_IF(WARNING, _p != aP) << "The reallocated pointer is not equal of prev";
	return _p;
}
template<>
inline void* CCommonAllocater<malloc_allocater>::MReallocate(void* p,size_type aSize, uint8_t aAlignment,eAllocatorType)
{
	void* _p= FAllocater.reallocate((common_allocater_t::pointer)p,aSize);
	LOG_IF(WARNING, _p ==NULL) << "The reallocated pointer is NULL";
	if(!_p)
		return NULL;
	LOG_IF(WARNING, _p != p) << "The reallocated pointer is not equal of prev";
	return _p;
}
} /* namespace NSHARE */
#endif /* CCOMMONALLOCATER_H_ */
