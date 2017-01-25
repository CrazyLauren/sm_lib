/*
 * shm_ipc.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 12.12.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef SHM_IPC_H_
#define SHM_IPC_H_

#ifdef ENABLE_VTUNE
#	include <profiler_vtune.h>
#else
#	define ProfileScopeEvent(x)
#	define THREAD_NAME(n,i)
#	define PROFILE_INIT()
#	define PROFILE_PAUSE()
#	define PROFILE_RESUME()
#endif

#if (__cplusplus>= 201103L) || (_MSC_VER >= 1800) 
#	include <unordered_set>
#	include <unordered_map>
#	define HASH_SET std::unordered_set
#	define HASH_MAP std::unordered_map
#	define HASH_MULTISET std::unordered_multiset
#	define HASH_MULTIMAP std::unordered_multimap
#	define HASH std::hash
#else
#	include<boost/unordered_set.hpp>
#	include<boost/unordered_map.hpp>
#	define HASH_SET boost::unordered_set
#	define HASH_MAP boost::unordered_map
#	define HASH_MULTISET boost::unordered_multiset
#	define HASH_MULTIMAP boost::unordered_multimap
#endif

#include <set>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stdint.h>
#include <cassert>
#include <exception>
#include <iterator>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <macro_attributes.h>

#if defined (__QNX__)
#	define HAVE_POSIX_SEMAPHORES
#	include <sys/neutrino.h>
#	include <boost/shared_ptr.hpp>
#	include <ctype.h>
#	include <limits>
#	include <malloc.h>

#	define SHARED_PTR boost::shared_ptr 

#elif defined(unix) || defined(__MINGW32__)
//#elif _WIN32
#	define HAVE_POSIX_SEMAPHORES
#	include <limits>

#	if (__cplusplus>= 201103L)
#		ifdef __MINGW32__//version of gcc
#			include <tr1/memory>
#			include<tr1/shared_ptr.h>
#			define SHARED_PTR std::tr1::shared_ptr
#		else
#			include<shared_ptr.h>
#			define SHARED_PTR std::shared_ptr
#		endif
#	else
# 	include <tr1/memory>
#	define SHARED_PTR std::tr1::shared_ptr
# 	endif

#elif defined(_WIN32)
#	define SHARED_PTR std::shared_ptr 
#endif //#elif defined(_WIN32)

#ifdef _WIN32
#	ifdef _MSC_VER
#		ifndef NOMINMAX
#			define NOMINMAX
#		endif
#		include <win_unistd.h>
#	pragma warning(disable : 4290)
#	pragma warning(disable : 4996)
#	pragma warning(disable : 4355)
#	pragma warning(disable : 4251)
#	else
#		include <unistd.h>
#	endif
#	include <windows.h>
#	ifdef _MSC_VER
#		include <memory>
#	undef uuid_t
#	endif
#else
#	include <unistd.h>
#endif

#if   defined(__QNX__)||defined(unix) ||  defined(__MINGW32__)
#include <pthread.h>                        // POSIX threads support
#include <errno.h>
#endif


#ifdef  __QNX__
#include <sys/time.h>
#else
#include <ctime>
#endif
#include <errno.h>

#include <stdexcept>
#include <stdlib.h>
#include <sstream>
#include <limits.h>
#include <functional>

namespace NSHARE
{
typedef std::string CText;
}

#include <UType/CDenyCopying.h>
#include <UType/CRAII.h>
#include <UType/CFlags.h>
#include <UType/CMutex.h>



#include <UType/strtonum.h>
#include <UType/numtostr.h>
#include <UType/CAssertException.h>
#include <uclock.h>
#include <logging/share_trace.h>
#include <UType/CIntrusived.h>
#include <FloatCompare.h>
#include <UType/SmartField.h>
#include <UType/IAllocater.h>
#include <UType/CBuffer.h>
#include <UType/CConfig.h>
#include <UType/version.h>
#include <UType/deftype.h>
#include <UType/intrusive_ptr.h>


#include <UType/CEvents.h>
#include <UType/CEvent.h>
#include <sm_socket.h>

#endif /*SHM_IPC_H_*/
