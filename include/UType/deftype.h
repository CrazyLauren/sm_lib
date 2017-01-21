/*
 * deftype.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 22.03.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef DEFTYPE_H_
#define DEFTYPE_H_
#include <stdint.h>
#include <UType/buffer_value.h>
namespace NSHARE
{
typedef int signal_t(void* WHO, void* WHAT, void* YOU_DATA);
typedef int (*psignal_t)(void* WHO, void* WHAT, void* YOU_DATA);
template<typename TSignal> struct  Callback_t
{
	typedef TSignal pM;
	typedef void* arg_t;
	Callback_t() :
			FSignal(NULL), FYouData(NULL)
	{
		;
	}
	Callback_t(TSignal const& aSignal, void * const aData) :
			FSignal(aSignal), FYouData(aData)
	{
		;
	}
	Callback_t(Callback_t<TSignal> const& aCB) :
			FSignal(aCB.FSignal), FYouData(aCB.FYouData)
	{
		;
	}
	TSignal FSignal;
	void* FYouData;
#if __cplusplus >= 201103

	explicit operator bool() const
	{
		return MIs();
	}
#endif
	bool MIs()const
	{
		return FSignal!=NULL;
	}
	template<class T, class Y>
	int operator ()(T* aWho, Y * const aArgs) const
	{
		if (FSignal)
			return (*FSignal)(aWho, aArgs, FYouData);
		return -1;
	}
	template<class T>
	int operator ()(T* aWho, void * const aArgs) const
	{
		if (FSignal)
			return (*FSignal)(aWho, aArgs, FYouData);
		return -1;
	}
//	int operator ()(void* aWho, void * const aArgs) const
//	{
//		if (FSignal)
//			return (*FSignal)(aWho, aArgs, FYouData);
//		return -1;
//	}
	bool operator ==(Callback_t const& rihgt) const
	{
		return FSignal == rihgt.FSignal && FYouData == rihgt.FYouData;
	}
};
template struct SHARE_EXPORT Callback_t<psignal_t>;
typedef Callback_t<psignal_t> CB_t;

template<bool (*psignal_t)(void* WHO, void* WHAT, void* YOU_DATA)>
struct  CB_static_t
{
	typedef void* arg_t;
	CB_static_t() :
			FYouData(NULL)
	{
		;
	}
	CB_static_t(void * const aData) :
			FYouData(aData)
	{
		;
	}
	void* FYouData;
	bool operator ()(void* aWho, void * const aArgs)
	{
		return psignal_t(aWho, aArgs, FYouData);
	}
};
} //namespace USHARE
namespace std
{

template<typename TSignal>
inline std::ostream& operator<<(std::ostream & aStream,
		NSHARE::Callback_t<TSignal> const& aCb)
{
	aStream.setf(ios::hex, ios::basefield);
	aStream << "Pointer to data:" << aCb.FYouData << "; Pointer to cb handler: "
			<< aCb.FSignal;
	aStream.unsetf(ios::hex);
	return aStream;
}
}
#endif /* DEFTYPE_H_ */
