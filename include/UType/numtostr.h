/*
 * numtostr.h
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 18.09.2015
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef NUMTOSTR_H_
#define NUMTOSTR_H_
#define NUM_TO_STRING_EXIST
//fixme to boost
namespace NSHARE
{
template<class TStr>
inline bool bool_to_str(bool const& aVal, TStr &aTo)
{
	if (aVal)
		aTo = "True";
	else
		aTo = "False";
	return true;
}

template<typename T, class TStr>
inline bool num_to_str(T const& aVal, TStr &aTo, unsigned const aBase = 10)
{
	assert(std::numeric_limits<T>::is_integer);
	size_t _count = (aVal <= 0 ? 1 : 0);
	T const _base = static_cast<T const>(aBase);
	for (T _sum = aVal; _sum; ++_count)
		_sum /= _base;
	if (_base == 16 || _base == 2)
		_count += 2;
	else if (_base != 10)
		return false;
	const size_t _size = aTo.length();
	aTo.resize(_count + _size);
	typename TStr::iterator _type_it = aTo.begin() + _size;
	//fucking warning: warning: comparison is always false due to limited range of data type
	//for checking whether a number positive or negative using bitwise operation
	//if (std::numeric_limits<T>::is_signed && aVal<0)
	if (std::numeric_limits<T>::is_signed && (aVal >> (sizeof(aVal) * 8 - 1)))
			*_type_it++ = '-';

	if (_base == 16)
	{
		*_type_it++ = '0';
		*_type_it++ = 'x';
	}
	else if (_base == 2)
	{
		*_type_it++ = '0';
		*_type_it++ = 'b';
	}

	typename TStr::reverse_iterator _it = aTo.rbegin();
	char _digit;
	T _sum = aVal;
	if (_sum > 0 ||_sum==0)
		do
		{
			_digit =(char) (_sum % _base);
			if (_digit < 0xA)
				*_it = '0' + _digit;
			else
				*_it = 'A' + _digit - 0xA;

			_sum /= _base;
			++_it;
		} while (_sum);
	else
		for (; _sum; ++_it)
		{
			_digit =(char) (_sum % _base);
			if (_digit < 0xA)
				*_it = '0' - _digit;
			else
				*_it = 'A' - _digit - 0xA;

			_sum /= _base;
		}
	return true;
}
template<typename T, class TStr>
inline bool float_to_str(T f, TStr &aTo, int const aPrecision = 4)
{
	assert(!std::numeric_limits<T>::is_integer);
	int i;
	int z;
	int exp = 0;

	if (f < 0)
	{
		aTo.push_back('-');
		f = -f;
	}

	if (f)
	{
		while (f < 1)
		{
			f *= 10;
			exp--;
		}

		while (f >= 10)
		{
			f /= 10;
			exp++;
		}
	}
	while ((exp > 0) && (exp <= std::numeric_limits<T>::digits10))
	{
		aTo.push_back('0' + static_cast<int>(f));
		z = static_cast<int>(f);
		f -= z;
		f *= 10;
		exp--;
	}

	aTo.push_back('0' + static_cast<int>(f));
	z = static_cast<int>(f);
	f -= z;
	f *= 10;

	aTo.push_back('.');

	int _odd = 0;
	for (i = 0; i < aPrecision; i++)
	{
		aTo.push_back('0' + static_cast<int>(f));
		if (static_cast<int>(f) == 0)
			++_odd;
		else
			_odd = 0;
		z = static_cast<int>(f);
		f -= z;
		f *= 10;
	}
	if (_odd > 0)
	{
		if (_odd == aPrecision)
			aTo.erase(aTo.end() - _odd - 1, aTo.end()); //1 - point
		else
			aTo.erase(aTo.end() - _odd, aTo.end());
	}

	if (exp != 0)
	{

		aTo.push_back('e');
		if (exp < 0)
		{
			aTo.push_back('-');
			exp = -exp;
		}
		else
		{
			aTo.push_back('+');
		}

		aTo.push_back('0' + exp / 10);
		exp -= (exp / 10) * 10;
		aTo.push_back('0' + exp);

	}
	return true;
}
template<class T>
inline std::string fund_to_str(T const & aNum)
{
	std::stringstream out;
	//out << std::setprecision(20) << aNum;
	out << aNum;
	return out.str();
}
template<>
inline std::string fund_to_str<bool>(bool const & aVal)
{
	std::string _str;
	NSHARE::bool_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<unsigned char>(unsigned char const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<signed char>(signed char const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<unsigned short int>(
		unsigned short int const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<short int>(short int const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<unsigned int>(unsigned int const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<int>(int const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<unsigned long int>(
		unsigned long int const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<long int>(long int const & aVal)
{
	std::string _str;
	NSHARE::num_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<double>(double const & aVal)
{
	std::string _str;
	NSHARE::float_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<float>(float const & aVal)
{
	std::string _str;
	NSHARE::float_to_str(aVal, _str);
	return _str;
}
template<>
inline std::string fund_to_str<long double>(long double const & aVal)
{
	std::string _str;
	NSHARE::float_to_str(aVal, _str);
	return _str;
}
template<class T>
inline CText to_string(T const & aVal)
{
	return CText(fund_to_str<T>(aVal));
}
}

#endif /* NUMTOSTR_H_ */
