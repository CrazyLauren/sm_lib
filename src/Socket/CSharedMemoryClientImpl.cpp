// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CSharedMemoryClientImpl.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 09.07.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
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
#define IMPL_CLASS CSharedMemoryClient::CImpl
namespace NSHARE
{
#if (BOOST_VERSION / 100000 >=1) &&(BOOST_VERSION / 100 % 1000<=47)
using namespace boost::interprocess::detail;
#else
using namespace boost::interprocess::ipcdetail;
#endif

version_t CSharedMemoryClient::sMGetVersion()
{
	return version_t(0, 1);
}

CSharedMemoryClient::CImpl::CImpl(CSharedMemoryClient& aThis,
		NSHARE::CText const& aName,size_t aReserv) :
		FThis(aThis), //
		FMyInfo(NULL), //
		FName(aName), //
		FReserv(aReserv),//
		FIsConnected(false), //
		FIsOpened(false) //
{
	if (!aName.empty())
		MOpen();
}
IMPL_CLASS ::~CImpl()
{
	MClose();
}

void IMPL_CLASS::MCreateClient(IAllocater* _alloc,int aUserId)
{
	VLOG(2) << "Allocate client";
	size_t const _client_size=get_client_fifo_size(MGetOption(CSharedMemoryBase::SEND_BUFFER_SIZE));
	void* _ptr = _alloc->MAllocate(_client_size);
	FMyInfo = new (_ptr) client_info_t(NSHARE::CThread::sMPid(),_client_size);
	CHECK_NOTNULL(FMyInfo);
	CHECK_LT(aUserId, std::numeric_limits<uint16_t>::max());
	if(aUserId>=0)
	FMyInfo->FInfo.FId.FUserID = aUserId;
	FEv.FEvents= &FMyInfo->FInfo;
	VLOG(2) << "Events ptr =" << FEv.FEvents;
	MCreateSignalEvent(FEv);
}
bool IMPL_CLASS::MReOpen()
{
	MClose();
	return MOpen();
}
bool IMPL_CLASS::MOpen()
{
	VLOG(2) << "Open client for " << FName;
	if (MIsConnected() || MIsOpen())
	return false;
	CHECK(!FName.empty());
	CHECK(!FMyInfo);
	CHECK(!MIsConnected());
	CHECK(!FEv.FEvents);
	CHECK(!FServerInfo);

	bool _is = FSharedMemory.MOpen(FName,true,FReserv);
	LOG_IF(ERROR,!_is) << "Cannot open " << FName;
	if (!_is)
	return false;
	VLOG(2)<<"The ShM "<<FName<<" is opened";
	void* _p = FSharedMemory.MGetIfMalloced(0);
	LOG_IF(ERROR,!_is) << "The shared memory " << FName << " has not server.";
	if (!_p)
	{
		MFreeBase();
		return false;
	}

	_is = MOpenServer(_p);
	if (!_is)
	{
		LOG(ERROR)<<"Cannot open server.";
		MFreeBase();
		return false;
	}
	IAllocater* _alloc = FSharedMemory.MGetAllocator();
	CHECK_NOTNULL(_alloc);
	MCreateClient(_alloc);

	FIsOpened = true;
	return true;
}
bool IMPL_CLASS::MOpen(NSHARE::CText const& aName,size_t aReserv)
{
	FName = aName;
	FReserv=aReserv;
	return MOpen();
}

bool IMPL_CLASS::MOpenServer(void* _p)
{
	VLOG(2) << "Open server addr=" << _p;
	CHECK_NOTNULL(_p);
	server_info_t* _info = reinterpret_cast<server_info_t*>(_p);

	bool _is = _info->MCheckCrc() && is_process_exist(_info->FInfo.FId.FPid);
	VLOG_IF(2, !_is) << "Invalid server info crc.";
	if (!_is)
	return false;

	_is = MInitSharedSem(_info);
	if (!_is)
	{
		LOG(ERROR)<<"Cannot initialize semaphore.";
		return false;
	}
	_is = MInitSignalEvent(FServerSignalEvent, &_info->FInfo);
	FServerInfo = _info;
	VLOG(2)<<"Opened";
	return true;
}
void IMPL_CLASS::MInvokeEvent(event_info_t* _info)
{
	MInvokeEventTo(FServerSignalEvent, _info);
}

bool IMPL_CLASS::MConnect(double aTime)
{
	if (!MIsOpen())
	{
		LOG(ERROR)<<"The shared client is not opened.";
		return false;
	}
	CHECK_NOTNULL(FMyInfo);
	CHECK_NOTNULL(FEv.FEvents);
	CHECK_NOTNULL(FServerInfo);
	NSHARE::CRAII<CMutex> _block(FConnectMutex);
	if (MIsConnected())
	{
		LOG(ERROR)<<"connected already";
		return true;
	}
	VLOG(2) << "Connect "<<FMyInfo->FInfo.FId<<" Time=" << aTime;
	event_info_t _info;
	_info.FEventType = event_info_t::E_CONNECT;
	_info.FConnect.FClientOffset = FSharedMemory.MGetAllocator()->MOffset(FMyInfo);
	MInvokeEvent(&_info);

	_info.FEventType = event_info_t::E_NO;
	double _time=NSHARE::get_time();
	bool _is_not_timeout=false;
	bool _is_try_again=false;
	do
	{
		for(;(NSHARE::get_time()-_time)<aTime && MIsOpen();)
		{
			_is_not_timeout=MWaitForEvent(FEv,&_info, aTime);
			VLOG_IF(2,_is_not_timeout)<<"Event recv="<<_info;
			if(!_is_not_timeout)
			{
				VLOG(2)<<"Event connecting is not received";
				continue;
			}
			if(_info.FEventType == event_info_t::E_CONNECTED)
			break;
			else
			{
				LOG(WARNING)<<"Receive unknown event "<<_info;
			}
		}

		if (_is_not_timeout)
		{
			if(_info.FEventType == event_info_t::E_CONNECTED)
			{
				LOG(INFO)<<"Connected";
				MEventConnected(_info.FIdFrom.MGetId(),_info.FConnect.FClientOffset);
				break;
			}
			else
			CHECK(false);
		}
		else if(MRemoveEvent(&_info,FEv))
		{
			LOG(ERROR)<<"Cannot connect";
			CHECK_EQ(FMyInfo->FInfo.FId.FUniqueID,0);
			break;
		}else
		{
			CHECK_NE(_info.FEventType, event_info_t::E_CONNECTED);
			if(_is_try_again)
			{
				DCHECK_EQ(FMyInfo->FInfo.FId.FUniqueID,0);
				if(FMyInfo->FInfo.FId.FUniqueID==0)
				return false;
				break;
			}
			_is_try_again=true;
			LOG(ERROR)<<"The server is handling the connection";
			_time=NSHARE::get_time();
			continue;
		}
	}while(!FIsConnected && MIsOpen());

	return FIsConnected;
}
void IMPL_CLASS::MEventConnected(shared_identify_t const& aPid,
		IAllocater::offset_pointer_t)
{
	CHECK_EQ(aPid, FServerInfo->FInfo.FId.MGetId());
	FIsConnected = true;
	MCreateEventHandler(FEv);
	LOG(INFO)<<"Connected "<<FMyInfo->FInfo.FId;

	FThis.MCallEventConnected(aPid);
}

void IMPL_CLASS::MEventDisconnected(shared_identify_t const& aPid,
		IAllocater::offset_pointer_t)
{
	CHECK_EQ(aPid, FServerInfo->FInfo.FId.MGetId());
	FIsConnected = false;
	FEventDone = true;
	LOG(INFO)<<"Disconnected "<<FMyInfo->FInfo.FId;
	FThis.MCallEventDisconnected(aPid);
}
void IMPL_CLASS::MDisconnect()
{
	VLOG(2) << "Disconnect client " << FMyInfo->FInfo.FId;
	NSHARE::CRAII<CMutex> _block(FConnectMutex);
	if(!MIsConnected() || !MIsOpen())
	{
		LOG(INFO) << "It's not connected."<< MIsOpen();
		return;
	}

	event_info_t _info;
	_info.FEventType = event_info_t::E_DISCONECT;
	_info.FConnect.FClientOffset = FSharedMemory.MGetAllocator()->MOffset(
			FMyInfo);
	MInvokeEvent(&_info);

	LOG_IF(DFATAL,FEventDone) << "The event handler is not working";

	if (!FEventDone)
	{
		double const _time = NSHARE::get_time();
		VLOG(2) << "Wait for disconnected:" << _time;
		for (; FIsConnected && ((NSHARE::get_time() - _time) <= 1.);
				NSHARE::usleep(1000))
		{

		}
		VLOG(2) << "End Wait for disconnected:" << NSHARE::get_time()
		<< " FIsConnected=" << FIsConnected;
	}
	LOG_IF(ERROR,FIsConnected) << "The event \"Disconnected\" is not handled";
	if (FIsConnected)
	{
		CHECK_NOTNULL(FServerInfo);
		if (!FEventDone)
		MStopEventHandlerForce();
		MEventDisconnected(FServerInfo->FInfo.FId.MGetId(), 0);
	}
	VLOG(2) << "The client is disconnected successfully.";
}

bool IMPL_CLASS::MClose()
{
	if (!MIsOpen())
	{
		VLOG(2) << "The shared client is not opened.";
		return false;
	}
	VLOG(2) << "Close client " << FMyInfo->FInfo.FId;
	VLOG_IF(2,!MIsConnected()) << "Does not connected.";
	if (MIsConnected())
	MDisconnect();


	FIsOpened = false;

	VLOG(2) << "Deallocate memory";
	FServerSignalEvent.FSignalEvent.MFree();
	FServerSignalEvent.FSignalSem.MFree();
	if(FMyInfo->FInfo.FId.FUniqueID==0)//the server is handled disconnect
	deallocate_object(FSharedMemory.MGetAllocator(), FMyInfo);

	FMyInfo = NULL;
	if(MFreeBase())
	{
		FServerSignalEvent.FSignalEvent.MUnlink();
		FServerSignalEvent.FSignalSem.MUnlink();
	}
	return true;
}

bool IMPL_CLASS::MReceiveData(NSHARE::CBuffer& aTo,shared_identify_t* aFrom,
		double aTime,unsigned* aFFlags)
{
	VLOG(2) << "Start receive.";
	for (; MIsOpen(); )
	{
		if(MIsConnected())
		{
			VLOG(2) << "Connected already";
			//
			recv_t _result;
			if(!CSharedMemoryBase::CImpl::MReceiveData(_result,aTime))
			return false;
			if(aFrom)
			*aFrom=_result.FFrom;
			if(aFFlags)
			*aFFlags=_result.FFlags;
			_result.FData.MMoveTo(aTo);
			return true;
		}
		else
		{
			VLOG(2) << "Try connect";
			MConnect();
		}
	}
	VLOG(2) << "End receive. Open=" << MIsOpen();
	return false;
}
size_t const& IMPL_CLASS::MReserve() const
{
	return FReserv;
}
NSHARE::CText const& IMPL_CLASS::MSharedName() const
{
	return FName;
}
bool IMPL_CLASS::MIsConnected() const
{
	return FIsConnected;
}
void IMPL_CLASS::MEventDataConfiramtion(shared_identify_t const& aId,
		unsigned aCode)
{
	CSharedMemoryBase::CImpl::MSendDataConfirmation(FMyInfo->FInfo.FId, FServerSignalEvent, aCode);
}
void IMPL_CLASS::MEventKeepAliveRequest(shared_identify_t const& aId,
		IAllocater::offset_pointer_t)
{
	CSharedMemoryBase::CImpl::MSendKeapAliveAnswer(FMyInfo->FInfo.FId,FServerSignalEvent, 0);
}
CSharedMemoryClient::eSendState IMPL_CLASS::MSend(NSHARE::CBuffer & aVal, bool aBlock, unsigned aFlags)
{
	if (aVal.empty())
	{
		LOG(ERROR)<<"Send empty buffer";
		return E_ERROR;
	}
	if(!MIsConnected())
	{
		LOG(ERROR)<<"The client is not connected.";
		return E_ERROR;
	}
//	CRAII<CMutex> _block(FSendMutex);

	VLOG(2)<<"Sending "<<aVal.size()<<" bytes to "<<FServerInfo->FInfo.FId.MGetId();
	eSendState _state= CSharedMemoryBase::CImpl::MSend(FMyInfo->FInfo.FId,FServerSignalEvent,aVal,aBlock,aFlags);
	LOG_IF(INFO,_state==E_SENDED)<<"Send "<<aVal.size()<<" bytes to "<<FServerInfo->FInfo.FId.MGetId();

	LOG_IF(ERROR,_state!=E_SENDED)<<"Cannot send "<<aVal.size()<<" bytes to "<<FServerInfo->FInfo.FId.MGetId()<<" as "<<_state;
	return _state;
}
shared_identify_t IMPL_CLASS::MIdentifier() const
{
	CHECK_NOTNULL(FMyInfo);
	return FMyInfo->FInfo.FId.MGetId();
}
shared_identify_t IMPL_CLASS::MServerIdentifier() const
{
	CHECK_NOTNULL(FServerInfo);
	return FServerInfo->FInfo.FId.MGetId();
}
bool IMPL_CLASS::MIsOpen() const
{
	return FIsOpened;
}
size_t IMPL_CLASS::MGetSize() const
{
	return FSharedMemory.MGetSize();
}
size_t IMPL_CLASS::MAvailable() const
{
	return MDataAvailable();
}
std::ostream& IMPL_CLASS::MPrint(std::ostream& aStream) const
{
	aStream << "The SM client is ";
	if (!MIsOpen())
	{
		return aStream << "closed.";
	}
	else
	{
		aStream << "opened.";
	}

	aStream << "Name:" << MSharedName() << " Size:" << MGetSize() << " bytes.";

	if (MIsConnected())
	{
		aStream <<"Connected.";
	}
	else
	{
		aStream << "Disconnected.";
	}
	return aStream;
}
void IMPL_CLASS::MSerialize(NSHARE::CConfig& aConf) const
{
	aConf.MAdd("name",MSharedName());
	aConf.MAdd("size",MGetSize());
	aConf.MAdd("con",MIsConnected());
	aConf.MAdd("res",FReserv);
	if(MIsConnected())
	{
		aConf.MAdd(MIdentifier().MSerialize());
		FServerSignalEvent.MSerialize(aConf);
	}
	MSerializeImpl(aConf);
}}

