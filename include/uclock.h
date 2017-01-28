/*
 *
 * uclock.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 02.04.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
 
#ifndef UCLOCK_H_
#define UCLOCK_H_

namespace NSHARE
{
extern SHARE_EXPORT double get_time();
//sec;
extern SHARE_EXPORT void usleep(long unsigned aVal);
extern SHARE_EXPORT unsigned sleep(unsigned aVal);
extern SHARE_EXPORT uint64_t get_unix_time(); //ms
#if defined(__QNX__)|| defined(unix)
extern SHARE_EXPORT void get_time(struct timespec *ts);
#endif
}
#endif /* UCLOCK_H_ */
