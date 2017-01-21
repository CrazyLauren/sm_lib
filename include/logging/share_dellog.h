/*
 *
 * share_dellog.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 03.03.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef SHARE_DELLOG_H_
#define SHARE_DELLOG_H_

#	undef VLOG
#	undef LOG
#	undef LOG_IF
#	undef VLOG_IF
#	undef DVLOG
#	undef DLOG
#	undef DLOG_IF
#	undef LOG_ASSERT
#	undef CHECK_NE
#	undef CHECK_LE
#	undef CHECK_GT
#	undef CHECK_GE
#	undef CHECK_LT
#	undef CHECK_EQ
#	undef CHECK_NOTNULL
#	undef CHECK
#	undef DCHECK

struct __gag_t
{
	inline void operator^(std::ostream&)
	{
	}
};
#	define LOG(some)  true?(void)0: __gag_t()^ std::cout
#	define VLOG(some)  LOG(some)
#	define LOG_IF(some,other) LOG(some)
#	define VLOG_IF(some,other) LOG(some)
#	define DVLOG(some) LOG(some)
#	define DLOG(some) LOG(some)
#	define DLOG_IF(some,other) LOG(some)
#	define LOG_ASSERT(some)
#	define CHECK_NE(some,some1) true?(void)0: __gag_t()^ std::cout
#	define CHECK_LE(some,some1) true?(void)0: __gag_t()^ std::cout
#	define CHECK_GT(some,some1) true?(void)0: __gag_t()^ std::cout
#	define CHECK_GE(some,some1) true?(void)0: __gag_t()^ std::cout
#	define CHECK_LT(some,some1) true?(void)0: __gag_t()^ std::cout
#	define CHECK_EQ(some,some1) true?(void)0: __gag_t()^ std::cout
#	define CHECK_NOTNULL(aVal) true?(void)0: __gag_t()^ std::cout
#	define CHECK(aVal) true?(void)0: __gag_t()^ std::cout
#	define DCHECK(aVal) CHECK(aVal)
#	define DCHECK_NOTNULL(aVal) CHECK_NOTNULL(aVal)
#	define DCHECK_NE(some,some1) true?(void)0: __gag_t()^ std::cout
#	define DCHECK_LE(some,some1) true?(void)0: __gag_t()^ std::cout
#	define DCHECK_GT(some,some1) true?(void)0: __gag_t()^ std::cout
#	define DCHECK_GE(some,some1) true?(void)0: __gag_t()^ std::cout
#	define DCHECK_LT(some,some1) true?(void)0: __gag_t()^ std::cout
#	define DCHECK_EQ(some,some1) true?(void)0: __gag_t()^ std::cout
#	define VLOG_EVERY_N(verboselevel, n) LOG(verboselevel)
enum
{
#ifndef INFO
	INFO,
#endif
#ifndef WARNING
	WARNING,
#endif
#ifndef ERROR
	ERROR,
#endif
#ifndef FATAL
	FATAL,
#endif
#ifndef DFATAL
	DFATAL
#endif
};

#endif /* SHARE_DELLOG_H_ */
