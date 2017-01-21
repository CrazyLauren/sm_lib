/*
 *
 * win_unistd.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 16.06.2014
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */

#ifndef WIN_UNISTD_H_
#define WIN_UNISTD_H_
#include <BaseTsd.h>
#if _MSC_VER >=1600
#include <stdint.h>
namespace NSHARE
{
typedef SSIZE_T ssize_t;
}
#else
namespace NSHARE
{
typedef SSIZE_T ssize_t;

typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
};
#endif

#endif /* WIN_UNISTD_H_ */
