/*
 * SmartField.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 06.08.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef SMARTFIELD_H_
#define SMARTFIELD_H_
#define SMART_FIELD_EXIST
namespace NSHARE
{
template<typename _T>
struct  smart_field_t
{
	typedef _T type_t;
	typedef smart_field_t<type_t> my_t;
	smart_field_t() :
			FVal(type_t()), FIsSet(false)
	{
	}
	explicit smart_field_t(type_t const& aVal)
	{
		MSet(aVal);
	}
	smart_field_t(const my_t& aRhs)
	{
		(*this) = aRhs;
	}
	my_t& operator =(const my_t& aRhs)
	{
		FIsSet = aRhs.FIsSet;
		FVal = aRhs.FVal;
		return *this;
	}

	inline bool operator ==(const my_t& aRhs) const
	{
		return MIs() && aRhs.MIs() && sMValueEqualeCompare(MGetConst() , aRhs.MGetConst());
	}
	inline bool operator !=(const my_t& aRhs) const
	{
		return !operator ==(aRhs);
	}

	const type_t& operator =(const type_t& aVal)
	{
		MSet(aVal);
		return MGet();
	}
	inline bool operator ==(const type_t& aVal) const
	{
		return MIs() && sMValueEqualeCompare(MGetConst() , aVal);
	}
	inline bool operator !=(const type_t& aVal) const
	{
		return !operator ==(aVal);
	}
	inline bool operator >(const type_t& aVal) const
	{
		return MIs() && MGetConst() > aVal;
	}
	inline bool operator >=(const type_t& aVal) const
	{
		return MIs() && (MGetConst() > aVal || sMValueEqualeCompare(MGetConst() , aVal));
	}
	inline bool operator <(const type_t& aVal) const
	{
		return MIs() && MGetConst() < aVal;
	}
	inline bool operator <=(const type_t& aVal) const
	{
		return MIs() && (MGetConst() < aVal|| sMValueEqualeCompare(MGetConst() , aVal));
	}
	inline void MSet(type_t const& aVal)
	{
		FVal = aVal;
		FIsSet = true;
	}
	inline bool MIs() const
	{
		return FIsSet;
	}
	inline void MUnSet()
	{
		FIsSet = false;
	}

	inline type_t const& MGetConst() const
	{
		return FVal;
	}
	inline type_t& MGet()
	{
		FIsSet = true;
		return FVal;
	}

	operator const type_t() const
	{
		return FVal;
	}
//	operator const type_t*() const
//	{
//		return &FVal;
//	}
	/*	type_t* operator ->()
	 {
	 FIsSet = true;
	 return &FVal;
	 }
	 const type_t* operator ->() const
	 {
	 return &FVal;
	 }*/
private:
	template<class U>
	static inline bool sMValueEqualeCompare( U const & aLeft, U const & aRht)
	{
		return aLeft==aRht;
	}
	static inline bool sMValueEqualeCompare( double const & aLeft, double const & aRht)
	{
		return approximatelyEqual(aLeft,aRht);
	}
	static inline bool sMValueEqualeCompare( long double const & aLeft, long double const & aRht)
	{
		return approximatelyEqual(aLeft,aRht);
	}
	static inline bool sMValueEqualeCompare(float const & aLeft,	float const & aRht)
	{
		return approximatelyEqual(aLeft,aRht);
	}
	type_t FVal;
	bool FIsSet;
};
template<class T>
struct smart_field_t<T*>
{
	typedef T type_t;
	typedef T* ptype_t;
	typedef smart_field_t<ptype_t> my_t;
	smart_field_t() :
			FVal(NULL), FIsSet(false)
	{
	}
	smart_field_t(ptype_t const& aVal)
	{
		MSet(aVal);
	}
	smart_field_t(const my_t& aRhs)
	{
		(*this) = aRhs;
	}
	my_t& operator =(const my_t& aRhs)
	{
		FIsSet = aRhs.FIsSet;
		FVal = aRhs.FVal;
		return *this;
	}
	inline bool operator ==(const my_t& aRhs) const
	{
		return MIs() && aRhs.MIs() && (MGet() == aRhs.MGet());
	}
	inline bool operator !=(const my_t& aRhs) const
	{
		return !operator ==(aRhs);
	}

	const ptype_t& operator =(const ptype_t& aVal)
	{
		MSet(aVal);
		return MGet();
	}
	inline bool operator ==(const ptype_t& aVal) const
	{
		return MIs() && MGet() == aVal;
	}
	inline bool operator !=(const ptype_t& aVal) const
	{
		return !operator ==(aVal);
	}
	inline bool operator >(const ptype_t& aVal) const
	{
		return MIs() && MGet() > aVal;
	}
	inline bool operator >=(const ptype_t& aVal) const
	{
		return MIs() && MGet() >= aVal;
	}
	inline bool operator <(const ptype_t& aVal) const
	{
		return MIs() && MGet() < aVal;
	}
	inline bool operator <=(const ptype_t& aVal) const
	{
		return MIs() && MGet() <= aVal;
	}
	inline void MSet(ptype_t const& aVal)
	{
		FIsSet = true;
		FVal = aVal;
	}
	inline bool MIs() const
	{
		return FIsSet;
	}
	inline void MUnSet()
	{
		FIsSet = false;
	}

	inline ptype_t const& MGet() const
	{
		return FVal;
	}
	inline ptype_t& MGet()
	{
		FIsSet = true;
		return FVal;
	}

	operator const ptype_t() const
	{
		return FVal;
	}
	ptype_t& operator ->()
	{
		return MGet();
	}
	const ptype_t& operator ->() const
	{
		return MGet();
		//return &FVal;
	}
	const type_t& operator*() const
	{
		return *MGet();
	}
	type_t& operator*()
	{
		return *MGet();
	}
private:
	ptype_t FVal;
	bool FIsSet;
};
}
namespace std
{
template<typename T>
inline std::ostream& operator<<(std::ostream & aStream,
		NSHARE::smart_field_t<T> const& aVal)
{
	return aStream << aVal.MGetConst();
}
template<typename T>
std::istream& operator>>(std::istream & aStream,
		NSHARE::smart_field_t<T>& aBase)
{
	aStream>>aBase.MGet();
	return aStream;
}
}
#endif /* SMARTFIELD_H_ */
