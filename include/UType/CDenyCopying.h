/*
 * CDenyCopying.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 02.04.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#ifndef CDENYCOPYING_H_
#define CDENYCOPYING_H_

namespace NSHARE
{
class  SHARE_EXPORT CDenyCopying
{
public:
	CDenyCopying(void)
	{
	}
	;
private:
#if defined (_WIN32) && !defined(__MINGW32__)
#pragma warning(push)
#pragma warning (disable: 4100)
#endif
	CDenyCopying(const CDenyCopying & copy)
	{
	}
	;
	void operator=(const CDenyCopying & copy)
	{
	}
	;
#if defined (_WIN32) && !defined(__MINGW32__)
#pragma warning(pop)
#endif
};

}//namespace USHARE

#endif /* CDENYCOPYING_H_ */
