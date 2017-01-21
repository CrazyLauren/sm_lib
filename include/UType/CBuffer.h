/*
 * CBuffer.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 14.03.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#ifndef CBUFFER_H_
#define CBUFFER_H_

#include <UType/buffer_value.h>
#include <UType/eAllocatorType.h>
namespace NSHARE
{

class IAllocater;
template<class Pointer, class Refer, class diff_type>
class  iterator_type
{
public:
	typedef iterator_type iterator_t;
	typedef Pointer pointer;
	typedef Refer reference;
	typedef diff_type difference_type;

	iterator_type() :
			_M_current(NULL)
	{
	}
//	template<class RPointer, class RRefer, class Rdiff_type>
//	iterator_type(iterator_type<RPointer,RRefer,Rdiff_type>const & aRht) :
//			_M_current(aRht._M_current)
//	{
//	}
//	template<class RPointer, class RRefer, class Rdiff_type>
//	iterator_type&
//	operator=(iterator_type<RPointer, RRefer, Rdiff_type> const & aRht)
//	{
//		_M_current = aRht._M_current;
//		return *this;
//	}
	iterator_type(iterator_type const & aRht) :
			_M_current(aRht._M_current)
	{
	}
	iterator_type&
	operator=(iterator_type const & aRht)
	{
		_M_current = aRht._M_current;
		return *this;
	}

	explicit iterator_type(const pointer& __i) :
			_M_current(__i)
	{
	}
	// Forward iterator requirements
	reference operator*() const
	{
		return *_M_current;
	}

	pointer operator->() const
	{
		return _M_current;
	}

	iterator_t& operator++()
	{
		++_M_current;
		return *this;
	}

	iterator_t operator++(int)
	{
		return iterator_t(_M_current++);
	}

	iterator_t&
	operator--()
	{
		--_M_current;
		return *this;
	}

	iterator_t operator--(int)
	{
		return iterator_t(_M_current--);
	}

	// Random access iterator requirements
	reference operator[](const difference_type& __n) const
	{
		return _M_current[__n];
	}

	iterator_t&
	operator+=(const difference_type& __n)
	{
		_M_current += __n;
		return *this;
	}

	iterator_t operator+(const difference_type& __n) const
	{
		return iterator_t(_M_current + __n);
	}

	iterator_t&
	operator-=(const difference_type& __n)
	{
		_M_current -= __n;
		return *this;
	}

	iterator_t operator-(const difference_type& __n) const
	{
		return iterator_t(_M_current - __n);
	}

	pointer& base()
	{
		return _M_current;
	}
	pointer const& base() const
	{
		return _M_current;
	}
protected:
	pointer _M_current;
};

class SHARE_EXPORT CBuffer
{
public:
	typedef IAllocater::offset_pointer_t offset_pointer_t;
	typedef buf_val_t<uint8_t> value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer; //fixme
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef iterator_type<pointer, reference, difference_type> iterator; //fixme
	typedef iterator_type<const_pointer, const_reference, difference_type> const_iterator;
	typedef IAllocater allocator_type;

//	template<template<class > class TAloc>
//	struct _wraper
//	{
//
//	};
//	template<template<class > class TAloc>
//	CBuffer(_wraper<TAloc> const&);
	//	CBuffer(IAllocater* aAlloc = NULL);
	CBuffer(IAllocater* aAlloc,eAllocatorType=ALLOCATE_FROM_COMMON);
	CBuffer(size_t aSize=0,int aBeginSize=-1,IAllocater* aAlloc=NULL,eAllocatorType=ALLOCATE_FROM_COMMON);

//	CBuffer(IAllocater* aAlloc = NULL);
//	CBuffer(size_t aBeginSize, IAllocater* aAlloc);

	template<class ItT>
	CBuffer(IAllocater* aAlloc,ItT aBegin, ItT aEnd,eAllocatorType=ALLOCATE_FROM_COMMON);
	CBuffer(IAllocater* aAlloc, void const* aBegin, void const* aEnd,eAllocatorType=ALLOCATE_FROM_COMMON);
	CBuffer(IAllocater& aAlloc, offset_pointer_t Offset,bool aCheckCrc=true,eAllocatorType=ALLOCATE_FROM_COMMON);

	~CBuffer();

	CBuffer(const CBuffer&);
	CBuffer const& operator=(const CBuffer&);
	CBuffer const& deep_copy(const CBuffer&);
	void MMoveTo(CBuffer& aTo);

	size_type size() const;
	size_type max_size() const;
	size_type capacity() const;
	size_type begin_capacity() const;
	bool empty() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	//todo swap
	//reference operator[](size_type __n);//for safety
	const_reference operator[](size_type __n) const;

//	reference front(); //for safety
	const_reference front() const;
//	reference back();//for safety
	const_reference back() const;

	void resize(size_type __new_size, bool fromBegin = false,bool aCanDetach=true);//bug fix. aCanDetach - kostil'!
	void clear();

	void insert(iterator __position, size_type __n, value_type const&);
	void insert(iterator __position, value_type const&);

	void insert(iterator __position, iterator aBegin, iterator aEnd);
	void insert(iterator __position, const_iterator aBegin,
			const_iterator aEnd);
	iterator erase(iterator aBegin, iterator aEnd);
	void push_back(const value_type& __x);
	void pop_back();
	void push_front(const value_type& __x);
	void pop_front();
	void release();
	void reserve(size_t aSize);
	const_pointer ptr_const() const;
	pointer ptr();
	offset_pointer_t refuse();
	offset_pointer_t offset() const;
	unsigned use_count() const;
	void release_force() const; //todo
	static void sMUnitTest(IAllocater*);
	static void sMUnitTest(size_t aSize, IAllocater*);
	bool MIsDetached() const;
	bool MIsAllocatorEqual(IAllocater* aAlloc) const;
	IAllocater* MAllocator() const;
	bool MIsRestored() const;
	const size_t BEGIN_SIZE;
	static const size_t DEF_BUF_RESERVE;

	static allocator_type * sMDefAllaocter();
private:


	struct buf_info;
	struct SHARE_EXPORT _buffer_t
	{
		static const size_type BUF_OFFSET;

		_buffer_t(IAllocater* aAll,eAllocatorType);
		_buffer_t(IAllocater* aAlloc, offset_pointer_t Offset,bool aCheckCrc,eAllocatorType);
		_buffer_t(_buffer_t const & aR);
		_buffer_t & operator=(_buffer_t const & r);
		_buffer_t &deep_copy(_buffer_t const & r);
		void MMoveTo(_buffer_t& aTo);
		~_buffer_t();

		value_type* MGetPtr(void* aVal) const;
		buf_info& MGetBuff() const;
		value_type* MStorageBegin() const;

		static buf_info& sMGetBuff(value_type* aVal);
		value_type* MReAllocate(value_type* ,size_t aSize);
		value_type* MAllocate(size_t aSize);
		void MDeallocate();
		void MDeallocate(value_type* aP, size_t __n);

		size_type size() const;
		uint32_t use_count() const;
		bool unique() const;
		void release();
		void add_ref_copy(bool aIsExist=false) const;
		bool empty() const;
		bool MIsRestored() const;

		allocator_type* FAllocator;
		value_type* FBeginOfStorage;
		eAllocatorType FAllocatorType;
	};


	pointer MInsertImpl(iterator __position, size_type __n, bool aCanDetach=true);

	void MFill(pointer  aPosition, value_type const& aVal,
			size_type aSize);
	void MFill(pointer ,const_pointer const&,const_pointer const&);

	value_type* MAllocate(size_t __n);
	value_type* MReAllocate(value_type*,size_t __n);
	size_type requred_buf_len(size_type aSize) const;

	allocator_type & get_allocator() const;
	void MDetach();
	bool MIsNeedDetach() const;




	_buffer_t FBuffer;
	bool FIsDetached;

};
inline CBuffer::const_iterator CBuffer::cbegin() const
{
	return begin();
}
inline CBuffer::const_iterator CBuffer::cend() const
{
	return end();
}
inline bool CBuffer::MIsDetached() const
{
	return FIsDetached;
}
template<class Pointer, class Refer, class diff_type>
inline bool operator==(const iterator_type<Pointer, Refer, diff_type>& __lhs,
		const iterator_type<Pointer, Refer, diff_type>& __rhs)
{
	return __lhs.base() == __rhs.base();
}

template<class Pointer, class Refer, class diff_type>
inline bool operator!=(const iterator_type<Pointer, Refer, diff_type>& __lhs,
		const iterator_type<Pointer, Refer, diff_type>& __rhs)
{
	return __lhs.base() != __rhs.base();
}

template<class Pointer, class Refer, class diff_type>
inline bool operator<(const iterator_type<Pointer, Refer, diff_type>& __lhs,
		const iterator_type<Pointer, Refer, diff_type>& __rhs)
{
	return __lhs.base() < __rhs.base();
}

template<class Pointer, class Refer, class diff_type>
inline bool operator>(const iterator_type<Pointer, Refer, diff_type>& __lhs,
		const iterator_type<Pointer, Refer, diff_type>& __rhs)
{
	return __lhs.base() > __rhs.base();
}

template<class Pointer, class Refer, class diff_type>
inline bool operator<=(const iterator_type<Pointer, Refer, diff_type>& __lhs,
		const iterator_type<Pointer, Refer, diff_type>& __rhs)
{
	return __lhs.base() <= __rhs.base();
}

template<class Pointer, class Refer, class diff_type>
inline bool operator>=(const iterator_type<Pointer, Refer, diff_type>& __lhs,
		const iterator_type<Pointer, Refer, diff_type>& __rhs)
{
	return __lhs.base() >= __rhs.base();
}
template<class Pointer, class Refer, class diff_type>
inline typename iterator_type<Pointer, Refer, diff_type>::difference_type operator-(
		const iterator_type<Pointer, Refer, diff_type>& __lhs,
		const iterator_type<Pointer, Refer, diff_type>& __rhs)
{
	return __lhs.base() - __rhs.base();
}

template<class Pointer, class Refer, class diff_type>
inline iterator_type<Pointer, Refer, diff_type> operator+(
		typename iterator_type<Pointer, Refer, diff_type>::difference_type __n,
		const iterator_type<Pointer, Refer, diff_type>& __i)
{
	return iterator_type<Pointer, Refer, diff_type>(__i.base() + __n);
}
inline CBuffer::CBuffer(IAllocater* aAlloc, void const* aBegin, void const* aEnd,eAllocatorType aType) :
	BEGIN_SIZE(DEF_BUF_RESERVE), FBuffer(aAlloc ? aAlloc : sMDefAllaocter(),aType)
{
	size_t const _size = (char*)aEnd - (char*)aBegin;
	resize(_size);
	memcpy(begin().base(), aBegin, _size);
}
template<class ItT>
inline CBuffer::CBuffer(IAllocater* aAlloc,ItT aBegin, ItT aEnd,eAllocatorType aType) :
		BEGIN_SIZE(DEF_BUF_RESERVE), FBuffer(aAlloc ? aAlloc : sMDefAllaocter(),aType)
{
	resize(aEnd - aBegin);
	iterator _begin = begin();
	iterator _end = end();
	for (; _begin != _end; ++_begin, ++aBegin)
		*_begin = *aBegin;
}
inline bool operator==(const CBuffer& __lhs, const CBuffer& __rhs)
{
	if (__lhs.size() != __rhs.size())
		return false;
	CBuffer::const_iterator _begin = __lhs.begin();
	CBuffer::const_iterator _end = __lhs.end();
	CBuffer::const_iterator _begin2 = __rhs.begin();
	for (; _begin != _end; ++_begin, ++_begin2)
		if (*_begin != *_begin2)
			return false;
	return true;
}
inline bool operator!=(const CBuffer& __lhs, const CBuffer& __rhs)
{
	return !operator==(__lhs, __rhs);
}
inline std::ostream& operator<<(std::ostream& aStream,
		NSHARE::CBuffer const& aVal)
{
	aStream << "Buffer size =" << aVal.size() << ",\n";
	NSHARE::print_buffer(aStream, aVal.begin(), aVal.end());
	return aStream;
}
} /* namespace NSHARE */
#endif /* CBUFFER_H_ */
