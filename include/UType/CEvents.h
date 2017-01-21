/*
 * CEvents.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 07.04.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#ifndef CEVENTS_H_
#define CEVENTS_H_
#include <UType/CEvent.h>

namespace NSHARE
{
template<class key_type, class value_type>
class  IEvents
{
public:
	struct  value_t
	{
		value_t():FKey(key_type()), FCb(value_type())
		{

		}
		value_t (key_type const& aKey,value_type const& aCb):
			FKey(aKey),FCb(aCb)
		{

		}
		key_type FKey;
		value_type FCb;
	};

	virtual ~IEvents()
	{

	}
	virtual bool MAdd(value_t const & aVal, unsigned int aPrior = std::numeric_limits<unsigned int>::max())=0;
	virtual bool MErase(value_t const& aVal)=0;
};
template<class key_type, class value_type>
class  IEventsEmpty
{
public:
	struct  value_t
	{
		value_t():FKey(),FCb()
		{

		}
		value_t (key_type const& aKey,value_type const& aCb):
			FKey(aKey),FCb(aCb)
		{

		}
		key_type FKey;
		value_type FCb;
	};
};
struct  CEventsMutexEmpty
{
};
template<> struct CRAII<CEventsMutexEmpty> : public CDenyCopying
{
public:
	explicit CRAII(CEventsMutexEmpty const& aMutex)
	{

	}
};
template<typename _Tp>
struct  CEventLessComapare:std::less<_Tp>
{

};
template<class key_type = NSHARE::CText, class event_type = CEvent<>,
		template<class, class > class TIEvents = IEventsEmpty,
		class mutex_type = CEventsMutexEmpty>
class  CEvents: public TIEvents<key_type, typename event_type::value_t>
{
public:
	typedef std::map<key_type, event_type> Sequence_t;
	typedef CEvents<key_type, event_type, TIEvents, mutex_type> my_t;
	typedef event_type event_t;
	typedef key_type key_t;
	typedef typename event_t::sender_t sender_t;
	typedef typename event_t::value_arg_t value_arg_t;
	typedef typename TIEvents<key_type, typename event_type::value_t>::value_t value_t;
	typedef mutex_type mutex_t;

	explicit CEvents(sender_t const& aSender);
	explicit CEvents(CEvents const&,sender_t const& aSender);//Copy
	CEvents();
	bool operator+=(value_t const & aVal);
	bool operator-=(value_t const & aVal);
	bool MAdd(value_t const & aVal, unsigned int aPrior = std::numeric_limits<unsigned int>::max());
	bool MErase(value_t const& aVal);

	bool MChangePrior(value_t const&aVal, unsigned int aPrior);
	bool MIs(value_t const& aVal) const;
	bool MIsKey(key_t const& aVal) const;
	inline std::ostream& MPrintEvents(std::ostream & aStream) const;

	inline bool MEmpty  ()const;
#ifndef TEST//FIXME
protected:
#endif
	int MCall(key_t const& aKey, value_arg_t const& aCallbackArgs);
	~CEvents()
	{
		;
	}
private:
	typedef typename Sequence_t::iterator iterator;
	typedef typename Sequence_t::const_iterator const_iterator;
	Sequence_t FCBs;
	sender_t FSender;
	mutable mutex_t	 FMutex;
};
template class SHARE_EXPORT CEvents<>;

} //namespace USHARE
#include <UType/CEvents.hpp>
#endif /* CEVENTS_H_ */
