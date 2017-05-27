/*
 * uuid.h
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 30.11.2015
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef UUID_H_
#define UUID_H_

#ifdef __MINGW32__
#	ifdef uuid_t
#		undef uuid_t
typedef UUID uuid_t;
#	endif
#endif

namespace NSHARE
{

struct SHARE_EXPORT uuid_t
{
	static const CText NAME;
	uuid_t():FVal(0)
	{

	}
	explicit uuid_t( uint64_t const& aVal):FVal(aVal)
	{

	}
#ifdef SHARE_CONFIG_DEFINED
	NSHARE::CConfig MSerialize() const;
	uuid_t(NSHARE::CConfig const& aConf);
#endif
	bool MIsValid()const;
	CText MToString() const;
	bool MFromString(CText const&);
	uint32_t MGetHash()const;

	uuid_t& operator =(uint64_t const& aVal)
	{
		FVal = aVal;
		return *this;
	}

	uint64_t FVal;
};
uuid_t SHARE_EXPORT get_programm_uuid(CText const& = CText());//При первом вызове создаёт уникальный UUID
uuid_t SHARE_EXPORT get_uuid(CText const& =CText());
CText SHARE_EXPORT get_random_str(size_t aLen);

inline bool operator==(const uuid_t& aUUID, uint64_t aVal)
{
	return (aUUID.FVal == aVal);
}

inline bool operator==(uint64_t aVal, const uuid_t& aUUID)
{
	return (aUUID.FVal == aVal);
}
inline bool operator==(const uuid_t& aVal, const uuid_t& aUUID)
{
	return (aUUID.FVal == aVal);
}

inline bool operator!=(const uuid_t& aUUID, uint64_t aVal)
{
	return (aUUID.FVal != aVal);
}

inline bool operator!=(uint64_t aVal, const uuid_t& aUUID)
{
	return (aUUID.FVal != aVal);
}
inline bool operator!=(const uuid_t& aVal, const uuid_t& aUUID)
{
	return (aUUID.FVal != aVal);
}
inline bool operator<(const uuid_t& aUUID, uint64_t aVal)
{
	return (aUUID.FVal < aVal);
}

inline bool operator<(uint64_t aVal, const uuid_t& aUUID)
{
	return (aVal <aUUID.FVal );
}
inline bool operator<(const uuid_t& aVal, const uuid_t& aUUID)
{
	return (aVal <aUUID.FVal );
}

inline bool operator>(const uuid_t& aUUID, uint64_t aVal)
{
	return (aUUID.FVal > aVal);
}

inline bool operator>(uint64_t aVal, const uuid_t& aUUID)
{
	return (aVal > aUUID.FVal);
}
inline bool operator>(const uuid_t& aVal, const uuid_t& aUUID)
{
	return (aVal > aUUID.FVal);
}
inline bool operator<=(const uuid_t& aUUID, uint64_t aVal)
{
	return (aUUID.FVal <= aVal);
}

inline bool operator<=(uint64_t aVal, const uuid_t& aUUID)
{
	return (aVal <= aUUID.FVal);
}
inline bool operator<=(const uuid_t& aVal, const uuid_t& aUUID)
{
	return (aVal <= aUUID.FVal);
}
inline bool operator>=(const uuid_t& aUUID, uint64_t aVal)
{
	return (aUUID.FVal >= aVal);
}

inline bool operator>=(uint64_t aVal, const uuid_t& aUUID)
{
	return (aVal >= aUUID.FVal);
}

inline bool operator>=(const uuid_t& aVal, const uuid_t& aUUID)
{
	return (aVal >= aUUID.FVal);
}
}

namespace std
{
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::uuid_t const& aUuid)
{
	return aStream<<aUuid.MToString();
}
inline std::istream& operator>>(std::istream& aStream,
		NSHARE::uuid_t& aUuid)
{
	NSHARE::CText _text;
	aStream>>_text;
	if (aStream.fail())
	{
		aStream.setstate(std::istream::failbit);
		return aStream;
	}
	if (!aUuid.MFromString(_text))
	{
		aStream.setstate(std::istream::failbit);
		return aStream;
	}
	return aStream;
}
}

#endif /* UUID_H_ */
