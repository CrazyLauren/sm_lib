/*
 * shared_identify.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 09.07.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  

#ifndef SHARED_IDENTIFY_H_
#define SHARED_IDENTIFY_H_


namespace NSHARE
{
struct SHARE_EXPORT shared_identify_t
{
	static const CText NAME;
	static const CText SM_PID;
	static const CText SM_DESCRIPTOR;
	static const CText SM_USER_ID;

	shared_identify_t(NSHARE::CConfig const& aConf);
	shared_identify_t();
	unsigned FPid;
	unsigned FDescriptor;
	uint16_t FUserId;

	uint64_t MGetId() const
	{
		uint64_t _id = FPid;
		_id <<= 32;
		_id |= FDescriptor;
		VLOG(2) << "Id of " << FPid << " = " << _id;
		return _id;
	}
	bool MIsValid() const;
	bool MIsUserId() const;
	bool operator<(shared_identify_t const& aRht) const
	{
		return MGetId() < aRht.MGetId();
	}
	inline bool operator ==(const shared_identify_t& aRht) const
	{
		return FPid == aRht.FPid && FDescriptor == aRht.FDescriptor;
	}
	inline bool operator !=(const shared_identify_t& aRht) const
	{
		return !operator ==(aRht);
	}
	CConfig MSerialize() const;
};
}

#endif /* SHARED_IDENTIFY_H_ */
