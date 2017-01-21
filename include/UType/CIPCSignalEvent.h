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

namespace NSHARE
{

class CIPCSignalEvent:CDenyCopying
{
public:
	enum eOpenType
	{
		E_HAS_TO_BE_NEW,
		E_HAS_EXIST,
		E_UNDEF,
	};
	CIPCSignalEvent();
	CIPCSignalEvent(char const* aName,eOpenType aIsNew=E_UNDEF);
	~CIPCSignalEvent();
	bool MInit(char const* aName,eOpenType aHasToBeNew=E_UNDEF);
	bool MSignal(void);
	bool MTimedwait(CIPCSem *, const struct timespec* = NULL);
	bool MTimedwait(CIPCSem *, double const);
	void MFree();
	bool MIsInited() const;
	NSHARE::CText const& MName() const;
	void MUnlink();
private:
	struct CImpl;
	CImpl* FPImpl;
	NSHARE::CText FName;
};

} /* namespace NSHARE */
#endif /* CIPCCONDVAR_H_ */
