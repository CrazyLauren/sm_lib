/*
 * CSharedMemoryBase.h
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 23.06.2016
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CSHAREDMEMORYBASE_H_
#define CSHAREDMEMORYBASE_H_
#include <Socket/ISocket.h>
#include <Socket/shared_identify.h>

namespace NSHARE
{
class SHARE_EXPORT CSharedMemoryBase:public ISocket,public NSHARE::CEvents<NSHARE::CText>
{
public:
	typedef NSHARE::CEvents<NSHARE::CText> events_t;

	enum eSettings
	{
		MAX_KEEP_ALIVE_TIME=0,//ms
		KEEP_ALIVE_REQUEST_TIME,//sec only
		RECV_BUFFER_SIZE,//Byte
		SEND_BUFFER_SIZE,//Number Of packets
		THREAD_PRIORITY,//see  CThread::eThreadPriority
		MAX_SETTING_VALUE//for internal use only
	};


	static const CText SM_NAME;
	static const CText SM_SIZE;
	static const CText SM_RESERV;
	static const CText SM_CLIENT;
	static const CText SM_SERVER;
	//arg is shared_identify_t from
	static events_t::key_t const EVENT_CONNECTED;
	static events_t::key_t const EVENT_DISCONNECTED;

	virtual IAllocater* MGetAllocator() const=0;
	CBuffer MAllocate(size_t aSize,int aBeginSize=-1,eAllocatorType =ALLOCATE_FROM_COMMON) const;

	class CImpl;
protected:
	void MCallEventConnected(shared_identify_t const& aPid);
	void MCallEventDisconnected(shared_identify_t const& aPid);
};

} /* namespace NSHARE */

namespace std
{
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::shared_identify_t const& aInfo)
{
	aStream << "PID:" << aInfo.FPid << ", Id=" << aInfo.FDescriptor << ", UserId="
			<< aInfo.FUserId;
	return aStream;
}
template<>
struct less<NSHARE::shared_identify_t> : public binary_function<
		NSHARE::shared_identify_t, NSHARE::shared_identify_t, bool>
{
	bool operator()(const NSHARE::shared_identify_t & __x,
			const NSHARE::shared_identify_t & __y) const
	{
		return __x.MGetId() < __y.MGetId();
	}
}
;
}
#endif /* CSHAREDMEMORYBASE_H_ */
