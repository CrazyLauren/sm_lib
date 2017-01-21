/*
 * CCondvar.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 04.04.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */   
#ifndef CCONDVAR_H_
#define CCONDVAR_H_

namespace NSHARE
{
class SHARE_EXPORT CCondvar:CDenyCopying
{
public:
// Construction | Destruction
	CCondvar();
	~CCondvar(void);

	SHARED_DEPRECATED_F( bool Signal(void)
	{
		return MSignal();
	})
	SHARED_DEPRECATED_F(bool Timedwait(CMutex * aVal, const struct timespec* aVal2 = NULL)
	{
		return MTimedwait(aVal, aVal2);
	})
	SHARED_DEPRECATED_F(bool Timedwait(CMutex *aVal, double const aVal2)
	{
		return MTimedwait(aVal, aVal2);
	})
	SHARED_DEPRECATED_F(bool Broadcast(void)
	{
		return MBroadcast();
	})


	bool MSignal(void);
	bool MTimedwait(CMutex *, const struct timespec* = NULL);
	bool MTimedwait(CMutex *, double const);
	bool MBroadcast(void);


	void * MGetPtr()const;

	static bool sMUnitTest();
private:
	struct CImpl;
	CImpl* FPImpl;
};
}


#endif /* CCONDVAR_H_ */
