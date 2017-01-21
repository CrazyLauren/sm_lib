/*
 * mallocallocater.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 14.03.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef MALLOCALLOCATER_H_
#define MALLOCALLOCATER_H_

namespace NSHARE
{

template<class T>
struct malloc_allocater
{
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	template<class U> struct rebind
	{
		typedef malloc_allocater<U> other;
	};
	malloc_allocater() throw ()
	{
	}
	malloc_allocater(const malloc_allocater&) throw ()
	{
	}

	template<class U> malloc_allocater(const malloc_allocater<U>&) throw ()
	{
	}

	~malloc_allocater() throw ()
	{
	}

	pointer address(reference x) const
	{
		return &x;
	}
	const_pointer address(const_reference x) const
	{
		return &x;
	}

	pointer allocate(size_type s, void const * = NULL)
	{
		using namespace std;
		if (0 == s)
			return NULL;
		pointer temp = (pointer) malloc(s * sizeof(T));
		if (temp == NULL)
			throw std::bad_alloc();
		return temp;
	}

	void deallocate(pointer p, size_type)
	{
		using namespace std;
		free(p);
	}
	pointer reallocate(pointer p, size_type _new_size)
	{
		return(pointer) std::realloc(p, _new_size);
	}
	size_type max_size() const throw ()
	{
		return std::numeric_limits<size_t>::max() / sizeof(T);
	}

	void construct(pointer p, const T& val)
	{
		new ((void *) p) T(val);
	}

	void destroy(pointer p)
	{
		p->~T();
	}
};
} /* namespace NSHARE */
#endif /* MALLOCALLOCATER_H_ */
