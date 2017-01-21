/*
 * CIntrusived.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 22.04.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CREFER_H_
#define CREFER_H_

namespace NSHARE
{

class  SHARE_EXPORT CIntrusived
{
public:
	CIntrusived();
	CIntrusived(const CIntrusived& aRht);

	template<class T>
	static int sMRef(T**);
	template<class T>
	static int sMUnref(T**);
	int MUnrefWithoutDelete() const;
	int MCountRef() const;
	unsigned MReferedCount() const;
protected:
	virtual ~CIntrusived();
	CIntrusived& operator =(const CIntrusived& aVal);
private:
	struct _w_counter_t;
	enum
	{
		P_INITED = 0, P_NOT_INITED = 1, P_REMOVING = 2
	};
	struct SHARE_EXPORT w_counter_t
	{
		w_counter_t(CIntrusived* aP);
		w_counter_t(w_counter_t const &);
		w_counter_t& operator =(const w_counter_t& aVal);
		~w_counter_t();
		CIntrusived* MGet() const;
		volatile _w_counter_t* FWCounter;
	};

	int MRefImpl() const;
	int MUnrefImpl() const;
	void MDelete() const;

	volatile mutable unsigned FCount;
	mutable unsigned FReferedCount;
	volatile mutable unsigned FIsFirst;
	w_counter_t FWn;
	template<class U> friend class w_ptr;
	template<class U> friend class intrusive_ptr;
};
template<class T>
inline int CIntrusived::sMRef(T** aP)
{
	int _val = 0;
	{
		if (!aP || !(*aP))
			return 0;
		_val = (*aP)->CIntrusived::MRefImpl();
		if (_val <= 0)
			*aP = NULL;
	}
	return _val;
}
template<class T>
inline int CIntrusived::sMUnref(T** aP)
{
	int _val;
	T* _tmp = NULL;
	{
		if (!aP || !(*aP))
			return 0;
		if ((_val = (*aP)->CIntrusived::MUnrefImpl()) == 0)
		{
			_tmp = (*aP);
			*aP = NULL;
		}
	}
	if (_val == 0)
	{
		CHECK_NOTNULL(_tmp);
		_tmp->CIntrusived::MDelete();
	}
	return _val;
}
}
namespace boost
{
inline void intrusive_ptr_add_ref(NSHARE::CIntrusived* p)
{
	NSHARE::CIntrusived::sMRef(&p);
}
inline void intrusive_ptr_release(NSHARE::CIntrusived* p)
{
	NSHARE::CIntrusived::sMUnref(&p);
}
}

#endif /* CREFER_H_ */
