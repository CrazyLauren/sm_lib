/*
 * FloatCompare.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 16.06.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef FLOATCOMPARE_H_
#define FLOATCOMPARE_H_

#include <limits>
namespace NSHARE
{
template <class T>
inline bool approximatelyEqual(T a, T b, T epsilon=std::numeric_limits<T>::epsilon())
{
	const T _a=fabs(a);
	const T _b=fabs(b);
	const T _diff=fabs(a-b);
    return _diff <= ( ( _b>_a ? _b : _a) * epsilon);
}
template <class T>
inline bool essentiallyEqual(T a, T b, T epsilon=std::numeric_limits<T>::epsilon())
{
	const T _a=fabs(a);
	const T _b=fabs(b);
	const T _diff=fabs(a-b);
    return _diff <= ( (_a > _b ? _b : _a) * epsilon);
}
template <class T>
inline bool definitelyGreaterThan(T a, T b, T epsilon=std::numeric_limits<T>::epsilon())
{
	const T _a=fabs(a);
	const T _b=fabs(b);
	const T _diff=/*fabs*/(a-b);
    return _diff > ( (_a < _b ? _b : _a) * epsilon);
}
template <class T>
inline bool definitelyGreaterOrEqualThan(T a, T b, T epsilon=std::numeric_limits<T>::epsilon())
{
	const T _a=fabs(a);
	const T _b=fabs(b);
	const T _diff=/*fabs*/(a-b);
    return _diff > ( (_a < _b ? _b : _a) * epsilon)|| approximatelyEqual(a,b,epsilon);
}
template <class T>
inline bool definitelyLessThan(T a, T b, T epsilon=std::numeric_limits<T>::epsilon())
{
	const T _a=fabs(a);
	const T _b=fabs(b);	
	const T _diff=/*fabs*/(b-a);
    return _diff > ( (_a < _b ? _b : _a) * epsilon);
}
template <class T>
inline bool definitelyLessOrEqualThan(T a, T b, T epsilon=std::numeric_limits<T>::epsilon())
{
	const T _a=fabs(a);
	const T _b=fabs(b);
	const T _diff=/*fabs*/(b-a);
    return _diff > ( (_a < _b ? _b : _a) * epsilon) || approximatelyEqual(a,b,epsilon);
}
template <class T>
inline bool isNull(T a, T epsilon=std::numeric_limits<T>::epsilon())
{
	const T _a=fabs(a);
	return _a <= ( _a * epsilon);
}
}
#endif /* FLOATCOMPARE_H_ */
