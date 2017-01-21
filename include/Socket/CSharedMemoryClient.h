/*
 * CSharedMemoryClient.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 11.05.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CSHAREDMEMORYCLIENT_H_
#define CSHAREDMEMORYCLIENT_H_

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
class SHARE_EXPORT CSharedMemoryClient:public CSharedMemoryBase,NSHARE::CDenyCopying
{
public:
	static const NSHARE::CText NAME;
	static version_t sMGetVersion();

	CSharedMemoryClient(NSHARE::CText const& aName = "",size_t aReserv=0);
	CSharedMemoryClient(NSHARE::CConfig const& aConf);
	virtual ~CSharedMemoryClient();

	bool MOpen();
	bool MOpen(NSHARE::CText const& aName,size_t aReserv=0);
	bool MIsOpen() const;
	bool MReOpen();//-

	void MClose();

	bool MConnect(double aTime = 2.0);
	bool MIsConnected() const;

	NSHARE::CText const& MSharedName() const;
	shared_identify_t MIdentifier() const;
	shared_identify_t MServerIdentifier() const;

	sent_state_t MSend(data_t const& aVal);
	sent_state_t MSend(void const*  aData, std::size_t aSize);
	sent_state_t MSend(data_t const& aVal, NSHARE::CConfig const& aTo);
	eSendState MSend(NSHARE::CBuffer const& aVal,bool aBlock,unsigned aId=0);



	bool MReceiveData(NSHARE::CBuffer& aTo,shared_identify_t* aFrom=NULL,unsigned* aId=NULL,double aTime=-1);
	ssize_t MReceiveData(NSHARE::CBuffer *, float const aTime);

	size_t MGetSize() const;
	std::ostream & MPrint(std::ostream & aStream) const;
	NSHARE::CConfig MSerialize() const;
	NSHARE::CConfig MSettings(void) const;
	size_t MAvailable() const;
	IAllocater* MGetAllocator() const;
	void MSetOption(eSettings, unsigned aVal);
	unsigned MGetOption(eSettings) const;
	bool MOverload() const;
private:
	class CImpl;
	NSHARE::intrusive_ptr<CImpl> FImpl;
};
} /* namespace NSHARE */
#endif /* CSHAREDMEMORYCLIENT_H_ */
