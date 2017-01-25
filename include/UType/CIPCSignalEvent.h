/*
 * CIPCCondvar.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 03.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CIPCCONDVAR_H_
#define CIPCCONDVAR_H_

#ifndef _WIN32
#	include <semaphore.h>
#endif
namespace NSHARE
{

class CIPCSignalEvent:CDenyCopying
{
public:
	enum{
# ifdef _WIN32
	eReguredBufSize=16
#else
	eReguredBufSize=sizeof(sem_t)+2*4+__alignof(sem_t)
#endif	
	};
	enum eOpenType
	{
		E_HAS_TO_BE_NEW,
		E_HAS_EXIST,
		E_UNDEF,
	};
	CIPCSignalEvent();
	CIPCSignalEvent(uint8_t* aBuf, size_t aSize,eOpenType aIsNew=E_UNDEF);
	~CIPCSignalEvent();
	bool MInit(uint8_t* aBuf, size_t aSize,eOpenType aHasToBeNew=E_UNDEF);
	bool MSignal(void);
	bool MTimedwait(CIPCSem *, const struct timespec* = NULL);
	bool MTimedwait(CIPCSem *, double const);
	void MFree();
	bool MIsInited() const;
	NSHARE::CText const& MName() const;
	void MUnlink();
	eOpenType MGetType() const;//if E_HAS_TO_BE_NEW - The mutex has been created, if E_HAS_EXIST- It was exit, else It's not inited
	static size_t sMRequredBufSize();
private:
	struct CImpl;
	CImpl* FPImpl;
};

} /* namespace NSHARE */
#endif /* CIPCCONDVAR_H_ */
