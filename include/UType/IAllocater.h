/*
 * IAllocater.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 14.03.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef IALLOCATER_H_
#define IALLOCATER_H_
#include <UType/eAllocatorType.h>
namespace NSHARE
{
class IAllocater
{
public:
	typedef size_t size_type;
	typedef /*uint32_t*/uintptr_t offset_pointer_t;//fixme Maybe problem if using x64 and x86 programm with SM
	//need using Small code model
	static  const offset_pointer_t NULL_OFFSET;// held in CBuffer.cpp by historical reason

	virtual ~IAllocater()
	{
	}

	virtual void* MAllocate(size_type aSize, uint8_t aAlignment = 4,eAllocatorType =ALLOCATE_FROM_COMMON ) = 0;

	virtual void MDeallocate(void* p, size_type aSize) = 0;
	virtual void* MReallocate(void* p, size_type aSize, uint8_t aAlignment = 4,eAllocatorType =ALLOCATE_FROM_COMMON) = 0;
	virtual offset_pointer_t MOffset(void* aP) const
	{
		return (offset_pointer_t)(intptr_t)(aP);
	}
	virtual void* MPointer(offset_pointer_t aOffset) const
	{
		return reinterpret_cast<void*>(aOffset);
	}
	virtual bool MIsAllocated(void* aP) const
	{
		return true;
	}
	virtual size_type MMaxSize() const=0;

	virtual bool MLock(void* p) const
	{
		return false;
	}
	virtual bool MUnlock(void* p) const
	{
		return false;
	}
//	virtual const void* MAdd(const void* p, size_type x) const = 0;
//	virtual const void* MSubtract(const void* p, size_type x) const = 0;

	virtual size_t MGetUsedMemory() const
	{
		return 0;
	}

	virtual size_t MGetNumberOfAllocations() const
	{
		return 0;
	}
};
template<class T> T* allocate_object(IAllocater& aAllocator)
{
	return new (aAllocator.MAllocate(sizeof(T), __alignof(T))) T;
}

template<class T, class Param1> T* allocate_object(IAllocater& aAllocator, //
		const Param1& aParam1)
{
	return new (aAllocator.MAllocate(sizeof(T), __alignof(T))) T(aParam1);
}
template<class T, class Param1, class Param2> T* allocate_object(
		IAllocater& aAllocator, //
		const Param1& aParam1, const Param2& aParam2)
{
	return new (aAllocator.MAllocate(sizeof(T), __alignof(T))) T(aParam1,
			aParam2);
}
template<class T, class Param1, class Param2, class Param3> T* allocate_object(
		IAllocater& aAllocator, //
		const Param1& aParam1, const Param2& aParam2, const Param3& aParam3)
{
	return new (aAllocator.MAllocate(sizeof(T), __alignof(T))) T(aParam1,
			aParam2, aParam3);
}
template<class T, class Param1, class Param2, class Param3, class Param4> T* allocate_object(
		IAllocater& aAllocator, //
		const Param1& aParam1, const Param2& aParam2, const Param3& aParam3,
		const Param4& aParam4)
{
	return new (aAllocator.MAllocate(sizeof(T), __alignof(T))) T(aParam1,
			aParam2, aParam3, aParam4);
}
template<class T, class Param1, class Param2, class Param3, class Param4,
		class Param5> T* allocate_object(
		IAllocater& aAllocator, //
		const Param1& aParam1, const Param2& aParam2, const Param3& aParam3,
		const Param4& aParam4, const Param5& aParam5)
{
	return new (aAllocator.MAllocate(sizeof(T), __alignof(T))) T(aParam1,
			aParam2, aParam3, aParam4, aParam5);
}
//if you do not have enough "allocate_object" functions it means you have a bad constructor

template<class T> void deallocate_object(IAllocater& aAllocator, T* aObject)
{
	if (!aObject)
	{
		return;
	}
	aObject->~T();
	aAllocator.MDeallocate(aObject, sizeof(T));
}
template<class T> void deallocate_object(IAllocater* aAllocator, T* aObject)
{
	if (!aAllocator)
	{
		return;
	}
	deallocate_object(*aAllocator,aObject);
}
namespace _impl
{
template<class TType, class TAligmentsType> size_t get_alligment_size_ref()
{
	const size_t _alligment = __alignof(TAligmentsType);

	size_t _length_size =
			sizeof(TType) > _alligment ? sizeof(TType) : _alligment;

	if (_length_size % _alligment > 0)
		_length_size += _length_size % _alligment;
	return _length_size;
}
template<class T> size_t get_size_of_array_len()
{
	const size_t _alligment = __alignof(T);

	size_t _length_size =
			sizeof(size_t) > _alligment ? sizeof(size_t) : _alligment;

	if (_length_size % _alligment > 0)
		_length_size += _length_size % _alligment;
	return _length_size;
}
}
template<class T> T* allocate_array(IAllocater& aAllocator, size_t aCount,
		const T& aVal)
{
	//CHECK_NE(aCount, 0);

	//Calculate how much extra memory need allocate to store the length before the array
	size_t _length_size = _impl::get_size_of_array_len<T>();

	//CHECK_NE(_length_size, 0);

	//Allocate extra space to store array length
	char* _p = (char*) aAllocator.MAllocate(sizeof(T) * (aCount) + _length_size,
			__alignof(T));
	_p += _length_size;

	*(((size_t*) _p) - 1) = aCount;
	char* _end = _p + sizeof(T) * (aCount);
	for (char* _begin=_p; _begin != _end; _begin += sizeof(T))
		new (_begin) T(aVal);

	return (T*) _p;
}
template<class T> T* allocate_array(IAllocater& aAllocator, size_t aCount)
{
	//CHECK_NE(aCount, 0);

	//Calculate how much extra memory need allocate to store the length before the array
	size_t _length_size = _impl::get_size_of_array_len<T>();

	//CHECK_NE(_length_size, 0);

	//Allocate extra space to store array length
	char* _p = (char*) aAllocator.MAllocate(sizeof(T) * (aCount) + _length_size,
			__alignof(T));
	_p += _length_size;

	*(((size_t*) _p) - 1) = aCount;
	return (T*) _p;
}
template<class T> void deallocate_array(IAllocater& aAllocator, T* aArray)
{
	if (!aArray)
	{
		return;
	}

	size_t _len = *(((size_t*) aArray) - 1);

	for (size_t i = 0; i < _len; i++)
		aArray[i].~T();

	size_t _length_size = _impl::get_size_of_array_len<T>();

	aAllocator.MDeallocate((char*) aArray - _length_size, _len + _length_size);
}

template<> class CRAII<IAllocater> : public CDenyCopying
{
public:
	explicit CRAII(IAllocater * aMutex, void* aBuf) :
			FMutex(aMutex), FBuf(aBuf)
	{
		MLock();
	}
	~CRAII()
	{
		MUnlock();
	}
	inline void MUnlock()
	{
		FIsLock && FMutex->MUnlock(FBuf);
		FIsLock = false;
	}
private:
	inline void MLock()
	{
		FIsLock = FMutex && FMutex->MLock(FBuf);
	}
	IAllocater *FMutex;
	void* FBuf;
	volatile bool FIsLock;
};
} /* namespace NSHARE */
#endif /* IALLOCATER_H_ */
