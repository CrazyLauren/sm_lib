/*
 * CSharedMemoryBaseImpl.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 11.05.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CSHAREDMEMORYBASEIMPL_H_
#define CSHAREDMEMORYBASEIMPL_H_

#include <UType/CSharedMemory.h>
#include <UType/CIPCSignalEvent.h>
#include <boost/circular_buffer.hpp>
namespace NSHARE
{
struct server_info_t;
struct event_fifo_t;
struct client_info_t;
struct event_info_t;
struct shared_port_t;
struct shared_info_t;

class CSharedMemoryBase::CImpl:public NSHARE::CIntrusived
{
public:

	struct recv_t
	{
		NSHARE::CBuffer FData;
		shared_identify_t FFrom;
		unsigned FFlags;
	};
	struct event_cv_t
	{
		event_cv_t();
		void MCleanupLock() const;
		bool MSafetyLock() const;
		bool MLock() const;
		bool MUnlock() const;

		mutable NSHARE::CIPCSignalEvent FSignalEvent;
		mutable NSHARE::CIPCSem FSignalSem;
		shared_info_t* FEvents;
		//time_t FReadTime;
		//double FLastConnectionTime;
		void  MSerialize(CConfig& aTo) const;
	};

	CImpl();

	CBuffer MAllocate(size_t aSize) const;
	IAllocater* MGetAllocator() const;


	void MCleanupLock() const;
	bool MSafetyLock()const;
	bool MLock() const;
	bool MUnlock() const;


	bool MWaitForEvent(event_cv_t& aFrom,event_info_t* aVal, double const aTime);
	bool MCreateEventHandler(event_cv_t & aEvent);
	bool MCreateSignalEvent(event_cv_t &);
	bool MInitSignalEvent(event_cv_t &, shared_info_t *);
	bool MInvokeEventTo(event_cv_t & aEv, event_info_t* _info) const;
	void MStopEventHandlerForce();
	void MUnlockReceivingForce();


	virtual void MEventConnect(client_info_t* aClient)
	{
		;
	}
	virtual void MEventDisconnect(client_info_t* aClient)
	{
		;
	}
	virtual void MEventConnected(shared_identify_t const& aId,
			IAllocater::offset_pointer_t)
	{
		;
	}
	virtual void MEventDisconnected(shared_identify_t const& aId,
			IAllocater::offset_pointer_t)
	{
		;
	}
	virtual void MEventKeepAliveAnswer(shared_identify_t const& aId,
			IAllocater::offset_pointer_t,unsigned)
	{
		;
	}
	virtual void MEventDataConfiramtion(shared_identify_t const& aId,unsigned)=0;
	virtual void MEventKeepAliveRequest(shared_identify_t const& aId,
			IAllocater::offset_pointer_t)=0;


	bool MCreateSharedSem(server_info_t *,NSHARE::CText const& aPostrix=NSHARE::CText());
	bool MInitSharedSem(server_info_t* _info);


	bool MCheckConnection(shared_port_t const& aFrom,	event_cv_t &aEvent);

	bool MSendKeapAliveRequest(const shared_port_t& aFrom,event_cv_t& aEvent) const;
	bool MSendKeapAliveAnswer(shared_port_t const& aFrom,event_cv_t& aEvent,unsigned aAnswer) const;
	bool MSendDataConfirmation(shared_port_t const& aFrom,event_cv_t& aEvent,unsigned aCode) const;

	void MSetOverload(bool Overload);
	bool MOverload() const;

	bool MFreeBase();

	CSharedMemoryBase::eSendState MSend(shared_port_t const& aFrom,
			event_cv_t &aEvent, NSHARE::CBuffer& aVal, bool aBlock,
			unsigned aFlags);


	bool MReceiveData(recv_t& aTo, double aTime);

		std::list<recv_t> MCleanUp(std::list<recv_t>&,event_fifo_t* aEv);
	bool MRemoveEvent(event_info_t const* aEvent,event_cv_t& aEv);
	size_t MDataAvailable() const;

	void MSetOption(CSharedMemoryBase::eSettings, unsigned aVal);
	unsigned MGetOption(CSharedMemoryBase::eSettings) const;
	void MSerializeImpl(NSHARE::CConfig& aConf) const;


	//fields are used for receive data

	bool FEventDone;
	event_cv_t FEv;

	NSHARE::CThread FSignalHandler;
	server_info_t* FServerInfo;
	CSharedMemory FSharedMemory;
	mutable NSHARE::CIPCSem FSharedSem;

private:
	typedef std::deque<recv_t> buffers_t;//todo replace to circular buffer with dynamic expending
	//typedef boost::circular_buffer<recv_t> buffers_t;

	struct check_connection_t
	{
		shared_identify_t FTo;
	};
	void MEventDataConfiramtionImpl(shared_identify_t const& aId, unsigned);
	void MEventKeepAliveAnswerImpl(shared_identify_t const& aId,
			IAllocater::offset_pointer_t,unsigned);
	void MEventKeepAliveRequestImpl(shared_identify_t const& aId,
			IAllocater::offset_pointer_t);
	void MEventHandler();
	void MEventHandler(event_info_t*);
	void MGetData(recv_t& _result);
	void MSingleConvar(unsigned );
	bool MWaitConvar(unsigned , double aTime);
	void MGetValidBuffer(IAllocater* const aAlloc,CBuffer&);
	bool  MWaitForSend(const event_info_t& _info, event_cv_t& aEvent);
	static int sMEventHandler(void*, void*, void* pData);
	void MReceiveData(event_info_t* aEv);

	bool FCondVars[event_info_t::MAX_EVENT_VALUE];
	mutable NSHARE::CMutex FBufMutex;
	NSHARE::CMutex FCondMutex;
	NSHARE::CCondvar FCond;
	size_t FCurentBufSize;
	buffers_t FBuffers;
	NSHARE::smart_field_t<check_connection_t> FCheckConnect;
	std::set<unsigned> FDataConfiramtion;
	unsigned  FSettings[CSharedMemoryBase::MAX_SETTING_VALUE];
	mutable unsigned FCounter;
	mutable unsigned FBlockCode;
};
template<> class SHARE_EXPORT CRAII<CSharedMemoryBase::CImpl> : public CDenyCopying
{
public:
	explicit CRAII(CSharedMemoryBase::CImpl const& aSem) :
	FSem(aSem)
	{
		MLock();
	}
	~CRAII()
	{
		MUnlock();
	}
	inline void MUnlock()
	{
		if (FIsLock)
		FSem.MUnlock();
		FIsLock = false;
	}
private:
	inline void MLock()
	{
		FSem.MLock();
		FIsLock =true;
	}
	CSharedMemoryBase::CImpl const &FSem;
	volatile bool FIsLock;
};
template<> class SHARE_EXPORT CRAII<CSharedMemoryBase::CImpl::event_cv_t> : public CDenyCopying
{
public:
	explicit CRAII(CSharedMemoryBase::CImpl::event_cv_t const& aSem) :
	FSem(aSem)
	{
		MLock();
	}
	~CRAII()
	{
		MUnlock();
	}
	inline void MUnlock()
	{
		if (FIsLock)
		FSem.MUnlock();
		FIsLock = false;
	}
private:
	inline void MLock()
	{
		FSem.MLock();
		FIsLock =true;
	}
	CSharedMemoryBase::CImpl::event_cv_t const &FSem;
	volatile bool FIsLock;
};
}
#endif /* CSHAREDMEMORYBASEIMPL_H_ */
