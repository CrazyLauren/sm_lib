/*
 * CSharedMemoryServer.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 28.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CSHAREDMEMORYSERVER_H_
#define CSHAREDMEMORYSERVER_H_

/*
 *	chanelog
 *
 *	Версия 0.1 (22.06.2016)
 */

#include <Socket/CSharedMemoryBase.h>
#ifndef SM_SOCKET_EXIST
#	define SM_SOCKET_EXIST
#endif
namespace NSHARE
{
class SHARE_EXPORT CSharedMemoryServer:public CSharedMemoryBase,NSHARE::CDenyCopying
{
public:
	static const CText NAME;
	static version_t sMGetVersion();

	typedef std::vector<shared_identify_t> client_array_t;
	CSharedMemoryServer(NSHARE::CText const& aName = "", size_t aSize=1024*1024,size_t aReserv=0);
	CSharedMemoryServer(NSHARE::CConfig const& aConf);
	virtual ~CSharedMemoryServer();

	bool MOpen();
	bool MOpen(NSHARE::CText const& aName, size_t aSize,size_t aReserv=0);
	bool MIsOpen() const;
	bool MReOpen();//-

	void MClose();
	bool MClose(shared_identify_t const&);
	bool MClose(int aUserId);//if aUserId is negative, close all clients


	eSendState  MSend(shared_identify_t const&,NSHARE::CBuffer const& aVal,bool aBlock,unsigned aId);
	unsigned MSend(int aUserId,NSHARE::CBuffer const& aVal,bool aBlock,unsigned aId);//if aUserId is negative, The is sent to all clients
	sent_state_t MSend(void const* aData, std::size_t aSize,
			NSHARE::CConfig const& aTo);
	sent_state_t MSend(void const*  aData, std::size_t aSize);
	sent_state_t MSend(data_t const& aVal);
	sent_state_t MSend(data_t const& aVal, NSHARE::CConfig const& aTo);


	bool MReceiveData(NSHARE::CBuffer& aTo,shared_identify_t* aFrom=NULL,unsigned* aId=NULL,double aTime=-1);
	ssize_t MReceiveData(NSHARE::CBuffer *, float const aTime);
	ssize_t MReceiveData(data_t * aData, float const aTime,
			recvs_from_t *aFrom);

	NSHARE::CText const& MSharedName() const;
	size_t MGetSize() const;

	shared_identify_t MIdentifier() const;

	std::ostream& MPrint(std::ostream& aStream) const;
	size_t MAvailable() const;

	bool MIsClient(shared_identify_t const&) const;
	bool MIsClients() const;
	bool MIsConnected() const;
	client_array_t MGetClients()const;
	IAllocater* MGetAllocator() const;

	bool MIsOverload(shared_identify_t const& aFor) const;
	void MSetOption(eSettings, unsigned aVal);
	unsigned MGetOption(eSettings) const;

	static bool sMRemove(NSHARE::CText const& aName);
	NSHARE::CConfig MSerialize() const;
	NSHARE::CConfig MSettings(void) const;
private:
	class CImpl;
	NSHARE::intrusive_ptr<CImpl> FImpl;
};

} /* namespace NSHARE */
#endif /* CSHAREDMEMORYSERVER_H_ */
