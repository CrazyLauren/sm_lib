/*
 * CEvent.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 27.11.2014
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#ifndef CEVENT_H_
#define CEVENT_H_

namespace NSHARE
{
enum eCBRval
{
	E_CB_REMOVE=-1,//remove cb from event list
	E_CB_SAFE_IT=0,
	E_CB_BLOCING_OTHER=2//The object don't have to call the other cb.
};
template<class TSender_type = void*, class TEvent_t = CB_t,
		class TEventArg_type = CB_t::arg_t>
class  CEvent
{
public:
	typedef CEvent<TSender_type, TEvent_t, TEventArg_type> my_t;
	typedef TEvent_t value_t;
	typedef TEventArg_type value_arg_t;
	typedef TSender_type sender_t;

private:
	struct  Type
	{
		unsigned int FPrior;
		mutable value_t FCb;
		bool operator ()(sender_t aSender, value_arg_t aWhat) const;
		bool operator <(Type const& right) const;
		bool operator ==(Type const& right) const;
		bool operator !=(Type const& right) const;
		bool operator ==(value_t const& right) const;

	};
	typedef std::multiset<Type> MapOfCallback_t;
	typedef typename MapOfCallback_t::iterator iterator;
	typedef typename MapOfCallback_t::const_iterator const_iterator;
public:
	typedef typename MapOfCallback_t::size_type size_t;

	CEvent(sender_t aSender);
	CEvent();
	virtual ~CEvent()
	{
	}

	bool operator+=(value_t const &);
	bool operator-=(value_t const &);
	virtual bool MAdd(value_t const &, unsigned int aPrior = std::numeric_limits<unsigned int>::max());
	virtual bool MErase(value_t const& aM);
	bool MChangePrior(value_t const&aM, unsigned int aPrior);
	bool MIs(value_t const& aM) const;
	size_t MSize() const;
	inline std::ostream& MPrintEvent(std::ostream & aStream) const;
//protected:
	int MCall(value_arg_t const& aCallbackArgs);
private:

	MapOfCallback_t FCBs;
	sender_t FSender;

	template<class key_type, class event_type,
			template<class, class > class IEvents, class mutex_type>
	friend class CEvents;
};
template class SHARE_EXPORT CEvent<>;
} //namespace USHARE
#include <UType/CEvent.hpp>

#endif /*CEVENT_H_*/
