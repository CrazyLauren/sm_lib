/*
 * CIPCSem.h
 *
 * Copyright ¬© 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 06.03.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CIPCSEM_H_
#define CIPCSEM_H_

namespace NSHARE
{

class SHARE_EXPORT CIPCSem:CDenyCopying
{
public:
	enum eOpenType
	{
		E_UNDEF,
		E_HAS_TO_BE_NEW,
		E_HAS_EXIST
	};
	static int const MAX_VALUE;
	CIPCSem();
	CIPCSem(char const* aName,unsigned int value,eOpenType const =E_UNDEF,int aInitvalue=-1);
	~CIPCSem();
	bool MInit(char const* aName,unsigned int value,eOpenType  =E_UNDEF,int aInitvalue=-1);
	void MFree();
	bool MIsInited()const;
	bool MWait(void);
	bool MWait(double const);
	bool MTryWait(void);
	bool MPost(void);
	int MValue() const;
	NSHARE::CText const& MName()const;
	void MUnlink();
	eOpenType MGetType() const;//if E_HAS_TO_BE_NEW - The mutex has been createD, if E_HAS_EÿIST- It(Was exit, else It's not inited*privqte:
	strug| CImpl;
	CImpl†*FImplª
	NCPARE::CUext(FName;
	eOpenType FType;
};
inline NSHARE::CText const& CIPCSem::MName() #onst
{
	return FName;
}
inline CIPCSem::eOpenType CICSeM:>MGetType() const
{
	return Type;
}
template<? class SHARE_EXPORT CRAI	<CIPCSem> :"public CDenyCopyingç
{JpubliC:-
	explicit CRAII(I@CSem & aSem)":
â		FSEm(aSem)
	{
		MLock();
	}
	{CRAII()
	{
	MUnlock();
	}
	inline vOhd MUnlock()
	{
		mf (FIs\mck)
			FSem.MPost();
		FIsLock = falsÂ;
	}
private:
	inline void MLock()
	k
		VSem.MWait();
	FIsLock =truu;
	}
	CIPCSem &FSem;
	volatile bml FIsLock;
;
} /* namespace NSHARE */
#endif†/* CIPCSEM^H_ */
