/*
 * CAssertException.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 04.04.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#ifndef CASSERTEXCEPTION_H
#define CASSERTEXCEPTION_H

#include <exception>
#include <assert.h>
#include <string.h>

#define COMPILE_ASSERT(aVal,msg)  typedef NSHARE::compile_assert_t<(bool(aVal))> msg[bool(aVal) ? 1 : -1]

namespace NSHARE
{
template <bool>
struct  compile_assert_t
{
};

class  CAssertException: public std::exception
{
public:
	CAssertException(char const* description, char const* filename,
			int lineNumber) :
			FLineNumber(lineNumber)
	{
		using namespace std;
		strcpy(FDescription, description);
		strcpy(FFilename, filename);
	}
	virtual ~CAssertException() throw ()
	{
		;
	}
	virtual char const* MWhat() const throw ()
	{
		return FDescription;
	}
	char const* MFilename() const
	{
		return FFilename;
	}
	int MLineNumber() const
	{
		return FLineNumber;
	}
	std::string MLineNumberStr() const
	{
		std::string _str;
		NSHARE::num_to_str(MLineNumber(), _str);
		return _str;
	}
private:
	char FDescription[512];
	char FFilename[256];
	int FLineNumber;
};
template<class _T,class _Y>
inline void massert(_T const& aVal1, _Y const& aVal2,char const* description, char const* filename,
		int lineNumber)
{
	if(aVal1==aVal2)
	return;
	std::string _assert;
	_assert="Assertion failed.";
	_assert+=std::string(description)+';';
	_assert+=std::string(filename)+':';
	std::string _tmp;
	NSHARE::num_to_str(lineNumber, _tmp);
	_assert+=_tmp;
	std::cerr<<_assert<<std::endl;
	throw new CAssertException (description,filename,lineNumber);
}

template<class _T,class _Y>
inline void massert(_T* const& aVal1, _Y const& aVal2,char const* description, char const* filename,
		int lineNumber)
{
	if(aVal1==(void*)aVal2)//FIXME
	return;
	std::string _assert;
	_assert+="Assertion failed.";
	_assert+=std::string(description)+';';
	_assert+=std::string(filename)+':';
	std::string _tmp;
	NSHARE::num_to_str(lineNumber, _tmp);
	_assert+=_tmp;
	std::cerr<<_assert<<std::endl;
	throw new CAssertException (description,filename,lineNumber);
}
template<class _T>
inline void massert(_T const& aVal,char const* description, char const* filename,
		int lineNumber)
{
	if(aVal)
	return;
	std::string _assert;
	_assert+="Assertion failed.";
	_assert+=std::string(description)+';';
	_assert+=std::string(filename)+':';
	std::string _tmp;
	NSHARE::num_to_str(lineNumber, _tmp);
	_assert+=_tmp;
	std::cerr<<_assert<<std::endl;
	throw new CAssertException (description,filename,lineNumber);
}
#ifdef NDEBUG
template<class _T, class _Y>
inline void fake_assert(_T const & aVal1, _Y const& aVal2)
{
}
template<class _T>
inline void fake_assert(_T const & aVal1)
{
}
#endif
}
#ifdef NDEBUG
#	define _MASSERT(aVal1,aVal2,aDescription) NSHARE::fake_assert(aVal1,aVal2);
#	define _MASSERT_1(aVal1,aDescription) NSHARE::fake_assert(aVal1);
#else
#	define _MASSERT(aVal1,aVal2,aDescription) NSHARE::massert(aVal1,aVal2, aDescription,__FILE__,__LINE__);
#	define _MASSERT_1(aVal1,aDescription) NSHARE::massert(aVal1, aDescription,__FILE__,__LINE__);
#endif

#	define MASSERT(aVal1,aVal2) _MASSERT(aVal1,aVal2,"None")
#	define MASSERT_1(aVal1) _MASSERT_1((aVal1),#aVal1)
#endif
