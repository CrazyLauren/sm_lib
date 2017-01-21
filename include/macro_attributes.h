/*
 * macro_attributes.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 25.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef MACRO_ATTRIBUTES_DADDFFDFD2342_H_
#define MACRO_ATTRIBUTES_DADDFFDFD2342_H_

#if  defined( _WIN32 )  && defined(_MSC_VER)&& !defined(SM_SOCKET_STATIC)
#   ifdef SM_SOCKET_EXPORTS
#       define SHARE_EXPORT __declspec(dllexport)
#   else
#       define SHARE_EXPORT __declspec(dllimport)
#   endif
#else
#       define SHARE_EXPORT
#       define SHARE_TEMPLATE_EXPORT
#endif

# if (defined __GNUC__ && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 0)) )||defined(__QNX__)
// __attribute__((deprecated)) is supported by GCC 3.1.
#  define SHARED_DEPRECATED_STRUCT(...) __VA_ARGS__ __attribute__((deprecated))
#  define SHARED_DEPRECATED_F(...)  __attribute__((deprecated)) __VA_ARGS__
#  define SHARED_DEPRECATED_F2  __attribute__((deprecated))
# elif defined _MSC_VER && _MSC_VER >= 1300
// __declspec(deprecated) is supported by MSVC 7.0 .
#  define SHARED_DEPRECATED_STRUCT(...) __declspec(deprecated) __VA_ARGS__
#  define SHARED_DEPRECATED_F(...) __declspec(deprecated) __VA_ARGS__
#  define SHARED_DEPRECATED_F2 __declspec(deprecated) 
# else
#  warning "The packed deprecated is not defined"
#  define SHARED_DEPRECATED_STRUCT (...) __VA_ARGS__
# endif

//<windef.h>
#if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__) || defined(__LCC__)
#	define SHARED_PACKED( ... ) __pragma(pack(push,1) ) __VA_ARGS__ __pragma( pack(pop) )
#elif defined( __GNUC__ ) ||defined(__QNX__)
#	define SHARED_PACKED(...)  __VA_ARGS__  __attribute__((packed))
#else
# 	warning "The packed attribute is not defined"
#	define SHARED_PACKED ( ... ) __VA_ARGS__
#endif

#endif /* MACRO_ATTRIBUTES_DADDFFDFD2342_H_ */
