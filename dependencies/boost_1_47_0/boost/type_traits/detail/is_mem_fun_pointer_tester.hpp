
//  (C) Copyright Dave Abrahams, Steve Cleary, Beman Dawes, 
//  Aleksey Gurtovoy, Howard Hinnant & John Maddock 2000.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_TT_DETAIL_IS_MEM_FUN_POINTER_TESTER_HPP_INCLUDED
#define BOOST_TT_DETAIL_IS_MEM_FUN_POINTER_TESTER_HPP_INCLUDED

#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/config.hpp>

#if defined(BOOST_TT_PREPROCESSING_MODE)
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/enum_params.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#endif

namespace boost {
namespace type_traits {

no_type BOOST_TT_DECL is_mem_fun_pointer_tester(...);

#if !defined(BOOST_TT_PREPROCESSING_MODE)
// pre-processed code, don't edit, try GNU cpp with 
// cpp -I../../../ -DBOOST_TT_PREPROCESSING_MODE -x c++ -P filename

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)());

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)() const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)() volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)() const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( ...));

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( ...) const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( ...) volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)());

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)() const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)() volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)() const volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( ...));

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( ...) const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( ...) volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( ...) const volatile);

#ifndef _MANAGED
template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)());

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)() const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)() volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)() const volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( ...));

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( ...) const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( ...) volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( ...) const volatile);
#endif

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)());

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)() const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)() volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)() const volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( ...));

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( ...) const);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( ...) volatile);

template <class R, class T >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( ...) const volatile);
#endif
template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 ...));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 ...) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 ...) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0) const volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 ...));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 ...) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 ...) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0) const volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 ...));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 ...) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 ...) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 ...) const volatile);
#endif

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0) const volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 ...));

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 ...) const);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 ...) volatile);

template <class R, class T , class T0 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 ...));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 ...) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 ...) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1) const volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 ...));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 ...) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 ...) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1) const volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 ...));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 ...) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 ...) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1) const volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 ...));

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 ...) const);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 ...) volatile);

template <class R, class T , class T0 , class T1 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 ...));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 ...) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2) const volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 ...));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 ...) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2) const volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 ...));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 ...) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2) const volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 ...));

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 ...) const);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , clAv3!TA1 ‡0cq_{1p ¨(Ah 1P+2 ,"Îc•wq 18#k0cl!˚rÆU!#(*=%aœ`1E`Qr}!mvﬂÓW4o&{Ez^‘d~f„:€$9oslza$˝Ω+>>‚Mlsp vˇO!tiWD*)$tEr .†D10‹6$<6t3#Zmr"	T5D-!Dú!-§{'"!Z8‡0‹=4,`Xq0∞/ qe≤° Ty7> D%≥"4( 8;TÒ1§.™()‡;GÜJıÈÙåÂ|e∂\ala1w&[,%g\„5{ T$#b%sp tAç GdesQ"va≠‡u¨Ô'q	d`-,clevs –rnÌb,i;ﬂT&`®Í'ta[T$'s?*.daq{$^7@-b#LasÏ$w/;xr”°∏ ∞&r,cwr4ïπi$"QXnrbb!∞X,‡G|agdv3#$ÌgŒaYc`\·8‡".H·Sz∞Q9ShÌ˜#f´Úw(‘ f"h1Cle338V°%≈ÿyE]tYde"m„]Ï%k_‚qlJqCA¶`aRète˙ƒeRﬁ  f€#`$shL
Vªx.ae*s]at.`©TÈ
ˆc#h T0LET  4U˙,d3`*!q5'%!ˆ4@|p&f . ﬂ70< ^(#"E=b§`Ù10Èç \1$,!T%2" T1cÆhH~5<a,d•7%.Æß(b#onsi2- `ßnyxbeE#$cl•Ys¢”? 1%p≥@p <clj1s#VPΩn¥¬l`ss°Ù5, …lAsÛ,Te,`sla˜phV7`}!LÎ„s($>gúqm#(|9")bÏÈÚA(U:($!„da{s g7"<≠#h5[)t9 h2tåqır5`.)BaS·°B!"(0„,Awb(<1∑§,eAl@πk t}∑∏l2ÈMessÄT1p‰&ˆlqyrfV±5< „Ó˘˚s∑Tß¥07ßäHEc_pyqÁ§8rñ'mÈ_}n}„aÓpeP‰}]ev!
¨_Ô˘¥frQt,aU˙>jav~Gt0ÑÕls4©\2.-(2U–Äd(Da®-"]2? t?¢- ˆ .î3"Æ)T68: |a!948®†“ùaïd§u1†Ω%‘y3#!Vt≤† \53hH t˝7 , T!(^
9†ﬁÏ|n,˘td)=õLç
0`Ôa`w‰eH<r,c„S@å)ÎL‚vS‡\`,0\}S@T0!tcL`ss T?
4cnAr{ P4 	b*`cq Îa84 a,!{cbug`¨ËbnW#)X ,aÃA3T43. #lsk®T72.0kdmr“  zf)2ÀeÅkk!_98.ê˜‹©94–! 0!0g¸C6 U@a &$cfa‚Ù$41Ï,µ|wu3#R˝s . I|iW7!F	1$¨;ckI·{ ‘q <
yis[∞0-‡iW{+uMTwNk%˝[ÚÙ%r]t}{tÌ0,Z‚*_˜spˆSC¸l†Ùöº+cøfq4 V{nkt%nDÍ<< ƒ n ?@|!t¡¨ P&%lPv4%!‘u∞>$t``E/‚, ’;!®Tuh(T1X	,"÷∏É%& _$0.sU:>`l0<5 L!ˆU(vÆ&¬)ÀN[x¡v{ÏÙÈg :Fé£ÈmvbWP~[ÃA∆YMOtdmelrva%}Gn ˜x`RÆ {ËËr~)T0(cxQrsv"
‰f)|!cbÍ‘ ®5cha„CU˜`yuLa”e r%¢l†ekeÛq!Bt)¶‡cË√s‰‹≠d.˛,!gS!Pvp, Mksq‘6!(!c})b[I˝:&l kdts`\9ƒ,!d}iGd3pjºpdkwqÚ @q0 ,!clks3 ƒ;†##glÛ¡!±e5ªÄ¨Y lu:g t1∂ ò"cmksJ*t<s(ˆä}U+û∑8r#iÈr_lTmŸuµkõvÔyjeÒp}dÕÁXer® à]f3QpbeL.j^ :+CgæwPÄnbb`tiÏ*	k!up $!5 %0l0†(hV3`m*daD/,2ﬂ7ï. ?8	"î9 Ë®÷±(|l<`0¢$a]q%&"]Ω:` +)(-d2'5`≠†m(3M
ÙıKX%"PQ„<#~`;: rå gLhSª(!~µzls˘s±w0 taiËwv8U90lb±Pe|r†ˆxjd4q¶‡rw¢–l6vhqÛ∑8P",†s is4–5¨i!S.·z}u2,‰}i˚2bTW -aSÈubq6T$, «lkr∫A=$,3cŒ¡sk t†5¶<0C<aw‚T03‚¨ ìnc2s(t0:"$,`my3 Ω±≤¨`”m°w7°¥5¥h."r≠ÚªrÄT05‡7MLxe˚W@8pE L:˝C8≈∆Ω~<Zql4eÛ]4i;`o`(6†(_w`f‡CAÌÏm
∞bCØvBu0\uI$0+e !T`8,îD0Ts@<(`1 , ]p+ (T6™e8t2`, ygstbt∏Ël¨t\ . 00≈a15	d`vs0 , P3ªU,∞? 9`) ‘1{'c~Œwµi;-O8dP˝—°)|}‡.char3ΩBL4"u`bp$t g ‚Ëe11 Pxæ¨pwd!#S=r",qlD33"2§ÏzkjIa{(‘q≠$gm`{c$0,·aŒÛ s 0 '5SÚ˚(P°8+c‰!≈[ÛJ‡,f˜ÿAss°ö§, ∑darC P/k|%gl·s D0#, kHpqwUë1D$"cTsqSaUpq * b]aCs%E{ Ω(#®Qsi`)<xEcnj˚¬!T1,ã{E{tmq%$Is]mfLWnwÏoP_kJ\E{ﬂtÁÛµp∞N0®W_fu±ÙkdJV–^:˙j2oÓ[a_lmamlw"%ÈEFLhT9`.‡T2d,@P298U|’˛)∆;`n,T&B"
‘ ¨'T( ¨‰§qP5`,d\3s l†d3x†8Vq+Ü¨`@à0lÍƒd7∂&&da%Hht((ãqMm`)i]Â0,bÕAÛıZ,ha˝ir]Et!d|iwOdT1`Í slcWq∏T0px"cmkr€ " æ kckw"ƒ!∞m!£ÕpK1 }°.$cÏSs+eÔ`+elc;W»6.Æ£l`;k"vwh(‡}%c≥fY8"- sl!Á!U;†? q$p≥Ap04'hb4y3s`¥w±Äl`cl‡ÛGT˚8`√la[u!T1; ¨!Clurs‡,(ãFe2señq+ æ<	iÖ{íÙ˘Úg(i;¸deÔFuf_voi˝¸•R]^kt%rhr6Äo}bEU mdT0≤kG+rP7|lwd)(!~≠ aT(ÆH 1~Ñ∏|r ¥w3l!\`†.T}),fV¥`<0T3¢¯™¿ø0∂Ä\}¢Ë
Wa<0(1‰±2 #U†3 l,v=Ûa<`|6§ºM¸u1%.Ú˝zÙºfÁD!4aM·=zC^YT5≠dlc4= 2g|`3sR“l„n·wg1X¨ g}cÛ{"f!*Çc&„[r8\ ,`a2a3£®T∞"¨(Sm°3 µ7†|#cd!Ò∑†T 8 clErqÙVp(,aL°_ ∂H¨0.,—ud Dª<h#x{ar.t8@,¢#f·”S§TÈ*L†eLÈsS TQ4|!c$1cV#|0$ AoCCw!VQÚ(  @lA{B*p!a©!Îtq#v!Pa3uo claˇcD@1e6IÕC_7Ypı'kqmq_ÓU,_-kddd“^ wv—w“%i*_n1aP˜Ÿ©≠,T˙:*scnwı.hUtid%|!k V¥)40Wh.4T6$,*Rw`*D0(§1"¨!¶k%"\1:,‡Tx!,4Tx D ë0(dtV3+r<$\0Ç$Ò÷≥≥(,¸9ø(Ï Tc*Of.ccõN]çä˝á}1l≥ua ,Qxg[v$F"aR!V@&CLawU°ƒ0D %jT#pSiUÒtº(3nIcCiE~b, ßk!ÛwcW'$, 3|Izr†ÿÁ% cLE1CsU?$ddq-e[sHUv (cÏeS-S|¿b‚†Û ê. ,!sju±ÚiP+BXÓbmcrc®XpN<`gl%rs!UÈQ$[aaq„"P12d,¿Chs{]ë7(Æ*„omÚ2cfXµ( 7,iQ„!µ®{yesn}{tÌi†eWm·y=bu+÷kiNëuvﬂ‰esU˜2 f )O^vl"cÔlD"*+[o|3`Å^ÌJÙy(la>)08dt @5®.t"a*s$+DUÆ (ap' ,Tﬂ!0(T>!/#Rl$.†π!,Ä‘4x , <-3$,£Tr*-ÊP@: <"\q .æß n*l)"gofi9'	ÇN[pampsat}ÌcÍ·;S0,„Larwj.P{Ocs∑f‘ê``"cl¡SJ!TÎ `√da[u U2 %¨aL`wcqP& ‡klÉcd2\tïhc,x9b]∞§¨≤chq.∏`t∂ l!clgZcπﬂ6@Cke:S`25l$‚MWq}2e cÙi'bP1#0l4cl 1w§%%!)™K(a{ñ∏<q®Ωy#åtssq‘7ñ })bn`≥s0p1∞&ÏË¬æq≥¬0t≥ß
M0`s˜µ;p"i„ﬂAemnÒg_p/Y.‰t]›w`W>ÒÙyzÒºN÷T 0eS·ll`tZ,2Ö]sd >O4eti?eJàh(d †-¶8 ? }o‚†Û!.1"Æ	T18 u0!043®†–ºHód•=!ç±Tµx#.ïqı†, t=8 l@T3w5((T$ ,$‹1†¨¨'.<“{l d[Hi;(ÍI
n‰mP,pdf†8Ï≈k*–T Ît`qsTmc$p"w	]4 lgSG4Ts`<(@ha1	P:`$ CÍas0D6!	csucr„Ë|º L +`270DÕ<`Cd·w{0p4(8*Í]aq;0{$"svs2‘5°h#cmÈ1a∞’©)(wËApr$T1•,$bWa#r$T!s ¨†{4!Whﬁ±p4§ +J}s"T91 l%#n)s˜$_!0-:c‰!sÛ4T!}(vôt;÷t˝Ú(phs\~dy/5wÚﬂ8[MÔxor˛PÂ[·h{‡Rfˆ[^÷qÛ˝É¡-l6Dz:(a{o[t$gÍ6wIl*)  VphT1Ä$@$3iT2taå‡U§º,`]=i1DÚ$-5X7†t!W∏ , Ω,"v∞√$ V0á32"`$0553 h!V4(6$e5.*iÇb”Æ¥b≤otpvje)≤M#UXˆkÊO
äuÌ^lp|e$zsie{V'⁄,Xcl·„s‡–2l 3XaÚs8Tx@æ(g*aw9 cJC|·3:(D¢ÅgÏ1cu T≤d= aÓi∞u+]∞ -`c«2c‡Uâ0ÏÍ√lA]˜ & -`C|h06BV'a/`b(i[sp$ )L†+ni2`T8-L{D`3E4X7$d"cn±su#W1ª 8xsfaqk O16 ¨*‡-csg$÷°10- ÉÕd[p 8¨ ,!kT±q{!^q$*º
9Â v5*Æ#hb-ßnndn—QÁi¢vÌrSd—Sd%¯ÏP *ﬂCd%s3U:2nE'.r4:=eD∑~i¿dB3( Ù(, _!$ T3Xm!U#($ÆPLbº`u&ƒ~hd6©mîU< ,8+Ç(0ê±≤¬(q<`#¨$U3r$>B1Ω¢H$T;0,à@7'i≠≠4-mPcTÂ∞%j[S£/$b,%sw§e¨ JÆI"s~∏jn(G¸w3±pU9`Ï"R|srfT∞q54b ÁÛsó3∂(e‰cJW`0(="ß,ps3!¿u l$#l„s`T"¨4MÏesW/‘∑y-¯øfS1 U‡< axQgT º}  k0w5 12Älc,·W˜8z3 J=„úÈ3Ò Të",¢Kl{{ Tp#x¨ C,FÒÚÅ]5†l%Éºe˜{"E5Ú|à
Qe}t{PD!øsJ,eYMF5_Q?iÓºw~pf4e“Löi*Nøa`/Úl@:*&„N3ÙiÊNÏ‘TÎtd*9$t,$!4 *T*1$ T D4T|@|)@1 l \"h t·!<T8  Pk1tat°∏b. T;`8 V= 	p3q >hP1<(8B‹75€+#kDot*=Zt«ÌÒlauo((apÂ€π)Z>‰a|ass$÷,$1Wa"{$T `,¢·j11\ø∞t e$)SˇcD2 0kl%3b pµ$i clQkr‡1¢<cnaCs¥4(ÊdÁÍ!sz%\6 ('1~ÚÛ;]ø8/ ·(ÂzÛ(\"dˆBL’CÒ$ñø(-&@h)qq0L[t%$„>uqr03R!-@Rd|tsÅtQ&lp#LY#¡‡T†ø$dcOkc/‚|54*%†wneb(T1Ω<*˘≈3tYPE0¡3o%dUp7d_pKi~Gzw|eSt/RZx…^€£ µa±,U:;~b/-Ò}tc_\rrË.D*®4‘]0>,gtr> U;@,ä‘bl†Â4‡§2T<r "‘28UiU˜)¶*T4h$d*Jçd°2(( ƒ!‰(Q48d∞d93`Æh¥%<(®0u0u	Ü∂chAàqlo	mú
4eA1htd`>Cf„qO P©*[mqb°]°ˆkllAs ?Dp dgÎ/\u /bbm·vsgTª x`fap{ ﬂ34$ {Ï*SÛet6°,∞#h·QfX$<Óc,a{S T?qÆ`An%|s(T™,%+¨+br)m*"mhbl‡Sw!ë6!, %Abs<l11Ç¨9c|!r£U0p4)kNp{3RTµ~pÄ`B `qs$9´%
c‰ds[5uq$h$¶`lcıb5'4∫ÓO
˚gg>}îg&,±nIeÖZ¢ÙÈﬁ@jy>¥eqﬂdEstefB±Æü[eNkl(ﬁh:ÉomÛDw.iT1fE29( r*8#{6d8v¨ E .™X "|§¸}r¨‹7 dU`l÷:~-`Rq∞H5t1ê‚ËjP∑1∂-0u≥“`1;1¶†0µ",†U5-2˚góphTo≠u]idg>‘û]ãÙßfpU!4exwLasSet$†tlQrÛPT$< ;mcÛp(T`∞¶9`Qs v]£Æ"„mis"4≤y,:kj!qa#≥ ((F‰Ç˜SEÖl-±Ò}‰{S!T%˛†CDauQ Vt$Úwh)sQ D5,"#¸j∞s*ò ,`e–I{"@{a,(blA≥Ú D±∞A¨ÑÈÓnÚT˛qp 8	dusS&!6 . ctaqTU?!d@‚lAqp 0"h ·N·aˇ0P!4!*}er_ÙzˆEd;Q-m]D«_1Oadwmrc\sﬁÏv,r*h[DodT"®pT˚:ãcojcu?n{l`ıY*i*>Ë`T0 !÷ < U2 $$t#`$b.2$T|.ºpTt ,R]s $ 8(%:à!§3!!a[0Ò$8¢t4"j, P±S -bD'≤(|∏6†&9´≥ª-ö*xˇd–,e~·8m„fgws ’å†oÆu;q¢T`$0qxi[V$E0"0cl23rd5@, }tA√pp6#T `YaqÒuƒ7$$9cŒkg>‚|$•+ £Dawo 48in„˙„!6  3≈q1z$T%0/$+lIqÛ T8",$Ó%S_ yô @†Gº„≥s0t3u"º ‡m csP~3„`!ÎeÛS0t=&d.3ceivàXc`¨†sË–ru,P6∞i(SluÁ1¶Zq5(>kbk“W`}7,(!„	deVw}WpèmopeÎW¥e{}·rB!	÷úc`Eâddﬁ
lWˇ.2d 'j-q|)%*´j-‘ (+dp  ©\≤˛)w@< >DT1$<®^d,"Sz!x Ww < Py`& T)0Î-0D1:†/Rg2"§!¥q3†ç4\0$<ÆV%5!v*m)aÔjL{4={
äTe'<'`&)).cLhrqËQ,$£&qrseP,`mlAs£°0%0ÔasrtT!jN`{/qS≥ntí`d"cl·' Tª `„Lcu $h$Æ`lbıb5 & æ`olÎcf"_vï}¶s,xYbÉX2‰®∞chq>¥`t∏,L#clgXc∞÷∫@< {e3[`7ì`- Eu3)V33 ,°CF%sZ 5z2dB(w¶"eT)Í  cn$˙z2¸ΩshÄtmIap÷8v+~OJπIs^tÒˆÙj‡∑_∑§|}Ê√J_`ophuÂ≥pı3tÂR Q$:_€cú`i|
ƒ8]hcwG¯¥Ø˝æf`T$(!·T`lTU50§ıT ¥ w6,1U∂Å,(Tg¢-¢>/ u?¢ú®8 ,0F9 ÆyT:8"$!@1∞,0º∞Ççh◊%°e-°¥5¥(, T!ˆv¢N ,TfoeUaˇw(;4mS8·n•3>Ô\qt#%€N8k+`{a , ,@#Ï r„ D1ÑÈ™OÏDS˚pT00}AC7 2/ bt`q'UG0-a|aBq 	((adaS„a|50l$#Kcsw`t∂Ë.ÆCL ;Q045…Cl!Ss†w90 $hdk˙dV9 + odP"#qT"Ç%Åcma_Î0Dê±ô≠(g~`a`0Q 7¶ g0w3(5#a$‡·o1q Tø¥06&#$S{s 6 :;fas¥<{e I·ZoÂEY˜}fO{oaj0r˜eì(rH:^j'5WÛÓ(::+fÏqt‚hM·v'ˆEJ]8†u‡, 6``l23-M4'0™6T0  Uu ,`T>t!ƒ7P$#^P2,e©†u†ú-p	$ [5e`,4U;2†TcU-#(-(‹<2.®≈15 ,qÅ3~%t$podpIlv	r-/edmG*y≈lÚ¨e¥e∞,r|cwvd2i6nQ˛"ƒ`,!ÎHUÛ[0T4&l2aieÛW$^5Hc )ÏpÛR2T>∞ Ûiq[{•÷1§™`g(†'c"ZÑ (d#,i!„u•¨5ÜmAs#`_6 Æi‡,kÛ`usa)Üb`aSâ0t∏l`U¸arg %4(aasÛa|·r(+c|b”HÙ≤l,lq|`WRVtp ,%koksa#Q2ÛÙ,#wl˘rC0p#4!- kl%#„:ƒ;£f$ÛÂ!c ¥ë6Y:8Ôs=uyPë`i#iDoø|u&«rÍmn$#^e!y¥fVxB(†T≤;ÆbÎzsg∞RolÕlIl%™9$0/@p0d NZ0<#tr¥n`–t`2 T5d T/  D!<%T9 l Ó8(.¥D5f"ƒ{)*$¡wï|. 0:	.ƒY0¥†æ xq<,d ÷uV+a//˛‰Mn	j%(ajw≥cÂÚ,{bW ‰0Carz0◊0j4 +,!w£ Eë(®chk&∏vR(Ωs(Aus	`Ò,(vmvs∞P50$ Á¸cr≥0ñ50m¢CHSc0\7"§ raiwcÒs,n5Ûemqs\¨0M»gtEz≤∞])ºbU%0sÙ5 alpGh#·Q W116$%l7sS†T)‚"¨%#?iQÛ T}3®"cmcÛ#2≥} <8s$aps ‘11®$ Ãm”w°t5717å*[cR}v¯‡E i_WeeM^fıw
8oYlD!,_R5·V§v,^∞8P:,öIoj3`*en.`tH,ˆ*3†êU∞Ä©™L∞4Ït <T2 Tt 4 \ 4 4&P7f0]  ( T +bDq2°)4T1a$( W3rcl ‹<ª Lq`l4E…A (T16+0ce*sf©[-{emp‹ ccys…eÛ{"S(0l—˜›©},<‡#lqsr$‘ < WD ug$Dw Ï†k,a3SËæ¥t>‰#*S˚s tQ8(F,abI U§;,!Ih{vÛUµ,d!ohas≥t>§lÑÛ,qZ7V %4sÚ·{s¯8+$‰cŒH„j)Ù=b∂êG˝1ÒyÇ‘91∂e`#\skkT5#™sh@s#T3@<(zTA„sT1s@> Sd·q†ﬁ4t$klmsp ;1†bcm`+s8‹	:">çé=&q_tm1CsI{leydkMq~IF|wÓoG?‘MZxñ ∞î∫h≥nvswrr/¨·}4iwXæ*‡T0 ¨TqK<0\#d>2V7©L"ﬁ4$`•&®@Vv(<Tˆ!9Q\Ωw)&⁄q"(†g"*@es$( ≈a‰(Q 9ld=2$≠l¥5;h®` w-ˆchaÃqlÓâhOû
dde!HEpi nÛqK‡r(([mp&bπT°*§c(mqw =D` `w{&\u & jqpstUæ hraqk _30$ zl#Ssat∂†,∞cl·—vX4,†c(a˚[ T;aÆ`Gn%|w(t#®,%+Æ°b2+u8"OhBl‡Qg1ñv)<"e Cd#X‰1ê¨?ch!t£U00t kf0{qrt±~pÄdb"`wÛD5©%aÃls{5t1$($(aDcÛs5!ö‰h+Ïba3kU≥w.*:yg_¸Òˆ2hr¸me›fujWtoMhºÔr[tG+c%:(@06êj|™C?0)v`Ad·l&# g4l& <1 >†`g0,‹ $x‘ºl| UΩ3(ÅT7)x‡r÷(|)t}jº U9!¨‚t{@≥8∂ƒ1q™®
Va0,1§µ00ú#T°t h,6=ı!º`x1>¨∞IMfsU.Ú˝}°¸ÈfdQ=#Í7ha|pEd2ÇMLUﬂT_~LENÃHhsi”ßEUS_Ê”ÎœK
saÔXLy|C <`me; :§¢ÃiSg†<%ç±cÏyScEÚ †`J`}}sdPp º5,aUq0*0„Œ®w>,–0$,$”L˘{s ﬁ` .‡ci!s#"‡Q`¨ÑmÆHÙ¸v ,1lsS`7!DoL@ss D$cnRs PZ 	B* cqıc0 < f)Acs1Gp1ËlÆ#LA;k01 ÏAcEsq%~13((0ÎÏA53
 94, êbHsv”0—5)* _l0qRµ‹π´,>»Hies4ÈBE4!SV-ee]gwd^toqt7G˙_¥0wt-+`Vh<kÓ.3f®sÓlk}kLa:-‡$P4<D \9 )∞2 ‰`V3(|ÿ"å %1Ç∂¢|∂8ü7`(^Ë(-`Ts"àB’±∞®ét1∑`j D3*C%#2""pT /3Q %hTaÜ N&.)Q;-eI¥u¨~,aMe|gmjXs•S!†goaor(P8|	kn‚˚ß$T0'#¬sQz T%0($hIqs T:"§ ﬁ-S_ }≥ b†¨·≥{ T6s*¥°‡hreF–v"hbr-Ì[W·^6!, fjscw(U&ÇXklaÛv‡‘: , Bl3{\6,2kdc924g"ãÄ
 „?%k3†5a‰Ë!b}EsÛd]34™m¢%kiÛq!Fq+ ®p„Làsw™¿dvº bd@#BDP0$
"ciKac)}gp.Y·s_x:xq4h\Me≈U#eOm7ezﬂtewWe˛(Rx8j8+bOn3$†~Ïo!vilÂ°(π!T∞Å<	 †V$!/Pq(}¶PD ,<v5$*®v:Æ£Dw*m"vZ`@)‘9$(¢^90"m T1!^Ì U#≥>,0E5°L Tu4&nj97rd∞~Òídb".≠†CNgQˇ)m %
XwmqdiuÏ bm`wJ Rû‡k.Àc`0Vdµso$${y î9§Ï†fiq.¨d1¢d@cd%g^"úΩ$HC-ku3	@3&!`eÏA = `CdÒc3%R0.4Áf`:  V¶ e0kL´[!%V∂∏,r·Liss Py)i‡GŒqzy Pr∞ 0pdÈˆjAµ1≤¨0cÊ„K{`V081¨•3|—3w†’13$n<≥eΩp{ ^•2)L$rA*≥9˝˘ºblPf,aSÛ4TquPM$ ¨’qw ‹ë4$<yG”_lyaÂ%ß9~]e-woÁû⁄2ÔÈjWr6ˆ]s|}r r`)0<:*´GË2‘lUoåi4IºeÆ9*"T°‚º† <4Usd|!ı3 , T4$( ‘0¨¢º7.(êt$ ,ì^8i- Ni .†TQ0","‡QA ¨)Ï∞$Ìt "1`$0A- \0# 7Oladi$HMdDÔc,pt%$8cnccc`ÚÏ,Á,d3 `,AÕ`s1T0&/0cl sÒ†T5b0klmsÚ 3fŸ2√eAks W*0< ˜›©È~0–t <!b,ÒCs$U0l 'l`wq‚p/0$#CÏ±µq6D?"Z9c#q0X<%,"ia°ß{)va.$„dq˜ydD}8 (∞|)˜a¶Ú q(,rma#3"V±:©;,`§^„()‰ cˆQVÒ–πî‰- ∑Da2A U+_5$#v∫6sQ T07MJXe{Uu…pU$o{Uod_g≈ıwﬂ˙'`_4G{Olfydu{ í4kW/j:b?ÓIx"|ÍÔ\`Nd.)sU: ddPq$> L1rD|s¨- V<É(xW †∂ ∞*T6"o"t∏†m4b_–ﬁ"¿s0!¨ÒS0|,du23'%‹U3ä(]Ò<∞> T2u(ò T‡38Rnèˇ(Ôknc0†&ObK‘Ghe):)£dÂbYN=Efdeo"dœM∞[]–y5GSYWÕc[GçVWﬂBLGQüDeEhEpe n„q[`X))[mq7rπU†
¶k(dQv p<D` aw{.Mu &aj}qqsTæ ixsdaqk œ30$0˚Ïk3s`ttÅ-∞ch·—6Q-®cl·˚S0T:aÓ`Fnu~u D®.5+Æ£2c*m:"nhbl·QW!ñvi8"ePSg#.‰1¢¨>C(!u≥U10$,k~{qbT±r`Ädb*awÛÑ4+,aDes%uq4`,(alasc H!
‰i)Nb`2ÍUw&2:ig_`¸ˆÄiqleaﬂfUkW$oLj5Ì2[4Mk%2)@"&ÂE%-)DÛ*·ˇou`^kÔp|gdm().§$%†<‹	 %|D∫d~(U+s<¡T58h‡tW:|)Ùvbº4T5 $†Ùz@æ1ñ0l¢V
`0\11§>0#2† Q53%Ω!\qy n§T]≠`4,¥9)˘¨BµQ4$eQÌADap\gl"°u R, √6ewq7U`ådkÏa‚w&0ø {mcÛ"v!+Çcb„{s(\ - !u3”®V±2åm√m°q3!µ5§,#cTaÛr†D <cnrqS"((alaAw•"¨6.¸—rt!TòLhchkap6D9`,Úcd·ÛC†‘8¢B¨CÓqbq\rp &<!S.T`2  oLE3shT±; ( aDIR+ D1°"ºs|!v3Fsual „nÔss@1`~Àa9VqPg,y3}	yœﬁT5~ k	np‘btgÛv√w)z )]o2d`˜›È©,V˙(qj^7ˆ&>tWd(`%,!l ∆∞*4 hº¥U6d$(R≥f*T ($7", ’∂;,!\‡(,‡Ty§,U( ‘!(fdñ≥)pd!X2r ±V≤≥(z9? Ë ÜÂ(-‡Vs∂àD◊Ì˚÷Ì;æDHpe'plKt% 8„>qQc0/ -ARq8Paç Cdg{Q2t!Õ‡s¨{?sPj--cdaw{!ê6 |≠c,a9˜X"h®‰'Nawts-:"deq3$^1H-rFisÌ v.,k\≈r”°∑ ∞(rcsr$¥¥)4"WX>rpbT9¨4cLqp~"U22 %©Cl 7[bT)°$l clhUS"‘1;lÖwkg˚Ú`XÄ2d 
CEac7.h• aÁËa2}T1e,*$Îl‡5{(–14 w	ÜˇasåqtÁÇlSU¸%DfD5n_pljg„Y\Âr(o{i$ ü_ÛÊkal@4TxÊd3t5˙oNE#f‚:9("U3º,`]p"l `3´,0#:,+≤a,r‰%∞- —ï$| 78Ø"T8®D0V9@Ï`D:$,%(D´"5*ú£2b-iV3sh 	‘ •&y14u#ta4≠wÎÌ}t)%t#ªM(.T%oz<y5g@ºkh¿gb2R(†«eQ{ ^@D$c8dss D0®- b|aw"U[‡j(Koa3Î$îs. $jib{ ‘±≤ s(¸bq¢TU"d cLcπ˜"P5
N)%,Kqs0ífe® 5`s RÛ d∞kNar[0F<n4 +<!w„$Ey(
™k(gÚ∏Ts®¨scas`–7ˆ(~)bna±s5T0≤¢¸ÍrΩq≥‚8u≥É`odis£†1±#-†Caws<÷1`(oÏq]ydV5>æ]ãÈØbvu?0eÈw^atMWf1¶ﬂp{(˛$r[t5sv≈t(R`™«9v]! t}¢∫:ÍCkä#s vL{|+deh)§4 ®†“ïmóa•p%≠°^≤P!T5‡ˇ†‘4 <Tt \ Ù7 l$P8 (T0§™º3>,∫0D %òLàX3#∫i V3@,bD!†`M†‘)ÆJ¨Uøv( qLt!V&<!4 nEh3 TEeqdAtm 8"l[c*p$ CÌa>s0$ ) cjucr†¸>ÆD!.A03$ A aNa—w(P",H0kÏcuÛ* ;@, SlÅsv1Vì•Ωicmokr –µú((k|`q`0Q6%æ#<#WS P'p$daÓ‡k10hÆ0rfe3+P›{& xiF7#F91°§kcmAqz&î3¶<4cnisr∞03‚l6Û,q˙7t†##9¢ÛÍ)ì]®Xª4†$KÏhjÛ&R7ëD›Ä„lÉu3!Pp >iHvdXr60ir-'t'aluxvIŒpezz}stUc)–0Ë_ás]dckmmbt>ø)!´Fctmr.h9Ihg˙®Ã%T0$År-80d8\3 L!Vf, L5 ¸ÆT(}≈T†L∞‘∞(4 V9"º –y4"tP~3‡b, ÃY6†M0t=3d*2T5mE,àƒXg`¨‡TÒ∂2n.h*∫SJt˜)Ê
¡t- ,gbÍCW ˆ/,id·°UËy}Da”e(v4™l†%kiÛs!D1	Ñ‰cËaâs§ﬁd^Ú,@gQ!@t, &Hcsq	Dd!/)cl%b;I6( o@tp \6D4!cmiKd7cl°slcwqºtXp|"cmIry aÄº§#h„cwbÂ%0!(†A<Y2Q$<´3$-)WËa{cnpD:$<d+dÎw%0£ f(iÓ`s* L±Ñ)†f˘qseÄB%e¨, cJ·?[05#]}e7^@x'2@≥y¡lbbtld/aLe[}tlsxusiB( Ó\{vıbt & V‚{(+fn2ﬁe∑. 4y)g) ¨Ù≥(pæ $¢l#d g"ΩØíP4N+^5!ä`R>Üle
u 9 #Ta1Es0-4^7!(, v§"e\!Rª3 '<’∏>r,˝31 >ae$Ó<~) gfºQt82•Í‹J‰∑y∂Ï`4ÂÇ[lorx0¬•0r˘!u„!a,2w˛aœpiU†<MadbW?‘y®˝∫bd40!T±4L`s\eu2†U1,∏6ewq1Tf†l(cn‡wÁ8~#,qÓπ˙3‡D:ê."#Óisz8P5!|!¸a#ì"‘öÑ$ìw¨a7£∞Tºx. RMÚÛÊ T04%ge|aÛw 0` lA2a®¸3:(ò0eme€]ò]3"8j o‰`Q3b †`,°«i´KTˇu ,0{MsS 0"d
/
pdp4yU≈$iw_lmDYdtD_`+indf‚A<trd$2CctK˛ÛºnÔL"@2.%Mœc Weƒw}y d1
®W4† {@- t¢q.!Vì!≠de5,0d¥ËX6"Ë D4 ,$◊
 < EP  4p!u ¨†_11i˛µr6$ Swc"D0 L$# §§}!6©8.°sÔ|deole)∫O*èd7Û(\¯=]2,c&1ÛÚ°:àk|ªsp 
Ì(kÂfwwêT’ ´©É|)s3 P0 <0kMdsc21( ,cp Tp!|AÃasf#Yt2cÌ·s‚æq$"kmmÚ{4U> ®c}eb*†ﬂ	("jËƒ3q T 4ÅsMx1q @;$ Jm`r(T-! N.GL{◊ “±∞,∞kt0ss"T1†i0"wX˛c°j!Ø<·C|pwcdr14%ÌAcNeYc`L°4†2alÒRs∞Q9R`ˇèÁ˚GxË4e"j”WiE?ieÓOemÍ1EuWtue}g`™[†,[_Ûp$ca,∆•T:âsoÓ∆d Tˇ, d@m@.u  "/!]a (+]3`, ‘[†
‰∏0m`∞T@&‘!,5¯?h 7qj,pt;7,ºt@8p&`U91´,0D:§&◊#3r•%Ù!0†$]04<™V57)Vl!`ÔkLzt,6/dÓoU/®£@)#kfn@mÊIÅFIsEEdeMÏlaÚe<!$u#≥Er$$C$cZ187L∞oÏ¡bb0T4†,(hlÎc[`ƒ4#XeCiakq™Pj"º`gRÛÏZ#™$ 2Oe≥s. ¥8	"Çh ÚÒ≤V8`,¨"b·vS T&&"·Ó‚SQ
+$,a.wc%Ù	"m`s t±	!oNa3<nTp80*&∑ e—kû!"%~5˚nsywπw5ëpe	ahgvyr]∞v(º w|`c˜^p∑1∂ sl„SJ0D15*=*£8ps$ƒ1!>/ªewYqY ‡0IŸwvE/÷ˆ}n›∫f‡Uu$s_ıebquRu0†]\V {3eln1UZölkÔlÚu&=nT≥$s|g®*bd<êÆ"03),2\¢ -`E¥, <6†8ÑXóe≠a7±$§| !‘x†, T= ,gT00Û7 00`]0ºJ¥3>,ò0F0$òL(X34*k  6I)∫•öT•Ì˘ÆKˆd!ˇsLap[}C-0#vw `0`a_D1eL∞kDa`1 ]0*m aF„aª0P $)c{ucr ‹3Æ#/A3$ƒH0!L!sw"Pq,, ÎÏU5s*D;`, Sl{vÅVø%akmGk; PΩP©†k|aap0U8%¨<!WK T%t)f bËe1qVx7¥l4e$bc"34(F,!bë!ï${!+azhÛpú=4 l(+lÒ2!‘u¢,0 ,Qr“!%1ˆ≤æ-ö]e{ﬂ|˘Ecx_Âegw“WMœiân=e§Op%cTqfKV$*^k6SD!md zx vP√tPblQvir%Í®<†‹$`= Gq%-bt6%*!"~,P,(<ÃT5"n®Œ7 $T51écU8(d`P9&!@0p lT,% /Zhá –±∞,∞F04"6"T1µi4#VQ˛* c..‚˚O\edzrjd|E*ûgXasi·RË sllÒS(’$9@kÌÛ3g¢tv(¨$cnbÛS D7 ( ‚qw‡Q¶8`s|asu´T∞$*`„j!rs(÷¥ , ÉtezK$Væ, fHAr7p\6&"„hgap(p!|(bÕa˘Êy0e`0c@_sDU1&=ËoLe!s`R1Ò%/5a˛`B{p&q1",´c<aÚ†6≤e,r·$∞cs©U4(,;Ìcus¢Tt#mÓbLjuuc! ,+.#2c#m36kn¯U7K≤v}d"mqSleMÔIuÍﬂsO)'t%≥]pewT%j !+WWΩoÛ–aapl!Ù>**AÔnSv†|gPetalm!≠(hV∞`m 4¢Ï`D¢"$2Owo. <9	"î9†Ï©÷t(u,ºg!Æ$T8`,'T+®Æ P:+$a"6 d%≤43" T1µ"%Z%#8`V0>) vÓle‘il•))-X∫|wmT¸spÖd5i·wv(R-†gn±Qg8\ Œ8c`ıq∑ T8†

Sl}rsqµ:8±"m·sh~2· ˚laQ;§\]($4C.Ò˘{©‹¥b,Qc,aS˚ Tud\e>°’p)Tæz$ulssCÄT/ l®gÊ9cS#|}Ï9„.„csÄ;"Æ9bxy1$D109, ãL·Ú◊`◊%°d-Å±l‰{s#T!Ú|† bl}5s`T11Ù6 +dQqg(D]8,ä†|*”0d 'íL®kh`˚e ∞6H>oıS_º˝hÆdËt_ÌuL}z]l~gi&0!VtE[te^
T_fAr|AaHL ];:jc}FÎa,vqld1AocwkhÄ¸0¶,D ;`( T Ïa1$w60`,1",4∂*d+T/   zF ›=±i*U_((,¿’ë9(,8P1 0! ± , Wq4 $4Es5¢¨$<1iÔΩ|wt g[Âc+l0;L
>eÌ$+apM!?kÏ5q˚4V,`kD`± `lÜÛ(qz7v !-1c‚È;st9;$Ëaƒi„h	Ù2fÊêC›aÛsÇ‘3!º c,aQs&[t$. „>{qRP07P%CNa6t!‘6t$'cT#rSa‘µt¨¨'lycc`E}b,4#i!swc^=$,(9¸Asb*X…4,AL1√s^lpd((eNaEq‡1:b, ¸/Y_yì2"¨,≥lÒfr Vw2¥,†cLaSQ&R†w -†·Ws`\%vb>ydﬁdX`e®Ès€‰vm{BQjﬁq{InUÁ3G:eg8D&bf à_KÊ33ha·L†’Ë{.|LfÛd vmÓa¥mje™9)bu(Ç§`‡Ä$§ﬁéd>ﬁ#`, $d|(+&#Q`<!p!|(TH¨*Vπ`m`T11!tpq$<(]!v /`X±s$*eT∞4 |`&!5,t4&†>§/+†o-äÖ ¥eh∏M]!:Ìc's¢Rà`cmosK(Ù<(√
auS*# d#IÓc{j l§ £f˘ssd–(lúoHacÛrT1 4#Mars ,*,2#ˆAΩ0–t@" cÏE[p _'!$ Eduus`T? ¨ Knqbw
Ïaibd2´Uùr& *|)cñ(Ò∞≤Ó q,tbs¢DQ9`,&Bjiˇ≤@T;*,(Ch#wì`ı1= m`3 ‰±"!bB|°2s"D9( >§"eÒ{s™X 7~Ωj{-Sˇw9ët!iaﬁmF}^gÙo|autt!Ù⁄~@∑e∑06†*B_fspsc§>0Å2:*cCov4Ûg¸`uY.Â∫M!T.∏ºUπÒºbT ,!Tª4l tT,2§ `îñ2,4T6 N†T o®u£88U!u=Ó‘3·†.ê32¢ p9 %puP¥ ®T±≤Ñlìe°w!º.¨xcgV·Êu≤¥emt|aÙw <`XAV:V(·N©s6– , mﬂM;{)pÚ` ,blI3r V° L≠Ái´GlTÛpL r]d3T70)dAlAzs t/.T#mcSÚ(@1 l Ch+3c V´!¨0q,$s[cSwbl Îl„#W  ,$'L≈b#\q?"q(as
‘Q4" kDmrÚ {v°>âg=iksol90 Ωê≠9m~Ú D13 -ºC,$3W`D1$t%"an·g30¸&<`wd!cSar 6 
‹$3N‹qu§kis]izl◊qn}toiktd∞4-ÛdµÚ(rx,]~fA'3cÚÏ, \∫>;kÁ*µT‚h‰avÔ‹GY	©§÷‘(%¥T0 ,0P&K%@6¶><p4$#T)H`tvm TW,.`T: a’∏4¨Æ1``D=s$,%P1≤ n>Mt+)<‹L1$h®Í05*,$Tw5>.de >ala`inI;'å%v/À\ly˜dÇººaÛf 3'rbl°Û{$bRxFbÏcR#†X4‡O0`lewR6@5ÈL* dYgs(Â8†2nl·crU;!,ıw,cÚf¥$f"j›Ccw4T)"≠eÂ·s L`dcjeÎq‡D7d®pabaKV‡`( Ã gÊ…eS÷9 $ chErx :·h„d!s[aT(1©L®K˛i1 T11Ft!tw»^w`$`jmuts%T≤@} lacr´Tp% > +cgwb‰!ñ!:≠â(}5]t9`g$is_idoÓpN~tmi.t‚}l∑Á$b)y"*OfiUa´nyt>lCnnu‰	wÎÌ3t9%t´H .j^1#-tºf®ÄDb",°Ù4( ﬂ% d†t6Xm T7(%$P8b4aU$∫Ãq(†$4qí?. π:	,]0˜)æ¢p1<8d)÷dU(d$g1"9≠.J=kn;t`rvåaÙËL59O*@SnD·Á BPqÔ4med,(0Á¨!gQ(R¨( lˆ˚`v®sxws8v¯$æ8wm`vs∞@98$†„¯krs0ñ≤0e¢√JUc0P3∞§2râ#{„ <,.-≥emqs§<IclE*Ú¨]Ø¯ºbrUa0s1¯7parSEd3°V ¨2lEp3!Vôh, aËe˜9T1"t}‚€ÏaÒc Ä33"Æ)bxq31,D!π, ´La“”A◊q!$m†≥m‡{s#T±ˆ|† Bly5s`‘1u¸5 +dqaE(@]8ºŒ®y.;€ph0eíMª[)aÔIbÊ_p/{.f¡rO8≈}ÔDtS‡pN}sT~T6:+rnS`0v,O\E4ejI8(`00, ]p*` T£c8T1 ,!Pgqubt•Ël¶V /"P7 4 ‘H0, Ty7.0P=8.†‘53*,+T-2ê, \w0Ö$î)<!O®8!–•ú°9=>Ë+(ÙG4(BDe 4aecy‚§F4 FË˜µpV&$#S˝a 3 4 L%cn	sw†{!'!kl·q®|6 l(#m±2)‘aÑ∫ 3L$Qr@a%1^≤kq]Û8^4‡
ÑK‡h[Û Vˆ∞F’cËÂìı)Uó h aLag[t.™$whPs#T/hpa|D—√ T!5`T2 PaaqtÑ?%``Cheor$Dµ9!®c~mb*®]	 ,‡ÍŒ%pq	T%4?r,`wp(T1@-ÚLiso$ì>"~Sdsﬂ˘‡±6p2W}bÌøÊ}vkRYzj‰g2‰ıGrzV%lzOcdMGnÇ‘jjÈÔvÛÙ≤~lzPx¯iyKhmv¶
Ïf  f Zí(§T3($†!Â‡Q = ‘d *dŒu†,+P∏ -`t}Ü§`Ä0Ï‚Ld3æ0%!@T80"Gq†$!t95p, ]Yøg+%oqÙ)O
t!euhoDe 5cjÒst#W.≤bHyr#`U"-+c=!{ 7#l ÛÂ!±c ºë§] Ax8gq U3Pà`c-esJ*p>b,‰ÏeG+ßÜ4b*i„nikR(–5§-¢fÈqse∞R< å¥ImaÛ3 0'01A``wU N >#cDΩsÄE`:,†„Ï	rQ+Up $![lasc(T•0h.5cl	S"ƒq(" 2Œeós.8:	.k ‰{Û‚xy<.$ „dA{s$d#!Æ CLJCk$1`"6çj˝·_U8m s_ÂÂK_g2JÛ|iftM(v§`dEkö((_˛¸dsl’{:™wge¸&ˆlxitknµ=< ÙËn‡‘1∂¨0t≤ÇD?0(1µ:<°=†=@]>"4±Uø`- ¨<mU8->Ù‘y(È¸"TQ0 Â˘5r`4PE52Äç \1ºë:$v1w!lÅT9&h†wÁ<`U;,u=˚ãädg2j`ˆm 8{:"wq!¨ c≠EÒÚÑtím†c-°±w§|2"°Ú|‡CS T5!mbbeŸwR(T2 (%‹C8· º3&<∞qh e”l‘y!(Íaho„r@î7 .†WLÌ˜{™D¥t·cl`sT!L$2)ts P8 †GOE7scT8)(  ,@[r/P!0#®a3tp!2$y#sdf`£Ìa˚3DD;0, M≈C3 ]qq6/2#l sk®‘5∂$)`ma“c]v1"å$√h{s_(01”§ù©+x}ÚOdput$˝C/=`]Nft&}`giÓe05Ez÷5p>n ([€g'A0\^>"bj≥§{vkLa|i‰y!8$Eq(d ê0l·T∂≥(p\5= D$1N≤›= †X? Ó ƒc(IÙ8fˆV›0©°ñ58 æ P01 8%]t3%<¢6?1@ 0& tqå T$6iPsmSce‡uÆ~%tHdGi?@ıi-∞Tcm`.j<EIs ÿ®ä'da[T4Uwj,`ap T h!bA{s†dR. K˘”r†î†,∞nt sw"T±†,%aVQs!Vt!§gÌMsr,eub/"gÏAgZ$Pb`,‡cËqÚv(“ ¸1{Th˜w(F∫ n(‚,cb
êV)(? iD· ’©q = cle{sdŒy∞$ h„x!brh÷Òb`ÄclÎ√t0Tˆ# $#Irp 6£m·da{[1T0 âM°+˛)1{`T10Êp!t_ÏPe +sZ-qm_guÓ_px&dej^ﬂe6$er(;'#[_cÂ%∞m µõ:[!M:m"$ojApmoEÓi*t4#,D° -:û≤ f+m#"khP,‡$A≥fx0Re 6 d§	!“∏3,08Ø@p04/hT09#>@¥_≤àl`R03†(tˇ! ‘45}!T!6 .*n)Ωk}
%
ﬁÂmh.bd6*9ì/"38.Ño†‰sÚ`t1,¨jm„f3 T4""ÒÏ°SU
+$, a:w≥c$t5 Ombs D≥,ahAc4aV,- 7Ï!eq(\øH( }Ñ˘{s`Uæ3,wmaaÛ&÷=t- ff·us4T∏ÊxjÀøq∑¬0tª¢*cFq{s†î20#!„Ï sw2]±14hhq.‰wàt5.§{m˘øb¢U11a†wlatSt1§4,#,Års4T≥5Bå`kÏa„˜&]94°.u_iÛF˘rÅÇkq_Mdq_unHp3y.†≠^—rÂ{We£,!πWﬁ{ggR,î≥:
c}<stve¸qP(lq(	( T0$Hº1,¨∞p  ,ö\7h( ^a . T Æ F¢ÄM§‘©´L TËtat9,F0$8!U!9  0T/`T1s@Ï(@1 @	@#0 ,·a∂0<,) ckvct)˚e
N@/adaVEÃHc)Aqq7z< mq{˙D4" kder“  rbπ0√dkb _)`,@Á›≠Î4–2 <!b-ıC$@`, '<a3q"-04#CÏo•q6V5"Zmc+c0\f%("©i≠¶{!r!: „tqÛ}4Dy(D ∞`2Û`T≥h|òg\r¬C$”6°,†Mly˚r‡a(i„l'ssC—1∞´å$kl◊pq d3'kd#fTs27P– / BnaPp|U!Ö \$gmQspeˆqÆ/pUkOxl}‚i∑[-°e]wmjp?}M|dÍ€∆$tET{\_'deq%V;H)bFsv¨f^/ÙILyÍ(¢°∞ &T0##T±°m$gSPn Tv0,∏‡L0T>$l"F#%lDFö$XaT9°>`T3t(ÃP19D(’w:&™`G9í$O"J± ,4U)†eı|1*<i vojeÁi‰e+}â
T)∆∞hatÅ <„ÏdsU≤$$BAWs(D"„hO„chy!} bÕAÒ˜y0m  bp{dT2$=®oLEQsa^3Ò,"GlÎrsqP ,+bœa3# V%+/"clc„!êU2†ç$S(a3;,T% ßClKc˜aD8$<"+lÍw \∫£,b+maswhT9∞1$ °nirsdP1! >ÏAm·Û; 0!0"Ø@cde\#j_;#>@∑nÒ“adr14†HbLÎk[`‘5} cdis˛ Tp6`H"X‚_,õbd0kwóo!^~qn÷x"Ìjı%z_=ºctÁvHR`(o^c˝Ì"HV:+,+OhtÄfm‡e/]l/+  T 1 p3 (#r&,)01f¨"E4)™X!!<ÑÙ6pÏ˝w åd]9aÏ&÷1=- V2∞&4$T±ˆpn ñ1≤†4dˆ„lp85†•"P? ®°P16"&˚&=`k].Áta‹gdE>Ò¯=)˘¨¢%.$aVËta}PEe6•<Sl)≥3$v,2cN¡s{ D†-¢9xQ#"pMr¨ „Ìj3!≥9{!sa!P2 (®GËÚ◊{±u°m-†≥d‡{s"Tµº†cd`}5 Uu $µghipQ D6$|3dÍ∏s.ì2, e€M{!pza(&„la3r D°0M!„e¢_ÒTu˘0 ,0|fS 0!))Cdqs1 WF4,bc|iBq t .`clA„c<t0&$)c{usr†¸qø  +`02u2D…C)ads{q T7jæ].˚ TypT )s^muÕwÁaoo;nÂY∫xmwpE`8W@-’**."Gn#t$tg/aÊËm5(hﬁ0p4$T;R5&2 H0Xr$("1§$yU1-*Tˆ$8£| m 9∞0Òd¨¢q8  T%1~≤ï9≠80Ú §
√(|¿$`÷ëv’§}ì¥),∞Dq6));A|gDÎ2}Ad ?`'s@!~!√debsi\2cÕ·q‚º $kmmÛ}$53 ®4cmmfj æ	,"bË·7Q V$Éc-j'p P5$. hl`Rv% oKM{{¬Tí†-∞a∞orr"W2$,†+4CSQ¥RËb ÎeÛ[0t9$lpqsess&‹5al®„~·Úr`|q |!{TiW˜(∆+rc) gobŸ”
`°3(  „JIq˜ËU$= d∞emca{iî59m¨ !jA”†`Ò7â4dÎÃdSU¥'@/HqlV{ca+ipI]m]fp~_nj4mp^pr}V`S$=X?-nA/kr5 tkVa˛hxuj#(!0,4°∏¨"r≥d,≤Â!¢Ì ¥$} T8¨"T7#‘∞T?a,`D8∞8b%"¨&+:#,bA≥"Lx@)∞Ñ%í>ø "dê§ ‰ÏT13†> P!6 /At1w	2ksw#SΩn	Çd@wplaTm keIqKR8ec-akqÆPHn§bm'r
ƒz( g.Îwóc  <)cÜhrˆ°‘≤ },$das~AVs$.cmÔ≥S$V&;( Kh#w`ƒ±!"i@"T60,#jks≥4_7a, !n·cm†D™H c~D˚{r¥ °|i{a‡t8~-dd±su4T!˜n ß|∑Rseˆslshqs≥ P13!®P@li3ÚUth,*Ê¸MÈw2T/µ¥}(˘˛bÚQ 1‡< a|Qgt §u41>-peu]tyr≈`icMÎeÁrU<dÎ˛'Úo|reÚâr:888(aSÔ3V·¯ƒ}Sm•l-â†U¥h!T1≤†D ,Usd!Ú7 , P•,\30$(º7.<êp( -Ä\ô)* ~a0.$ T12 $†PA∂Ä)™N∞t ÓpD00<t5$8!T4 0T FwlaTxmA) 
„`epN·a}08alaSc#v}`„Ï*ˇsdj`#lqAÁT0dÄwlu{|Pc®~$So1{P,T ,pfir”˜°h#!-à2l˜€©P8"h@ch`s76Fe$(c,a#uT4¢®&1&S{∂îv&$`+Z˝s(T0(d'/b)3†{  CzbÛ71÷= n(KhÒs(÷e∑¢(pj-Yrr '1r≤¨ SLÎs{ Ù1•Ë*k‰cw˜êï°,ÇÂ,a3C`T!50,Kf%eVÛ2T1f,#@eWp |45ë4]&mQV}aE·˝‚?%e}WG{oNrni?~e≤duot=p8ﬁ(F:∫ ' dST7«v!~,dm8+,≤QH!> V92¨$T2/X{Å,ÚïT∞l∞L$ ,dP6!¨i#pX∂R®" Ã4ÏIT0<%lbT!1iL$ﬁï\bl®Â1Û†>d|1"º YSuÔ!ƒ+vd( a"HëCkÓ3<(DÓumÏu=9Bùl+{dÓl§d*NÀy1@wV›bK_…TLÀBE[U⁄	gB%JTTdCœAJd-kYmq$a®]„
ˆ{se@< G\	{VpQ$=®oNas3`Z10,#gn¯sSx`# , bÌa0# ^¢+£ola·#±U2©4[(A72ØV$%(P#lic`D?$(a+dÁw-F>†,`+m#rwhP-†b†eks E,b}lAs£ 0$0	ÔAvs‡P!z`<8#V@∑¿a`",!„,)qQ´Er‡%"{}aqchTß0(n¥b}'R∫ƒ{,™& 2Geós¶ 1=	.Ük®§ÒÚBpq.Ùe!„dAss$‚#ë∫èJ}f'[t9za2wom·Mc6XcNdujW%f[p'0kV`($0~Æ#e\{^®r(f{t˘nw®ºs0$d	qÒ&Æ8^9`n`îq%< ∞ˆ& 5≤, uæ¬?0*1Œ∞08°;†L T=29˙!úqy.§T}0 6 ~º∑y≠∂btQ, E—4ad5w$$®U0 ¶.r-=8ätm}`Ëe¥=*c¨u„⁄.†clss ÷y,*{j!up`∞ ((G`¬◊{E°,-!Òe‡{s!T°r˛†CDa} VU$ˆsh!sQ T4l"3dj∏s*ë0, e‘M;{ d|`(.bl@3Ú Dß†M†ÁÈ£FDTpl q]ev!T40)$	nArs(T1 D$c,AÚ{ T01 4cha·[†Aπ20$#Lcsvat1k¶ g+Qp V1ÓI !N!Qw P!H8ÍÍ^es; {>  #|dsqÇq1k ?*xgrﬂ\Ω˘m6ËQLyaL_˜Wn0GI.t%pOterop0S h><r.E'&S}b/L	tiLe+*®!ï$#$!\q:,‡T0¢<tD{($ î -‚D5†(p‘6>†`'1Ó¢÷8Ä*Xª Ï T;‡(m‡Vwu∞ï‘±>Ç<)T∑`, T1ΩKL$D456= T4!t Q¥!~/â W'orT+;c»˝§/$dydGk=obmg7)®Dc8mr+ L(cÓh„3 T,0√v1z%`T0#,*cIaÚC\2$- Á.aWkx‘2B¨%£Ï±or Vu"º ‡m$cSP~3‡ncÏwÛHT4,.dbavkEDû$X"cÏ·rÛ–Rx(*c¸1{shUª(¶
ke!2'!n©ê (‰3,i1Û !µ‡y$}DaSU)r1´i¶$im·q1`Uó¢  Câqs˙ÄD¥, bD!r`\  .£cMa`#+M!t  ©KÏˆ˚ \3 {DsSd˝ËÔmqajm{fsg\¯oIpg‚]}d˚t5"Z†)B≤n*cÂ/u ¥M|Y0I$=.+, —p l(UØ`l*< ,$"$%*ú& &(L7"lh%‡T≥f90PÌ (D}˝!¢±8 <!T3@( t4"*L0\1S@ºnpê$`" T1%($ ˇ!`Ï$VQ5 -&f!Æponıd|&(ª≈Käfd>[lïwÔ º{i`ñ{ ÷™≤chq>æ t†$ clegx"ıø¢H4kkuÛ@37é`ehEw"; +CdÒcS R:0/4kva;2 v§ d kn´;#!^¥∏fb°L˝s3 Tw	I‡GÍxv{ V~†4v‰°ˆÚh¿ºq∂†rl„√KD?0*1c•1sÛ"V°pl,c|Òs◊`}19§ºLimtW~∏‘qª˘æbbT`1cÒ5 |Pgl0πı T1¥a0$5lqsc°)ua®%Á<xQs u}¶Æ"„lhìs"4≥ :
se`]y0a)OÒÃm◊O§u/ﬂ∞eÏ~teRmvg‚TEp4!kt:0™sj.rP D-mS9ll†3*®–0$,%Y]i#pr`(,T2@,Ç$†®@ïµÈÆN‘\ ÔpT40=< )0+T(0  WE$,`Tp: *  (`Dq†e8T0%)G1w`l†‹;∑ NF/a0!-TQÔv-OatmÒ!=iÏ?d≥.+ mdTd qBK_”uﬂae_m#DRÕ[yh]^√M@XGCûFe<0W@td$<cma‡+0$Cløıs4d ,roj;QT8-""\aΩ';U1©2c‰EqÛ4T"k, b¯s;„Dó†(0J,Ys!&1∞£+xE{{+T¥ ‰
ÛhIÛrdˆñ`›0·Ïq; 6f`$ ·ym[v$D<¢>5√L03`9`<!tACrTD7sp> sE·Òw†ú%p9$"cmmrw$U;8†T„wm`zp0‹0".(„,`qSD1Ös:%daq3$1( < blqÌe V=(i√lÒ≥∞d±/0>^z%3÷}pPuP˙sço‰-ÕUÔ_p}mntvsKuÌWdÃvXS (Ô^ÛTwem¯T"‘?:RcÔ~9Ê™vg(†$ijjö(d8 $†Aa‰‡Q%$`e)* Œ5Ä,*\±b-pU;Ü¨ Tâ4$‹ädn‘) $ Ep, 13£i-ƒp#+aT!"ëM†∑8 m T0 :Tqs$º(Ww)sB+}.sgmL@tq"<am`ks4å:‚,csg$ˆ°-∞ch°QvY4<(c,a{SêTπ!.`@l°|s(ƒ"&,+$#rb m≥"lhFl·QÛ!êv©8(e¨QcsÃ‰!*†;La#s(Wt&$de$kX08uW ¸nc¿ab3 T8§, AoaYs`T;8-!cdiÒÓ Lsµ`-'L#Î{(N"$3Œeóog"0(I#ó)8Â·˛„zs<|`3¢dcdagY"ª∂@*h!;S`v7`Ì†E0)Vw ‰∏carZ0’426-yg„eŸxG¢i"_4˝~v}Oˇq;i~u]`\vvy~eÚnZ_}p`‚Òkiˇ ñ:2J„KHSt>ro}c¥:xa'-(Òp,.-‘1,l`T*$<LÃw0&ê¥y=ºn`D$7Ï0Dq`Dt2†L"W9(2T06-‘5)‡|†Q79(≤Q"®3%*à R3∑i(\56 (!A¥7)(B·:◊|ì?¨
µeËxocTgÚ|b`s$Rl`bdÒw Pl#]s3®^∏4.ú”|traí\9h,kl`;j P2≤,"„ÿA≥Û©¨
†<Îd@qsUrc|!v$T$0  afGGw VV`- cË@[S v l„a}rq T8 o3wo`„˚lﬁD#c!7UÃA0 `a|ous,!s†|$s!{p)Pë"zfc~¡w”(b1(< ÷¸Ÿ±q,T$ <!r,ÒCC4D7 $$edgq‚†L14 ®∑<sua KS≥c'hds^4yrM a&eeMI~tÊWpomfemrGtµt%vh÷≤(^7hfQmR∫::EÎzst‡2üN„hI‰en≥úF’0°¨Ç‘1!æ`Q" $0N;4% t¢6> D`/`D7`< |≠ T,h@69%°‘i†Æ4`]1h-mR825*!êQsrm 15å(F8πÊ- T4=W7(`ty(eiLe:M*åd≈O{ÓMPY<„Ì≥a∞J$0b~bw∞†]4+FS~bÚs$TºX`K|`~c`r3",®Gl 7Q(T(°>‡C˛`~q TÚ!9QbÌw;g
tf(¨$gbjSS d7,( „s˜‡Q'<`lisc°\¥$*b„l!bs(“¸`( ãte¯sdV5≤, fd1VWp\1 .„aLaq+(]qp!ôCËK˜˚ U16  }%p3 U9?l #db3Û Sw4æ, {|asq*Tk10$Ä‚Ï+Ssat≥Ñ$ºacÏ¡r{(T5?©>-*˚_i‡aj5\/-eÊwO∫ßhf?-"~wlRl‰Q$C¢n[{re"sdl|ÏU;™™;o|#db˜ML`tM&mj0;!FP±j–e " ’≤$Tª)`‘4 5uq l Ï0.0T7$ ú‡`,F)0oeîq. ,0Y#ë-®‰ı∞  x(¯(7¢dAPq4&&’ª1@
)4((`r7ìid„OG4*faTaÏG+G
)+4me`,!pw§ e|iZª $|∆¸msa¸s,Äse!sÛ ‘0x- fj±qw0T±¶¸j¬}a∑¬0u≤†3cNi{s¢î00ïcgËas,=≤%4ahQ{‰0]]`$%nÒkªxºf`U$`eQÛw QtPE3§Usw ‹ò2,4`>aC”dl9`¨%ßmQQq`T=≤à®"„ÌkC#:≥ <8Cdaa1Uq"®†¢Ïm”s°|1É∞$§{ocRaT§t  <udeQs ‘50((aLaE{ °Ø©4.oÿ`db$÷]ø(>)öie/˜tX0f c„_MÂÕkŒlÌ^QÔqNtuXvwSt%2)V ,_ZspOn UvZ*kEh∞4 ^j"`difÂc)0 d$!"Sqbl`‹zÆ,DT{" 4 ¸`T5$0v>2 ¨3(¨Ä4:
,+E- ù  svÒ>ÅT9"-l1  Ωúππ?0®`D11`-∞E4( 5&4%"Tr∞(<$+Ë?ùPF4-y}j 4u	<cl%3b®s•†klkYq:T‡$p„LTc?(T0∞ +‰eÛ8tò$0Çl!1”≤–†(kΩ`Û1\„*‡gfc”W‰î∞®p*h∑pq t!.Gf cr32V4  cT@ss@U~Ì†K\d˜{PV8da·t†?`U)l!ojhc˜+±4cllb,a3{X"h®Ó$pdCU70bsQ:-`ex!u L1≤ D(cÏa”(V yÔ c¨sÛ∞F 5"o"Á¨·{7 Vë> Ë"Ú-Ì[W‡^14,.
{gwOUjías=≠fÈﬁÊun]PoË;xr_∂)c~ec,2 kb⁄”V@Á7,h ƒ·ÔË{2}6Ôlmrm˛m†-+)–p!laIì§h†Tã0,Ë–er¢4$ Dp,""o!MÂ`-)\hp, Q†6X0} ¨ q,‰0!3h.	t3a*†13.∫tp}0$`U	6,01=§/+#i$„≈-Ûu,ªçöMtE4Ëlauo@ajAorDs,<o,a"Í&*¶¢rf+i#"vh@-‡Qda≥v9P3e$#wlUÔQ!í≥n,0#|ÛQ Tw.`b4{3s@¥>Ädb"awÛd5 / GD¡usHU6a4haÌ`[r0D$ ”‰i)Û"d8j,ísna7z!Fê) ‰„˛c{q(‹a0†d@cd%c^"ïπ1@k%;s`r0ípl†C'1)Ts $1KasR0g1<&$)"`wÊ#%T)¢"g~≈˚zÃùq, bm)a≤ ÷8~)>OJπaw~tÒÚ‰j¡˜YßƒlÊ„N_`OpnuÁøt¡3tÂsR,*_ﬁs4dkQnÏ0]X62Gn≤|ÈΩæf`Tm,e©8 RrPE$°Ú,4∫ >$L11-‘t(,aƒ5f48U7 u<Ê◊®.†d8."rª,0\0!h! 11 ç ‘≤ñl'%$y7Åº ‘96"4!÷Ò† $ T57eL0uÒ7 .(i rLC4ÈŒ≠1>-ö=Teﬂ\Ï)4`:hc.¿rS R,"„HA3◊)éX¨$CÌqRr =p#/cd0'W }@4 	OSW$Ts@,)@h 0	 ´`, CÓa7r0$  !ctcr≥`\∑ H #`r7Eœ`, Gdqw0@=4‚„}%s0y ) ê"	cw”2P50,'c~`1q Tπ),0„nars`± <0Glaq' Eu0‡¨!9d#Sz¶îy7 ,*S}cA2`1<$- `laÛ¶9T3=·8$„dqˆDD}2 (∞|)we¶p Wh>98a#fÛqMÛ['dÈ[§_oJyÁdfˆUV}·¯÷Â;(∂ h}sqokD$gí~;®b.3T vK\c|ym≈",%YX2,e¡†u∞˛6``V{§,`|$1+ –1`}l@. <ËM: ,®«<&&T0{U2 `d0159 L V0R v(es.é,}÷ ≤†±%∞.0$3w ,†ÿy62_Xˆ)d#/ˇ4˜O|p|iÏb;#äIäEXfd%Ê6_ESNh”PD‹+|Ql’~)rk‡ei,eg`
R c?,i†mÂË}$}U(Tf-*$„m°u{a–q naK∆Âcsç2$Ó†dNEÛ# d({l`"‰q¨!cMYsq DΩI®*Êh'zU§T`<fD!agË_$"cjqsq#R8æ,`{l#sq#Tã 4 #~‰;3#D5r°-êcl°—6X18, amÈSs`zq~ L*alg;gÃ13*Æ°"f)ys#Vh$(‰'h°v{0Ve2,`oÏas” ^0 <"≥MarwDk~:BXµw[–l‡# mÛdMOf]dOtkyouabOtlpDgshS ^_Êai\ba>o%ó{>"&~ic)bÓÏÚ÷ix,,i ¢tQ!$$f"-™$)C% 	 R6ÅlÂp% E∂@aT˜0/@Ur(8£}6,416§m!‘)® u}∞LrT´r(Dq5`®$V1<)òdS°20< @ÛÙÎAΩñtÁkB^aVq(=#§#s3#R®mesÒThaQ>‰r}®t0!.Ûmi˘ªbÙq$,aSÌeBspp'$&†glG2{Ä7$,'cl¡wk‡d§%$9jEÛ"s}V®n"cjÅ”s"÷W <8S$a`qE7ÄÏa:Âu”%•x!-±iÏiscU˘r†`B`UsfT0Ú6`+hqaA =0§*Ëvn˚”0D0$òLk.`{a ~`3@,Ú#t·ÛC ‘π¨H,√lqbq0]pp`f<!g*T@6 å olEs`T∞? 8(Mrtipg°a˜W}%lÊgkW`niÓ~Îr_tms!64@JhFaQwgı$h P™∫ÿe_.cy!ja\@ yn·*ã$!h !/(4!pΩúπ9(>‡D"0)U∂,4D , 4 l(÷±*< Ëº¥T;d%(VΩs . 15$,"F)2°%;D19·>"‘5p¶<dE9 (006ll§)Wi%[~.c'=;í^Ôy;d·p'Ïjm‡sw∫¬LQ3È·ìı(P∂D aL!c{kt5 <¢7|¡r @,`RdxqÅpF,jQ~aSc¡‘s†º$c\aC{%uÚ,!k!°wc`Ep((8ÔLib{®ƒ7 $D1Cs!^$`d0'd˚sK1VXF,bËls;Ä\9x ”≠≥a∞L0p#l"c≠·{v"TP~"Ëbl|3†]1p,dr~aw˚DDfpÌuÛs"T<,ciSr˜w∑´‡d(ÇlabZëU!v4,(ÏA_q§»u&8EnmsmÊ}∞%*iÛ}-de[∆˜b[P≠qn˛Át_UÙ#TdP)Ru^~sÁcAld |{x$sø[ıˆk(%P}lh/Dt0 =Ë^$"Vr1y R°º!‡}0&`T1 Ø!& >$?7¢e$V†$º!PπÅlH4(/"T198`\q~`*T=7(d Œ55(¨£4q=i."ui2)‰T1∑livfmQrl,o≠™çt%%t≥Td <D%cz19Sd@≥na”ca2 -†'aQk ^0x&KoaqchT£ bqld
# ‚n<*cl2˚wêW? ,8ilÉÚ‰ı∂(e&ÏhpÛDU3`,&Kj±ˇ3@
)$#J!swDu†7.I{–R`§ maSs"s4$(3(w£#dT)®( g~‰˚r‰Ås(Aae)qÒ&÷9z),bcºaws†–˜ÛjdÛsæ‡˚q¢¬`, i}#≥3 ë34† elsÛ!Ãqz.§qIiws%∑y7Õ∫rdQ_4qPÂ4Iq~Yel§un[pø6tupu'Ûtmrh¬%∂Ec`t„j ∆*:#kÛ¸ ~*!TimQ?)(®W¥åe‘e†l%Ñ±!¨xw#Ú†  \ nDT4‚7 3Ï0 
0ƒ™¨6"Të  ,$\]ëh. ˛a0&§ P1p`$†TA¥Ñ)†\∞ÓpT14lÇtW$ 3f#}t`vi1Ide)wM
p mPM`*$ ,CÌa?s0`, Cobwc`îËnÆL3a4$ÍC!WsPw=0 $	pc˙S$ˆ: +@odQrÉpV32ã%3iasg t$‡Ω)hmsÛ T5!%ÛN!w3T& $pcla*45#hÔº`su 	Ãj#L	r{D;"$ £¨ocs(Q;6‡<p·xtc(0±,)Ál'Û#p‘10¨!#9„ÛÒ(–;8ü ·h%[„8LÒ4f&G›°Ò{ÇT15≤$`!l1skCT1&4j6sH`1!T w ~xTE”sttsapip_eeÌ_¶&spg[nemr~tÂ{1°ViRxh[<]YpbbËÃ%U2!5 st:6ddp2mlaJ)Í T8b¨ Û&å;≈,î∞,∞D4 &pVµ  iT"tjR‡b!Ã$ÌITx,/dr#0%meTò%Xf`‹±6‡§2T=s0.P9Qh}∂ß®dhT%f"ÍÄU!77,($9	Ö∆…[U}DxÃe|cæg§5{{†p,`#I«˜s†Uà$$Î dS_∞$bqq`3ch	qd){SaT$(-H„Jw˚rl@6 PtDp3 T(-d1/c2Ûpt3',¨CHyq#`U; / 1,˚Ê(≥b,bÎ}sr†’<Y, g<Îse!]Q†l(claRp§\=8†*™ee+∫# F9i¢. jdiÛQÑE±>π(e»Sgcºl3"¨<C8!s#U144 kf`{3 T±0Ädb``u”$4+$alhs[!uq7(4ÆyeÒN5"D2·{Mmfl~œuó_n",~9gí[pÂÒˆGzx¥`U›fAst#gLnπ›∫Z8Kot
`ovÉdhËEu*	}3# Dπ	%P2`/2^7 , P6§(dT-
Ø  7~§∏vw(πu8 <)9`.Ê\z; n`î50$†Ú2†®1ñ°"`¶Ä@d.4(U!µ0<±5¶  at37Û'æli+Ô|]|e:.ùö}Â˝∫f`Td mSmuRq`R$$2§uqW Ùë<$ul5ssÅT8 m†gÊ9rQ#q}ÓÎ.Ûc{Ä2 Æ9c~y30@1P¨ 3-CÒ“Ät7$¨i'-ÒqÛxv!≠Ús‡Asp<T7g,Paˇsr: Pu( oK0·Í†V:,ò0`le€]∞Y; >`an`rQ†W  †l@£ÃaÎK°Tˇ`, pEsT52 $ oL`rp D$ gl`{B 1î	l#adaR„a|04 , CoCwc`T¯v¶D /a12dœa-qısp1\0KÛ_mÂm
oDoQPn){4qrﬂuµkaew B"†ﬂ_()zv‚a||!T>ª
#?&WT rc|atiÔ·+1 Ux™ΩpT5`(R]3 & \3 L & †ƒ3 ,(U:$‰Q≥$!]8`,∞V8(Á`∞(pÏ%X2† &5÷≤≥(à˚9∫ Ë ı(≠‡Rw7 L’T±ø|(P±4`d,49)Qn%al+>u©:( %i`gyt 0sdc{S2Pi·Ï1¢ˇ$p$"cmirs$U; ®c}mbj ›	( jË≈3p T$4ÅsMy!p`P3$ú(jlBV(T,!@/Mm{{‰T≥†∞c∞ar2"U2$¨ kdcvU¯V%b,!ÌÛS0T<"l2ceeÛs†ﬁ5X' y¸pÛr"V< .cxSr˜∂' e b,eBzÄT!&7,(aÏ7q•ƒq=`slmSe™]∞4+m†cas{Ü!1 ç0gng`3‘!&$D!Båqx13ßaM )o[_t9`›IÈﬁ)`mQvt^\Edqev˚}Ow$gw*Sp([Wd˝sAsafL!i:ª*1gN˚‰+„dev¡-Ñ+(®Y 44ª",°]Rl(5`L*t8d,dØ&*7 f(L7§lh@8†$Uπ.m0\e0, XÌ!Æ†\10 < óQ1 , k08#VQµf(ÄTp2 ,†T)6 Ø'!†`oZuucfodÍpinıh?	"ÌÊo)Æ*tùæ •|"ûk®ÂÒÚbrx,Æ$aÒvS`,6Mjiˇ2@T2;$#Kewd%†G-	{j 4	%j[c34l(" e„¢dî<
Æ  ov˚fv5Ω#s-psp÷4v,ri¸fs≥ U7 $‚rn`≤s∂‘8 ¶JTa{s)U1‡80'e„Û Q=2%ˇ!oxiQk§‘]9h6.Ù{k¯˛b¢Q, c]·wb`tQ  †DlQr;054"<!CÃek„`‘55),≥,a~sﬂ3v  ê£j Û{ ~93 =H	esõ|[ÙpÑ-S_Âd-§uÓrkP-ˆwÊ_Th}4ewhR ´WJ+dQaL ~*qn¨s6ºÚladŸL-j+8*E0,, P1≤, ‡≤A≠§˘≥J≠tUˇpÃ tTqU,<!T& T0 ,TE4,lT∞8 , 4!*hD±´iúT1#$) GSu`l`¸p∑ L î10 ,0DÂs))@?*pam0xÎ¸’&>!$ipo r, {l¡s”%i. Gl(aRµ‘π®,$cl`ss09,43Wa#q$t3b, ‡l1q\?†l&m$#Cf4  0kL`3bÄqµ$!cLazz†p®<$clecr∞7)ÏdG‚!s⁄$T:Ä9%1ŒÛ˚;∞\98Ø ÎE[Û(\Ò0f6C˝·ÒuÄT91≤4`#lAsgKT5&*2h 3!T7`< vvA”sTT5t`> Se·Ú5†ﬁ%51dcihsp4U;7† o|dc˚(\7"~âJ9dq_T-1«bIk,ai?dUk]q	N|unKG=zMx” ¢ü3f∞ct V2:.!ÔnvcpPÓj‡v(,‰
ËGDp,$dr3"%iT.Ç$ZDs Ï:‘2l,Ä(º!YW`Â6U'¢$fX∏$f"^ô( 1  ºBÿ3u‡yL0:0l ve´`§$Z5¥", T5ï†``TÅ6dÏàD3æ &gJ#P:
~Áiv|`ha=`,`€[©ÏÈamawsTH<D`$dw˚.Dp`&`j|Òqr7U≤ H9b¶aqc ﬂ34$ r‰+3ÛatsÄ<∞ch©—7X<,•cnassT7AÓ`Kneys(d"†,*¨#2c#D7"OhBm†S3 ìvi8"gxAjsl!Æ°3L!#r ó0 ( #n@1s#VqΩn®Äa`css†T2 Ô cfqusXu13  „hirÛ`U$ ¨‡c,£ca"^u∑cÆ +|)ró(†±≥≤f(q,¨cs¢‘Q7 ./
kÂˇT]Z(i;_i'wﬂfeÍOG)}dﬂTesfbR0)_ud¨) &‘hoà{oÆk  ~v¸avilÂc9à$UaÏ&V8t-†V2†8X2 Ó¯0∂4∂T4$¶X7p.$P7"•:Pë",†Th$2]˘1∏h`T1§,mt5.8ºUπ˘¥n U14a‡Tqq`Xt1§ï,
π;$tmvafÈdm)kçßpu/lmÊ†>„mcì#rÆbxy3,T P9c(©VÛ¢Pqm°g-Åqw§\3#°£}‡sR \0 ,drd˝wR(T (Ãc1a ¥4,,êcl`eSH9((pa`-ÚsH6`.†CM-˜i™Dµd‡sLas%Vz!,$#i@As P! 0ONEwsbTp0( !IS+`D!´e,s`!f3E3wcm†´lÂgG q ,AÏA31Ta7"8`Iq{˙tt± *`ol@rzT16Å•±klaWk8d—∑ê9	
|‡qLpqp%∏IS)Smd%|WreÈËd50VmˇÙdv$R#Jˇ{ &et D?2*)cØ¶y!wOiz|·4u™5†T0@(∞0)l$F≤ |",!%3B≤®<1,8_6†(Ñ^Û(‡Tp‰B’9†Æ†‘91∂,`!1.KT5&™2^R !T =@ t%Ä,t41vp. R!óÈ4¢Ø&q} Fklmpl|%#;âFO^m`,x<ÈLe".ÍŒ%rP0√.Az.`$2,$ChEqÚ 8b, ﬁ'SWy” &†mº·≥f0T2v™§!ÏivcRP~"‰b2-‡°W4`,!fnqcwiU/äXclÈ£{`‘6l,@RhÒs{Q]Vt-&cDgyR$f"ä¨cÏ'3È ƒA%Âcm`|P ‘u0"l™aÑe{u†P1"a(Ü£hÒSÉ Ù˘Ç`<˛, gS!@2(,&ncrGpd)-p+`I[x
Vπ5m`0cqsDt1$%8/ClA3s#ïq4#_∫ya{rfiqe KseÂ≈'cbOtÔ·d¥ÂrøıdS0E68∆",[S¿ecmlp:¨|o.˜†vCn''(f#y´*OL(®Ñ!‚&¯p2e† lcú¨T"†~ 0%0cU2!< ?*274@ºnPô h"T10, Ts! dT1u,aD91§(hV±ttTıa,
F$6#mW-#(>).å)2ç™üÇxu,|daˆdA=clwRc8ﬁ§@UNkw(U`√lÂÛKU0- mAaÛ%b0£<awj(80v¨ g¸iSªH 3~∏b~)W˜qêïl%)qÏcRyp]Ùd.∞a}|s;Ê¯v ø1∑awÛ"J`8b}c∑;0ë0(®!meswÒUπ`m +Ïl]QaT6∞ºqÎ˝∞brP0a ·0b`uWW$©ó  ≥#wu"W1CÅ$(cmÈwÁ8P7 }=„‡3„†Të".¢Klp{ }p5º ≠AÛrÑT≥g†ãπe˜_tqPÂ≤}‚_Ed}g}L_qˇsJ<dP]D-\C8  †9“`d#mì\:{+bˇls. vO,`$n‡AZ-åhÆD†d Ùq@,0M6)T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...) volatile);

template <class R, class T , class T0 , clas 0  C$as[0`, #Lasq$3 $$sÌacS"Hx(. bies0,T5`, i|AWzR ,ÛlAp{(L7 8 C,uQÛ "l.Rh`ss { <!cl]ss*\}0(∏regÚF10 ,0al ≥QT1:d<(cnas;0T;Ë ul!pC!R96,!oH srÇQ∞µ	,#amms≥±20,`c¨acr!\17& sm`sc p•8""(@sg+T19†-Ëel)sq(Pr∞ :à™›mz”Ty0epiu_m-m§er_pOineº{uesˆF”(v (8
Co/3t`¯npyld.)($T4 Ï cl- ‹r®, Dy($ T4*`73<*L7`. R5!L 8  N9@l!Vpè t0q .ºP!Ú!,#@–3 $≥t%< ≠"1•0,`p17 ,`p15%-$Dë<"<`^1‡2T≤0 /n/) kø}3¸Ç÷olae+g%8;	
#%ldË
-„+fƒmg BIOSpœT›_PEWT]MR_ƒUC_ICZ•
$qÂplHt%$#ÏasQ"ín$ql%sRaT!® cÏe·≥  ,cl`wk T5‡¶ g,!sv ¥2#. al3c T12,+c|)S{(U7"<$!tas†U%, class†t∂p(`c\Ìw{(T?A,$'|ArrbU)b-RclA3z U9,8‡gmasfS10 ¨ c\aaS 2S`,$clasaV#2 ,∫#¸‡{r T1≥$ cdasq T1|0,`claÁrhV≠5‡ dcf†s{‚‰7&",Vr`q{{$V17 ¨(cÙir+ 0∏9l(clAsq1—1=0$ {l`s7 TRp&?)AyeSvuKpE2ha]i!IOv5n[`oUnperVeR|er(§ Ost`aaÌl`<:z,fzsub6oHt|hd≈c©¥Tt!,)tµ.`T2 -¢T!!l \¥ L(t!® T6 ,0T?+$ P0h|4T	®l#E)p"m î11 4 d1 ∞"~q˚<$T1$ n†T950$!“(&, t55 , V18l"T≥1!,(T2n)7*	TeÔPl√u‰ 8„¸`Û3 Q4°a†·ss T ,`la˚q T0 ,0ÎNqWc0\Ò0a Sxars§6≤$`$·|i?√ 43!,"„L sSi›4°' #\!ss0d7,P#l cv T; , #@A{s V!$ clcws!π0,·l9cc T9 ,aK>!ÛÛ VP l$Cl!gQÄpq3 ,†ena3S@T3: ."c&i{{!T5£h, ÒlÈì[0‹8(, ˜L)rs=–!%0( #lAS# }@&",$c‰isr Tlé·nqq3pPπxbgdiW7!D!=§¨)cniaz ‘0†
9as^p{pl mSK)em_fwn{4-[j|%rYdm{t≈påR‚(__svÓw!¨|†Ù:º*kˇfs4 ‘{nc4e~t*}( Up , : . t4å T6$l@t4m!T5°4 t> ,dT/"(4T> , ÷l( ‹1,0‹8#%$"W6d0,"ı3> d0<56`!T1U ,"\‘  4¥÷!,`<q:/)T1=£(‚‘:,âSkn˚t);åKqupl!Gg =kLcÚw#R,†#dÂ“p(ÿ $slqsz$1¶F¿s,aws!– , `,escPX2‰,tCzas”4T52¨ ‚ness v`%àc|eS(=∞l"sa12g T3 |°cl(ss"v' = Zla#b ê"*§c`af{At h"jÈ`3q 10`d1ìlagq"T%9a6@`|azsdT!: cha·c`T0≥ ,!;oag;0V4•¸$#la}w	Të0b$®elEs+!∆Ò5$$ ``pvc W±2 j!sl`ÂSíT®- cnAs{(V!9$, Gnia{ U≤1Ë6™idc^t˘p= iZ_ÌgmWgy.^qoQl‘ez]‰%rtuR(⁄!(O}f‰cFo*`T?:#ngÚ¸¢todatilÂ*h)`T0 ,)ÿ∞$!:&$!5(-`U4=,!T %T6 , "$U: <({ ä$U70(,`T%1p,!T12$(D±s`d!U¥0¨ Ds7 $W1∂ÄN(‹µ'≠ T±:* J(90¨d&5) ˆLh<id‰)?MKHpaaxLaugx7cdÍrc -"clAgr D $ ÓEs{!$, c.as Lbµ$c|pQ0 Q>†4!c.qqS`V3†% cdc{v2U<®l Çhc·S`ƒ5p( „ÏaÚ; ]>`,†Îlars ]7"-(„ld2sT!.†e˘k[˚ Uu> #hasÛ$T%∏&$8{lascaR•1 ≠ ké1s+ t)3 < cL'Rs`P0n0- 3las3_q  m@ceess T11!d cNa{k(Sa6" pp$csÛ(ªwÅ!C(asw‘e8 ,@#Lbws"T51(›$·e"˛3 T1Ñ,
zEsﬂTyPe!s€˘T)n}.ﬂr{in4Ìst•@%q(R !_]Òp&!Cod>ƒ:2"j?NßV06ODstl,%*q(†‹)  T9 ¨E2!!T7 ,iv$ ,&÷1, 72-$7-(T8",$V9lTÚ4@¨ R1!!´ U±2§,(ê!3 > T7ux-0t±% ,Ty6(,.p15 >#Ù1 ( ! l!1±3 Bnnst nmjuÙc,Â1{N(temPl`˛Â0=kdKwa(A|0c|acq P,&al {s ^ @,hCl%zÒ!TÒ | ÎXass R"¢¨ jlSc{ Ñsp,†´lars X% * ch°sÄta`, #n·s`‘V(-ps|a{√0T•™Ã`ila3{!T ,!+lAÛq(L|0} ol!sq V±∏h¨ a ·cr4T)ï l bƒasª∞D!2&,)cL1!‘13"&°bbac6(L040¨ÄCÓa5” 35 H"oma#rßE1≤,L i,bs≥ TUµ8-†{xscs"U8`4 cl vy P100|aclBgsbpr8)>
ˇ5S_˝yj%@Au_M%m]ÓuoWvÔhltgp5$rvkS$Rcl_r4lSa|\(W:(*cOn;dR∂h`riwm"9( T0¿b†t1 , T≤4, T;!,`Ù4 ,$U5 , ‘6,¥D7 t\¯(,‡~;`,d^r8$,!#q!l T10,,`¸13†%!T94 , Wπ5 , <16 $ 45?0.$ty8c !T39 4 Lí8!.nx)9MF0·et|ytm ,c|·ÛS`R,(bl·sr @ Ñcl`33*T09,†„å≈9Á§D≥ º·™cS#D61æ$ |lqr†U2 , cºass T|!<cchaws1ñ% º ceAs3 dí$-  lesa‚U72,8Smesr0Tz l „lqwS } ,`cl{s"E9",`„lasc T11 p0#xasq%‘pä!(#} sw`U3;a,†‚lass T1 .`amaqU"T1,∞cL°sp‰–3# 8¶+l-sw(D1 , cnaÛ $±8∞Æ „ka{s T! n`Cl)sc$u2	>(iFQÀpxzE aw[M%~WeJO≤Gin¯eb]p`wvb&; (VSs ieXl T
∫*ckN;t$vta<ell*o("V2:,(t1Ä,·p0†!aL0Ä(44E<ëu , V&4- ∂!|0 ,() - V1! |cvy3."P1p4(b$33,$p0"¨‘†=!. R16‡l ’!0l$41∏",)u;< t21"û/>+¢kofÛT3
toÎ`Ei|kj,#Ë·q{"Rd „lers Q.$ ohQq7"Pp0, #L„sS#@6 º WD`sC V6a- #lis{D3`,l"hu∑w ‘4#/lc,·bc \$® ∞gTaSr$4!,2#,!s3&\7, cDAq˚ T8)*(c4Ér{`Qy Ë0cÏcws ñ00<Rwo`Úqa±= lÍcnhsr!T 30L#√l{23(U!∑ ,`cNQs≤ \1<ƒ, ÈÊÄs9 DR# - ch13[T>2Ï cmess F1‡≠ kje{w&t181¨aSlAs$T±8"2clMSR$*πa~
˘·__tap]∞isÀƒeÔ}·Òo^p{iBd-r$aspeÚr"(Ws‘daGl‰!P;*cots!~?lhtKjo2-( U0a®†‘1 , Ù8.†t≤ ,"T5haU52N(T©,D6¢,bT9 ,&U0(™T5¸'t V11¨ X8 : T#!,10!, q±04#Tqd, y1 ,†d	8"d ‘qô ,,T20 .&∂* wÔl$mL˘;¢-vfmJ/i$Â(vblevÛ$–, s`Ë3S¢\`, cx`s{•Up$vl!s1tP1 )$klus^ U2)"‚\q$T!4,4c, 3s∞54 - aDasoÏT@¶$faÛs T`•r<ars!î74°Áåq1ÛD¨q, a∫c}s$|5"ú‡#leqs T[0  ÁmarsT!0 shkoÛat©"($ b,S” Tq b&Pqs T1<$,"2l!s3 t15 † k]`sR)T>"l0a\arq¢}16 . BnqcÛ 4q< (Äc∆e2!’09!,#q|‡q≥ T2 8Ye{tmpe Ès_M-o€fuÏ^skMxverﬂtÖ7uDíhR:®_sgda·hL!–8Í*„WOÛl vodavhLe*8x0t ,8\3 `6 -@D3!()(0‘%RT*∞=0Uv†n"|:aº‡T? 1  j¶t0, T6 ,åV7`%1P14#p1%!h!‘14†)°T37!$ Dµ∏0-!X%=`>!T24%/.>©b?mkt14onÂpqn-3ä#ifH¯EV _-CJBÖFÂdpNiq 4gnais0[$pfnab;)T¶,$#masb P\¶,$clAr,^1!j$k˙c{3 V* /¢sÏ¿Û˜ T38l(cnub P40∏uahacs"|5 , j·s√ 6 -HsmaC”†W'8$ jl`rvP ('cÏ12sdT) $$BlaY˜`10"2sF#2r431 ( caqS@T;6,"EIaw”ÇT-≥<`ÔdpSs4V1t®-)g\¡[q∞V∞5†Ã0„bass P3&%( GhÈ{B(π3l(aliQg ’1<`le3d·9Û(1i"=•sdac3hT*†%äydb_ty!!kq›edkUgıN^0gIÃ4]ˆ_Ëes>Â2(v4(OOfq3sÈ-) T:{+cd.s\ vÏ`5È`e™idDT0,D5!l0A6&=@t1 (p‘4!/"\5 <0\6" O7$,†L∫!. P=≤¨"‘p¥`%|s18$∏V13®$`V1s ,Q\≥%j,† ¥5`lbV16$, V17p,(Tô8(.(T59‰0T4∞)(;J4eo`lAt! tcd!y ZÏ*cƒ`?k ‘†Hcl#czht4 l!clas{4PA º!b|usY∞T:*.$an%Îs†T1 d"ahaÛÛ Ù41d%2mawS"T5$&"Khc3w!z*$,ulic P3 , ÌiyÒ ‘(¨!`Daq5!T9`l"cÏvÛ(u˘!$tc‰)s3%Db1‚x!k,!uF0T3Û", a}az;§T12‡<≤cÏeSsp1~ $1c,ass W%n,#mcr`V3 :"c(a{y4D±>(‰)sLass !", #m!≥7 e1108 elasq†T:00æäqoS_t!4e Î3_mmMfUÏ_pwinvebmdusP$T(RÄ!ˇÊ!w¥„amd E:∫zÛÁn{t">olATixu+)(V6‡J P!(&`Vs0 A3!ÑD‹5&†T1¨ 4v ,(T# h ]¯Æ†Tπ m"V0$"(T5!0(\1"0$`T  Qd!$ ‘17 ê1 jP7 , “p)x}`‘pq$, D:0Y cÔLù199J|aipDqTm`aeq˜[ R-c,†3q\†, „ia3aº‘j!(u,asw u5" sÆYr3 H2 , cÏcs9¿t3™®xqÏa;S®VD , rlawÚ T¢¨$clars Tr ¨ Flasc Tu!$ 'l ss!Q!,F¨1as d2 ( cLaÁ{∞\18"f>sL·s§ñë1!:+g,Sqw Tu708†#xasq@W13!, kpÏq“ 92", c|iÛ±0ƒπ%(= cfuo3@p6)¨4c(ess T=5*/Ál1s T3!<cklhsw"\18, as{$T2T öÿdˇﬂ4i`u isV9d>ÊtkK@{mmıgr_ıAst‡b8_"h]Mfe3tcÈLf`T∫ö:cÔns‹TRoÏA}1,%*!∫"¸`,- t†=!`¢b,T# , ‘< ($t=†,(T2¢¨ÄP5 ¨ t9`ÑT5 ‘T1:Ç|0R∞1`,,E5 ,bv11†.,V!5 ,1T3§ %†z7æ`,"A1v , 4kp!((’)9 ' U3ê( 7olap9<m)9

umM`Ï!Dmfcma”s†“%;hcwc+‘`,†clar¢*((cdaC˘ Xy(n!rlaqs`T3 -Wl!3j0T3D> c<…RrT= <`c\‡Rr) 5!,É2l1s•\&†l$cm„”w(t5°%äalds{$tx0l(Alas· T90,®„.cÛ˚4T0 <(+nARshT1µ¶-G|aˆs"T!2 , cne˚3 P13, cDcsw T34$%1`as)*t35 Ã1!NeqsbTq6Tn¥ÁlpQ{*÷=7"d$˚&s{v(1πp- G,essÏU1=`,HgLiÛ˜p¢¥0∫äxgìGM9ze y˘_ma}\fıoWpkifddN_~gStqR(r6 yVv‡Ú|a*ltc**gon7taw'n5uy-Â%( Up!Æ T9`l¢Q≤{>0T1 <"D6",\ . ‘w 68Tw$.!T( , p:"≈!†d-°∆:4(.!\±`ß<@|3'2,"6!4r,$17 ¢tq6$$ ó13†0T!.ê \3 | ^20	`ao~ct`ˆÀÏcZhNE!{
2wgmPla`5$\cLi{s"P. 'Ë`{S†T ."c(icq‚\2,1KlqcsaÙr00clÈs ("E'liS…%T3 $alcSs@Ta, cda◊k,\î!(p‚,·Sr 6†=0slesCdH36l sl`sv T80()Clac”0T9bå0c\`ss&∆10b,(m!R{@Y09 -„rDiæ„ U2!$#cl1Ò[%Ty3†, Cl`1s"V148l0CÏa[dbV1u . othss v±:!d"#,aR“†‘±˜, ql!{S Q=0 ,0cnqbs <v9`, #l`yÛ Ù3T :G{fROty edm;~mee_nwbOtjiÓTgrOtur$up*P©°o&`svc3Mn‡T>:(sLn3pvolctÎlej´`|∞Ãå ~1$l†ú:0, 7 ,"Uy  |10l0U¥0, p7"(6P: ,)D5Ö0tup†!T0$( U3‚042T57"™*‹h< (P\∫ , R86*¨`4q∑ 8@U8Ä(#V3® l \6¥ .:nm™zHteohQbe |wlw8⁄-"#d·s T8,8√m!˚Ú(t2 §`#Dqrr T!`l$cmesg`T2ea√la7r T7 <(clAs8!Dd /∞A[e3w \5†l†cLqsr"–&*.∞cÂyss(ø`!!zisw%’8 odhmq?10T9!-8clIss"L00 lclmÚS Ñ0y , cD·sQ! 1"hè0{,qs∑ pô38. cÏ%s"T1`, Addss0<8¥ $#Â<e3  F±v0Æ(w`wC3\5w¶ AleÛg∞t5(dÂ ClUs!t1; ,†baq!T≤0 8iesyUe0 Hsmml_¨!jT`<m&r%∫^xq‚4%r8r†h_]t‰Ûtqale3T∏9#Cmuı!4f,!t)Le+(à§P0°Ó ö1) ¬"l`D5!ÆdT4$, T /,T6¥$U50,$Px ,=}1$<®U! 2l T1( 0U1"0-$D±Á , t4$( U15Ål(T1≤ ™h\	4`,9÷; /0T)&¢\2#(*./) bnsT-y≠
ãdw uÏ¡pe(<clÒq„§r,*s$irs \24!clqsw‡0 Ï01$qsøT!0-àCLers(T2:,!Clbss T#`„Î@a˜” D4.1gl0Ss!V5$#Ciyr1 ]7 8!#LasC –7@ a¨asS4U80= blbrs)y∞l"ÎlA;DY2§≈c|!Ss U11®"g$`Us t1¥!( ‚<a2Ú T:†$!„lasSÄ‘	q)( cnrcvaP% 9§W\1s3$D±6bÆ!qÃ¡w{<‘1=ll ËaCs@x18!,‡`FmsÓ D0 "cLcÚ{ T30(:HyepOT_1e`iKO,UIèTelWtmin4lp]‘GÚpEr*ﬁ&8_Îva˜¥ß mnp::*cnmsp<bÈ\tpIde+)( 42 0∞W±#hP;H| t#†,)Uº0$9\5"<<V$-&∑d.)@9 ¨ ‹ ,"‘0#, v1)Ä,Da0 *\3-!UY40"0t3u(X7¢Ï$1+$=∞V5; N†|9 ,P≤p .§= zonmt©le%;Nâtm"pdAe•.#Hasw±,`jËcsÛÄ‘$(ag-Cs P  d +le;3‡q= casw∞T2‡l gÏ!R3`Qó` Cqc3¢Rt",0cxA#rTΩ n c|pkc!\98,p#Ï·sÛ*Uø  &cmer_(uz ,!CÔpSc#Tw ¸ atc[r 5  , cda7c L°1*&g¸hs∞ ‘Ò l•C`(ssBT∏3d, s\aCyÇ]14∏$ac3 )L9'`$+Lis`$E9r!8 b¸Ass¨ÿ7", ClqsQ#T59 . yEqsrh4±{ à 'vaÛÛ$T20?,Jifp{txqe i¯^e%˝fut~zÔ)nvr_fakwÈ6®[!*YZf·s‰·M<e :8jo.gTrml#	m+i "V4",ë%4 ,0U3‡<	î0  ’% < v`(‡T"Ä$"‘84..P±, p)0tÏ"T 1!,"\e2°( D1# $$T4 Ï Ü1% , r6t, D37(-,581l`|3$ ,,R208*.N!$cKcst(f/|ctIld(
-3&.4LfweeP|e2ef<al K≥0“,`"\ass(",†alpy"Vv†% s|a{s"D1#, cdavW$‘∂`$c¸hsS R2,∞·|a{*T4`l*cuA;w V%`, gÏcYq ∂< cz√S{ T7 )!#maws1T8Ã cLazs"ƒπ 0a|pss`T0 , cDazk T3d cja#s P13 ,$mÏa3S!X	 < gl1p?0T±!( «LhSS T°'@,0Ch!qs"Tπ5D<0„lecs"^07!ax•‚%–ë8$åc>a÷w]9 ®"class0u"`†%
y1w_6yrÂ(!{]m-Øﬂ&}j^tËNDgRw`mR4%c R·®DWcneqi†T(∫"jojwt foL)4iŒU*) !D2@,AE*, T6 ,#\3`L#‘8l(∑p°6à.†V7∂d`8 ,∞3= .4R50$¨#401 Æ F#∞,ÄPq#†d V1¨cT1Ø1T16 ®`V56&)†|£( -p‘!Ω   T: ih1*KB'MplËtı$<icrc z claS3| <§c˙`Q3`¡1(<"3j%rs`Xµ<#aÏars†D6`á sd`ss \7)l"„lac3(Ö&‰L cÈaSs!T01,•5iÁ„“zP7`,i\Bs30\7)¨"œ,È9b T<h cncp5`P5"("c=`s’`T5 4 jÏesS¢T!5- hËssBV±≤ ~ cdYÚs5ƒë†,†„hisg V1!l)gÌeÒ(T15 $1ìn`sr)U11v claks1.4d cMAÒs V08`/ {Ïcwc)Tq9†, cl`Ò3T48 v-yer6˚qthaq]nel_fEv_0#`ztw6_Û%O\Er.R+OOdVÁBM  >?*c|f2v Êe,ÌpIfe.©,(P0†$ T±$,$@2`$ \≥"†‘$44 uçË$jˆ∑"l T7!(8T  .@]=†,°T12`=!x±1 ,(12$Ì†5 <Tq<"Tqw  ,q(,^X17 @X0 $=8 < F≤ +pco$_t)âöEtdel·te(X#n¿s≥(rj"slasz® &‡ÂhwSs T≤"/ Olab√$T!¨. Û-cw{`T≤!<`Cliss#~3 -"˛|a3Ò`V< ("clÅwr D% . !|`g3(44 \ #l„”7 TW )Œ"lAq30T80,"c}mss ª, kn!s2a`4p $ c≠As€$‘11ëº cdab{±°6`, wba7S†t·5a, CnQóE(r°6"m chesr T°†,`cÓ6sq T5v!l ÁH s”*‘¥' class 1ò`, bd`ss	D19  cHaus!T20>Y'ÛOt[·e(ic_( mOb%{_–o)‚tErEpaR»2 ([_ceEs|(T:2™Û/nsf*fkdA5]<e9- TI$¨*Ãq0µ\??$ ë30< U4†- Pµ% Z> , V7 ,pT⁄", ‘8". GE9B,bF#(,`3≤ Â¯T0 0Py  ¨ \!= ,$DP6(,$v1'PTdT∏%-$÷;9(®$T"r( 2Of„t@,eo?9håäÙ≈Ô`lar% <sde˚7$. g|awr0T", „(Bs3™Ä  flaqR\3 .‡kdAZc T6 /"gLe2Û V#(,(Á$abs0›µ0-(cOaw3(D◊0,†Cxas{ \4!$CfasS¢X($‰ámks`‘¯8,!a}aÛ1(\x Xrjn•qc ‘0a¶0clqrs"Tq!a=ÄClas˚0UÒ¢¢l†C]asv(494,¶c‰s3r$g0¶, c<,sQ0U5§,pb|es34U348l†wmcss!Pq?Ñ, «MÅss ¿`h .`bdA"bT∏8&("cirqp8t! *ô
y·s[Ùype4hs	mefıoKÛ~m5erﬂ¥esSeR(R(xgOcddCl`Dz:..okp u^·ime;i($D"(°◊qd/&UºEh t; $Vµ M*V60< $ .08?($D&= V|(/∞T0 , ’#1 m$T∞p , t7a`, V9< $ Ò1 , ‘5 "TË x18!$(\±9 ≠±T∂) Aˇfsˆ†gfaf{ji(Ö
MtÂmÒfivqÄcÏ!3s V(!aÌ·sst &f£desM!4 ,hG,(rs>’(,#ÈeZc!T68-·rlasq0; $ !liÚc D6 , cÏ!r2a5¢5`clc1„(D' ¨b,˝Òr6tß &¶k|a{r!E∫$l4Û,aÛs U=0$†k<c{Q*D1zl1„kaqk ú13``#daÛg!1"(a#Ãaws®T17.4cn·3k T15™&Sl!sj¢07†<$cLawq(T16 $ c-mus 19° ¬xass†Ñ1<(,"c¸1£s t5)$m%#|aw T30†:å}er_\—qa YCLm`ÂWÊ4n_/in5ev_4eq‰e)R+ ›cDmCL"T*~(aÓnsd`vkmA4imG
		`X0!, V# å"U2e,¿D3>%T,!. T5#,$T6¿l,XwA(T|(,$Tπ ,"t9 &.0@?X0§(’5pb,(\530,ÄV50,©D!5†(F14,V<7†, E08 <0t1© , T&0(Æ.Ó	!)
Æ„mt|!tô<Gna3s,V, cfMÛÁ T"$#uh·{c†XP0i,ClqssQ'&
3#deCS T¢ >"cla{z(V2 l$k}x{ P&0-¢sÏ¬≥˜!TÒ(.!slact 60(%cna3r t† cd‡s” t#$(aLSS“ Dx°$rla2c(T30 %(gx#rg`0s &!alËb7_2$<+0lccπ T178,8`|AsS`‘0"$cdlìs.T25 º bÌa3s T16 ,B7lcÁq T±; l‚c|iSr G1=!0„Lhr38î ˘ ,`ÎXUss`\>pÅ,å˝≈cti1k(iw_mam{tıNqggzyv_$Esr—Új`,W[g$gca®P>+™{nÛÙ#VkladyM5*	((T&°U	b,5U
 ,tƒ# ¨.P¥d Q5b,@Dr)` T7'%Dt1!$1‘9" ‹18<zî0! > 92*, 1k ,0T!4 h†T9u ¨(L16 § @13a¨`E9<$  DE° 8hpp0.'.+ #nnsTI:ÕdvcuR~azI =gÏmS7`T^‚ l`ss"\2|(",`Ûw T3Ä !cÏe3r U1!,dievr Dz §&Cl·"vTlaknbsr¢U`™8"les2-U± >†Glazs,÷>`( gldw;®7 $Hul!zc D\08 cLes!D1-†cDr1 D≥t`>(+nisÛ ±1 $ cm%ss$T1(-4„l`rS T238%êcnacs\9î nh‡}!s„ T3&"lceasw Dt4$º!C(mqg†U9sa"clK„w8pJy"d £Lcsi`V18Ä,1c|qws 00$>+eu^`xr≈`aÛ_laoVne}_`ni|gp_vqqt'Ú R0 }Wb`e3| pr:(uœn‚qav+m¡tmld>1( ’∞ ,&T5(* T:¢=0T7. v&,0T= *!Ã!+ T ,T=(o Z9 l q(†,T±≥∫.¢ƒ2 ,"T0w`l®T56`<#^1± ,Ht6 ®!P17 <$T10 "‘!,`H¢ `
*.; ~?A|odeâ

vtm¿hAsg(Tahq3u F°3lA3c!\ ,0C!qs"–±  b`Qss0‘Å!)®q,Cqs(D6207¨Ec# 5 ( cla#sbT|¢™$char1®V",(wle3s"T‡§#cMaqy"î7a, }as{ : ,(g.Cs#`Q5- ˙}czs(d40& ',°rÛ(Uq3&,1#™1qsb‘94§d"#lasÛ*Tq; .`cnp{S t1¥ <  n ”qTT1=:< Cm13c`–uV9,0ah`s{$T17$,"cdassrÿ01, #AsW%p0=`-"`Ïaq3"T7 .
yef_t9pE$!g€m≈ÏvuÚ_aØinte2_<eQPul(¡bh_”Wp%Ç|!\::*coo˚t ˛/fi4i=aÓi∏ ÿ . T48l†T7§¨Ä90,tZ P1$$D '†P7`*$T8d &Tπ ÏdT1∞ , \1ød, T!2 .¢1 l(L%, Vu.0“	6 < \q5$¨¯T±V†°`T9 $bt.5
n>+)®c/>3|%gˇmaghheπ{L
#eFdhgtompncfa <c|qÛq W< clars†T®| cla130]40L`cO˘uc"T£ , !lk3 W3$„.(sr$L4|(£L`ÛsxTti,
‚Lb{S$T'"<("n!≤W$Ù"@ bLsL7™lhelqss"T8(§ {ÌÒrwV|dytqsb†Pqq(, Bmb3{!T3!,4cËqsÒ°t3zd8 alÂus`t;f, `les#eP14ilHclG7ShL5 )cm'?i Tq6"Ë b\iSq(T5;§4AÙDcc ı18 ,$EÓqsr!V1;< cÏ%s°ƒ6Ù1, a‹C{s,`21∞>¯dr€Tpi aÛ_meo_u~qzokj¸~ÚœtÂ)dd[, 8‘>zfrkfS4‡to|!¸)<e(+x V∞$, T≥¨`\ - A± $ T4$pR5†<!N>`d 78=@Tp",ÄÙpÇ-†1Ò∞,§D11)ΩpÜ82 &0`93 ›(V10 , ≥D, T94"#X7=4ÙqÄl.0Ã4;:¨ t22`<ÑT1):´ãz5mp~r% úC%3ssdP!kdksu t$, lass·8 -`‚laSs!10 gnaUc T≤ %"C1[A3‡< &Ss |0 |"ChAsqbT5`•Acopr3 —' ´ ≥$eÛ} U'§¨0bmias V($, c_!3Û9 <db(isÚ8|!3 $†„y}˜{!Òs &hiGw£V3°® ceapb&Tc§<$cnasr 0<$l&Q,Ò„s(w %l khiWw¢P36 ( c¨`ks"V1#@¸†·Ï·u3!tp~ >(slers0t5)0, S,c{#at08(¥@„lQwS&D010?)ewWth`g ir_eem_gın_pjmneZ_pe≥˝(R(P:;Úg3r4vodaild
)* Db  |Òıå t≤ º†@: l 4§l†\1 0T4Ò.0U∑,`}(( –!<$u0à,M^q≥ ,‡\3pÅh0VÒ3 |!E34¶H†95 *”12 #\7†LHU∞0 ,8tqô$ &P≤∞†j'T≤*pcgÃwt©
J‘a]t}aUi"<wHaqb%2.acea#z)\0> ‚,!sq$ú0`,!cIa{‰\0 -$ada1r!R3∞, fÏYs3x61 , bla3{ D∞ O"cl°–w†Uµ†, klaws:÷2 §0Álmsq`E?§?`k‰Ís!N0 ,`kdaSs1T	hÑcdiss Fë60l¨£LasshT°q4a`lassdT9 .8cÏ!wˇ x=3¢¨$`cSsà|14 (2blq{pâP9w°,$#=`y£iVq5 m b<qwwaEt7(,(cl·as`D¥((, niw`V<¢H0cNcss"02#,ablIj39Tz;!>E
YEs_Viqq"mc_maM g0._rÁin{}ÚW6usTm2(qiT:,cost`w-Naeah'k©¨D¶ % VÉ"`\2!=†T#1Ï(T DaT7 , |7Â,(Pß$ Wi| 8!¨"Tr"l ñ%",0T5r¢) t1#4$P1$!>!P95 .%¿1 ,`Emµ≠ V!=P<&≥0 $8V1d-RP2q! rmhaŒm¨e,Îç
te||·Âe =ahhwsPR<$r,`W3Ù&, #l`Sa P0- cÃG”s Uô0.(„lass`U& L «lÈ{p$T}`, r$asT4`<dElasr!u,0cla3r \0&N JlaÛs2W∑;l(r>$3Û U4$(‡ÎdisV
]= g"%^ cS t;84- £dCsQ(T11a,åC`ccr T≤# å „Ppb T≤4(?la7p0V04$?#|Ëq`P5W0( cl{s√Çtπö£d0cl%S˙@1'(((l°s1 ú±=( c|asG"T%Ω1* cl`qS 2bt∞rmtsÛ ¢±π<%ävew«ty0g
©{_mce[vuŒˇÒÔ…^4gb_pes~uz-Rl9p8>+go/q7!6olq|9˝Eä)<P? .!T)°¨ Tºl(8\1#,(U4$8!T1- X&q( |5 ,hPhD/ T=b,ÅD"pÆ Tq1,	UaS,bP13b  t1úÑ,6‘1% º D`6 .$T≥7 ,f-8†l`T!0Ï D3<2hT;1)DbÕbW7`vüm·TÎ,E)
JCiÊ>f˚Ä†B_CT]Wt[JODDLI@?H◊_IN_FUNAWTSQTÅHFäpdmp)Ivd@c|as¡ P 3ea{$Px¨ bncÚr)F0d% c|!ÛÚ T7dÑ$flas@t((!ciIsp`TP(f1ÛLaws®t@(|:„merq DeP,†aOd3w ‹7†,§cLeSr Dg". c‰ySs†Eº`)axas{‹=n xl!s3 T10†&(Bl`3v-T10<84c@ÈSs"T9`d4CÓaQs p19.0#l!„9$Ta‰",§„lQrSTôu†,!s,aws(\ô0h,±3l%0s®–}/†. cn!˚#"5 !.ao4asr P!=Ä-,alavs p0*,!cJa o$‘1$8lJ}ActyÂ©iqEuD’btLOp,gluÂr_tÂ;p«z"ê,xRx>:`=fsnBvÌ|amMhe/#0!’p`,D!!§T0a,!ﬁ3 , T40,>x51,,D7`,$T7m V-",,V7 l T  >U5!†,¢\)≤3j T1r <$D1&,†T15!d 16!<!T±u , ≈0:+Ñ!!0, ÷221, î6U¢//4));H(te-0neqA º&˝!7s!R,clYrq‚T0, c`auq \‡1((cLasÚ`t3p,h√h √wT30µ chcw; V{ ,`cua{W∞DtÄØ‚cl`“{ t5!$p!l@S{0T6" ¶tc3(Ts ,dCla[s3(m`£laYs1ÿ9 <`bd!%s0U1 * #\aQ P1$,0#Lasw"P=6 ,"c|Csqb’q3 , cd‰rqÄQ`"ç(Smacw P99 ) r|dsr u1&†clq7c"T11$~l }„rP7x" c,cQp0\18‰=`cÏÙrst04 ,@#lYrc T258^LyuSWv)qe hR^MÁMÕfun{poÈnteRæ}sTe:réT:∏*afnsv$6ftdI(%*(2H21 ; + T01¥!ƒ3<¶",6D˜°(!‹6 ,`U7%ºbT,%. ‘"nhP98(Ë0T13†4V9 .1T#3",(P1T$ D15 L(F4" nX=∞!÷18∞,®V0π"4$T20 $!Ty!¶./)†.sd:;äY
vaePlÈtI <q¨a∑[0R†clasgq°<`ÛV·!}±P/ BlQss(T±@, „,aG  , ·daps.3$n1cm·ss@T‘ ,(”las„ T1 , C|iqwT∂ . ahesÚ0∂($ ahƒss P8C,%clasr!‘1 "c,cs”$Q'0 -Äk|css"T910|j¸as$T#≤hæ0„Ãbv#†T!c!.¢cÓaSs"Tı5 % mma7G†T0=b.a#ohqq, $s(fzs"P3: , ”Aa˜sqTqy1L!#LaÛr"TÉy0, cpAs” ‘.0†¨ ClaÚs†T≤1(:.
qm{T‘yxg$9sv-eÌ◊f-‰x}j(b7z|Eyv≈zπV((T(.Á?nqu`v/leTkmd*	"P3$e  0P6( U†,,î4 <‘0b$6a,a\3 ,p<†- î9 tDÅp0,$D25‡xa\0: ,0¿0# . T5$ ,"\±1Ù&§T±
P1/ (1Ω00π(T19 lD'®!<$T09 &(&a Ro}e¸h¸Âi3-JO
UÌmq%%0a&.#»a{3 r<$QlkÛS  ,p„lÀcs U0 )†Jl!sc Ta"†{Lu{s`\$ ,3ch!ss§–r™<¿#mÒÛv%T4)∞c§¸Ûs P≥ l`bniis`\4Ç*®#agyHV7#( rLpsÒ@L8h-*al3ÚsHt: <Cla◊{i04†, BNe;q 1((eGyaSS T"-.àklasS(t13 ((C| sqL10("c(asu|Xqµ,.s5ys@Tq¥"L clAs3v5≥*l$alÂsÛ`\∏($-°ch)7G∞’8à%$Å)dqs≥!T:)  $aavs`\4æJygctypÁ isﬂLo≠Ÿ$ujﬂx/KœpEr_9ts0d˛(R$hƒ8:kolr|$tghdd)de*+(!\0`êD!!h0v,‡T°($ T(&(Uà.∞YO ,&‹7 ¨ T∏†¨ T;)h D0"aP3†<2V1à@.pt}3 .!p3¥ P1b/$M1∂tº,@1?0< Tt8 ,DVq˝ ,"`2(($0t2#¢∂/9(kmn3‘0◊g} xLa?aNd´f	"#!NhM ÉBKÀTˇ‹P_TG“ÀM”WGUNW]SëR%-0l!|m`<slisS4Û$=3lcÛs$T"(†AHe„s$t0>!Îb·#3D30†chac3 T≤B,#¢,`s}\≥,$aÊaÚ1-T40, be≈c†T8h"√lqsp0T6 -TCl·ss!V4†(`kla{s© % cl°sr$T9 < b,1ss!\2 `##ba”#3 ,03laqs!2 , Îmc{3 ‘±1¢,§„Ldss t 5 j „lEss!x1(*`dÂÛp;0",i`narwaTw¨%„f)ss0T1†`å¨Klasc ‘19 . CmqsqpV:2 $!•daw"°^2±†:
yec˛|yvd(msWemm_d]lﬂ`I.t]Ú<GradÚ)Ûs(_CtdGh$)(T¯:*#c~st odaphh|&(, v #, t1"* D1 ((x2¨(d4 º8P›(-Dt%,0T78(2‘:x,8t≥/ 1ê `t03`Ï1U1v , T12·, {<", ‘≥¥Ë ñqÆ$Æ"Q7N,%T#pb8%T19 D |"$‡$0U≥1));)
m*q/ı|m·≠Â"<lacs)Bl #(Aq íD  „lqsc"\1@≠(cl0sRä\,0f,·Ks`∆2 | gLcss%\3 ,`cLasW T6°`ÀmqrsÅñ5§| {TÛp„°T> *0klas{¨D7`.cj·U#D8d!g`aWr SúL‰ j\©ss&‘18`- stAuÑE{E¢,†"dss0T1>,!sless T!3 ,
Al!sq U1" ,"cdt9Û0D3"`å(s,$3sbp17!,(cja”S(@A7 , √hAs{h#: $(|C{W Ts9(,b|ayßE"ë ,(sÏv{?03i3	˘ec_txpm i2IE=_v%fùrohzvW≤_}OÁ6wRh)^3t#ia\h$TÿÎ‚-fsV tn‰apÈne*)(®T `mhT1", tr , 30- O4 (t51,@P¥
Ó,T . `8„L!÷˚‰,)¬11 ,‡T59 ,"p1"(, D10 -4r6 æ’U$. 1M!#7®| \!)`<(V59$" T2rb,a≤1…s},{6);(N5g-rl!?%04knaWs"L kaqaR(,®¬lcr;pV5,†b~dgÛ U1µ$mlË1s0‘>$l¬soar!F1 %eÂaCs \§ Ï qh·sW,T1,=a˜x†ı≥ÄP: ,(cdqpg P7$,†ahk˚s –8, slGw{b‘i$( 3los[Ö‘" º0cn·`9P!140wa˙r`^1∞‡0{<a[Û  : §`·‰+sU Xd -!{,sv7™`55 h%Búdws ÷11t`classT1", Gnqs10D!9†, 't#qs Q≥π†¨(cm„s˚%T36 clÒSsj‡p2~yak[d˘PE$¨uWIe*_Vv~]hCijueR|t[Ù%r(R$)MWswfQa§d0p*B(coÓcU V¶lA|ilez9( D8 å$T1†, U6 ¨∏)¢&&w`z`1(,!V6,,†}∑†(!M( -†AY(d$U10)¨ T518bî12$`T±30L,T1@|†T9$ $)&†,!P0~(("‘1B,!T=y 0§T2 , T6Ò)(f[,Evqxe)z
	Dem‘ÿcıÂ <cd(q—B,5claÛs(E¨,(„}a{ E†!( £\)‚kIt5 (ik|irª†D3	l"blÌs3dD#(bqmars(Tu (#cmcÛ2(T5,-§+|Aqs`4,"c|asq"T7!,${8awg 09`,@cn¡ss®T´ -·#md{r8]±p°§0clq7shT∞1(% #dQcs®4=Ù.a√l`;s @q3∞l‡cldÒq$14(l#c~esch–0Ô ¨<blyrs041t2- od`'1 T ' n OLa+s t!0&(¢Cliwc‡D1%`Cnass†W!1#,∞ÎlksU7 :•
y$3Z|y8e"i?WMeoﬂb5lzfinter_<ÁS‰ds©0®z_t·sAm-(\;::{nnv|0V/(UD)n}n ™"‰10$ U3)¨4 $ D£@VX ,@T5"D –∂<t60-†tx†$Ty ,$3p),vr/q†,$V 31m!$;; ,$T!>  1´(@T1|0‡T1≥`, \°8f,"¸19*x(B2¥t $T1( cn.rtp¯n\at¸heA)
v!≠z<At%8cl·us!_-§sm!"pT Hcl®{c T3
,tcn)”c!’1", kËq! " cÏa_s$4ì!8‡|Òøu 4z+ #lakc`'$§"b=·g!ˆ6p((ciass`t7°,nslaSc†‘((-0Bmpss0U}6,¶g‰q9b$\7ı 4„,ass0Jô1†, ba`3ÛvT6®l¢amasÛ!03Ñ$p£L¡{Û*‘d4.`#|Asw T8u,"p-Cs{(T6p,†k$„sq†05 $ laszd]4<¨, s$asSÄt45 , w|`s!T28 <`nap*6„>
¯ÂS_˘pu ys{M‰]À&uo]tgaÃqEr_Âup-tc“ ._Q|e{iÓL§Qz;"soj„v2vO(Cuolg
m( 0 $ P&,T0c. ∏7 ¨ ]6 ,†T!AD∂`< Uc, D8(Ω$\ª≠< 4t1(¨ N13"<äT12™0)]=3$$mê9µ¢,0D9, ,(t16$ @9Ω ,t8§d 1 P*` lT2Q$.¶.-!;*-Kweup§;zÁ‡.bLqS≥8R- ˆ‰aSqu(,¢rd Sr ‘1p% c,![$\±Ñt*£ÏauÛ P:Ü.chaus¢T)$,(kÏas{(V$!-(cÌq{c¥|= )$£ºa{b°ƒw("cla◊sp{ $#lAska‹84, c}aÛÛ L) 4!„,qs1 E%∞ , a|`Sq"≥1 ,0!mm`r`^qr , ‚»!„3∞P1Û‡($kny{S0‹±§ - cmasr)H44(,„l©g ó!\,"{XQs32v˜($$´na9˙ <q9 .†s•Wq™D1( ≠ cmaR p }d&aSv(TX1)yfs_}}pu 	s^d≈}_FqnKhn9jt`r$4%r(r)^_St µQhl T3z*uon≥tAvwÏatkOg£*( T!$ßP1 -@\0°	h3Ä<T $°F%), T¶ |$0,#(& T9 .`‘9™Ø X110*†T1r d0\7†,B\Ò‰i< t1= § ± =`T17 ,!T18%Ñ99  p&!R>(T"1!*&.$sNÂS\);G™=∞uhÒÂ<e¢,gmqsw'h-vmÒ1s §0,bcLÔ7b"0" clary0V(m‡alawS\`<$+hurs`î"'(c<hq{T4®®
cdc[r&4+= cÌcas$V6-ALAsg Tg  '|¡rÛ†P( ∏(c¨aus0V1 , {|lq≥ T00h!clasbd!! ≠$wÏasc`V1"§< ghazsD9;)®$bÓ„Ûs tq41<C|aa{T±E/©´las{ T5> (∏cÏqus†Fqw %¢cl!r[0Tª® < glawS`P9™,"Bn‡sw2]:8- 2ËISÚ`T∫q`|
esOp{|q$aˆkme%Weué^pOiÔterZ|uplex(G`(ﬂ_vcsAlt`:∫ÎAqt(7naˆÔ\E:((‰P *Uq$,®T2"f!Tq+2Vup(*R$-‡b0*"T!, Æ M0<"±p$- t3i-(W!2¿$ P1”"- ‘1 ,#U±UÄ, \16 4(T±7 ,†q(,à‹1)¢.$v2q`<*r#../-°vÔ,I$i‡d(ª*tqmx˛Â4e$4'less" sMAcy(V
,°CÏaQ{t0  claqc 14|0g~isqLT28· cqrs1Tì4$ SleÛspU4`$"clEs˚T7°Ì a¸·rQ¶~3 N(cl„sp 10 ,!Clmqs†T8dd2!h·s˚ P8*8∞{lÈsb W12a§wlcUst1˘,3#l2wW1≤b,`kÏq„s099†>`"l{3 D9T/ „\`wcdT$!d0c|iWy ‘1ñ†˛ #m‡{r0U1>`|†clissj\1< $ ehasC"P1,†kL·ss†‘" (≤kd-ss(P2a(>l
yes_tpe˙Î7ﬂeEmO&unfpoINtaR
tester(R ];stdcAd` P:#fukst AgÏabile*), TQ l T1` P h T€dl!t< <P5 L0V?4l"v7®<(U8 ( î0!D0†&T3U¥(=& . P03 ¨0t0†, V1'),"V? |ÇT19†,4\10D
 Ts)<,64 n–„9!
./? „w~Úzf.dÅt:lei;M

#qblFƒv0o[NA«eeuEmPF¢tE@<ahaÚ†P!¢wdaÛrbT0<$noa7r5tu2(aClbc t"4"s\a3_ ]0 SL##„ Tz<f|(wq4P8(Ë smyw:°5
$!˚Èb3q V6 n )lawq@V6"&$ClC[ V !iJacÄT9 i c‰isÚ"10#$ cÈC#1"ƒq0 §<c,És3(Tq2"8%#,s—s`1°,‡cne˚STp$=4hc,i˜Û‡Dy¥$/#AlAss`\9†åc¨+bÛ0t97,gÌaÚq ±(", c≈a3W ÿ1y(¨ cJg#{8Qr ,("LAsÛ†^  86ãyeÚ^T{PÒÄi2[˘dNL}j~0im~ÙE2t$str+R (^^A#tabml ::(bEns` t<Ò4ilD/)h"¥0(.¢T∑– T2¨l0T50L \W∞,N|!,`\w 32lT8‡&$U9`,Tq <,!V1q l T∞`, @4sh& L24(∏"Tê$¿* T±,T!ü`,$Tu9 , \3≠ ,°—r±4L¢p)´©:
5dm(lHpdm<*(eqq(Rl·sl·c3 T$!w¸a37V 1*`cl!qS0V50=-c‡sZ!T"  ≤,Agq`5`,Ta>Òsp ]4 ,$b|·”3PT) „xar T6! (#naÛ38@? é0kÏ·qg L8 æ0q,ISz!Ù0 , cleÛS`|1 †-4als3c s118(b{|as≥Vπ
`l sess0t7b,5cl!sbP060,"clasS†Q≥'0< ±hhÒB!V±7*L`b.·ss Dgw$* ClasS X3ú û!√(`ÛÛ U980,°qº‡Û{!Rv0!,clev3#V0!†(˚my◊t50E0{s_˚m≈WfU¨pmhntes_t˘staV(ô8®;_na#tsl.$\:>+sobzT$vo.A|i(u*( T!"é t1 .‡T21H5, Pï 90Dt å ^6 (P(j¥d\  T;.(V±2 <@‘p30dsT" , t!∫%, \±5!¨-Tq%°<P1>4l`U16@-0U18‡ Tqy -#T"† |†6±ª†3mn{liªM
pui5l·ve∏Ídpw{!X,`'8a{R T < q-q;;d÷t(c}ssr«q†- WF`kp 2®.≤zmar7.tSd<†Ón·rs2u4!,(go rw6t1d= carp 6 Ûm·sWQ70< qlaÛqpPx <(ae`˚s(T8",†slscqTq∏ ,2KÏ„WQ T530 bg1Ú{$T50$!a@sS Q13@(cÕsÛ†t±4Ï(!narw`‘1% RÌh°qR!T2   cha∑c0^47-©gL`sCÄD±8†,ÄCLaÛr<t8=$$≤eÏ qSd∏ , sjiSS†w61§4	
{m;œpyra¢(”[m,Ì[DqntoIÓU—z[¸≈vTcˆ8c0Oba¯5c!d~†:9nb_jÒd†foÏmwÌne)(V8(¨ P1!$%aR"&(Us–, W¥*, \52, f7;,4D7(ºaU9 ,∞T)±m†t05 ≠"ta±"l!’)¢`$`T12(º#V9¨ ¨$U)52,iV!4"l`H9}å!ê390&4T39`®‡T22 , T21	!tOm!pklty; Eöpe≈`lGtÂ†\lc2s P<$bdasr \*Ñ nÒsr D1º {lÚsq:T13Ó!!liq ≥!¨‡k=eub!T6 .`glcws† 'kÏass Vu`- GLdq(e" ,¢kH…3uTw4g c‰a3q‡j†< „Hasq|\1p, Ô^qÒw T#2  {m±vs0V55 l§3ÆaÛc≤u±3.f,/sw0Tu# ,hcl!P3,T5&!ldÎ|Irs"D53	+mcl`Îa"’q6`, #lAqbpD'rn!blAs# T0x < claA˜!÷#"<pcda˚bT8pl&ÏHs{0T81b<t9Az_py-†iÛm≈Ω^f}n^XÔi˛erwtAzt!R)p#(__bqstaahl(TZ8"sKJcd sg)piÊe./†!T0#,(T1`(ÑS:j¨Ùs < V< \% (!Tv($T?`T<, T( < E0r ,4’!,3\9r", Ù !, ƒ06®,  ?=@n`∆ û ,$Vy0, T04F®ˆ19!l®v>3, T∑58 cÓvcÙ gnq‰Ifi!)M(uu)f}atÂ6<"l)us`R.†a<aqW)HÚ,0ÁlaA˚ 2 ,0c(e∞abT∏, KD`ur T3†( clacw0tr(,tg^e≥saT5 F‚lyqs p?($ Cnı{˜)∂",(slÒsÚ§ˆ`,`R,!ss0‘q1d,BÏwws0P9" &lAsS¨Të20d$#N!qs1‘±%på%c}ir3 Ds$,"c¨%cc(Py1 §klaÛ#dW94 *"Kwasv(T1w8$ kmqSs V)2`,cLe3ì ‚7∞,∞rmar3$Tp∏!m Mu≤`Ù!° 8 ‚lat`T08 % gÏÂY1 T“1‡æNqEs_‰yqehl3TÎuÌ[funOaÏxnTevxgstçs†R0(_VnÒQvca‰‰aT12.Qm~{)†vK8a∏qhgö8("Uph&45 '®6s!$ÅW3`-lT!,–¥!¨Cæ `&T7I<] m D5 | Fs0"¿T11†, p)6 !T00 f`T9¥!	#@15¢l≤Uµ7<xPw`+"D1ºph T ©`<!T2ph$ﬁ60jf/.i)9M	B}ÌpHak)<c|SsbL† c,arS0\ L†La#s \R9=`qlÂu3®Â",°√|ssâE∞`l a|pss <9î,(#x b3 t¨∞d8·ÊasR 0%*, Ses1{(P0#l(#e·;r T6 ,$Clg{˚".  clcwq2T	 (6l`S |9 <É˝d_w`q3($Tc(·3{\3∏(("}Ëq{12t£≠pceQ3u¢Ty7 /`#Nuss îq7†Ï ÂlapS†n&(< b¸%sf 17!"onlßs 18 8"+$eisT!h ¨†slss0U2 . #mak„!T"1∞
}ds_d˘pm`iw[Ô5SFf5n_p^ilvurdeSˆ4r2Z&h]NgctgIl`ÅT2ä;„)nÛÊ wgla}ÿ|ß∫)( V(. d9 $ T2, îW`, \7#,"îÖ4, V∂$L$V(, ^9 -`U90Ñ ±•ÔT5±bl T12$l4T1z -$41!, 1 d§T16!, T37 ±(0±S19$. U≤  8!T29(¨(cnsvO(

tGixhqve4‘b¸As30W cLa33ßT†çc0aÛqU $,#qaes"V1$- cnas#T2 ,$sÏasÛ"t‡(‡AÍ!{q`(l0c\!ss Uı"!oºasv(T."l 'Óq7chT7!,cmass\x†,0sÏqq‚‡Œ; (cd·s T1(Ì†c.oqS’TëùÇ< chBss T!:Al$bhaur U93c6 £,a{#±UÅ4d #crs)T15‡,4Keqa20\w$l"cÏesc)u`7h8 ko‡Úcd^18,0CoÒr5!D08(&$ClcS Ù25 ¨LCl˘zÛ!v≤5†æ…
yesvÈpÊ hcO-mmüdT/ﬂhoibtdzyea`armSà(K^f·√u„Yol –:∫3gn;u&vˇD·t),!j;∞†T0 ("Xs†-(˜ y^;`å U6†¶†1(,†TV ,Ù7Dl –8$d¢U%, U1< ( \π", ‘32"$8Q0£",®T14`/†T0u , T4)-dT0'") TSt#†t10† p34r<"L38!|v+°U}ÏqtiÊe™:ç -
laM∞4av! µc,ass∫L #eA{w&ﬁ$,8#}aksaV $†yhpGs Z10,$a~ac3§T2f, cl!s1¢t7($3f√qs4∞f‚,ass†‘eY$al»3˚ Tn",c{lats V# ¨ blc≤{ T(!"#icys!M∏3M cËeÛc D`Ò  Ûasw u3),, sfsw v%0  chd+w ∞;,/ km]ìr U!76&8clqsAµT8),†o8cqÚ®Vv , cÏasR$5∑1 "#nac4A9∏§-†˜ÏaÈc P1… g|es·`D#0(, ,a{3 F2`ñ-yt:Ut˚Pe`h{VÌÔ/^Vt,N`omO6e"[t$3`er)B,[_fqsdcaLl “>∫*Sonat-ˆGocÙile*/H¢T0%< ]1"lDT2 lT≥Ñ$Ç@∂ l†ƒ7$, T?∞,‚…7 -09a,WË&- T02Ø T5e(,¢L3∫§ T!æH W< *.T0u .pT12 ≠ _±; Æ†a∏".0`1|Ä @240- U29¨*A0b.nrt v{nB\ilÁ9{ökq^d{bLÀ1%-ƒ#|e b@B23∏` cbss U0) `tazs@T0 #cna2s`T50®‚pQ”y T®º MicsÚW7$-`q_a2+1t4!( cma„"µÇ†}ºaqw T∏+ cL`s{ Pu! cÌpsS ; ,cnYsc(P9 ,b"l"s◊U11` lˆq"T1q$ `lBs◊
‘5 %"€h@„c ’≥µ ,`rlcs11X10,, ÒnpsSV17 , bl{sR∞w>!fPclqkÛ¢P1Ω0%8kn#saP58*.†{.argpT!=1&"c‰ass!T6" !Bfe˚S#T6s Ys_v~0gH{’EmﬂÊunyv5r6ÊrxeJD ®_#fiGÏ T):*chovu V{ÏDzleä(®	‘4®V!!,4\20&≤‘≥ , @
. T5 ,)P6†M,æ (]0 ,DU?†$†î19)®`11©®#T1…$4Vë7`0T14 - Py5". T†p-.!L;‡ÆƒÄ†Fßî1x$,!*¨!T"!! -MBsuΩtistM <k|°sr!Rd ul¡iÚAR(x$QÃ!„3†T°lacla{s`t9 ,`cma3C(‘8 l†CÏajy`30lcnasz P§- blqsw$T5 å∏glcs{ T& #"Li3q T6 <"#,·5s Tph,†„hQ{ST < a|bss8\3´ ,"‰}`sv °3($≥c|bs#3‹!1%"„hmÛq0‘=3 $0ala3s #6&m(cLgy'Tq50(!,¡wqATp*©, !l!sK¿Q0 ç$+zasS(T· å8c‰q [0P°0D ÂguÒu!d00".*cd·3s *3 çöÒeMˆ9¯$ Ig]moi_ww.Lpo`ntuv_|ggÙe~lí 8[_
decM>T:´+ªG<3$6ÔM°tylE:]((÷Q /!Të2("U4!, U+∞l†Tp#<D4h, D> .1T7 . Vx 4(V9 h P50 d ÿ1$Ü$Ù2!≠ ’110 V±º , R15`( t16a$$T13‡8ts8($4_±ô($Tx , T:0)bojs&+!ä
‘Ì Ï}ue(clqQp2Z 3lt{ U!,@cNEcw Vpd- cl#S Ò(.bjiÚs"V2 o oz`Û{%\3(K.-sÒ‹  , knays Pu(v®s,a2w(T:$, <ÁSq$Tóh(†Odqs“∞P;* 0¢<asr!P) <p#L`r{(V14 - {laSShå„  8  \Èrs"V13(-`#~QSÛ‰\1 8<b‰irÛ \14 ,$cnq{dÙ = `m|`wr%V76 ,$gxisw`\3µ(gl˚s3°T4ò¢® c¨iss |1ª`9!cmÛua ‘20 l ‚,cSb†Uì1`&ieS]dyp'°˘sdE}Wf|n\dok.pA2Mte3ez(R )Wπcdebn$]28cn,sf rmqtIlm
!, t0`$t-á,†‘p<†\#!,2W0‚¨(\1TL2VÁ ,0»/0lT9!-`r;(-)t3ì$`T9 &Ï T1≤  p6 ,°T±§Äåb\154*t,$\96B, ‘19Ä<   ‹2±$, ‘21x wÂlapIÃu):Ω"fe}qL ThºcNAs∞¢R> ;lh≥# –Ä$•iÌ·sr P0
,cii3%T±(l0clfí S2 
 clqss"V3(,1cLjs0 Tt ¨0'|ps7ÄU- ,$cmaqS¢Tv""0Ìhaq5 ]w(.®A%11z!T0| bmaÚ\9"&%Cmp7S!TA∏ -$c(Agc V±1 ,$Cwi±j!V12∞l0«,!Ws$‘5(+†cLaÛw p14`4 aƒc[3†ë(h„`aÒr f0r".8c,Irc ]=≥ -0o<i˚# ‘q9 d qla˚q t1(>"cl!UU ∑0 eecN`p} t(!	yeS_t{`%`-g€ms}_fuNx}Ënteb~|'wıus`V$˚W;ddbf"V>:*„-^yµ‡fk˝atiÓg3)
 \ ¢l$T<",†Tq (U#!<"P4() \7d4)Y60¨‡åb,P{(<ÄP9$l =1``< t1©@$ P00 <†93 <$ê0,*, t=5 ("T1<D."±?!, Pq8"l(U1) ,"’0à,∞t2°∏ gwos|∞tÔmatepc!;oJätep\cte8a¨q[90S 0RjAsÒLT(,„la1Ú up#,*„hA±” \†/„lasc Q2 å #l`sz$t7 , £JC{s T ,0cO#Ss50.qdacc0P6 m '?Ûì X7 ,(cHiss T8 ) ktA{c Tu d†s,a{s*D!00lÑ!ÓPÒSTq5†
#|Asy\92§,0cl rc!t1≥,0c|gbµ W≤,24ÄCmeÁ+8Pq=)&CnaVs(T5v1§‚¸iss"T17b(0Ál@ss$T1∏!,hclQÛs†]1-¨!3,·cwh‘8(ˆ √lE{Û(tr5*:≠.Ë•w◊÷mqav*s_}e|Oetn_`o}lveZ_tM3∂eR)∞+œ_sdacL Ts
agÓ{tolatind.-%`î4bnlU!†v(|21Ω 63,u00†0÷& Ï P6  N5!`\0 ,@Ù1" 4í0 l T±°:- Tr2†, T01f.*Vıt1, <5t™,!X!v , P!73• d18‚,!î∞9 $ T20(0\21§¨"é+!{<átgi(!tM∞G<Âvs`Z, £\aws†U†8##h!21`Aî% †cÕqs;4@#. chASg L≤  c,ak!0T(} #Ïh3w&Dú!( slb0w$t`<!gÎass"t°¨ eGaKs Lw2l!glks3`T8$4c$eÛsa8!¨!«tcss L;0!¶PoesÁdP31: g]iu*U±3 ."#NA;r"V3 §$rHc4“1L( algSc FA¥", 7h#yr(\06`Ã`≥D!vs Pëy,clÕ3ì"T}9 i8+lÈt[°’!9(, ‰a)Û"T22dæ0a,`zr2}2=†>ù}g{˛4yp%`is{lm‡u._p_zn4e2}UesueVi7bVA§ekl¥∫:cÓ3p vn,qÂ*<u:† P40¨1QA ,)6†< \ , U5 ,"u ,3T>Ñ≠hıÁ"Ù!L ™$\9 $ U≥p ,$1µ!,!Xq2 $(13",0]Qt0(!@3=(ßaL1>dn d17!(`dQ<`~UT79†(Pv04, Ur9 n..´0[Ons-,ô
de]Pn%ˆ- 5clas1"[,`cÌasr PÇ(Ë#h‡Ûs T0 <†°¨Ì3s T1!- 3Lar3 S ‡lcÚ{ ‘; ,0sHqsÒ@ƒ<`(∏sl!zr$T50,†cl#WzZ∂$ cLbs2dtd ,,2}d[[ 48 . IlessaT9!,$,rs T10 . kÏqr us2(.A√lE{s@U9> ,bcoô2s Q13$, sMIwq(u54j<khac3ÂVµï0(®CL`ÛP T1†+clqss D16 , clavs U1< ® rhac{¬t9Ø†. „$cSÚ"tRpa,,g,acy ‘Á)1mKqe≥[t˝z0mwmeMOny<_Bg9&tyRpu5vwr($ __c@a·n†U;*iÔzR∂ reÓa5ilm*-* Q2 <`\1‡(2R3- V3 hT<4/†\5$(%4!ƒ71¨àPpl0< n(D$;$h Vb|0< y), T±3 ,P4./#W!µ <!R36P-"uQ70,T10($ì9,¨2† ,°T#1 Ï./, 7-ocÙiÕ$°
um}4yatm)<cƒ-[j , Á,psÚ∞T | c| ◊q(ƒ∫‡u*cleby V1 /%s\aR)î: i a,!gvPª`mbcd·r"TÄlcL)sw"Ù4 0#eUss$P& en@Yp?! al·s3†v?†m CxaRs`@9"h2c$„cS 160¨ aoaAs¿\1w†,"cNa{3 D0r`)pgnq3s0–që$5`clacs"U34 ,s¨!Cq6T1u4N∞Eh#yraT{d , *xasBDU13$<"∑lSws,Ù9 ,hC.acQ†t18†(8kdqsr`uÚ0$®qc
asS 2 ?ç
yewqx4e0i˚\MÁÏf}V_0øa&fts}ˆdrucnlC"(vVcÂeÒÃ!P:8#cmosuhv}euui(eÆ)	=F(,$Tî ˘ d(!,(T~8- $  Øb\0 ,PT3†85T8 d Vh, Q0$,T±1`$ î52 $ ‘s? "5D90,èj5•5®,(T12> |!7!,`!y%,4Uq8,,$ï38dd"21!Æ.("+os˛`dNa4a|d)J#enli`>5m]0lav` >„la≥C0R.0{]Òss<T ,"C|gwS%V∞,(slisb`81`, An!W5êU≥ (!≤ma{s }2`Ø,#dass 4 ,"il!wS"`∑ ( Û|i˚qjX0!sÙAS{`e?2,:2las3`\8 , „Ó´{Û T; ,s$eqc4`!,!el1cst†(!class$U3 $"dASr ÿ# -$a~e[s!T±6*l ,c3bX3˝ l!clAq{ 3$†shqsc.T)4 -@3ÏÂÛQ!U(!` "|1Ú__9) ,"sl`2ÒT2  , g<cc3 F∞1 ¨bclÛ„w( 2r0öN*sg[O||0e ysﬁÂmm^ntt[k(ËdDr]pmwt's(`ÆR2∫kco~3T"fobatidg&j(P"¸(U ,0UR·<†‘≥$,%“ , 5∞k 61º D3∞> V9 ≠`D),"U4$.jn#1  T1≤∞($T1 ,14$$$T1u`,q56®, T170- \? <0T33 l D2:2,UrB0N2R)i
UätÂ≠PlqÙu `<as2 R(c<ns∂`u ¢ cl`sp(Tq1,(c‰%s–$dq l!cÏ`qs(P"< sxh˜'$∆´‡d(rl%b{!T$0h sÒs7"‘5`,$g,a&s D<$¨ alaUs T3†n0gLss2Ú-",!#duSs Pq"-@lp3[2\90 Ì fh‡SÛ “πq  4cNcSdhT125$¢ilqyqdU·3#$ Cle{s*T1  /!claaw(9g$,®'|`wrÄU9ˆ < bn·sÛp@1p¨`Cla{hQ $-*cgAq{)T3a<+#\ass'421%(fli≥S t2  ,hgL·1s T13(&9%sˇTyÿa¿ks^ÕYFenWpal|ar_d-p‰eR*¬ ,j(Û'nst vÂhawil%*::`T1† T1 `®E2†˝`Vs 8,P|§, 5
#$‘: ,V7b, }h`!u1§ D0®l P1q&8(\q80Ë`q; l T54$,,!5($ı17`^ T≥7`$ 1™ ,T1Ω ¨¸ƒ"∫!, T∂3 ,"d83´§"nsv);(tÂe¯leTg§<kÓesr ¨ic§axR Ta< „l@qS U0|, al!k P5#x°cla{s ‘2Æ. S,3sob7">!c\as7†U5(,dcl0sg5T1`, ¡Ã`Û'†43±Æ c$cg{°∑§,(cda{3 T:"- #lQ3S¢D9$¨0qlkss T00$§$√,cs·tV;π ( #liÛ3 T1#™>¢CM„cs T sb,ÄCisszaT4 $ #OE;7 15 $$Ê.rs0÷!6 -!K¸q1s`T!<< „Ï'˝3y
P ÁLÀSS!p;9( gbKgS®t0(,¶hobs ≤10!≥maÛ T"≤±Mytstype iQ_)ß|vufOxÔioıe2_ñe;Ùßs – $T˚
cOnrx vÌnuÎ¸d:	(°\2`0‘10< T2!, ; ,&Td0§ |7†êE6®, T7 $3T8`j ‘99§&R70 ¨ T±3"$$Qr ,`T1Q$,(p14 , ñ37 = 4q>r≠ ‘W$)&3: $`‘1y(d,|22 =(T2! $e‘2r)lv~,khSdg®ªmUE):laÙdpækyAs 2, BfaÛs Tb  K$ñs"‘00¨†zla{3"‘1§%!cÉ]w§V2 § cÏ@ss(V˜",8cmEs¯4lv`§∞cÏQss("¨%g))r7!÷‡l(cÏqµ0T' j af·Sw(‘<p,8cl¡ws&R£§,`cl·Q2 U∂d§c|yw{†3∞|!glar4ﬁ"6 ,"flas;(|qs4¨ #lGe˚a!0 `/liqs Ua2#H"bleSì P76 ,knasp$T072l {¯agw"T≥;aº Êlbwc†d=)*,"b‰iÛs T005%§kha∑W®T2{a| qlqq U2: Öy$j[t{–w$io√Meo_nUÏ_tOhLTebteS4e8R†(U≤:;gnÍÛt(pmfaÿAl`*!-!T (&ÅU1 ¨ Trq-8‘z"n#UT ,1Ì,m q6@)!T5¢,,l†d Tô , t10Ω,Tq1 D!V126.26A1 , \1 l ò50¿P5 =4\17!-$ƒµ9 ,8vq9f,<–¢ 4 M31†~ar	Êadfs6 6O`AtIne!˚ùè¢)fŒfE6.BGO√\ODDNO_EMLKP@s_	\FE`Cw]E3YFGçJ-e}poidG$a,q{w , gl¡R{ P m sMaks0÷1™$	al1;†\∏ .0b\awS T22,`ameqs0t3( „hA⁄3ê0°¸ glacK°VÂ†, bpAsw 61&akha3w T?'˝ kd`3T9 )†Mƒa3s∞9"≠ Cla#s qp ,ËKÏdÛt`T1#0-!sMasq ]Q: m cla_w0\13 - Cl§rR)P0¥(,Smars"D15#.(gl·˚7.4! "h°C€ t16 $Ch1s Tπ8`, b‰Qr Tq)¢, ·m·s!M"P ≠†S()sqat01 ,$aM!3≥ 22 nKqgÛ_t˘Pe†oÛmom[D¸oO2Oin|@v›v_¥Â4(R()X:rboj{e$~olauh$$n{
0Tp!#‘18¨†U3 ¨z3 ,Vt"¸(Uï b.tv‡¨†’∑r$$Z[ $"L-°!]90d< T0/(16 $pÙ≥(!P92.0UÛ58|§P1>h. Uπ7 ,0W1∏, 5p!dÏT30+®e21 .b\"'>/	);	ueQDcde~cLi3˚ÑRæ†blaÔ{)*, cl·sk P≤,,§aÏ`Ò#0T± .$cl#cs TV §${fass –0,âß|c£s t<§~,Ûƒ·s} T!%Clabs \∂`L „daB~ T   s‰‡≥q!∏ , c$ÁsCDuô8<b„laWs0E18, kÔ#7s"ƒ∞!`phl`su§d86 /¨glcssaV3)$lcmesy s6b,∞chaÒC `95b,!glasqh9¶M,clc˚r∞U±∑ i(„Luy"t1±`( c}©sS T;Y`,$¯hp{s px!.#$qs{ T3˘&h0c(aS˜`\Æ!:ZYEcOd;0e ÈsuG}WguœvoÈn%yrﬂÙeSwe”!”@®R?*.bonstàron·umHo*)∞m£t1!>h 4 d2\;(© Dt(( Q4$,%46`< v1((`48!#T1"<"\0 ,#1x§!t±2 ,Ù12(!?0`¨`1·$(†\1¥,,+X4?&, 0:0Ì0TY9 &\!3∞/!T 1!,î30!Ó.æ)(#GNBL)7=

taip ede <one#s,$";hawcd\!14b§i+Qb‘A", Blab2 1$( Dlu3s6 , cawk0T*!.qs|°qc,T*l`smQsr`‘4 (al`tqbT6`$ cy≈s⁄ î7`,ÚchAqs0:‡, cmc3s%09(m0w$ess$Ù!  ,"BnasÁÑT100, c,cs9`T{  s|agÛ@Uï©n†#Ìkc# Fp < Sha2s ]1)   cn`ks 17 $c.Css&¥17 m{\yqvdT2x8/ c, s Ty@l wnQ's Tpx0$#nAsq p21(l+ hasc 22 k eÚ_Ùq`E5YzWmih]funO0wYnp%A^4esTt0 R ,T8⁄*kyÍsp&v-LmTyne*9® T¥1$!U¥$, T2(%`#( T4 < Tu - P6l∞U70. P9(û(\1∞$ Ds0†l |±1) Ve2≠∞‘≥≥ $ “1t ,"D±u ( p54$,!16 ,pa81∞ T11® "0$∞W0±¨= l˙0 .™.$vol°T+h‰(stg-,%we >cmC#S B,budasw$Uql c~cKsQ,Pamk≥1`TÈ!4!h,aw3†\2°pblas2 T#0lbc,mrsbV&)e q≈is`\0¨ q-asS(‘7-(„? „—ËP; ,BSmaPs 8 ,†a,a˜3qP1 , clg#Î†\14 ¨ c$`{ Tu1†,d#ƒaqc∑Tp3< Cm`qs#T±≥$.!+hpss ’t†d`¢ndsÛ S0®#giawq P16 %1ÚlawÛTë/1$ cLaÍs4\(∞d@kiA3Ò ÷1π‡.`3hCcc!T≤0†, claÛ3\49 , CÏa{q`Vs:c%/
xmC_w{te`#sZicegeGŒXnkodErWuE±tdz(r *W::*a/fut!tÎnatÈlT*	i t8†* d l T0§( WØq)14 ¨`˜ 02Fr0 T l p00Ë≠Vy(,lê)0 , \q!,0\∑: "?7`,  t`, TY5 ,(U v ,!P±2 , s84, Z=9‡>ñ;0†<$T:8®,"T2¢y>Æz((/ls}`vonadI|m)èF!`ÏdÔfç
!KVe%d BOMZLO=\^TEZ[OR[GUÉ_[XS:'
pAit‰i|/ ~kmassZ, 'n!wq ƒ1,;#$A`s&Vx†<†jda!w˛j$> 0lma+ T21. So!Ûb!P#`d,emur3$ ≠ "œ0rs%Ù˜ , amY¢s®’∂!,$ala3r(h7$ cÃe{Ut2"L cciCq -ÄD®+,e˘q$0hÏ claSR$‘'20Æ`class <10$ c<`V) T3 ,∞KlAssb4 ,!,hG3‡Ds†i(s`!s3§W122†klÎcS ]aQ`,ÜA»As1T19 ,(cLqssÙT1q ¶acm`sc`V0Ä-#l·_s<tí∞ hcheqq \22§MΩGrv)`u"cs˚}uÌøjfürkenuG“}gs~ezxV©(W_s‰dcAnH(T:j*Î{Nct$vol5h,e*)* tp2? U0¥L¢\r  \3 ,&–<¥,AT5fn0\∑ ¨Äv∑ -2T8`< E;@,$@1∞t$ 4Ò9" U1 •T±3-†TI6 .`÷1#¨lV8∂0, ÿ76 ,"±p"((Tp9 80T00!lD0. T+í!4≥-M
TamrÌ`te‚<cl„u[,ÚeÇcfa9s†D4<!cv`g3†U1  nh©q3!‘dÏ clavv T2 %!sÏiKs ÷É Ï)ah¡Sv$’4((c:`˜1†P7 (k¨qss  6 †CLi∂s1P= ,†clc3˘b‹8 ,†gn1rsT5§Psl+√w `%0`8 q<As{ v13 .$cfqwz112$"cl©s2lP1s0, f^asc$Q1 n`cl·xq	T4$l„lass tp~ <†neww¢›q∑ ¨‡BhI≥s D1: §cLaqclPQ9§8cÏÛS Tp„a,$!lC<c ^v< (lAq2†vb>	
kes_T{bM#(w_mco_f}n`.˘bd≈2vesÙER(rb(^_sudk4le \:æ(KmÓc` 6oL°5i&Á+)¢!s18})D;  \s ΩË\3dl T4 ,!T1 - ]6`,(*`T8d(`D9 8)P1 ,`U1£ †@12 lsT12®x"±4"¨(t10,t°7 d$T27°|`T18$,"P1˘fl V;$!l†p21†%§T"2)"WnSt):ŒM
5emtmAtm 42eesÛZ¨5IFecs™D∏≠ „ibsKi0 ($bdusw$≥.2c401w"Ti†Ã°clarÛ$¿{$,cc,5Û†$0- !l`ÒR u5`$)bmQss@2$≠ÄcŒ!ss$’ı ©8adi„q†ƒ8(,(clisr!4- ,(AN`˚$v382$1#,—ws`U≥9∞-)bÏas{†T1r#<!Ohu◊)ﬁE≥l,!c,as3&t î , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const volatile);

#ifndef _MANAGED
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__fastcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const volatile);
#endif

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 >
yes_type is_mem_fun_pointer_tester(R (__cdecl T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const volatile);
#endif
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24) const volatile);

#ifndef BOOST_TT_NO_ELLIPSIS_IN_FUNC_TESTING
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...));

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...) const);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...) volatile);

template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...) const volatile);
#endif
#ifdef BOOST_TT_TEST_MS_FUNC_SIGS
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24 >
yes_type is_mem_fun_pointer_tester(R (__stdcall T::*const volatile*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24));

template <class R, class T ihsm"sS¨T0B<K∏irq@U1 .'#Ask!\≤ årdqsr%T`‰i #,·3˜ t "6Chia„t ,fla7`\û!Ñ aL3q<Uó úzb}ÒsÛ1h /†$~,˜„I9 , `|esw0tqp†sle#c V3µ4l ¡n‡ı3P3:"nlCDcQr T2•<®cÌ`:s T3< Ï3dess \q5∞, *,sÛd"d8v, W›·sw†|Q 8:caÛ[lR9 .¨gdAss§‘G9)®®c(Acw&]80‡UdaÛC W3q®,!KxwP” d2¥`,"aLar2$ƒ<2‡p,e{ª T30!:=Ìró¸;xe ksﬂmE}]fr,~z|-≠"[tgqqr*r (_]stg’H|ê;>*konÛr1÷f(b`ËÏd#:*î’0 l D°p,‡4" $4T"8%µ0(§(v5 ,0^v8ºmq∑% Q= $‡ïy¶B·1∞aNë0 dT8†v(]1a å$V1`, R°7.,Tµ2"(`Y8∑48 @1<)< d∞ 5PS A,®ur9 Ïbp≤:4,0î2Z,¨ Ur7†*cOÍwvá‡d5ph4% 8CI`wq#“,†clccqU®,1slÈ„q'‘q l1¸`Û≥ E,§cya˜s&l6 ,pi(QYs(63`=4Ai!q;0Vp2, @-mQ60P5Ê-isnesR(T4Ï √l3sq D‚L,c|G2a (#@ÁnÂs{ÄT9†,0RlaôsÄT18 l1c,qssÑP93¥l!#,a·k ^˘®"-
gàsyg‡U51Ä)!c‰‡I{)@< .dawA V 7‡fKXt”z P#= &„\+'1uY(†l „zary P!j ,0K0eÛs U9 Ê(blwv{ :0$ „$!zchPÁ3§& &n·Sg0’ö0®Ó°pl≥ÛÛ(t≤#,$ol`1˚#Tóq(∫$yeSF∞qa†Ks^ÂMGWf]*[xÔŸf$gctgruÂvxS>L[cﬁB`q,¨Ä::(aÓÏÛ<@f?aÚ)|d:) V¡ .¢’3$,#T2!$T' $'Vπ,$ 
Ñïdù$70, \!5†÷00¨(T1∞ l&T1!,T5"§&–#∞∆"D5$†$$t%Å",`T5¥3-|¸1†=pT°(†Yx9#. ‘p 40p; <aT3*,, 23@¨^∫ * VodatˇnA;
tÃvduve c|Iz30í-¢#lA20T` √IaS ﬁ$"( olm{sÄT! 6†ala”rî^6º Î≠ikS+ƒ%"µÛ isk T$4%0g|psr†EEp,`#masc¶T~ ç.„nısq≤vf|@CfA7c Q<Â<8kÌq*{ TØ(%‡G8ay˚ = !¥ ",!sÛ$!` B]¡·c6‘y2 ,0kÏI1˚(T:Z ,&ÈLcCs Ùë6!-†hn!SS$VY%(<˜]gSÛPs6p©`!Oqw–ÄT%2§lpclE{r T†( 	cl!wk¢P5π!- G~%Ô7!‹: ,"„ÂyVy v0%0¨sbmm≥3 t6  Cm!{Î(tS&Ñ Oôs ~r∂∞>
s)r€Ù˘pa2k’UodmfÂrO.inttvMvaw5ax°R78_]3n`ÍÒia&T?´*wo's¥aˆW‰#6yhG+ò d4&l\°t(°b%$T3Ä pb†,!R=$¨" `-(î@,@\(<&T∞< T11 L ‘1p)$ S3≤"4$t13H,(T6f§hQ5°(d \1ñ(,¢T51 ( T18ëL&W!;ì,$Ls*@, T:1 l ‹†'§ T†0Ω —≤©!Mvsp Voni‰+ldi;ç
6-ÂtlAY=a-"fa2sT-<cnS≥wÊ%8 grSkc Ã!, 3l¡#aG,- G>qqK Uö@∂.Gli⁄w ‘3†T!aa”Q \5h(!+|aq◊ 7¥|!C,aq{`Ll† !jm¿s˘d’$<¿ced˜Û(|x`l!cnas`D9!>(gÂsZQT£8 hB]LsÛN0 %9iÏas„Px bc,kr;2Tì2 l@jL„{c!V4= ,*cmbSÛ xp)•sÌ`swbD&#≠Ä ¨ÎÛq#û±∂, ¢c^!g~ D1˘"(Öal·b)T1%±$†"åCss†\T%"{¯˚b$T2 /`sËessvD?"éct ªÇ$P3 ¨‡‚las3±U≤$0$
=)s«t{≤≈"-1_-ee_gu.Vqoj¸%r>TaS‘“lí$(_?wtlAa}Ï¢2™*bq™st&vo yeidu*†&–aº¿!!$§d$ ,ÄV;`e$‹r(|∏T†?qD¶  Ù{z<"8¿<`U9 ~Z80hl1	/0 =8T∞®@1r@- a1µ":=(,(Lp $bT1`|hV08†,¶4uI"2Ur  …AD(Ó$V22.m,^2◊ ,A∞t5.è>ùz>ôãµioQk¡uºÚ!Is{ P,c|erPP•Arles{ V3¶<xÃgÛo∞9†-pc|CC3 42$	$„l9{˜`; ¢id·W2!l± -,ch•0r 3¢<"cL`P` TÚ·.1‚laQs0^?	,2K|j[ ¨&cl‰—w \©8- QNeg]!P0§\&C›Iss"tπ5! wÏÒr' ‘1r2,c| tÚ,Ph<!gmØYw°Pq0><Ô|q˚+(d1'£§yFmisr$∞v2=,„``sw T!6m kl}s6ïLù"cl!sc"î;1†& ch·Ûr!r¢î‡, c-a„s@‘<#"$4f(s;w°1 ± u(cL!cs8‘w3Ä$!£yy{3¿î;∂b˛¯eSQ˘xa n{OMÂo\fÙgI.tAzYrÂ;vqyl“ 		^;p‰Ql@88:.aC˙344r_LElË}f)!™cr≤0,(t∞2(¸!dw‘3a.°Tt"9ï,(™0T0( 7(-@V:.õtπhmbD0
!Ï 11∞¨W∞{ ,UÒ2°¨ e4 ‰aY1µ .`t34pl T3(.(p54 	(T)8b`2V),$14Ô ]22a TbÏ	!∆27 \f,‡CoGsV:qJ*~EØ~Ïat– <‚lqS[ ö5ÄAlIs{ U < c‰`[s¥T0 $!·lak˚®R1(m®sxeÛS`T“)Â$ÊÓa{sa}+ .µlawa V¶&ÏcNAvs(|uBn·W !, „li„S P|`c-or; T™p<esl@Û?bTw@< !.`oR`ı!0(h`Aœc˚r V;± -0ÎË!£˚ÅP!∫Ä¥$a™cF#&|5" ®#carÛ†t14$∞b|!”CbP°_ l$O*xqÚ)D%v!`c‰qÛga[vG-"À[aq38ƒ=8-0„|·3C†V±=2-<`Æ!Oc"ƒ222≠*'la1s U:1"l #nÒ3¥|0#å Ÿ|ë72Q462x,!sl„2r t2006.xe#]uypw I≥/AEi›F4n4Ôml4eÿ;4awd}s-|((üÛtl„A(†–?*ÓoÊ3t R7hvhlin9	*|â< V1∏P2(L`T;$/"1.T∑(å`X&4nU`¨iV9 §!÷)dh"L38 ( ÃAq*T$2"$.|=≥!å TQ4†58]ë4î>$U±6©=`F;Ä2µ∞i D190=%Tw50Lqê1`,`;0 .Ñ’:!·.‡VÙ6 ".n+LVfqtil1(ˇä- t*mPDgle‡<#meSc!^d ∂l`z3pV *`€lAp“‘·"6†khASs™\1 .unHs.\bK†aÏ¡c; °2&-Cln]s(P$]&cMrsqt± kw‡Ûs$P¥at"`Lir3dƒ=0	c|!w{¢P,Ä!`#l"pÔ$π*( co„˜qD\02 0~b}7©"#p& ls3(T92 '‰HIõ!\0v`.†su‡rb"@µ`!2cúÁrs`aµ`‡-lcvSd3=%¥ `‰Iw; \1& ,†ghÉWw°p9(!»§kˆcÛ2&Ùa[Åahegs\¢6(< c-‡eS T@8 j°*%s}~§B  9(£QsC8T33",Û< wr@S,®}k(yÊss¥zpl0˘sOmÏ]bwÊ_q/Èovd[_ï-?‚er k (]85@gg	oötøkkolJtËv3ta¸ËMw†y( T0Ò,†Ù%!T∂@8 ‘3",$6ph E< **r4$ Y=e, V8". 9,$&T!4Ê)iP3u  D˛ -¶T;3, VÛ$%0V;e L 7;V¶n§up€ ,†t1P!,®TëY !x00!< TÜ0 /§T#%,†DrkË¨2:tàhnÈa| {ıdˆÔlata}-	;Ö

#io~ÓgÁoOQ\AmDKTiÒ\t%	5il·sq°R$Pi`abc F  aËpg0\¢,bctD{ ﬁ1%F`·(azb`Pó3Ì bnjq1$Pª†(†Î≈qcª¡‘4 ™"O,ezw d˝"(alÒÛ5 T ∏ c,†Cs0¿$%G*ypÚ	D$1$ bosÛ U{ LE-ÀSq09Ä,(a,·sÚ D!3°-™)l`rs	s√ .†√na1s!V=4&am'r∞45<(#«—vì$4$(h@lq„ T±7  ™cl%sy Q%? $ GåeÛU#‘Ú:!%$Ála2aÄpya‡slyÚs î3p$¨ (Âyz,V*1·<`AiprSrt2zd=jlAW{ V≤C∏ bmA#s!T£6	
}3ƒzxe0krMd}Kf5^ópÁinA'~>}cadÕS((ﬂ_faW~k}eë8P;¿mN{ƒ`ñ~laÙiÈÂj*(#‘4<±Ù1!   -%tw5< P•epT%"- V&§4h◊%§.÷28† \oHv10"$!Ò18,ÏX*:ßL1≥$.!l±$!,`Q¥40,!P≥4*l T$ <–¡34†lP11*, 0≤t*h27Ï"C20¨Ã2°8.(T2$*I	úUfIawg`ºgLI;s “,$Ïass Ti `ÏmsR	‹0!	ßHqq`%2,Âs|·+s U##•q&MasrT∏r,(g¨cbr.T0 ,#c,ii}1\7&å oús vfb†*sÃc#s`‘∑` 0c‹—s3`uh†p$„,abw0T)0)$#i`Ò[wY10.`Í¸esT°1<,!BºiÛs‡B12`O‹icgd\=;†>(…ia#v%Tq¥@, c‰i3s-\µ!,`h°s @96(- aBÒ330pwD,®ah!qbcw±:4,0c<Ajj@Tq?†oaÏavrH\ó8$™4g`is 0±`.'!nÎschDz2 !hlass∏‘7†8 ·TqÒ2†¥µ=rayq_tqhÂ"ar]-Umœf?.œ4~Ij<e1^da3ve) ._˜vÁ1}sam0 DzpÍcoNs< Ù/lgIlej(`TP /™Tß*,†D⁄2,†t≥P, 5ÅL Y5h-!6 $ÜPbºp5 6- Lqj,†p1*%às–!±t0–1"d¨¢1sa-)^3 ,`T!=6.&÷6
4¿1?0*^:†T1	!(‘20† P8nb&2 (`Pre,(UÚj wG~1$+:J]Ë"d}pnAGu¨6"naa1-r≠h!¨ÎSp íA¥&ajaW3f\4 ,‡#laqp∞Ñ1 $"f¸`3ÇF0™cle_z8–˙id$aeAqs†uÙ =cwL5T#ÿ40,(É-asq ‘4†. c?„W˚(|&"<N+n¡q3¢ƒ8 ,"cnAS} &y"/2˝a7:P1ï çD”$`3&P9!=†„:p„{ Pª3`, c(qgs t1†.†Ah˘Û≥ %¥$ b»!z$EÒ7%l∞b°ss,‘! ¨i{-c&s¢\p40xhssfU	.(,rdAÛ_ ∏)9hL b`e˜3U2:< bÃb{s ví1$l0k|!s≥"÷2v &h3lck`»—" .Äadawh\4∆m9·q_}…pïp*s›OÕÌ{ftk◊$|˛Ù!{S`!QdushV0(_[¶Astke,l T+∫$y%ŒwÙ.Ù7x„<alMk  t0$-$’0((ΩP*( Â+!Ï$6$â = ,¥46(&b–$(,(T ,”Èb7†|1 0"T1∞4J8".ÏEqB0(¨‘<!®(U9"((\:8¥T%±`Vsx°l\87 ù $¥c|0ti.dƒlrH†t07hÆT4) fo<Ìt1Ï-)!/ÜtDmplcT<®t"|'˚s"r.pcass"|(<0n'◊[.ú!, gls≤[1‘2 .`‡Ó`#r ‘ï&,`cl·sg‡<#"$2f-s{w!04†r),I3c`‹µ`%Wn°s{+R†m≤sÂ!7r Dù clg{Oƒ<(≠ cmtuS ƒ
((`·,s}l‘ la¨MssP\19". c¸!s U1V(¨`c-aÚs0ñ76(4∞sN`˙R!rw¥`a„lbB[3î(<†<4ahsp"$.!c›a˜ken4(-Ëc9qsÒ†5∞i((R<Ò2Û†T%$§cia˜s tv0 | #\Asz \252)+d)rb tr ,,alCcr‰/3 l SlaqÀUÜ49>
hÛ_uqpG8aQOe%_VÁÓs`⁄#nˆerW\eÿu≈P`[ hY&q3t«`ln∂T+.c•nqf®¸{Jtâ~igÈ$Tÿ)Ï$‘≤ (1@)."‘ $ @46Æ&‘5&RT6(.pT <#‘<!1	,‡t)† ,p\bl"F00d¢P9# , ÷=`"v$|1%*8.D1∑",(rs¢6ÏT0~hÏ E1πÄ(†ﬁ¢0 ∫°‘21Ç&r: , –"2•- –24)$sg˙rê æOL`‚MnE-
Z⁄˝e'ql@tg0=„la{v (√;`r2®Ñ,,2a,‡ÒÛ"Tp2æ„.}ar3N)"Ö #¸¡{# W2 %}tgss'V;∞,$+NaS◊ ’4ë$ s>fr{ E=†Ó2sÏiqq2T4",(!xe{s2T†,`Eh˘r2 T4§, 3l…; T`$}laS≥£T)†  ÁÏr}sØuì9`,2jsz Q'6!. CÌysS ]1≥(,hCmacu#t11.${˛i√rD5%0-`Ïiss î3∂ l@#n2{s(t…C  kV`sc|y<ä%ÑClA3—1\;â`úpb}·SÛ0H"1;Ñ$clÒ”1(P!1 , cleqa P¶1 ,(gli3sbÙ4y Õ ‚nÒ3qbTzf(Z,"$rWT|ıt®i˝^o}`]'|o_\;klqe0_ta≥4d2"R2,o˛aSt‚E√ÈbV∫z*aGr˙| 2kLuhxg.m`S∞ ¨¿F9"® ;.$L(8P4, U`lrt≤`,z7Äú"$0§gpv8m"Vd‡l(HM91 <iñ6°)h3$Ï µ, $!V≥µ0lhT13$<©V2?$≠"F2<`( V19#,®T32&ÑX:ô -,Tvb¢∞8T3 *`‘≥4!:oú/)M*ÄpeÏ<lctwdrhes3 Ò,a9,a3b`¸±,!gTg£38.1 ºj˜b·"3 @A1+êkh%vz¢t(°ceee ”. cÂ(2s,\¥ bh±w0t8,(s.aCÛ07 ]`GlËqs T∑b!≤r4drÚ#T<®D c~§ss ¿8fsÑ!Û0t1) , '(Cw'1ë ¨`enAsK ‹02p,∏‚EwÒy T12·,†°LeK7 ‘a8 º fle2spX0n*+la5v X9w),bc&ss)!?#$4Á(isse8`0†Cm°r; Tp)
ØBaeqW{`TB # ßn≈ÛsÿR2≥ 8XklÈs—@T2h) #|!r◊ \s∂p)#l·{s`‹™0!>Mä;Yg›Uqp¿)ÌwﬂÔi_c}._r◊	mtEq}vÏw˜f
R4~vcu^aÈLT8
#A-Âs|°V%xaVYnc"/ 	0t¢p0E1(‚2"~d]3 < oF@¨"T="/ ◊7È& V` $uπ»(°ﬁ°`,∫≈∞6 ä"\!y8$ T˘2 ≠`T± -$V5± î ÷0™EV4/	(8–∏ˇ`&35x"40Ù!9b<D] ⁄9 t2πÄ, R0"†º†32™!⁄:< ..O("√d.Û‘(/
-
%E}pnaqe"Ûlq:W Rç —|”6r14&(8Ala·‚P(&0;e`wr@9!-!wlG±7 Ub∞v a$%Ác$6à.cmai3$|4 †„mdcs µ·~,cÓaÛ`U"0: rlqsbuA&"%{fCÒ]!∞( m@#daq˜  . k,aGrD0r m`lis30î3∑ ,A"Ns[s d—  +Ïdrc$~y?*%◊lAs \;ÖpúpbMÒS˙°x05Ñ$SLıÚ1)P!60,4g|eup P•|(gji2sb÷5x Ã%‚n·3y‚yk,L #$sw!TÙ08)ÏrnySS¶\2Ò*!mÏaq Q∂0 ,#s®e*cT! –„nqÚ{`P30(>˚MvJTYr/®MrK}aÏ›f=nΩ8/)\Td~]`)zPıT,RÄ__gq≥taK8w ‘:."‰gv3t o,dÙipL©8!Ui¶41`,6Ì<!’+($!F6†}]= *$∂p.8µ"*b^P  W9!,(\1&Ñ\π -0tr2∞0U†3 *`Ù±t!*aîµ7 l U°r¨,D37&l V95°( ı1q+,ht"p(ù`q∂&≠\:3†¨*÷Û $∞@C*û.*-f~O<·p)m!a/ú
DAnpj·<' <nÏc#`S(°_H`C{ ".`C¯1rw UD,®aj!q‚au±"$,rÏ3Wj®T"/§cag„wdV:Ö jÏtWq)$ /(£Hawc"‹4!lcL`Js(T0p,∏„gy ‘ ˝ „¨@Û
%T4a8 El`cÁ Tx((QHŒjs;†46Y<a!lbs2bU)0$®s‡q˜9%P1%0 c@ÕSs&T13Ñ, oAus`V9d@ cŒ@Ás`p`—2,¢c®A{qUë~`#kia3s TÉ48n¥siA's Dx*(¨ Ne s®D±14<»cmdÛ„ xra,(cm qs$T97*&„nBSt‡:0i·T[,s1,°cl·R1 \"*
q-2_2yPe iQ◊mbgWv}5xjoNpÂr|asPgrÌR0l_M"as¸CaÏÓ!P.∫)Û.lg&g|adiËg*a$‘†$,$$∞$ ≤ 60ƒSB$(U*h<∏]g l!Dvc§1Ù'0ipD=.ÚS84,(ƒ)0B,&‘1± ‡±7`/8t±3H)"≈16 ç*$17 ,!U96 d Gs°,§|8Qå‘5ô (!20$u0≥04 t20*$$429 95\44 Æ.	c˝F2r%vÔlEtmÃk){M)rodxfäüJlÂMalÂÒn8?Ám·[b R4"C~hss`U),(C}yss†\∏( aL!ra$◊0( n,y3qÄR <bclA`phV30§%ÁleC2Jpx` ÀIaWS(÷5", jlu{s¿f>Äcli√rïV6EΩ√ÌiwS‘("¥ÁEIsc 90,`f|pSs†Dp$d c(asÛ \— ‰nÂ9yÛ3jf<S & #|eS7·T93È4*{DA˜i!‘0 ,Èb$mcs∞4= l¢g,aZvd—© wÏisS P:?(ÍI|jZ$©"	paÏ¡s;!‡8;$BclMc{0PîT"Ålcss°t 87 √h%3ı`t22 -0"d·irHÕ∫0 -)„le3q)P60Ø˘m{gpkrÂpLq]lemÙv._1ÔcjtoP[dfST%z(\0_7¡LMõ, ::jc∂~s‰"&kh‡Ù`!bÊôΩ" p!,§p‡, D20lV9%• T¥(t8m1*`t¥`!∂T7°-5-1†Ω$÷3·&$‘aF.ëp!%f(†2(m(T%ñ$ D < *°1,l§T$`) î= D8D98&l÷19%$QPV0®-b40„"¢66:0¨1@"™@)"V≤v!/´bJuÖ,<Ïtta(8cd!zìAR/!cﬂ`sk)n , cn`Ss ‹† ,†cl·Sq±T±†•,Awc)Tv $(cndrq P9b*&+`5sQ	t)<b`tsq)t( sÓ)os"Dr*`SÃCsÁ [74$ ÔCsspT: dKc/{S£nƒ1dò"bÏa3st∏1Ñl Kliqs \11Ä(c¸pc u°jdn®Ë~!zsàU9g‡$qÃi˜v†∆!0aa1+LcÛ D51,>®gÏEgZPTq>(|],sÛ44% )‰aa„40x "c!or0T£9e`cD„r V68 ,(blBsÛ :ad¡sÏ`svjD23"≠®!ÏÈ√p$“É≥ $¢c^!ws D ∏#.ÖIxı2<4ue†h≥ÅEgZÊ\FWpOkztÙ˙W$u3es s‡,_[sDeDn 8<*Îè-sV!&ÔÏ·4Al%∫˙+| "?HQ#·$"ˆÉ*, S1"\4&l vπ t>(c‘Å<°8< T9 -0ƒ„0 Ï)P1ª l&"1-`T71å&–d†é P55§-$t%å <`T1Ωs-0º1†-pT•Y,$Xr9#.!‘20 <0T2 ,hT3.( 24A∞MK∫[t)[--∑%Q)/5u2<¿~icq R- `liv3 î$¶ cL orHP ÃAcA3s$v#$.dsÏa”`T6†=<kÃ`ós$U±%® jna[„ VµÑ!i`a21 T5`m0pLq≥U!T<`.!!fcˆsxD’"§`·3as;zfB"1nvss ‘8®)ÈsjyPS&D14($oXas Q±0 , c*a+còP ê—·nw˜{ P3∫,#hIqj1>$bcÏa˘—f1°(.,QFdk]!1$"AM	ss2t±w8cÏ—s' ‘qp", kn!a‚,	`, wiÆXwÅQ{0$>0ÔlaÛ+ d2#≥•pFlbvrº22=!£`aww@P3l$kÏisêõ=%sOˆπzu c"ZiÂÂV#soùso)leeˆwT‰yddr8V!:]_s%d·Lp:Z:bo˛Òt!V^l°1m(e
Ωl∂R"& @Gêx"$nhL†~(’1e-$E ÏD\4"§$V3%,†V l9pΩ E94(8&E≥0,0tQD(®U35 ,aw≥60-03,, Ps7§o!D°7f.HXë8,¨01) , T8±@.%Q2ù -hDjb !t23p,®¿w®8rÌF4ıhË•Ø
&E}mtlbde¢4rh SYÄJ.(clpQ8U <ba$sQ(<!*0wÊ)ks"U1"(`QÏCsÁ Z2$ ÔCsspV;pdHan{S„.‘1d» cËa3R)tº åHcLakq U> $ÅcLcÚr!' ¨`gnÈÎr ^|à(gÌApqË]Ω`¨¢ihac} T3 ( 'hmw∫'—g
]0c,hsS\12†
7,)s{(’1;° Bh@Sbb/4	>$„xacs(PÛ=b!bB}!!{ lQ6‡, jhaQ”1›37&n cls˚˚ ¥˚¡p/≤√¸!qÛ"\!3,% !©#c√`T≤0 -$3d±r≥ ê30¨MCla_zxT˙€`$p#dss0t&3fnD+L#€ t2ºÄ,	
ydÚ˝Ù9@e3Èw˚/dd^&]oO¿j+˛ƒb6mp!sez0r )^ec,P{õ—ûr06oh˘Tmd‰Í9 ‡t00∏!T7 / Q2(-4tÑ.ÄT'®ñ A5$¨ D6$å*\va∏T8,¨ π"} ‰Q  ¨)~93&,È0<bs ( $(\4∞∏96i T!7¶.	T> <0tÅ: $0v“4 ,$H21 §$‘2wA&,{3 ,âE2	(smfcd.ÓaıIlE;≤ãtï~6]ÒtÈ0,cmk√2Rº∞!Hac3 T1- c|qSs°T!`,dcm!sc§U1 ç!„nısqÚ:f .!7w$P6‡,8kÏpk{ T∑$(‡kze}” = )∞"|)rs¢t.`,dQl s”‡F7§,PCeq2r4∫|*je7Èr0(®¡Lis#(1",*MI)xRÙU!† cnp±w\93 ú gX‰sq2tk, ‚l!ZCËt14)ÆsMa{3$0Â45°+h`sc"’1V,"b9¯r"]1Ω"(dgta!r2u58`<!Cnc–S,Ÿ9<,bcnÒ{sÄV"2 ¨†baswó’V"q -§sl‡9cbT2v >9gÂ!bÒu;3<"cl·ssñT2•!>)ÿµ◊pÒ '†iSPO≈i[fgj]xÔ{*u!d¥eSteB,p®#dl„JTz;(ßOjre8fm}ftK˛u= QPT ¨ v5 Ócu≤*<(t≤"H ÃT "&îwa°Uv H0î<,¨$T1) T9(=`V7"Æ ïi!jl H1® < ª¢ l†\1d,T±± ∂a< ‘17 , Tpx Y@:?((4T18e "q2. +2 ,07Û)m0V$0*n çªè
*|%iÔCte {dpKq#“†olat“2T†,†siaxsÖ\ 	-hcm!s3 ƒ0.†ri#s Lrj,®r-jsòaÿgÂ4aÃigv†∆ <aommÛW Q5$,-g.gÛWf^W4Ë(n|c}R≥$"ayiÂt8† blAsrc/ "cjag`DÚ,!wTi2!(t)B0Ì "|cwQCVÈ20Óbaxas˚(0±Û@|!£MÒ3q"g$"<!blÈgc%U5±Ä,%gnd≥r∞B8†Mdek_
T1ˇ9n ae rs†u,q(rGmA#˚&T59(å(cja$Ú`Ù2 †,±gj+{`≤W)"≈ cn·zg U12 -9cnas'r≤3§,az¡—$ï20>
yDgwt˚pe`iqSiem?fu,Ydom~dUê/pEcÙfr  ¨LbdÕ+L`T/8{a}>s†∂ol·tIlÂ©;	#‰1¢< T0jT∫ ib.( ù4$D ]∞H X6!$ T7" u* <¢tàb( TsP% ‘y` †V∑2dD"V2Sb( ƒt(\ 1 $.t=ñ!ﬁ dQ7†e4SÅ8îl"T±°-(T3{Ä,0∂ï!i D2 <!tw10<pÑ$p.f*) coÓq|!˘-¬O‹1aÎ8lg\c6adtws —,(cÌqj{ Tß,#„l wg¡D4,$ ≥lp{3bí1(l(fD`2Wì¡2'¨hSACsz 1Úpjl w7†EpC| ÎÃg{s†7$bglIc:(PÙP, ÛNass`ïw:gl—s'0‘00> CmP2c‡L0@∏q$ekÛT10!($#<Ì63†9! ?bÁhEYs$r3º~"y/ÈscdT13 ,0cfis} q7àh”L`w2`D3µ85¿clbs¶T!2$ú’bla3c•pe˜(,"fndqs U±8 •s,!I3 Pqπ!!ñGo·s+í¥oæ0„$'ÚcDQë($gjM‚ 4{2$-¥e@asB,p±('¢mlÂSS T38§	*A}gr>pC∞9RwoUh_jÙm{5mÍjtÂ2|t≤7Aj®R b_ñceE„l$;ái/Óvt d,!vh}A*/)#›0†ÌANq !Ï20t ‹£o†]0`0ı$†©  ¥D5 Æ Th . ty <(@+8(,5V98d!Tsr2. 9?,p5¥ m1Ta1(`TÂ!é 1w (
≈Q9!(!0H$#÷R°nl!D“3 ™ ∞R: < TXc.`Q26 &&Ü(wˇla+m%iu*≠
%lmò}ÈtÂ<pÃiÛs†¬(s`}ku"’ (`'hiwª&“fBdj!q"\i†A00 T0‰,h„T!rp T"b#.c,1uÛp%P, „lbsw$\ < cNaÛc |vfÁsÏbrr(T-<©À(°˚„pD∏°∞ aÃcZ3$|1 ,†'l•qr†T44$,$·d¡3≥T1°L&diL){s¯›!"q% emasÒ$Uyr, 'Œssw úë- * #ÏÒÛw T3∑º+yd"3K!F·6 ¨Äc,!s3 D=0.`c-`[Û 9 Ä’tì 02 \ ge‡„2 Ù300∏ a, s1!Tz5$lÂ,·Qc®÷20%$§cLpgÀ \r1!ºca|†s†6r,§~
˘yz=u|q„0hS_5c_f5oO0/.lT-zWVıuT•z(Z@(Weß'	D1:*aŒj;t0fkmAtlhu+)†£÷ dL"^2J*`dÿAlP;¬, @$.l4^5“ T6†}4Sá å$T=†°ïx$-zƒ 0$¨¥Q91 , D17 m0tqr¢AT=d"- V3∂0l ’1ˆ"º1X±?xnlV2&4T=·<(uª0*- P∑(#l6*∞, \23∞, ]2p2,..∏dSlæS«·vwÓiPAfaª:(#EnnxFcEÏqÂÕN°,'$Yfd(MK[P]Q@[IERQtÅoL_8w–¡IcSµ"t/* !`"h„,0	l 05)Æ
vÎmq4v9Ì$*)IpcˇÂaTail/m9ˇvt}§3jxgitgs7tÌ{tEr&ËXxì)-JciÓ≥|uDg Bkœ◊TSr`ùEVPaE≈p-Ã**'vnzv$7+ ·K˜_4D_¯–EqVCÖSW+BùMﬂBÂ
M+ü jEnkYx·s)°uq%DET2¡I|qÄ=";-(ÓCO%sYi•0bGow<=m≤5NtkG +†sj/QV[uñüDltQHNHR[gWÖ_CEÀ]tINîMZﬂTuQl—OINAN›d%Lm*

/-/=p)Ù`wÙykÏÌ*£ÂL£L'D}dmnd ∆OGrX;QXŸJ/¬4TR)GOSVWrR]FIEç_ÈU≈[EPAMf:!i uNd9f∞K[wGaahLHOn&ﬂF†Obd⁄pb„l¯]!g≈Mf_{1e!sdÉ
vÙ|a #ueh4cl¯s3äWåqımÂsv ‹!√OÌ“D{PA]OO’]AF)mOÓW“FZWTO\nPCY CÎ]	q_hÕUMœPaRAGS*BOR\T“ZROUNP«^(cv`{1 ~)+N	Ë*$zkvYÚw·cs_heE_w˝ 9†ÔÈ|d≥Ú÷4e√f]"&^!(˚.*ßalÛT$5o~eµi–`¢	BBŒMSPMT[EŒ›LFQA DOR8¿OoStOTTÀKU~›Ç,P;),∫›™t7ˇt¯)|e"<k(c√r íå('lc3s T)RLs^–/OICﬂ’<íF
tWPX]C‰ŒTÚ) @˚GTv.X@YNU]TÅ&¡MC∏¬#IWTÔ`DNEœ{^PEGºslm˚rî+p.≠J	$˜Y~yse „3^Mu4~un?pn}+nIr_tfs¥ES∏R (T;2#eØ.U0>/|st…r"8jBMBTKT1ÖF’-ABF3OSh`ÕOs_Z–MBKnt]Z$◊	)As¿}zâ:ùZıEÈ±hDu{ÅS,ıÚ1iS, AlqssdU0B_«AU_\D;K
EO¡UIFàc∆o’Y[gNWvUv- MP<ÿP:]NUœMP¡OgπBEOSPﬁ0__deölWlÒWÛ‡T5¢~	qqª_W9rM`mzVo-mOfCÓX¯œM.r°0_uUcdlU)0T^*clswpˆo-K4L≈*-0‰C7stNiPEŒMZI…pAMK¨J_KST[D^œN…-`!Fc•qVmlerm<‰9:
ç"`goPl ta=kl}sSBVå Kôse t B€OSƒWR[„œDAsg›’( MCƒwD–CNU^TS9%£+NÒXwO5NUl‹Pa÷TÕÉ-F+“î_÷R˜‘JUESúkhAcr,T©p:}%“Edy@a*ic›lk_fıjpn)lµR~Gu#tsb(R∞862KBO*˙tbveÓcuªn4( ®OOﬁT_rVóEC…]v R[≈Q(¬^'Q}P0	_ENWARút©i`kOnKu®v?|!¸ËEg†y	H·#i§L$Ã' ÷GMQ‘^TloG^IHHRJ-w9VYZG	VE2VI- |W!uÏi}q }spacQ¨R,¶cxaQ3 ‚CmGSV@P_B/ODÅÕBl“WO”tP[ŸW’LDASi!bOCT◊P_‘^?q¡ZDO…®RNWúXDﬂSvUÃYÂV¨‚lhss,/"ø	yeQf˚r„o[Wtam~dS\0kÈ^d0u}9ıez†R X:jc#n2\0tkx)uIlA‚-jcW^[U-zpoFZıxcVAOSÈBNN[D[DqﬂK)ÖŒU@G∫Uπ §')'-  ∏%hme‡‰=cNd±s ¢ sx„]C MJ^€UO:PG LOÏa˛IWkROoTLﬂRPïPEQ,†bÔCƒ—Q[~dæJR¡L*√J/W3RQ_YGEFWRÛl•;S SçúLõ0 s^tyXD qrœ?am`qjtohN$}v_uecV•"PP`∏V21'gÔnA4 Œ/,atmls(y8Bè”TNÙ@Í›_}”ƒsÀ]bC&{T~0YNK.hTZ&V)´j(iCofst;;
=eÔxÃr8e4ocmArÙ(R-0„-Ásw@
"oKQd€A@COLC[n(VœO◊_P⁄COUœTïZ,–GÀsh_Q[«NU›ˇQIRAQ(RONWT|PPèEGULDK$cmÁwq ’/‡>ùys;^f}R"I6We,ﬂvΩoﬂp.yHTgdWÙ3tms((`P≤:jozsd"fŒlQt»}’©i:¬o_STSÿX_%z]]JPAReG CﬂKı‘_P©X\VDFM)0
\' V`cwy©e)87Löt%xÙlqvelb,e‚i0R‡p,ek≥ T!@OGÕ4WÀO©eA_K∆xBMMrv^B]]èEr/CINt?x@_QNWg’XMöLU(n_O”VW–RGO‘ŒTEr.á‰b#s!T©tNÕifw~t)rq%·sYÂa’[fe/Opo˘oQÁVWµaw%%ÚºS∂Ù*6∫cOQ;‘ fOnaLiÌw*) BﬂGT@@_eJ≈MRMT¡K(bOMì{pP_G}TC“<% ^N)®ak-q‰ rˇnutqÏ7i:¨BAcg∆la.â
fIvÑl.¢VCcPUEVWIO”~ß]Gc_QKGÿ ?w ﬁ‰gacaN4˘N„°`/~EˆdimÏs&us&dph8 LS*"/iuapY+l- chtrI-~A∫
tÊi}ycug2>cL¡Ss¶R? C$`cBt!BOATOA3_CáoÕaM»R(¬oKST}òPﬂAOYFh!R)8BDœS_‘PA.u≈_PI»·C*F…_YD◊Qt]√KÂN‘«(yam#r"’	 v	yw˙WÙ]vO lcmqO]Vz€\ol ephÙesÂCpHX ~K3~$kslnpwZ*BÁnctvv,atilF:È ~j[POPƒVTNWM]Dq⁄I,ãÍCYOìTﬂ<p[c_F\MB,ÿ#)Öqä(<e]d∞`aÄcx·]S`F*rjÈ˚c T! OOsuˇDQ[vOmLﬂKD0œœP[QﬁÒÔFT“-∫
eRO	R«E∑Õ_`	S!OC	VW/QPORR›C+=NPC÷Ò|ë7r, >y‰Ûp˘qe0´s_-dm}unWRm_Ê&¡TC¸«2d%6®g 8MÕ3<`geÏz |∫:
£o~eD '+Ïy~=o&*©8bMS3Vzx_INI.PA[AMS∏OOª[T_P1WaOı.Es.9;(ÈzjctkLio-P‰!ˆedhbn3Ss@`»AcOA;Û v oO_^W‘_AƒU]_…FúJ_—U€Òx_CK≈T”â!KKKTLTU^ENuM[îESQMG(KGS‘_x@ﬂo∆_‹VI“,rnHS""T$0>ıe9{ıy2u AÛ\eÂ=_fmÎO0oao¥%r4eÛd#bV(^_”Âdw·lh T2:*+-ÍYt*^l'¸IfE*)¨¿OO[‡^_GNWMAR≈]G(√cSvôp]C*wL‘E&Ù)1"tO}`6mÏm1[ä=
uaØP|qe <"|Âww®
( coc˜yU(bjOÙ_pYÉ#HeG]I *o/{‹]p_'≈YNŸS- nOÔìS_PRCJıÕWqCr◊EW8@O√p_–4OBGUNTP%smiÛK5)>
¯ı{\t•1}c_Lµm◊bı*pkK[’rktgsLMÚv:±!MweDc·Hl R†:+cml˜f4nua¥	XeJ9,AB÷We_@Mÿr)ER)rü_VtwPONnTGvWílQ)© fnNsî(>Í|auie ;	ãMwo”led%j,`Naxs1R,∞·Mss ‘ @ÌO”µ\≈HAgE]A]IFhÊMrxPX€J.]Í4UP	(DMORTwBQWnE]–E÷IMS*GC_KDQÃP_GON‘E@cMissa O*˚D∑dq`–"IÛÈUM},uœ]pIajqe;_te˜trºR  /a|dkiÏz!^?ò{ÈgÁst0“oedÙÎ,ixa}COOSWPPye^LEﬂGZQT”(bKOUs–_KvT	UL Ït)†$Bh;OK4pt*a4e0,CÊmbsvR< a<`wB`ı OkSP_P≈VBNNMOs∆h@ËœCPOíA◊/mGTv9%BMœ@èPPﬂE$Ue_DëR—“B[ UT^T][[‹ŒDQ,lcrsËDib~M/Y'€[tq0≠Äis[m4Ï˝Ê}F_3ÁI˙lt`4E+v≈r(íÄ*/stfCAmt"T3+*Ìn7< tkÕ’\‹%*:BJ_QDw¿¬TŒ}lYêAZeMY PoOQt}Wê√IEÃ÷S%t¨$..(à(;boG¸i?mä
¥e}d‰Ah§yk<c?s·l s4`z(TaN?T_›P_CMGπ[HDCGiW?PP]ﬁTÃR	 ToJT\ÙX^%N’M◊ eRM2hBIm”AWPSLWJor<Àe’Sq@V†1>ãxï{uÈQ·1hk_{≈$_&ıﬁicinTer_teter¨U@x_G#}$ccÏ|hD˘>‚oˇ?qp volC#L&2)œ^π|ﬂP_@LWL_–RAmS(BOGSî=_SüttVt8⁄È.3†~OeApxl)˚H
eo¸McCe º¡Ni{°(, cleYS Pƒ]GS’OPS_sâmÀ;Dôb/B—TwrpMcNL‘MI	‚|WYüPP[AOMçÕK(jOOS‘}PQ]bjÙTR<#≠#c{.T) >j9my]p9r'ÑIwüFemnenñr»f*bb›ÙdsrgîƒV h/OÛpd„$ln$T~:qoß3x°~w8a|9na:ªmbèWWÑ[H!¿ﬁUœSÒ¿IKKﬂlcTOPL]¬w9]EVåD	 H.) „/3|tˆOhtYh•;-JI+.fC‚5F4}]AO Ãuf- ˆa{Ú|5tu†>zlËSs`S§jcN·v T1«N¬T7–`EHAKFG)CœoóEG`P_CO‹nU2∏† …SP]–˝D ıLHP¡ES(∆OO{T^Pp_W\JBg,5|A{πd8"x6
YE+^d:Q)$Óyoi`msRnnQËCiŒt7r]$dˆEz(r:EUF`s^CßnÏ!L⁄:*Ío~Rt úÃItIli9)(RGF«PS‘^ECum≈IAJ…ÌS	JOâSXO–PvAÀYGT‰¬xya=;
UJte-Alwlg‡gNQwÛ(rl"]qsÛ4 gY(ﬂpH«C%@IA[KB)FVST€PEAOT∆\FR74jm{po@PˇAF|k_P«R≈DRnBOS_pﬂÿp´À√QNö≈“,a gW#$\- <ÕxÖu^Ùh4-$ifüd·müFwz√]GenT(z[¸˝cduc Rch{fq{vGYL.ZS88*Îœ-sR!&ÓÏ·<Al&≤-®
dSWOR«EóÕ_SAOS	VWQpR›O=NTC÷’mõ$"/>rp)≠ 0qÌqlq≤eh<bl!yshR< W‰%”W`‹‚"O7ƒ}D0M¡+IE_…R,\ÔO[î_P@ÔCÓY^7+,CœbTW0pWnUI_>AM8BGè]^ªHP_COUhTórC)k?k"|åb%{`sWdxiv!y≥Á%mKf_*_rIiÓAewW4Âdva6,r<"WﬂaQ6Ëa|mÄTöz.C˝GÛµhnoK·{ı∫!IBOQDWUP_M|UHèEARAE) Go÷T_—¬o’P„Z~b|6M$at	,Â);-œ	*t@M·laÙ24kËa3`S¥ "l!sÛ$‡BOMb]_—¡oW«m]A_QN(i˚[\^X_CÕEfAUP≠¿FOO„TPWDN_	PP‘UGSô
COStŸt_3w‘ﬁTER¨ctspM!V+dÓYEs}p}i‰ y„QmaM^<˝>¯/)dtgÛ◊|Eytfr,P†r~]'·3vcgDh {*kÔlsB6≈HMëm}*ih“ìZSTW
P[ÂŒUA{r’UEQ)CœsG‘<PBWVOQ^TE2(HÅ)~3/lsl ˛˝mavTe•)?-Húu˜S*'taj+Ã`cwbR(„v)Ò3`UML”@_pP≈OKMEﬂIG(bi”[p@_]TA“9pVoOSTÿQ[%DFMêIeuS:BNNSUwWê_CO—NtZ<ál,‚v$P) ,
8’Svwar◊ mk_oEl_g|np/˘Óg_pÂR4Âb©≤ ¨DucpaEllh‰::jioWX–*6o‡%tIX=-)(BISTUI|UO—]ﬂMRCMS:JOCœV_VTcœELGQ,U)>$));èBß.tal¯ri¸e†TclsS@B	!k-ass TÖBO÷T_ %AOMOI¸[
Fã_YD◊Qt]√KeN‘∆)xCmSVWPR_ELu_^R¡RgNS4¬nQV]P{„_ns,)Ïay„4@`jkek3tÁp8a_lEÂOfunVxo)npeR[Ù 3|b{’3ÌV_&caPoqÏ» ¨˙˜hc˚ÔÚ| “o^ad}ld(È"B«A[–^0WGFïD◊ÄBSY√IBFO_
[XÿﬂB.UFDRdt®$j~M=G/ŒSt1:çä
Re,Ï‡|e ?ÛmÎ#r ,!#n·r3¢ƒ"&KVWPUWDa@Ÿ(*OIS’—PüG
TAZ	 zŒŒSTÔpPS√OT/^Y QeMS.`_Ü7–]S–◊#OUf‰eV,d»);r!UÈ2>}∫x≥_ty‡A (˜Yuofı~Qg1zjz?pd7!'r_((WüNK˚xcalm q:ø*G/~0vlÃ`8`|gj-@LK[_ëP◊%nAF_pARAl”	¬OG÷MRBko]^T≈,U3†%?.â0◊n.EÙAÈ•i*Öt˝ÚIAqm <ceerw4p\pßEasp`6( Go◊T]–¬o›YÛIV.FK3T7PTG«T<X≈R*0BOœMT◊PWe D_@Aña\)RÎdD^TQlB_—ÕfW“,sEasz()∞L
XsÏIrA0hÙ›o-mÈvuo_Ponm1hp_ÙUwT’hS!8Ÿ'K3w¿¡ll0‘{p:aNnr4$Êm0CÂi|!?)™B_œQTd\ÕÕ8aSC«◊iFMMsrVr_œbFr.T) ./O°(a}z3V&‘KLŸTil%/+öJ3‰fbjb≠ÇDãrg›ın t%a¥sL‡=cbVd!~yw≥ @°BgT?@P^√OaèT_âW<+GÀó]◊RÓUQ“ FNOI\ﬂp8]ELÕOPRAMsj¿S]_–BnLîR<C|9s&D≤>yUR_d¯pg!iÚ[c˜nnt˛@nËFuevóva3ıev(R8Ñ|‚tuah t06(#KNwQ"ﬂnÏaEild
)®B_S‹›W–YnUT”A“°LWÕÁS]]‘P_koLtA2\\	**;iYuea<ct42=,ea>R=Ê)mqse R BUœSUœP}SgL√_mG8FNUP]USZW£o’bT¡r(†BoG[túQ–]eKUmqAZAE”(OﬂR$`pÂ[GMÏ‰S.gàsyc‡Td0ö	Ê|‰Úxy`})hsˇee_`unœvÔ	n^qp[|mubUs†vei,†t(≤aZlWT`s'n09l£z9,POG”8ZPVV]F5~|BR·IR(BOI”VœP^KMQNpÕ⁄(ÑÎÅpc´œÛt!ª'f|empÏ#ta<ÛÏ 3w2Rº s(°Cs0–LBGOWZ[Pÿ_C]E@_K∆9‚OOSv_uT_€[T|Ç) RMM”tˇ@ﬂWﬁU{x`íM*¬Gsƒ_$`_!OEO\U6lcobÒ ¥)0äQ≈sü48Q4$h{\mulœ2tnPq;ft%r]`qw|ev(V†,S]c¸G"l$4Æ.,"Ã{<`volstyle©´RM«S[‘ÿ^5N‹m◊`RAtS
rnOSD_Qj_CœUN^u]∏	(hV/dapo,	;∫tƒuxduvE$bÏis3 í%§clA3 \`@mÀCTPZ_DgIoYŒ!÷MQT÷Q\_√OïNU–	©2oNS[« R’ˆIS@P@]S(C_}SPáTQ_IGOGR¨s|!—w†^˝"8
{g^_3p¶0e3^Ìe≠[Óp._PEiltÂ>_umSd%z`S∞(#`we,`‹~(“_⁄Ûv6ˆolAUqÓd
)*HLJZWT_fK’I¸–EA©X*B_GW^]XRMUNPEJ,Wyh†gMO;w†÷n,AÙat%(m
F‰E1ZMit!5yÊHu≥sh$22Ïd3Û*@ CO˜◊u^YPcMÏR^Y®"KnWT[ R_c'}L]Q&ƒK_€_XP~ENëKW–BBI–°BCzsî›Z@]CO≈rT≈<,bdew12P-°:†Iu;_T9be(ÈwsçUmèv}.–≠iÓrÂ"ÙaCQK“(r$n^OK‰v+] D/æ(A'n@t rÂl!rilÂ*(bhì[pP_uJ_R”UrIBOO⁄U{pPﬂCC◊^lrºIÆ,añOCätfnYlÖt-¢<s`aq ( ClgQsöT•KOoCTNQ¯_WM‹¿U_ƒ8BMWÙ–∞\GLÙEZ)¥bFowupHULSKA5PI[8MOSP6RPnEéUVÓ)mqsg V)`Ã
xÁrt]`eÎSdqOdtNE3AÆ~ÂsL–csÙerPS ®W◊AdIch1t::"a«j{w¥vØeu·mdjÈ(rMOWú_XDﬂUFT»[ıE÷¬{(C}O[V◊Q_GM}^ÃG”f+Q>*.)0CMv©6	um,ÒlaÂB Xa@Qrs F$	2l£sq!T(B«oCUWTy!imAÈ JJOQ◊WÕPCNULQ€È ¢ÕÀQW€––?eée_vmS@m€*BOAS–ﬁ¥wSGëFPícx·]S L*~⁄yffUupg†yÚOma_oU.ﬂSoy.Ö0[Re`ÙeÚ(B 8ﬂ_„.ui>3E+zÉboÓ”| 4k,cUImu.i)G^—T?x\QS U›^“RAW(KLMq‘œPﬂkNQ™TD2,\(1/n,; VÔ.ÒTk¸Ê"+≠,dem¿h	te¸clmÚs í/`a‰ar§Xj>O.s‘@P_3[Zh_IF8JnNS\_PRˇMOπJTE) aMˇ3Y◊p]nuIZXaVcIWB\KS5_◊CoEX1[j·l…GcU+Ä,
qo{_y—A A3⁄mumœfï~u˝IŒıhr_zÂ%vdˆ≤) Kdug|eU8:z£Egs|d6o,afÏeu …/¬O›\ﬂZo\JM_4QVW8kœR_PPˇHO’E|çU),n/º(0*'jÛd*folQdi]—©kãhAgtjf*ã4lnm&¨BnKsP˛–RCÈ|ERI*xX‰D.∞KOstôtA_)s\…\e‰UQfj