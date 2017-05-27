/*
 * strtonum.h
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 18.09.2015
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef STRTONUM_H_
#define STRTONUM_H_
#define FROM_STRING_EXIST
//fixme replace to boost
namespace NSHARE
{
template<class T,class TStr>
inline  bool str_to_decimal(TStr const& aVal, T &aTo)
{
	assert (std::numeric_limits<T>::is_integer);
	typename TStr::const_iterator _it = aVal.begin();
	for (; _it != aVal.end() && ::isspace(*_it); ++_it)
		;
	if (_it == aVal.end())
		return false;

	bool _neg = false;
	if (*_it == '-')
	{
		if (!std::numeric_limits < T > ::is_signed)
			return false;

		_neg = true;
		++_it;
	}
	else if (*_it == '+')
		++_it;

	if (_it == aVal.end())
		return false;

	T _base = 10;
	if (*_it == '0')
	{
		if (++_it != aVal.end())
		{
			if (isdigit(*_it))
				--_it;
			else
			{
				if (*_it == 'x' || *_it == 'X')
				{
					_base = 16;
					++_it;
				}
				else if (*_it == 'b' || *_it == 'B')
				{
					_base = 2;
					++_it;
				}
				else
					return false;

				if (_it == aVal.end())
					return false;
			}
		}
		else
			--_it;
	}
	T _cutoff =
			_neg ? std::numeric_limits < T > ::min() : std::numeric_limits < T
							> ::max();
	T _cutlim = _cutoff % _base;
	_cutoff /= _base;
	//fucking warning: warning: comparison is always false due to limited range of data type
	//for checking whether a number positive or negative using bitwise operation
	//if (std::numeric_limits < T > ::is_signed && _cutoff < 0)
	_cutoff =
			(std::numeric_limits < T > ::is_signed && (_cutoff >> (sizeof(_cutoff) * 8 - 1))) ?
					(0-_cutoff) : _cutoff;
	_cutlim =
			//(std::numeric_limits < T > ::is_signed && _cutlim < 0) ?
			(std::numeric_limits < T > ::is_signed && (_cutlim >> (sizeof(_cutlim) * 8 - 1))) ?
					(0-_cutlim) : _cutlim;
	//  For instance, if the range for longs is
	// [-2147483648..2147483647] and the input base is 10,
	// cutoff will be set to 214748364 and cutlim to either
	// 7 (_neg==0) or 8 (_neg==1), meaning that if we have accumulated
	// a value > 214748364, or equal but the next digit is > 7 (or 8),
	// the number is too big, and we will return a range error.
	//
	unsigned long long _sum = 0;
	for (; _it != aVal.end(); ++_it)
	{
		T _num = 0;
		if (isdigit(*_it))
			_num = (*_it - '0');
		else if (isalpha(*_it))
			_num = *_it - (isupper(*_it) ? 'A' - 10 : 'a' - 10);
		else
			return false;

		if (_num >= _base)
			return false;

		if (_sum > (unsigned long long) _cutoff
				|| (_sum == (unsigned long long) _cutoff && _num > _cutlim))
			return false;

		_sum *= _base;
		_sum += _num;
	}
	if (_neg)
		aTo = (T)(0-_sum);
	else
		aTo = (T)_sum;
	return true;
}
template<class T>
inline T& istream_decimal(std::istream & aStream, T & aVal)
{
	assert (std::numeric_limits<T>::is_integer);
	int _c;
	_c = aStream.get();
	for (; aStream.good() && ::isspace(_c); _c = aStream.get())
		;
	if (!aStream.good())
	{
		aStream.setstate(std::istream::failbit);
		return aVal;
	}

	bool _neg = false;
	if (_c == '-')
	{
		if (!std::numeric_limits < T > ::is_signed)
		{
			aStream.setstate(std::istream::failbit);
			return aVal;
		}

		_neg = true;
		_c = aStream.get();
	}
	else if (_c == '+')
		_c = aStream.get();

	if (!aStream.fail())
		return aVal;

	T _base = 10;
	if (_c == '0' && !aStream.eof())
	{
		_c = aStream.get();
		if (aStream.eof())
			aStream.unget();
		else if (isdigit(_c))
			aStream.unget();
		else
		{
			if (_c == 'x' || _c == 'X')
			{
				_base = 16;
				_c = aStream.get();
			}
			else if (_c == 'b' || _c == 'B')
			{
				_base = 2;
				_c = aStream.get();
			}
			else
			{
				aStream.setstate(std::istream::failbit);
				return aVal;
			}

			if (!aStream.good())
			{
				aStream.setstate(std::istream::failbit);
				return aVal;
			}
		}
	}
	T _cutoff =
			_neg ? std::numeric_limits < T > ::min() : std::numeric_limits < T
							> ::max();
	T _cutlim = _cutoff % _base;
	_cutoff /= _base;
	//fucking warning: warning: comparison is always false due to limited range of data type
	//for checking whether a number positive or negative using bitwise operation
	//if (std::numeric_limits < T > ::is_signed && _cutoff < 0)
	_cutoff =
			(std::numeric_limits < T > ::is_signed && (_cutoff >> (sizeof(_cutoff) * 8 - 1))) ?
					(0-_cutoff) : _cutoff;
	_cutlim =
			(std::numeric_limits < T > ::is_signed && (_cutlim >> (sizeof(_cutlim) * 8 - 1))) ?
					(0-_cutlim) : _cutlim;
	//  For instance, if the range for longs is
	// [-2147483648..2147483647] and the input base is 10,
	// cutoff will be set to 214748364 and cutlim to either
	// 7 (_neg==0) or 8 (_neg==1), meaning that if we have accumulated
	// a value > 214748364, or equal but the next digit is > 7 (or 8),
	// the number is too big, and we will return a range error.
	//
	unsigned long long _sum = 0;
	unsigned i = 0;
	for (; aStream.good(); _c = aStream.get(), ++i)
	{
		T _num = 0;
		if (isdigit(_c))
			_num = (_c - '0');
		else if (isalpha(_c))
			_num = _c - (isupper(_c) ? 'A' - 10 : 'a' - 10);
		else
		{
			aStream.unget();
			break;
		}

		if (_num >= _base)
		{
			aStream.setstate(std::istream::failbit);
			return aVal;
		}

		if (_sum > (unsigned long long) _cutoff
				|| (_sum == (unsigned long long) _cutoff && _num > _cutlim))
		{
			aStream.setstate(std::istream::failbit);
			return aVal;
		}

		_sum *= _base;
		_sum += _num;
	}
	if (i == 0)
	{
		aStream.setstate(std::istream::failbit);
		return aVal;
	}
	if (_neg)
		aVal =(T) (0-_sum);
	else
		aVal =(T) (_sum);
	return aVal;
}
template<class T,class TStr>
inline bool is_decimal_correct(TStr const& aVal)
{
	T _to;
	return str_to_decimal(aVal, _to);
}
template<class T,class TStr>
inline bool str_to_float(TStr const& aVal, T &aTo)
{
	assert(!std::numeric_limits < T > ::is_integer);
	typename TStr::const_iterator _it = aVal.begin();

	for (; _it != aVal.end() && isspace(*_it); ++_it)
		;
	if (_it == aVal.end())
		return false;

	bool _is_neg = false;
	if (*_it == '+')
		++_it;
	else if (*_it == '-')
	{
		_is_neg = true;
		++_it;
	}

	long double a = 0.0;
	int e = 0;
	unsigned _num_dig = 0;
	for (; _it != aVal.end() && isdigit(*_it); ++_it, ++_num_dig)
		a = a * 10.0 + (*_it - '0');

	if (_it != aVal.end() && *_it == '.')
	{
		for (; ++_it != aVal.end() && isdigit(*_it);)
		{
			a = a * 10.0 + (*_it - '0');
			e -= 1;
		}
	}
	if (_it != aVal.end() && (*_it == 'e' || *_it == 'E'))
	{
		int sign = 1;
		int i = 0;
		if (++_it == aVal.end())
			return false;
		if (*_it == '+')
			(void) 0;
		else if (*_it == '-')
			sign = -1;
		else
			return false;
		++_it;
		for (; _it != aVal.end() && isdigit(*_it); ++_it)
			i = i * 10 + (*_it - '0');

		e += i * sign;
	}
	if (_it != aVal.end() || !_num_dig
			|| e < std::numeric_limits < T > ::min_exponent
			|| e > std::numeric_limits < T > ::max_exponent)
		return false;

	while (e > 0)
	{
		a *= 10.0;
		e--;
	}
	while (e < 0)
	{
		a *= 0.1;
		e++;
	}
	if (_is_neg)
		a *= -1.0;
	long double const _min=-std::numeric_limits< T >::max();
	long double const _max=std::numeric_limits < T > ::max();
	if (a < _min || _max < a)
		return false;

	aTo = static_cast<T>(a);
	return true;
}
template<class T>
inline T& istream_float(std::istream & aStream, T & aVal)
{
	assert(!std::numeric_limits < T > ::is_integer);
	std::string _str;
	int _c;
	_c = aStream.get();
	for (; aStream.good() && ::isspace(_c); _c = aStream.get())
		;

	if (!aStream.good())
	{
		aStream.setstate(std::istream::failbit);
		return aVal;
	}
	if (_c == '+')
	{
		_str.push_back(_c);
		_c = aStream.get();
	}
	else if (_c == '-')
	{
		_str.push_back(_c);
		_c = aStream.get();
	}
	if (!aStream.good())
	{
		aStream.setstate(std::istream::failbit);
		return aVal;
	}
	unsigned _num_dig = 0;
	bool _is_last_handled=true;
	for (; aStream.good() && isdigit(_c); _c = aStream.get(), ++_num_dig)
		_str.push_back(_c);
	if(aStream.good())
		_is_last_handled=false;
	if (!_num_dig)
	{
		aStream.setstate(std::istream::failbit);
		return aVal;
	}

	if (!_is_last_handled && _c == '.')
	{
		_is_last_handled=true;
		_str.push_back(_c);
		_c = aStream.get();
		for (; aStream.good() && isdigit(_c); _c = aStream.get())
			_str.push_back(_c);

		if(aStream.good())
			_is_last_handled=false;
	}
	if (!_is_last_handled && (_c == 'e' || _c == 'E'))
	{
		_is_last_handled=true;
		_str.push_back(_c);
		_c = aStream.get();
		if (!aStream.good())
		{
			aStream.setstate(std::istream::failbit);
			return aVal;
		}
		if (_c == '+')
			(void) 0;
		else if (_c == '-')
			(void) 0;
		else
		{
			aStream.setstate(std::istream::failbit);
			return aVal;
		}
		_str.push_back(_c);
		_c = aStream.get();
		for (;aStream.good()  && isdigit(_c); _c = aStream.get())
			_str.push_back(_c);

		if(aStream.good())
			_is_last_handled=false;
	}
	if (!_is_last_handled)
	{
		_is_last_handled = true;
		aStream.unget();
	}
	if(!NSHARE::str_to_float(_str, aVal))
		aStream.setstate(std::istream::failbit);
	return aVal;
}
template<class T,class TStr>
inline bool is_float_correct(TStr const& aVal)
{
	assert(!std::numeric_limits < T > ::is_integer);
	typename TStr::const_iterator _it = aVal.begin();

	for (; _it != aVal.end() && isspace(*_it); ++_it)
		;
	if (_it == aVal.end())
		return false;

	if (*_it == '+')
		++_it;
	else if (*_it == '-')
	{
		++_it;
	}

	int e = 0;
	unsigned _num_dig = 0;
	for (; _it != aVal.end() && isdigit(*_it); ++_it, ++_num_dig)
		;

	if (_it != aVal.end() && *_it == '.')
	{
		for (; ++_it != aVal.end() && isdigit(*_it);)
			e -= 1;
	}
	if (_it != aVal.end() && (*_it == 'e' || *_it == 'E'))
	{
		int sign = 1;
		int i = 0;
		if (++_it == aVal.end())
			return false;
		if (*_it == '+')
			(void) 0;
		else if (*_it == '-')
			sign = -1;
		else
			return false;
		++_it;
		for (; _it != aVal.end() && isdigit(*_it); ++_it)
			i = i * 10 + (*_it - '0');

		e += i * sign;
	}
	if (_it != aVal.end() || !_num_dig
			|| e < std::numeric_limits < T > ::min_exponent
			|| e > std::numeric_limits < T > ::max_exponent)
		return false;

	return true;
}
template<class TStr>
inline bool str_to_bool(TStr const& aVal, bool &aTo)
{
	typename TStr::const_iterator _it = aVal.begin();
	for (; _it != aVal.end() && isspace(*_it); ++_it)
		;
	if (_it == aVal.end())
		return false;

	if (*_it == '1')
	{
		aTo = true;
		return true;
	}
	else if (*_it == '0')
	{
		aTo = false;
		return true;
	}
	if ((aVal.end() - _it)>= 4)
	{
		typename TStr::const_iterator _it_true=_it;
		if (tolower(*_it_true++) == 't' && tolower(*_it_true++) == 'r'
				&& tolower(*_it_true++) == 'u' && tolower(*_it_true++) == 'e')
		{
			aTo = true;
			return true;
		}
	}
	if ((aVal.end() - _it) >= 5)
	{
		typename TStr::const_iterator _it_false=_it;
		if (tolower(*_it_false++) == 'f' && tolower(*_it_false++) == 'a'
				&& tolower(*_it_false++) == 'l' && tolower(*_it_false++) == 's'
				&& tolower(*_it_false++) == 'e')
		{
			aTo = false;
			return true;
		}
	}
	return false;
}

template<class TStr>
inline bool is_bool_correct(TStr const& aVal)
{
	bool _to;
	return str_to_bool(aVal, _to);
}
template<class T>
inline T& istream_number(std::istream & aStream, T & aBase)
{
	assert(false);

}
template<>
inline unsigned char& istream_number(std::istream & aStream,
		unsigned char & aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline signed char& istream_number(std::istream & aStream, signed char & aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline unsigned short int& istream_number(std::istream & aStream,
		unsigned short int & aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline short int& istream_number(std::istream & aStream, short int & aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline unsigned int& istream_number(std::istream & aStream, unsigned int & aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline int& istream_number(std::istream & aStream, int & aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline unsigned long & istream_number(std::istream & aStream,
		unsigned long & aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline long int & istream_number(std::istream & aStream, long int& aVal)
{
	return istream_decimal(aStream, aVal);
}
template<>
inline double & istream_number(std::istream & aStream, double& aVal)
{
	return istream_float(aStream, aVal);
}
template<>
inline float & istream_number(std::istream & aStream, float& aVal)
{
	return istream_float(aStream, aVal);
}
template<>
inline long double & istream_number(std::istream & aStream, long double& aVal)
{
	return istream_float(aStream, aVal);
}
namespace detail
{
template<class T, bool>
struct from_string_double
{
	static inline bool from(CText const& aVal, T & aTo)
	{
		return str_to_float(aVal, aTo);
	}
};
template<class T>
struct from_string_double<T,false>
{
	static inline bool from(CText const& aVal, T & aTo)
	{
		std::istringstream _stream(aVal);
		if ( !_stream.eof() ) _stream >> aTo;
		return !_stream.fail();
	}
};
template<class T, bool>
struct from_string_integer
{
	static inline bool from(CText const& aVal, T & aTo)
	{
		return str_to_decimal(aVal, aTo);
	}
};
template<class T>
struct from_string_integer<T,false>
{
	static inline bool from(CText const& aVal, T & aTo)
	{
		return from_string_double<T, std::numeric_limits<T>::has_infinity>::from(aVal,
				aTo);
	}
};
template<class T>
inline bool from_string_impl(CText const& aVal, T & aTo)
{
	return from_string_integer<T, std::numeric_limits<T>::is_integer>::from(aVal,
			aTo);
}
template<>
inline bool from_string_impl<bool>(CText const& aVal,bool & aTo)
{
	return  str_to_bool(aVal, aTo);
}
}
template<class T>
inline bool from_string(CText const& aVal,T & aTo)
{
	return detail::from_string_impl<T>(aVal,aTo);
}
} //namespace NSHARE

#endif /* STRTONUM_H_ */
