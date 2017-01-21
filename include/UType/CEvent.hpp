/*
 * CEvent.hpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 27.11.2014
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#ifndef CEVENT_HPP_
#define CEVENT_HPP_

namespace NSHARE
{
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline CEvent<TSender_type, TEvent_t, TEventArg_type>::CEvent() :
		FSender(NULL)
{
	;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline CEvent<TSender_type, TEvent_t, TEventArg_type>::CEvent(sender_t aSender) :
		FSender(aSender)
{
	;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::MAdd(
		value_t const & aCB, unsigned int aPrior)
{
	iterator _it=FCBs.begin();
	for (; _it != FCBs.end() && !(*_it == aCB);++_it)
		;
	if (_it == FCBs.end())
	{
		Type _val =
		{ aPrior, aCB };

		FCBs.insert(_val);
	}
	else
		_it->FCb = aCB;
	return true;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::MErase(
		value_t const& aM)
{
	iterator _it = find(FCBs.begin(), FCBs.end(), aM); //�� removew algorithm
	if (_it == FCBs.end())
		return false;
	FCBs.erase(_it);
	return true;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::MIs(
		value_t const& aM) const
{
	return FCBs.end() != find(FCBs.begin(), FCBs.end(), aM);
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline int CEvent<TSender_type, TEvent_t, TEventArg_type>::MCall(
		value_arg_t const& aCallbackArgs)
{
	int _count = 0;
	for (iterator _it(FCBs.begin()); _it != FCBs.end();)
	{
		eCBRval _rval=(eCBRval)(*_it)(FSender, aCallbackArgs);

		switch(_rval)
		{
			case E_CB_REMOVE:
				FCBs.erase(_it++);
				break;

			case E_CB_SAFE_IT:
				++_count;
				++_it;
			break;

			case E_CB_BLOCING_OTHER:
				VLOG(2)<<"passing cb";
				return _count;
			break;
		}
	}
	return _count;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::MChangePrior(
		value_t const& aM, unsigned int aPrior)
{
	//TODO Call CB

	iterator _it = find(FCBs.begin(), FCBs.end(), aM);
	if (_it == FCBs.end())
		return false;

	Type _val(*_it);
	FCBs.erase(_it);
	_val.FPrior = aPrior;
	FCBs.insert(_val);
	return true;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::Type::operator ()(
		sender_t aSender, value_arg_t aWhat) const
{
	return FCb(aSender, aWhat)!=0;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::Type::operator <(
		Type const& right) const
{
	return FPrior < right.FPrior;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::Type::operator ==(
		Type const& right) const
{
	return FPrior == right.FPrior;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::Type::operator !=(
		Type const& right) const
{
	return FPrior != right.FPrior;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::Type::operator ==(
		value_t const& right) const
{
	return FCb == right;
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::operator+=(
		value_t const & aCB)
{
	return MAdd(aCB);
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline bool CEvent<TSender_type, TEvent_t, TEventArg_type>::operator-=(
		value_t const & aCB)
{
	return MErase(aCB);
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline typename CEvent<TSender_type, TEvent_t, TEventArg_type>::size_t CEvent<
		TSender_type, TEvent_t, TEventArg_type>::MSize() const
{
	return FCBs.size();
}
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline std::ostream& CEvent<TSender_type, TEvent_t, TEventArg_type>::MPrintEvent(
		std::ostream & aStream) const
{
	const_iterator _it = FCBs.begin();
	const_iterator const _it_end = FCBs.end();

	for (; _it != _it_end; ++_it)
		aStream << "Prior = " << _it->FPrior << ". \t" << _it->FCb << std::endl;
	return aStream;
}
} //namespace USHARE
namespace std
{
template<class TSender_type, class TEvent_t, class TEventArg_type>
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::CEvent<TSender_type, TEvent_t, TEventArg_type> const& aEvent)
{
	return aEvent.MPrintEvent(aStream);
}
} //namespace std

#endif /* CEVENT_HPP_ */
