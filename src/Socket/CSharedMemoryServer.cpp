/*
 * CSharedMemoryServer.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 28.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#include <deftype>
#include <crc8.h>
#include <Socket/CSharedMemoryBase.h>
#include <UType/CSharedAllocator.h>
#include <Socket/CSharedMemoryImplTypes.h>
#include <Socket/CSharedMemoryBaseImpl.h>
#include <Socket/CSharedMemoryServer.h>
#include <Socket/CSharedMemoryServerImpl.h>
#include <UType/CSharedAllocator.h>

#define IMPL_CLASS CSharedMemoryServer::CImpl

namespace NSHARE
{
const CText CSharedMemoryServer::NAME = "sm_server";
version_t CSharedMemoryServer::sMGetVersion()
{
	return version_t(0, 1);
}
/*
 *
 *
 *
 *
 *
 *
 *
 *
 */
CSharedMemoryServer::CSharedMemoryServer(NSHARE::CConfig const& aConf)
{
	CText _name;
	_name = aConf.MValue(SM_NAME, _name);
	size_t _size = 0;
	_size = aConf.MValue(SM_SIZE, 0u);
	size_t _reserv = 0;
	_reserv = aConf.MValue(SM_RESERV, 0u);
	if (_name.empty() || !_size)
	{
		LOG(DFATAL)<<"SM Server: Invalid parameter of config "<<aConf<<". Require "<<SM_NAME<<", "<<SM_SIZE<<" parameters.";
		FImpl=NSHARE::intrusive_ptr<CImpl>(new CImpl(*this, "", 0,_reserv));
	}
	else
	{
		LOG(INFO)<<"Create SM server from configure "<<SM_NAME<<": "<<_name<<"; "<<SM_SIZE<<": "<<_size;
		FImpl=NSHARE::intrusive_ptr<CImpl>(new CImpl(*this, _name, _size,_reserv));
	}
}
CSharedMemoryServer::CSharedMemoryServer(NSHARE::CText const& aName,
		size_t aSize, size_t aReserv) :
		FImpl(new CImpl(*this, aName, aSize, aReserv))
{
	;
}
CSharedMemoryServer::~CSharedMemoryServer()
{
}
bool CSharedMemoryServer::MOpen()
{

	return FImpl->MOpen();
}
bool CSharedMemoryServer::MOpen(NSHARE::CText const& aName, size_t aSize,
		size_t aReserv)
{

	return FImpl->MOpen(aName, aSize, aReserv);
}
bool CSharedMemoryServer::MIsOpen() const
{

	return FImpl->MIsOpen();
}
bool CSharedMemoryServer::MReOpen()
{
	return FImpl->MReOpen();
}

void CSharedMemoryServer::MClose()
{
	FImpl->MClose();
}
bool CSharedMemoryServer::MClose(shared_identify_t const& aVal)
{
	return FImpl->MClose(aVal);
}
bool CSharedMemoryServer::MClose(int aUserId)
{
	return FImpl->MClose(aUserId);
}
CSharedMemoryBase::eSendState CSharedMemoryServer::MSend(
		shared_identify_t const& aVal1, NSHARE::CBuffer const& aVal,
		bool aBlock, unsigned aFlags)
{
	NSHARE::CBuffer _data(aVal); //fixme
	return FImpl->MSend(aVal1, _data, aBlock, aFlags);
}
unsigned CSharedMemoryServer::MSend(int aUserId, NSHARE::CBuffer const& aVal,
		bool aBlock, unsigned aFlags)
{
	NSHARE::CBuffer _data(aVal); //fixme
	return FImpl->MSend(aUserId, _data, aBlock, aFlags);
}
CSharedMemoryServer::sent_state_t CSharedMemoryServer::MSend(void const* aData,
		std::size_t aSize, NSHARE::CConfig const& aTo)
{
	if (!aSize || !aData)
	{
		LOG(ERROR)<<"Buf error.";
		return sent_state_t(E_INVALID_VALUE,0);
	}

	NSHARE::CBuffer _buffer(MAllocate(aSize));
	if(_buffer.empty())
	{
		LOG(ERROR)<<"Cannot allocate buffer "<<aSize;
		return sent_state_t(E_TOO_LARGE,0);
	}
	memcpy(_buffer.ptr(),aData,aSize);
	return MSend(_buffer,aTo);
}
CSharedMemoryServer::sent_state_t CSharedMemoryServer::MSend(void const* aData,
		std::size_t aSize)
{
	if (!aSize || !aData)
	{
		LOG(ERROR)<<"Buf error.";
		return sent_state_t(E_INVALID_VALUE,0);
	}

	NSHARE::CBuffer _buffer(MAllocate(aSize));
	if(_buffer.empty())
	{
		LOG(ERROR)<<"Cannot allocate buffer "<<aSize;
		return sent_state_t(E_TOO_LARGE,0);
	}
	memcpy(_buffer.ptr(),aData,aSize);
	bool const _is=MSend(-1,_buffer,false,0)>0;
	return _is?sent_state_t(E_SENDED,aSize):sent_state_t(E_ERROR,0);
}
CSharedMemoryServer::sent_state_t CSharedMemoryServer::MSend(data_t const& aVal)
{
	data_t _const_fix = aVal;
	bool const _is = MSend(-1, _const_fix, false, 0) > 0;
	return _is ? sent_state_t(E_SENDED, aVal.size()) : sent_state_t(E_ERROR, 0);
}

CSharedMemoryServer::sent_state_t CSharedMemoryServer::MSend(data_t const& aVal,
		NSHARE::CConfig const& aTo)
{
	VLOG(2) << "Send to " << aTo;
	shared_identify_t _ato(aTo);
	unsigned _flags = 0;
	aTo.MGetIfSet("flags", _flags);
	data_t _const_fix = aVal;
	if (_ato.MGetId())
	{
		VLOG(2) << "Send by id";
		eSendState const _state = MSend(_ato, _const_fix, false, _flags);
		return sent_state_t(_state, _state == E_SENDED ? aVal.size() : 0);
	}
	else if (_ato.MIsUserId())
	{
		VLOG(2) << "Send by ID";
		bool const _is = MSend(_ato.FUserId, _const_fix, false, _flags) > 0;
		return _is ?
				sent_state_t(E_SENDED, aVal.size()) : sent_state_t(E_ERROR, 0);
	}
	return sent_state_t(E_INVALID_VALUE, 0);
}
bool CSharedMemoryServer::MReceiveData(NSHARE::CBuffer& aTo,
		shared_identify_t* aFrom, unsigned* aFlags, double aTime)
{
	return FImpl->MReceiveData(aTo, aFrom, aTime, aFlags);
}
ssize_t CSharedMemoryServer::MReceiveData(NSHARE::CBuffer * aBuf,
		float const aTime)
{
	CHECK_NOTNULL(aBuf);
	if (FImpl->MReceiveData(*aBuf, NULL, aTime, NULL))
		return aBuf->size();
	return -1;
}
ssize_t CSharedMemoryServer::MReceiveData(data_t * aData, float const aTime,
		recvs_from_t *aFrom)
{
	CHECK_NOTNULL(aData);
	shared_identify_t _id;
	if (!FImpl->MReceiveData(*aData, &_id, aTime, NULL))
	{
		return -1;
	}
	if (aFrom)
	{
		receive_from_t _from;
		_from.FBufBegin = aData->begin();
		_from.FSize = aData->size();
		_from.FAddr = _id.MSerialize();
		aFrom->push_back(_from);
	}
	return aData->size();
}
NSHARE::CText const& CSharedMemoryServer::MSharedName() const
{
	return FImpl->MSharedName();
}
size_t CSharedMemoryServer::MGetSize() const
{
	return FImpl->MGetSize();
}

shared_identify_t CSharedMemoryServer::MIdentifier() const
{
	return FImpl->MIdentifier();
}

std::ostream& CSharedMemoryServer::MPrint(std::ostream& aStream) const
{
	return FImpl->MPrint(aStream);
}
size_t CSharedMemoryServer::MAvailable() const
{
	return FImpl->MAvailable();
}
bool CSharedMemoryServer::MIsClient(shared_identify_t const& aVal) const
{
	if (!aVal.MIsValid())
		return false;
	return FImpl->MIsClient(aVal);
}
bool CSharedMemoryServer::MIsClients() const
{
	return FImpl->MIsClients();
}

bool CSharedMemoryServer::MIsConnected() const
{
	return FImpl->MIsConnected();
}

CSharedMemoryServer::client_array_t CSharedMemoryServer::MGetClients() const
{
	CSharedMemoryServer::client_array_t _clients;
	FImpl->MGetClients(_clients);
	return _clients;
}
IAllocater* CSharedMemoryServer::MGetAllocator() const
{
	return FImpl->MGetAllocator();
}

bool CSharedMemoryServer::MIsOverload(shared_identify_t const& aFor) const
{
	return FImpl->MIsOverload(aFor);
}
void CSharedMemoryServer::MSetOption(eSettings aSet, unsigned aVal)
{
	return FImpl->MSetOption(aSet, aVal);
}
unsigned CSharedMemoryServer::MGetOption(eSettings aSet) const
{
	return FImpl->MGetOption(aSet);
}
bool CSharedMemoryServer::sMRemove(NSHARE::CText const& aName)
{
	return CSharedMemory::sMRemove(aName);
}
NSHARE::CConfig CSharedMemoryServer::MSettings(void) const
{
	NSHARE::CConfig _conf(NAME);
	FImpl->MSettings(_conf);
	return _conf;
}
NSHARE::CConfig CSharedMemoryServer::MSerialize() const
{
	NSHARE::CConfig _conf(NAME);
	FImpl->MSerialize(_conf);
	return _conf;
}
} /* namespace NSHARE */
