/*
 * uclock.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 28.01.2012
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
 //fixme to boost chrono
#include <deftype>
#ifdef __MINGW32__
#include <wtypes.h>
#endif
#if defined(_WIN32) && !defined(__MINGW32__)
#	include <windows.h>
#	if defined(_MSC_VER)
typedef long suseconds_t;
#	endif
#elif defined(__MINGW32__)
#include <unistd.h>
typedef long suseconds_t;
#elif defined(_POSIX_C_SOURCE)
#include <time.h>
#include <sys/time.h>
#endif

#include <boost/math/special_functions/round.hpp>

namespace NSHARE
{
#if defined(_WIN32)
inline LARGE_INTEGER
getFILETIMEoffset()
{
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return (t);
}
#	ifndef CLOCK_REALTIME
#		define CLOCK_REALTIME 1
#	endif
extern  int clock_gettime(int X, struct timeval *tv)
{
    if(X!=CLOCK_REALTIME) MASSERT_1(0);
	LARGE_INTEGER           t;
    FILETIME            f;
    double                  microseconds;
    static LARGE_INTEGER    offset;
    static double           frequencyToMicroseconds;
    static int              initialized = 0;
    static BOOL             usePerformanceCounter = 0;

    if (!initialized) {
        LARGE_INTEGER performanceFrequency;
        initialized = 1;
        usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
        if (usePerformanceCounter) {
            QueryPerformanceCounter(&offset);
            frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
        } else {
            offset = getFILETIMEoffset();
            frequencyToMicroseconds = 10.;
        }
    }
    if (usePerformanceCounter) QueryPerformanceCounter(&t);
    else {
        GetSystemTimeAsFileTime(&f);
        t.QuadPart = f.dwHighDateTime;
        t.QuadPart <<= 32;
        t.QuadPart |= f.dwLowDateTime;
    }

    t.QuadPart -= offset.QuadPart;
    microseconds = (double)t.QuadPart / frequencyToMicroseconds;
    t.QuadPart =(LONGLONG) microseconds;
    tv->tv_sec = (long)(t.QuadPart / 1000000);
    tv->tv_usec = t.QuadPart % 1000000;
    return 0;
}
#else
extern  void convert(struct timeval* aTo, float const aFrom)
{
	aTo->tv_sec = (std::time_t) aFrom;
	aTo->tv_usec = static_cast<suseconds_t>(1000 * 1000
			* (aFrom - (float) aTo->tv_sec));
}
#endif //#ifdef defined(_WIN32)


#ifdef __QNX__
inline uint64_t GetTickCount(void)
{
	uint64_t _time;
	ClockTime_r(CLOCK_MONOTONIC, NULL, & _time);
	return _time; //ns
}
#elif defined(unix)
inline uint64_t GetTickCount(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ((uint64_t)ts.tv_sec*1000*1000*1000+ts.tv_nsec); //ns
}
#endif
#if defined (__QNX__)|| defined(unix)
extern  double get_time()//sec
{
	return GetTickCount() / 1000.0 / 1000.0 / 1000.0;
}
#else
extern  double get_time()//sec
{
	struct timeval ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ((uint64_t)ts.tv_sec+ts.tv_usec/ 1000.0 / 1000.0);
}
#endif

#if defined (__MINGW32__) || defined(_MSC_VER)
extern  void convert(struct timeval* aTo, float const aFrom)
{
	using namespace std;
	aTo->tv_sec = (time_t) aFrom;
	aTo->tv_usec = static_cast<suseconds_t>(1000 * 1000
			* (aFrom - (float) aTo->tv_sec));
}
extern  void get_time(struct timeval *ts)
{
	clock_gettime(CLOCK_REALTIME, ts);
}
inline void add(uint64_t* aTo, struct timeval const& aFrom) //ns
{
	*aTo += (aFrom.tv_sec * 1000 * 1000 * 1000 + aFrom.tv_usec*1000);
}
inline void add(struct timeval* aTo, uint64_t const& aFrom) //ns
{
	uint64_t _old = aFrom;
	add(&_old, *aTo);
	aTo->tv_sec =(long)( _old / (1000 * 1000 * 1000));
	aTo->tv_usec = _old % (1000 * 1000 );
}
inline void add(uint64_t* aTo, struct timespec const& aFrom) //ns
{
	timeval _time={static_cast<long>(aFrom.tv_sec),aFrom.tv_nsec/1000};
	add(aTo,_time);
}
inline void add(struct timespec* aTo, uint64_t const& aFrom) //ns
{
	uint64_t _old = aFrom;
	add(&_old, *aTo);
	aTo->tv_sec = _old / (1000 * 1000 * 1000);
	aTo->tv_nsec = _old % (1000 * 1000 * 1000);
}
extern void add(struct timespec* aTo, double const& aFrom) //s
{
	uint64_t _time=(uint64_t)(aFrom*1000.0*1000.0*1000.0);
	add(aTo,_time);
}


#elif defined(__QNX__)|| defined(unix)
extern  void get_time(struct timespec *ts)
{
	clock_gettime(CLOCK_REALTIME, ts);
}
inline void add(uint64_t* aTo, struct timespec const& aFrom) //ns
{
	*aTo += (aFrom.tv_sec * 1000 * 1000 * 1000 + aFrom.tv_nsec);
}
inline void add(struct timespec* aTo, uint64_t const& aFrom) //ns
{
	uint64_t _old = aFrom;
	add(&_old, *aTo);
	aTo->tv_sec = _old / (1000 * 1000 * 1000);
	aTo->tv_nsec = _old % (1000 * 1000 * 1000);
}
extern void add(struct timespec* aTo, double const& aFrom) //s
{
	static const uint64_t _nano_time=1000*1000*1000;
	uint64_t _time=aTo->tv_nsec+ static_cast<uint64_t>((aFrom - (uint64_t)aFrom) * 1000.0 * 1000.0 * 1000.0);
	aTo->tv_sec += static_cast<unsigned>(aFrom)+(_time/_nano_time);
	aTo->tv_nsec = (_time%_nano_time);
}
#endif //#if defined(__QNX__)|| defined(unix)

extern  void usleep(long unsigned aVal)
{
	using namespace std;
#if (defined(_WIN32) && !defined(__MINGW32__)) || (defined(__MINGW32__) && !defined(_POSIX_THREADS) )
	long unsigned  _sleep=(long unsigned)boost::math::round(((double)aVal)/1000);
	_sleep=_sleep==0?1:_sleep;
	Sleep(_sleep);//fix Thank you windows for what make you're my code more difficult
#elif defined(__linux__)
	struct timespec _ts;
	_ts.tv_sec=aVal/1000000;
	_ts.tv_nsec=(aVal%1000000)*1000;
	clock_nanosleep(CLOCK_MONOTONIC,0,&_ts,NULL);
#elif (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >=199309L) && !defined(__MINGW32__)
	struct timespec _ts;
	_ts.tv_sec=aVal/1000000;
	_ts.tv_nsec=(aVal%1000000)*1000;
	nanosleep(&_ts,NULL);
#else
	::usleep(aVal);
#endif
}
extern  unsigned sleep(unsigned aVal)
{
#if (defined(_WIN32) && !defined(__MINGW32__)) || (defined(__MINGW32__) && !defined(_POSIX_THREADS) )
	::Sleep(aVal * 1000);
#elif defined(__linux__)
	struct timespec _ts;
	_ts.tv_sec=aVal;
	_ts.tv_nsec=0;
	clock_nanosleep(CLOCK_MONOTONIC,0,&_ts,NULL);
#elif (defined(_POSIX_C_SOURCE)) || (defined(__MINGW32__) && defined(_POSIX_THREADS) )
	struct timespec _ts;
	_ts.tv_sec=aVal;
	_ts.tv_nsec=0;
	nanosleep(&_ts,NULL);
#else
	::sleep(aVal);
#endif
	return 0;
}

#if defined(__QNX__)||defined(unix)||defined(__linux__)
extern  uint64_t get_unix_time()//ms
{
	struct timeval _tp;
	if(gettimeofday(&_tp,NULL)==0)
		return _tp.tv_sec*1000+_tp.tv_usec/1000;
	return 0;
}
#elif defined(_WIN32)
extern  uint64_t get_unix_time()//ms
{
	FILETIME _now;
	GetSystemTimeAsFileTime(&_now);
	const uint64_t _epoch=(uint64_t)116444736000000000ULL;
	uint64_t _time=(uint64_t)_now.dwLowDateTime+ (((uint64_t)_now.dwHighDateTime)<<32);
	_time=_time-_epoch;
	return _time/10/1000;// /10- usec; /1000 - msec
}
#else
#error
#endif
}
