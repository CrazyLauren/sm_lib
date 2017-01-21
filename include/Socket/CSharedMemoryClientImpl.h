/*
 * CSharedMemoryClientImpl.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 23.06.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CSHAREDMEMORYCLIENTIMPL_H_
#define CSHAREDMEMORYCLIENTIMPL_H_

#include <Socket/CSharedMemoryBaseImpl.h>
#include <Socket/CSharedMemoryClient.h>
namespace NSHARE
{
//todo receive and disconnect
class CSharedMemoryClient::CImpl: public CSharedMemoryBase::CImpl
{
public:

	//The argument of event is  "CText"

	CImpl(CSharedMemoryClient& aThis,NSHARE::CText const& aName = "",size_t aReserv=0);
	virtual ~CImpl();

	bool MOpen();
	bool MOpen(NSHARE::CText const& aName,size_t aReserv);
	bool MConnect(double aTime = 2.0);
	bool MClose();

	NSHARE::CText const& MSharedName() const;
	size_t const& MReserve() const;
	shared_identify_t MIdentifier() const;
	shared_identify_t MServerIdentifier() const;

	eSendState MSend(NSHARE::CBuffer& aVal,bool aBlock=false, unsigned aFlags=0);
	bool MIsOpen() const;
	bool MReOpen();//-
	bool MIsConnected() const;

	bool MReceiveData(NSHARE::CBuffer& aTo,shared_identify_t* aFrom=NULL,double aTime=-1,unsigned*aFlags=NULL);

	size_t MGetSize() const;//fixme what is it?
	std::ostream & MPrint(std::ostream & aStream) const;
	void MSerialize(NSHARE::CConfig&) const;
	size_t MAvailable() const;
private:

	bool MOpenServer(void* _p);
	void MInvokeEvent(event_info_t* _info);
	void MCreateClient(IAllocater* _alloc,int aUserId=-1);
	void MDisconnect();
	void MEventConnected(shared_identify_t const& aId,IAllocater::offset_pointer_t);
	void MEventDisconnected(shared_identify_t const& aId,IAllocater::offset_pointer_t);
	void MEventDataConfiramtion(shared_identify_t const& aId,unsigned);

	void MEventKeepAliveRequest(shared_identify_t const& aId,
			IAllocater::offset_pointer_t);
	CSharedMemoryClient& FThis;
	client_info_t* FMyInfo;
	NSHARE::CText FName;
	size_t FReserv;
	volatile bool FIsConnected;
	bool FIsOpened;
	mutable event_cv_t FServerSignalEvent;
	NSHARE::CMutex FSendMutex;
	NSHARE::CMutex FConnectMutex;



};
} /* namespace NSHARE */
#endif /* CSHAREDMEMORYCLIENTIMPL_H_ */
