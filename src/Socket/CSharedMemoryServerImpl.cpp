/*
 * CSharedMemoryServerImpl.cpp
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
#include <tasks.h>
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

namespace
{
static uint16_t g_client_numerator = 0;
}

struct IMPL_CLASS::CClient: NSHARE::CIntrusived
{
	CClient(CImpl* const aThis, client_info_t* aClient) :
	FThis(aThis), FClient(aClient)
	{
		FIsConnected=false;
	}
	bool MInit()
	{
		return FThis->MInitSignalEvent(FEvent, &FClient->FInfo);
	}
	~CClient()
	{
		VLOG(2) << "Client destroyed.";
		NSHARE::CRAII<CMutex> _block(FLock);
#ifdef _WIN32
		FEvent.FSignalEvent.MFree();
#else
#	warning todo maybe freeing cleanup
#endif
	}
	void MEventDisconnected()
	{
		VLOG(2) << "Invoke event disconnected for " << FClient->FInfo.FId;
		if (!FIsConnected)
		{
			LOG(ERROR)<<"It's not connected";
			return;
		}
		NSHARE::CRAII<CMutex> _block(FLock);

		event_info_t _info;
		_info.FEventType = event_info_t::E_DISCONECTED;
		_info.FIdFrom = FThis->FServerInfo->FInfo.FId; //
		FThis->MInvokeEventTo(FEvent, &_info);
	}
	void MEventConnected()
	{
		VLOG(2) << "Invoke event connected for " << FClient->FInfo.FId;
		NSHARE::CRAII<CMutex> _block(FLock);
		FIsConnected=true;

		event_info_t _info;
		_info.FEventType = event_info_t::E_CONNECTED;
		_info.FIdFrom = FThis->FServerInfo->FInfo.FId;
		FThis->MInvokeEventTo(FEvent, &_info);
	}
	inline shared_identify_t MGetId() const
	{
		CHECK_NOTNULL(FClient);
		return FClient->MGetId();
	}
	void MSendKeapAliveAnswer() const
	{
		if (!FIsConnected)
		{
			LOG(ERROR)<<"It's not connected";
			return;
		}
		FThis->CSharedMemoryBase::CImpl::MSendKeapAliveAnswer(
				FThis->FServerInfo->FInfo.FId, FEvent,0);
	}
	void MEventDataConfiramtion(unsigned aCode) const
	{
		FThis->CSharedMemoryBase::CImpl::MSendDataConfirmation(FThis->FServerInfo->FInfo.FId, FEvent,aCode);
	}
	eSendState MSend(NSHARE::CBuffer & aVal,bool aBlock,unsigned aFlags) const
	{
		if (aVal.empty())
		{
			LOG(ERROR)<<"Send empty buffer to "<<FClient->FInfo.FId.MGetId();
			return E_ERROR;
		}
		if (!FIsConnected)
		{
			LOG(ERROR)<<"It's not connected";
			return E_ERROR;
		}
		NSHARE::CRAII<CMutex> _block(FLock);
		VLOG(2)<<"Send buffer to "<<FClient->FInfo.FId.MGetId();
		return FThis->CSharedMemoryBase::CImpl::MSend(FThis->FServerInfo->FInfo.FId,FEvent,aVal,aBlock,aFlags);
	}
	bool MIsOverload() const
	{
		return FEvent.FEvents->FFifo.MOverload();
	}
	void MSerialize(CConfig& aTo) const
	{
		aTo.MAdd("con",FIsConnected);
		if(FIsConnected)
		{
			FEvent.MSerialize(aTo);
		}
	}
	bool FIsConnected;
	CImpl* const FThis;
	client_info_t* const FClient;
	mutable event_cv_t FEvent;
	mutable NSHARE::CMutex FLock;
};

CSharedMemoryServer::CImpl::CImpl(CSharedMemoryServer& aThis,
		NSHARE::CText const& aName, size_t aSize, size_t aReserv) :
		FIsOpened(false), FName(aName), FSize(aSize), FReserv(aReserv), FThis(
				aThis)
{
	FCleanUpThread += NSHARE::CB_t(sMServerCleaner, this);
//	MSetOption(CSharedMemoryBase::SEND_BUFFER_SIZE,
//			MGetOption(CSharedMemoryBase::SEND_BUFFER_SIZE) * 2); //default value is 2 times longer
	if (!aName.empty())
		MOpen();
}

IMPL_CLASS ::~CImpl()
{
	MClose();
}
bool IMPL_CLASS::MIsOpen() const
{
	return FIsOpened;
}
bool IMPL_CLASS::MClose()
{
	if (!MIsOpen())
	{
		VLOG(2) << "The shared server is not opened.";
		return false;
	}
	FIsOpened=false;
	VLOG(2) << "Close server " << FServerInfo->FInfo.FId;

	client_array_t _clients;
	MGetClients(_clients);
	for(client_array_t::iterator _it=_clients.begin();_it!=_clients.end();++_it) MClose(*_it);

	VLOG(2) << "Deallocate memory";
	deallocate_object(FSharedMemory.MGetAllocator(), FServerInfo);
	FServerInfo=NULL;
	MFreeBase();

	FSharedMemory.MFinishCleanUp();
	return true;
}
bool IMPL_CLASS::MClose(shared_identify_t const& aId)
{
	VLOG(2)<<"Close "<<aId;
	smart_client_t _client;
	{
		NSHARE::CRAII<CMutex> _block(FSmartMutex);
		_client = MGetClientImpl(aId);
	}
	if(!_client.MIs())
	{
		VLOG(2)<<"The client "<<aId<<" is not exist.";
		return false;
	}
	bool _rval=MEventDisconnectImpl(_client->FClient);
	{
		NSHARE::CRAII<CMutex> _block(FSmartMutex);
		_client=smart_client_t();
	}
	FSharedMemory.MCleanUp();
	return _rval;
}
bool IMPL_CLASS::MClose(int aUserId)
{
	unsigned _count=0;
	smart_client_t _client; //fixme std::vector
	do
	{
		VLOG(2)<<"Remove "<<aUserId;
		{
			safe_clients_t::RAccess<> const _clients = FClients.MGetRAccess();
			clients_t::const_iterator _it = _clients->begin();
			for (; _it != _clients->end(); ++_it)
			{
				if (aUserId < 0 || _it->first.FUserId == aUserId)
				{
					{
						NSHARE::CRAII<CMutex> _block(FSmartMutex);
						_client = _it->second;
					}
					break;
				}
			}
		}
		if (_client.MIs())
		{
			++_count;
			MEventDisconnectImpl(_client->FClient);
			{
				NSHARE::CRAII<CMutex> _block(FSmartMutex);
				_client = smart_client_t();
			}
			continue;
		}
		else
		break;
	}while (1);

	return _count>0;
}
void IMPL_CLASS::MEventConnect(client_info_t* aClient)
{
	IAllocater* const _alocater = FSharedMemory.MGetAllocator();

	if (!MValidateClient(_alocater, aClient))
	{
		LOG(DFATAL)<<"Invalid crc";
		return;
	}
	DCHECK_EQ(aClient->FInfo.FId.FUniqueID, 0);
	aClient->FInfo.FId.FUniqueID = ++g_client_numerator;
	smart_client_t _client = MAddClient(aClient);
	if (_client.MIs())
	{
		{
			CRAII<CSharedMemoryBase::CImpl> _block(*this);

			VLOG(2) << "Event connect for " << aClient->FInfo.FId;

			VLOG(2) << "Unique ID=" << aClient->FInfo.FId.FUniqueID;

			MInsertClientIntoList(_alocater, aClient);
		}
		_client->MEventConnected();
		FThis.MCallEventConnected(aClient->MGetId());
	}
}
void IMPL_CLASS::MEventDisconnect(client_info_t* aClient)
{
	MEventDisconnectImpl(aClient);
}
bool IMPL_CLASS::MEventDisconnectImpl(client_info_t* aClient,bool aInvokeDisconnect)
{
	IAllocater* const _alocater = FSharedMemory.MGetAllocator();
	FThis.MCallEventDisconnected(aClient->MGetId());
	shared_identify_t _id;
	smart_client_t _client;
	{
		CRAII<CSharedMemoryBase::CImpl> _block2(*this);

		if (!MValidateClient(_alocater, aClient))
		{
			LOG(DFATAL)<<"Invalid crc";
			return false;
		}

		VLOG(2) << "Event disconnect for " << aClient->FInfo.FId;
		DCHECK_NE(aClient->FInfo.FId.FUniqueID, 0);

		_id=aClient->MGetId();
		//Clean up the event in order to avoid memory leak
		std::list<recv_t> _recv;
		MCleanUp(_recv, &aClient->FInfo.FFifo);

		aClient->FInfo.FId.FUniqueID = 0;
		MEraseClientFromList(_alocater, aClient);

		VLOG(2) << "CLient " << aClient->FInfo.FId << " erased from list ";

		{
			safe_clients_t::WAccess<> _clients = FClients.MGetWAccess();
			clients_t::iterator _it = _clients->find(_id);
			if (_it == _clients->end())
			{
				LOG(DFATAL)<<_id<<" is not exist in client list.";
				return false;
			}
			{
				NSHARE::CRAII<CMutex> _block(FSmartMutex);
				_client=_it->second;
			}
			_clients->erase(_it);
		}

	}
	if(aInvokeDisconnect) _client->MEventDisconnected();
	{
		NSHARE::CRAII<CMutex> _block(FSmartMutex);
		_client=smart_client_t();
	}

	return true;
}
IMPL_CLASS::smart_client_t IMPL_CLASS::MAddClient(
		client_info_t* aClient)
{
	smart_client_t _client(new CClient(this, aClient));
	if(! _client->MInit())
	return smart_client_t();

	safe_clients_t::WAccess<> _clients = FClients.MGetWAccess();

	LOG_IF(DFATAL,_clients->find(aClient->MGetId())!=_clients->end())
	<< "The process "
	<< aClient->FInfo.FId
	<< " is exist.";

	{
		NSHARE::CRAII<CMutex> _block(FSmartMutex);
		_clients.MGet()[_client->MGetId()] = _client;
	}
	return _client;
}

void IMPL_CLASS::MInsertClientIntoList(IAllocater* const aAllocator,
		client_info_t* aClient)
{
	client_info_t* _last = FServerInfo->MFirstClientNode(aAllocator);
	bool _is_exist = false;
	VLOG(2) << aClient->FInfo.FId << " is inserted into list." << " #";

	for (; _last;)
	{
		VLOG(2) << "Next " << _last->MGetId();
		if (_last->MGetId() == aClient->MGetId())
		{
			VLOG(2)<<_last->MGetId()<<" == "<<aClient->MGetId();
			_is_exist = true;
		}

		client_info_t* _next = _last->MNext(aAllocator);
		if (_next)
		{
			_last = _next;
		}
		else break;
	};
	LOG_IF(FATAL,_is_exist) << "The process " << aClient->MGetId()
	<< " has been connected.";
	if (!_last)
	{
		VLOG(2) << "It's the first.";
		FServerInfo->FOffsetToClient = aAllocator->MOffset(aClient);
	}
	else
	{
		VLOG(2) << "Insert " << aClient->FInfo.FId << " into list after "<< _last->FInfo.FId;
		_last->FNext = aAllocator->MOffset(aClient);
	}
}
void IMPL_CLASS::MEraseClientFromList(IAllocater* const aAllocator,
		client_info_t* aClient)
{
	//looking for the client place in the client list
	client_info_t* _prev = FServerInfo->MFirstClientNode(aAllocator);
	CHECK(aClient);
	if (!_prev)
	{
		LOG(DFATAL)<<aClient->FInfo.FId<<" is not exist.";
		return;
	}
	if (_prev == aClient)
	_prev = NULL;

	// Iterate through the list until the previous client is not founded
	VLOG(2) << "Client " << aClient->FInfo.FId << " is looked for";
	for (; _prev;)
	{
		client_info_t* _next = _prev->MNext(aAllocator);
		if (_next && _next != aClient)
		{
			VLOG(2) << "Next " << aClient->FInfo.FId;
			_prev = _next;
		}
		else if (_next)
		{
			CHECK_EQ(_next->FInfo.FId, aClient->FInfo.FId);
			VLOG(2) << "Client " << aClient->FInfo.FId << " is founded";
			break;
		}
		else
		{
			LOG(DFATAL)<<aClient->FInfo.FId<<" is not exist.";
			return;
		}
	};
	VLOG_IF(2,!_prev) << "It's the first.";

	//if _prev is null then the aClient has not previous client.
	//it means aClient is to be the first.
	if (!_prev)
	FServerInfo->FOffsetToClient = aClient->FNext;
	else
	_prev->FNext = aClient->FNext;
}
bool IMPL_CLASS::MValidateClient(IAllocater* const _alocater,
		client_info_t* aClient) const
{
	return aClient->FInfo.FFifo.MCheckCrc();
}
bool IMPL_CLASS::MReOpen()
{
	MClose();
	return MOpen();
}
bool IMPL_CLASS::MOpen()
{
	VLOG(2) << "Open server for " << FName;
	CHECK(!FName.empty());
	CHECK_GT(FSize,0);
	CHECK(!FEv.FEvents);
	CHECK(!FServerInfo);
	bool _is = FSharedMemory.MOpenOrCreate(FName,FSize,FReserv);
	DCHECK(_is);
	if(!_is)
	{
		VLOG(2)<<"Cannot open SM "<<FName;
		MFreeBase();
		return false;
	}
	IAllocater* _alloc = FSharedMemory.MGetAllocator();
	CHECK_NOTNULL(_alloc);

	size_t const _server_size=get_server_fifo_size(MGetOption(CSharedMemoryBase::SEND_BUFFER_SIZE));

	//checking for the server has been run
	void* _p = FSharedMemory.MGetIfMalloced(0);
	if (_p)
	{
		server_info_t* _info = reinterpret_cast<server_info_t*>(_p);
		if(_info->MCheckCrc() && is_process_exist(_info->FInfo.FId.FPid))
		{
			LOG(ERROR) << "The SM server for " << FName << " has been opened already by "<<_info->FInfo.FId;
			MFreeBase();
			return false;
		}
		VLOG(2)<<"It's the old server";
	}


	_p = FSharedMemory.MMallocTo((uint32_t)_server_size, 0);
	DCHECK_NOTNULL(_p);
	if(!_p)
	{
		LOG(ERROR) << " Cannot allocate memory for SM server";
		MFreeBase();
		return false;
	}

	_is = MCreateServer(_p,_server_size);
	if (!_is)
	{
		_alloc->MDeallocate(_p,_server_size);
		MFreeBase();
		return false;
	}

	return _is;
}
bool IMPL_CLASS::MOpen(NSHARE::CText const& aName, size_t aSize,size_t aReserv)
{
	FSize=aSize;
	FName=aName;
	FReserv=aReserv;
	return MOpen();
}
bool IMPL_CLASS::MCreateServer(void* _p,size_t const _server_size)
{
	server_info_t* _info = new (_p) server_info_t(NSHARE::CThread::sMPid(),
			_server_size);

	bool _is = MCreateSharedSem(_info,"sv");
	if (!_is)
	return _is;
	FEv.FEvents = &_info->FInfo;
	FServerInfo = _info;
	_is = MCreateSignalEvent(FEv);
	if (!_is)
	{
		FServerInfo=NULL;
		return false;
	}

	_is = MCreateEventHandler(FEv);
	FIsOpened=true;
	FCleanUpThread.MCreate();
	_info->MFillCRC();
	return _is;
}
unsigned IMPL_CLASS::MSend(int aUserId, NSHARE::CBuffer & aVal,bool aBlock,unsigned aFlags)
{
	if (aVal.empty())
	{
		LOG(ERROR)<<"Send empty buffer to "<<aUserId;
		return 0;
	}
	VLOG_IF(1,aUserId>=0)<<"Send "<<aVal.size()<<" bytes to "<<aUserId;
	VLOG_IF(1,aUserId<0)<<"Send "<<aVal.size()<<" bytes to all";
	unsigned _count = 0;
	bool _is_error=false;
	{
		std::vector<smart_client_t> _s_clients;	//fixme to pair
		{
			safe_clients_t::RAccess<> const _clients = FClients.MGetRAccess();
			clients_t::const_iterator _it(_clients->begin()), _end(_clients->end());
			VLOG_IF(2,_it==_end)<<"There are not clients.";
			for (; _it != _end; ++_it)
			{
				VLOG(2)<<"Next "<<_it->first;
				if (aUserId < 0 || aUserId == _it->first.FUserId)
				{
					LOG(INFO)<<"Send to "<<aVal.size()<<" bytes to "<<(_it)->second->MGetId();
					NSHARE::CRAII<NSHARE::CMutex> _block(FSmartMutex);
					_s_clients.push_back(_it->second);
				}
			}
		}
		if(!_s_clients.empty())
		{
			std::vector<smart_client_t>::iterator _it=_s_clients.begin(), _end(_s_clients.end());
			for (; _it != _end; ++_it)
			{
				eSendState _state=(*_it)->MSend(aVal,aBlock,aFlags);

				switch(_state)
				{
					case E_SENDED:
					++_count;
					break;
					case E_ERROR:
					_is_error=true;
					break;
					case E_AGAIN:
					break;
					default:
					break;
				}
				{
					NSHARE::CRAII<NSHARE::CMutex> _block(FSmartMutex);
					*_it=smart_client_t();
				}
			}
		}
	}
	if(_is_error)
	{
		LOG(ERROR)<<"Send error ";
		FSharedMemory.MCleanUp();
	}
	return _count;
}
void IMPL_CLASS::MEventDataConfiramtion(shared_identify_t const& aId,
		unsigned aCode)
{
	smart_client_t _client;
	{
		safe_clients_t::RAccess<> _clients = FClients.MGetRAccess();

		clients_t::const_iterator _it = _clients->find(aId);
		if (_it != _clients->end())
		{
			NSHARE::CRAII<CMutex> _block(FSmartMutex);
			_client = _it->second;
		}
	}
	if (_client.MIs())
	{
		_client->MEventDataConfiramtion(aCode);
		{
			NSHARE::CRAII<CMutex> _block(FSmartMutex);
			_client = smart_client_t();
		}
	}
	else
	LOG(ERROR)<<aId<<" is not exist.";
}

void IMPL_CLASS::MEventKeepAliveRequest(shared_identify_t const& aId,
		IAllocater::offset_pointer_t)
{
	smart_client_t _client;
	{
		safe_clients_t::RAccess<> _clients=FClients.MGetRAccess();

		clients_t::const_iterator _it = _clients->find(aId);
		if (_it != _clients->end())
		{
			NSHARE::CRAII<CMutex> _block(FSmartMutex);
			_client=_it->second;
		}
	}
	LOG_IF(ERROR,!_client.MIs())<<aId<<" is not exist.";
	if (_client.MIs())
	{
		_client->MSendKeapAliveAnswer();
		{
			NSHARE::CRAII<CMutex> _block(FSmartMutex);
			_client=smart_client_t();
		}
	}
}

CSharedMemoryBase::eSendState IMPL_CLASS::MSend(shared_identify_t const& aTo,
		NSHARE::CBuffer & aVal,bool aBlock,unsigned aFlags)
{
	if (aVal.empty())
	{
		LOG(ERROR)<<"Send empty buffer to "<<aTo;
		return E_ERROR;
	}
	VLOG(1)<<"Send "<<aVal.size()<<" bytes to "<<aTo;
	eSendState _state=E_ERROR;
	{
		smart_client_t _client=MGetClientImpl(aTo);
		if (!_client.MIs())
		{
			LOG(ERROR)<<aTo<<" is not exist in client list.";
			return E_ERROR;
		}
		_state= _client->MSend(aVal,aBlock,aFlags);
	}
	if(_state==E_ERROR)
	{
		LOG(ERROR)<<"Send error "<<_state;
		FSharedMemory.MCleanUp();
	}
	return _state;
}
IMPL_CLASS::smart_client_t IMPL_CLASS::MGetClientImpl(const shared_identify_t& aId) const
{
	VLOG(2)<<"Get client "<<aId;
	safe_clients_t::RAccess<> const _clients=FClients.MGetRAccess();
	clients_t::const_iterator _it = _clients->find(aId);
	if(_it==_clients->end())
	return smart_client_t();
	else
	return _it->second;
}
client_info_t* IMPL_CLASS::MGetClientImpl(unsigned aPid) const
{
	VLOG(2) << "Get client " << aPid;
	IAllocater* const _alocater = FSharedMemory.MGetAllocator();
	CHECK_NOTNULL(_alocater);

	client_info_t* _last = FServerInfo->MFirstClientNode(_alocater);
	for (; _last; _last = _last->MNext(_alocater))
	{
		VLOG(2) << "Next " << _last->MGetId();
		if (_last->FInfo.FId.FPid == aPid)
		{
			//	VLOG(2) << _last->MGetId() << " is founded by PID " << aPid;
			break;
		}
	};
	return _last;
}
bool IMPL_CLASS::MReceiveData(NSHARE::CBuffer& aTo,shared_identify_t* aFrom,
		double aTime,unsigned * aFlags)
{
	VLOG(2) << "The server starts to receive.";
	if (!MIsOpen())
	{
		VLOG(2) << "It's not opened.";
		return false;
	}
	VLOG(2) << "Connected already";
	//
	recv_t _result;
	if (!CSharedMemoryBase::CImpl::MReceiveData(_result, aTime))
	{
		VLOG(2) << "Cannot receive data.";
		return false;
	}
	_result.FData.MMoveTo(aTo);

	if (aFrom) *aFrom = _result.FFrom;
	if(aFlags) *aFlags= _result.FFlags;
	VLOG(2) << "End receive. Open=" << MIsOpen();

	return true;
}
NSHARE::CText const& IMPL_CLASS::MSharedName() const
{
	return FName;
}
size_t IMPL_CLASS::MGetSize() const
{
	return FSize;
}
shared_identify_t IMPL_CLASS::MIdentifier() const
{
	CHECK_NOTNULL(FServerInfo);
	return FServerInfo->FInfo.FId.MGetId();
}
bool IMPL_CLASS::MIsOverload(shared_identify_t const& aFor) const
{
	safe_clients_t::RAccess<> const _clients = FClients.MGetRAccess();
	clients_t::const_iterator _it = _clients->find(aFor);

	if(_it==_clients->end())
	return false;
	else
	return _it->second->MIsOverload();
}
void IMPL_CLASS::MGetClients(client_array_t& _array) const
{
	safe_clients_t::RAccess<> const _clients = FClients.MGetRAccess();
	clients_t::const_iterator _it(_clients->begin()),_it_end(_clients->end());
	for(;_it!=_it_end;++_it)
	{
		VLOG(2)<<"There is "<<_it->first;
		_array.push_back(_it->first);
	}
}
bool IMPL_CLASS::MIsClient(shared_identify_t const& aVal) const
{
	safe_clients_t::RAccess<> const _clients = FClients.MGetRAccess();
	return _clients->find(aVal)!=_clients->end();
}
bool IMPL_CLASS::MIsClients() const
{
	return !FClients.MGetRAccess()->empty();
}
bool IMPL_CLASS::MIsConnected() const
{
	return MIsClients();
}
size_t IMPL_CLASS::MAvailable() const
{
	return MDataAvailable();
}

int IMPL_CLASS::sMCleanUpMemory(CSharedAllocator* WHO, void* aWHAT,
		void* YOU_DATA)
{
	CHECK_NOTNULL(YOU_DATA);

	CImpl* _p=(CImpl*)YOU_DATA;

	CSharedAllocator::clean_up_resources_t* _res =
	(CSharedAllocator::clean_up_resources_t*) aWHAT;

	const unsigned _pid = NSHARE::CThread::sMPid();
	IAllocater* const _alocater = _p->FSharedMemory.MGetAllocator();
	CHECK_NOTNULL(_alocater);

	VLOG(2)<<"cleanup the mutex";
	_p->MCleanupLock();
	{
		safe_clients_t::WAccess<> _clients = _p->FClients.MGetWAccess();
		clients_t::iterator _it = _clients->begin();
		clients_t::iterator _it_end = _clients->end();
		for(;_it!=_it_end;++_it)
		{
			VLOG(2)<<"Try clean up "<<_it->first;
			_it->second->FEvent.MCleanupLock();
		}
	}
	VLOG(2)<<"Clean Up server";

	//The leaking Non-block resource is mean that the client program has been killed.
	//Thus The server has to disconnect the leaked client.
	//In case the leaking resource is a buffer The server checks number of holders.
	//If The holder is only one, The server resets the memory. Otherwise It has to
	//'move' the buffer to the current process to become its owner. Thus It will not deleted.
	//In the other case The leaking resource is ignored.
	CSharedAllocator::clean_up_resources_t::iterator _it = _res->begin();
	for(;_it != _res->end();++_it)
	{
		CSharedAllocator::clean_up_t & _val =*_it;
		if (!_val.FBlock.MIs())
		{
			VLOG(2)<<"Try Lock ";
			//CRAII<CSharedMemoryBase::CImpl> _block2(*_p);//can be dead lock
			VLOG(2) << "Clean UP PID " << _val.FPid;
			client_info_t* _info =_p->MGetClientImpl(_val.FPid);
			if(_info)
			{
				IAllocater* const _alocater = _p->FSharedMemory.MGetAllocator();
				_p->FThis.MCallEventDisconnected(_info->MGetId());

				{
					safe_clients_t::WAccess<> _clients = _p->FClients.MGetWAccess();
					_clients->erase(_info->MGetId());
				}
				//Clean up the event in order to avoid memory leak
				std::list<recv_t> _recv;
				_p->MCleanUp(_recv, &_info->FInfo.FFifo);

				_info->FInfo.FId.FUniqueID = 0;
				_p->MEraseClientFromList(_alocater, _info);

				VLOG(2) << "CLient " << _info->FInfo.FId << " erased from list ";

			}
		}
		else	//fixme logic buf. see CSharedAllocator
		{
			CSharedAllocator::clean_up_t::_erased_block_t const& _buf=_val.FBlock.MGetConst();
			CBuffer _reset(*_alocater, _buf.FOffset);
			if (_reset.empty() || _reset.capacity()>_buf.FSize||_reset.use_count()==0)
			{
				VLOG(2)<<_buf.FOffset<<" is not buffer.";
				_reset.refuse();
			}
			else
			{
				CHECK_LE(_reset.capacity(),_buf.FSize);
				unsigned const _count=_reset.use_count();
				VLOG(2)<<"Use count = "<<_count;

				//To avoid signsev, if The buffer is used by another process,
				//The  buffer offset will be moved to the current process.
				//Thus It will belong to the current process.
				if(_reset.MIsRestored()&& _count>=1)
				{
					VLOG(2)<<_buf.FOffset<<" is used by the other process. Relocate it to "<<_pid;
					_val.FPid=_pid;
				}
				else
				{
					VLOG(2)<<"Use count "<<_count<<" size="<<_reset.size()<<" offset="<<_reset.offset();
					//the memory will removed by the shared memory allocator automatically
				}
				_reset.refuse();
			}
		}
	}
	VLOG(2)<<"Clean Up server finished";
	return 0;
}
int IMPL_CLASS::sMServerCleaner(void*, void*, void* pData)
{
	CHECK_NOTNULL(pData);
	CImpl* _server=reinterpret_cast<CImpl*>(pData);
	for(;_server->MIsOpen();)
	{
		_server->FSharedMemory.MCleanUpResourceByWatchDog(sMCleanUpMemory,pData);
	}
	return 0;
}

std::ostream& IMPL_CLASS::MPrint(std::ostream& aStream) const
{
	aStream << "The SM is ";
	if (!MIsOpen())
	{
		return aStream << "closed.";
	}
	else
	{
		aStream<< "opened.";
	}
	aStream << "Name:" << MSharedName() << " Size:" << MGetSize() << " bytes.";
	client_array_t _clients;
	MGetClients(_clients);
	client_array_t::const_iterator _it(_clients.begin()), _it_end(
			_clients.end());
	if (!_clients.empty())
	{
		for (;;)
		{
			VLOG(2) << "Client " << *_it;
			aStream << *_it;
			if (++_it == _it_end)
			break;
			else
			aStream << ';';
		}
		aStream << '.';
	}
	else
	{
		aStream << "No clients connected.";
	}
	return aStream;
}
void IMPL_CLASS::MSettings(NSHARE::CConfig& aConf) const
{
	aConf.MAdd(SM_SIZE, FSize);
	aConf.MAdd(SM_NAME, FName);
	aConf.MAdd(SM_RESERV, FReserv);
}
void IMPL_CLASS::MSerialize(NSHARE::CConfig& aConf) const
{
	{
		safe_clients_t::RAccess<> const _clients = FClients.MGetRAccess();
		clients_t::const_iterator _it(_clients->begin()),_it_end(_clients->end());
		for (;_it!=_it_end;++_it)
		{
			NSHARE::CConfig _conf("cl");
			_conf.MAdd(_it->first.MSerialize());
			_it->second->MSerialize(_conf);
		}
	}
	aConf.MAdd("clup",FCleanUpThread.MSerialize());
	aConf.MAdd("size",FSize);
	aConf.MAdd("name",FName);
	aConf.MAdd("res",FReserv);
	MSerializeImpl(aConf);
}}

