/*
 * CSharedMemoryServerImpl.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 23.06.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CSHAREDMEMORYSERVERIMPL_H_
#define CSHAREDMEMORYSERVERIMPL_H_

//todo проверить перекидование buffer из удаляемого процесса в другой процесс
//todo сейчас пока не возникает ошибки в процесе отправки WD не запускается
//что не верно. Нужно добавить KeapAlive c периодом 100mc и менее
#include <Socket/CSharedMemoryServer.h>
#include <Socket/CSharedMemoryBaseImpl.h>
namespace NSHARE
{
class CSharedAllocater;
class CSharedMemoryServer::CImpl: public CSharedMemoryBase::CImpl
{
public:
	CImpl(CSharedMemoryServer& aThis,NSHARE::CText const& aName , size_t aSize,size_t aReserv);
	virtual ~CImpl();
	bool MOpen();
	bool MOpen(NSHARE::CText const& aName, size_t aSize,size_t aReserv);
	bool MIsOpen() const;
	bool MReOpen();//-

	bool MClose();
	bool MClose(shared_identify_t const&);
	bool MClose(int aUserId);//if aUserId is negative, close all clients
	CSharedMemoryBase::eSendState MSend(shared_identify_t const&,NSHARE::CBuffer & aVal,bool aBlock,unsigned aFlags);
	unsigned MSend(int aUserId,NSHARE::CBuffer & aVal,bool aBlock,unsigned aFlags);//if aUserId is negative, The is sent to all clients

	bool  MReceiveData(NSHARE::CBuffer &,shared_identify_t* aFrom,double aTime,unsigned * aFlags);

	//fixme todo my name as from_t
	NSHARE::CText const& MSharedName() const;
	size_t MGetSize() const;

	shared_identify_t MIdentifier() const;

	std::ostream& MPrint(std::ostream& aStream) const;
	size_t MAvailable() const;

	bool MIsClient(shared_identify_t const&) const;
	bool MIsClients() const;
	bool MIsConnected() const;
	void MGetClients(client_array_t&)const;
	bool MIsOverload(shared_identify_t const& aFor) const;
	void MSerialize(NSHARE::CConfig&) const;
	void MSettings(NSHARE::CConfig& aConf) const;
protected:
private:
	struct CClient;
	//typedef NSHARE::intrusive_ptr<CClient> smart_client_t;
	typedef NSHARE::intrusive_ptr<CClient> smart_client_t;
	typedef std::map<shared_identify_t, smart_client_t> clients_t;
	typedef NSHARE::CSafeData<clients_t> safe_clients_t;

	static int sMServerCleaner(void*, void*, void* pData);
	static int sMCleanUpMemory(CSharedAllocator* WHO,
				void* WHAT, void* YOU_DATA);
	void MEventConnect(client_info_t* aClient);
	void MEventDisconnect(client_info_t* aClient);
	bool MEventDisconnectImpl(client_info_t* aClient,bool aInvokeDisconnect=true);
	bool MCreateServer(void* _p,size_t const _server_size);
	bool MValidateClient(IAllocater* const _alocater,
			client_info_t* aClient) const;
	//void MEraseBlock(uint32_t aPid,std::list<recv_t>& aBuffers);
	void MInsertClientIntoList(IAllocater* const _alocater,
			client_info_t* aClient);
	void MEraseClientFromList(IAllocater* const _alocater,
			client_info_t* aClient);
	smart_client_t MAddClient(client_info_t* aClient);
	void MEventKeepAliveRequest(shared_identify_t const& aId,
				IAllocater::offset_pointer_t);
	void MEventDataConfiramtion(shared_identify_t const& aId,unsigned);

	void MRemoveClient(clients_t::iterator _it,std::list<recv_t> &_rval);
	smart_client_t MGetClientImpl(const shared_identify_t&) const;
	client_info_t* MGetClientImpl(unsigned aPid) const;

	safe_clients_t FClients;
	NSHARE::CMutex FSmartMutex;//fixme read write lock
	NSHARE::CThread FCleanUpThread;
	bool FIsOpened;
	NSHARE::CText FName;
	size_t FSize;
	size_t FReserv;
	CSharedMemoryServer& FThis;

	friend struct CClient;
};
}
#endif /* CSHAREDMEMORYSERVERIMPL_H_ */
