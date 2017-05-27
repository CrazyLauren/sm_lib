// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CSharedMemoryClient.cpp
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 11.05.2016
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#include <deftype>
#include <crc8.h>
#include <boost/version.hpp>
#include <boost/interprocess/detail/atomic.hpp>

#include <Socket/CSharedMemoryClient.h>
#include <UType/CSharedAllocator.h>
#include <Socket/CSharedMemoryImplTypes.h>
#include <Socket/CSharedMemoryClientImpl.h>

namespace NSHARE
{
const NSHARE::CText CSharedMemoryClient::NAME="sm_client";
CSharedMemoryClient::CSharedMemoryClient(NSHARE::CConfig const& aConf)
{
	CText _name;
	_name = aConf.MValue(SM_NAME, _name);
	size_t _reserv=0;
	_reserv=aConf.MValue(SM_RESERV, 0u);
	if (_name.empty())
	{
		LOG(DFATAL)<<"SM Client:Invalid parameter of configure "<<aConf<<". Require "<<SM_NAME<<"parameter.";
		FImpl=NSHARE::intrusive_ptr<CImpl>(new CImpl(*this, "",_reserv));
	}
	else
	{
		LOG(INFO)<<"Create SM client from configure "<<SM_NAME<<": "<<_name<<".";
		FImpl=NSHARE::intrusive_ptr<CImpl>(new CImpl(*this, _name,_reserv));
	}
}
CSharedMemoryClient::CSharedMemoryClient(NSHARE::CText const& aName,size_t aReserv) :
		FImpl(new CImpl(*this, aName,aReserv))
{
	;
}
CSharedMemoryClient::~CSharedMemoryClient()
{
}

bool CSharedMemoryClient::MOpen()
{
	return FImpl->MOpen();
}
bool CSharedMemoryClient::MOpen(NSHARE::CText const& aName,size_t aReserv)
{
	return FImpl->MOpen(aName,aReserv);
}
bool CSharedMemoryClient::MIsOpen() const
{
	return FImpl->MIsOpen();
}
bool CSharedMemoryClient::MReOpen()
{
	MClose();
	return MOpen();
}
bool CSharedMemoryClient::MConnect(double aTime)
{
	return FImpl->MConnect(aTime);
}
bool CSharedMemoryClient::MIsConnected() const
{
	return FImpl->MIsConnected();
}
void CSharedMemoryClient::MClose()
{
	FImpl->MClose();
}

NSHARE::CText const& CSharedMemoryClient::MSharedName() const
{
	return FImpl->MSharedName();
}
shared_identify_t CSharedMemoryClient::MIdentifier() const
{
	return FImpl->MIdentifier();
}
shared_identify_t CSharedMemoryClient::MServerIdentifier() const
{
	return FImpl->MServerIdentifier();
}
CSharedMemoryClient::eSendState CSharedMemoryClient::MSend(
		NSHARE::CBuffer const& aVal, bool aBlock, unsigned aFlags)
{
	data_t _data(aVal);//fixme copy data
	return FImpl->MSend(_data, aBlock, aFlags);
}
CSharedMemoryClient::sent_state_t CSharedMemoryClient::MSend(void const* aData, std::size_t aSize)
{
	if (!aSize || !aData)
	{
		LOG(ERROR)<<"Buf error.";
		return sent_state_t(E_ERROR,0);
	}

	NSHARE::CBuffer _buffer(MAllocate(aSize));
	if(_buffer.empty())
	{
		LOG(ERROR)<<"Cannot allocate buffer "<<aSize;
		return sent_state_t(E_ERROR,0);
	}
	memcpy(_buffer.ptr(),aData,aSize);
	return MSend(_buffer);
}
CSharedMemoryClient::sent_state_t CSharedMemoryClient::MSend(data_t const& aVal)
{
	data_t _data(aVal);
	eSendState const _state=MSend(_data, false, 0);
	return sent_state_t(_state, _state == E_SENDED ? aVal.size() :0 );
}
CSharedMemoryClient::sent_state_t CSharedMemoryClient::MSend(data_t const& aVal,
		NSHARE::CConfig const& aTo)
{
	VLOG(0) << "MSend to is not implemented";
	return MSend(aVal);
}
bool CSharedMemoryClient::MReceiveData(NSHARE::CBuffer& aTo,
		shared_identify_t* aFrom, unsigned* aFlags, double aTime)
{
	return FImpl->MReceiveData(aTo, aFrom, aTime, aFlags);
}
ssize_t CSharedMemoryClient::MReceiveData(NSHARE::CBuffer *aBuf,
		float const aTime)
{
	if (FImpl->MReceiveData(*aBuf, NULL, aTime, NULL))
		return aBuf->size();
	return -1;
}

size_t CSharedMemoryClient::MGetSize() const
{
	return FImpl->MGetSize();
}
std::ostream & CSharedMemoryClient::MPrint(std::ostream & aStream) const
{
	return FImpl->MPrint(aStream);
}
size_t CSharedMemoryClient::MAvailable() const
{
	return FImpl->MAvailable();
}
IAllocater* CSharedMemoryClient::MGetAllocator() const
{

	return FImpl->MGetAllocator();
}
void CSharedMemoryClient::MSetOption(eSettings aSet, unsigned aVal)
{
	FImpl->MSetOption(aSet, aVal);
}
unsigned CSharedMemoryClient::MGetOption(eSettings aSet) const
{
	return FImpl->MGetOption(aSet);
}
bool CSharedMemoryClient::MOverload() const
{
	return FImpl->MOverload();
}
NSHARE::CConfig CSharedMemoryClient::MSettings(void) const
{
	NSHARE::CConfig _conf(NAME);
	_conf.MAdd(SM_NAME,FImpl->MSharedName());
	_conf.MAdd(SM_RESERV,FImpl->MReserve());
	return _conf;
}
NSHARE::CConfig CSharedMemoryClient::MSerialize() const
{
	NSHARE::CConfig _conf(NAME);
	FImpl->MSerialize(_conf);
	return _conf;
}
}
