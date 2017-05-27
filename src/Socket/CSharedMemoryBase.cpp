// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CSharedMemoryBase.cpp
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 23.06.2016
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#include <deftype>
#include <crc8.h>
#include <tasks.h>
#include <Socket/CSharedMemoryBase.h>
#include <UType/CSharedAllocator.h>
#include <Socket/CSharedMemoryImplTypes.h>
#include <Socket/CSharedMemoryBaseImpl.h>

namespace NSHARE
{




CSharedMemoryBase::events_t::key_t const  CSharedMemoryBase::EVENT_CONNECTED =
		"Connect";
CSharedMemoryBase::events_t::key_t const  CSharedMemoryBase::EVENT_DISCONNECTED =
		"Disconnect";
/*
 *
 *
 *
 *
 *
 */

const CText CSharedMemoryBase::SM_NAME="name";
const CText CSharedMemoryBase::SM_SIZE="size";
const CText CSharedMemoryBase::SM_RESERV="reserv";
const CText CSharedMemoryBase::SM_CLIENT="client";
const CText CSharedMemoryBase::SM_SERVER="server";
void CSharedMemoryBase::MCallEventConnected(shared_identify_t const& aPid)
{
	MCall(EVENT_CONNECTED, const_cast<shared_identify_t*>(&aPid));
}

void CSharedMemoryBase::MCallEventDisconnected(shared_identify_t const& aPid)
{
	MCall(EVENT_DISCONNECTED, const_cast<shared_identify_t*>(&aPid));
}
CBuffer CSharedMemoryBase::MAllocate(size_t aSize,int aBeginSize,eAllocatorType aType) const
{
	VLOG(2) << "Allocate " << aSize << " bytes.";
	IAllocater* const _p_alloc = MGetAllocator();
	if (_p_alloc)
	{
		CBuffer _buf(aSize,aBeginSize, _p_alloc,aType);
		VLOG(2) << _buf.size() << " bytes Allocated "<<_buf.use_count();
		return _buf;
	}
	LOG(ERROR)<<"The buffer "<<aSize<<" cannot be allocated as shared memory is not initialized.";
	return CBuffer();
}

/*
 *
 *
 *
 *
 *
 *
 */
const CText shared_identify_t::NAME="sid";
const CText shared_identify_t::SM_PID="pid";
const CText shared_identify_t::SM_DESCRIPTOR="d";
const CText shared_identify_t::SM_USER_ID="userId";
shared_identify_t::shared_identify_t(NSHARE::CConfig const& aConf) :
		FPid(0), FDescriptor(0), FUserId(std::numeric_limits<uint16_t>::max())
{
	FPid=aConf.MValue(SM_PID, FPid);
	FDescriptor=aConf.MValue(SM_DESCRIPTOR, FDescriptor);
	aConf.MGetIfSet(SM_USER_ID, FUserId);
}
shared_identify_t::shared_identify_t() :
		FPid(0), FDescriptor(0), FUserId(std::numeric_limits<uint16_t>::max())
{

}
bool shared_identify_t::MIsValid() const
{
	return (FPid && FDescriptor) || MIsUserId();
}
bool shared_identify_t::MIsUserId() const
{
	return FUserId!=std::numeric_limits<uint16_t>::max();
}
CConfig shared_identify_t::MSerialize() const
{
	CConfig _conf(NAME);
	if (MIsValid())
	{
		_conf.MSet(SM_PID, FPid);
		_conf.MSet(SM_DESCRIPTOR, FDescriptor);
		if (MIsUserId())
			_conf.MSet(SM_USER_ID, FUserId);
	}
	return _conf;
}
}
