/*
 * CThreadWin32.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 10.02.2014
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#if   defined(_WIN32)
#include <deftype>
//#include <boost/thread/thread.hpp>
#include <uclock.h>
#include <UType/CThread.h>
#include <string>
#include <process.h>
#include <stdlib.h>
#include <winbase.h>

struct _thread_canceled_t{};
namespace NSHARE
{
struct CThread::CImpl
{
	typedef SECURITY_ATTRIBUTES attr_t;

	CImpl(CThread& aThis) :
			FThis(aThis)
	{
		FID=0;
		FPThread=INVALID_HANDLE_VALUE;
	}
	~CImpl()
	{

	}
	static unsigned WINAPI sMThreadFunc(void* p);

	inline void MStart(const param_t* aParam);
	void MWaitForCreated();
private:
	void MSetCpuNum();
	void MSetPriority();

	unsigned int   FID;
	HANDLE FPThread;
	CThread& FThis;
	NSHARE::CMutex FMutex;
	NSHARE::CCondvar FCond;
	friend class CThread;
};
void CThread::CImpl::MWaitForCreated()
{
	for (; !FThis.MIsRunning(); Sleep(1))//FIXME
		;
}
void CThread::CImpl::MSetCpuNum()
{
	if (sMNumberOfProcessor() == 1)
		return;

    if (!FThis.MIsRunning())
       return;
    if (FPThread == INVALID_HANDLE_VALUE)
       return ;
    if(FThis.FCPUNum<0)
    	return;

    DWORD affinityMask = 0x1 << FThis.FCPUNum;
	SetThreadAffinityMask(FPThread, affinityMask);
}
void CThread::CImpl::MSetPriority()
{
	int prio = THREAD_PRIORITY_NORMAL;
	switch (FThis.MGetPriority())
	{
	case CThread::THREAD_PRIORITY_MAX:
		prio = THREAD_PRIORITY_HIGHEST;
		break;
	case CThread::THREAD_PRIORITY_HIGH:
		 prio = THREAD_PRIORITY_ABOVE_NORMAL;
		break;
	case CThread::THREAD_PRIORITY_NOMINAL:
		prio = THREAD_PRIORITY_NORMAL;
		break;
	case CThread::THREAD_PRIORITY_LOW:
		prio = THREAD_PRIORITY_BELOW_NORMAL;
		break;
	case CThread::THREAD_PRIORITY_MIN:
		 prio = THREAD_PRIORITY_IDLE;
		break;
	default:
		prio = THREAD_PRIORITY_NORMAL;
		break;
	}
	SetThreadPriority(FPThread, prio);
}

inline void CThread::CImpl::MStart(const param_t* aP)
{
	FPThread = (HANDLE) _beginthreadex(NULL, 0, CThread::CImpl::sMThreadFunc,
			this, 0, &FID);

	if(FPThread != INVALID_HANDLE_VALUE)
		FThis.MSetRunnig(false);
	else
		ResumeThread(FPThread);
}

unsigned CThread::CImpl::sMThreadFunc(void* aData)
{
	CThread::CImpl* _pThis = static_cast<CThread::CImpl*>(aData);
	_pThis->MSetPriority();
	_pThis->MSetCpuNum();
	_pThis->FThis.MSetRunnig(true);
	try
	{
		_pThis->FThis.MRun();
	} catch (_thread_canceled_t const&)
	{
		_pThis->FThis.MCancelCleanUp();
	}
	catch (std::exception const& aExcept)
	{
		LOG(DFATAL) << "Unhandled exception."<< aExcept.what();
	}
	catch(...)
	{
		LOG(DFATAL)<<"Unknown unhandled exception.";
	}
	_pThis->FThis.MSetRunnig(false);
	_endthreadex(0);
	return 0;
}

CThread::CThread() :
		FImpl(new CImpl(*this))
{
	MInit();
}

CThread::CThread(const CB_t& aCB) :
		FImpl(new CImpl(*this))
{
	MInit();
	if (aCB.MIs())
		MAdd(aCB);
}
inline void CThread::MInit()
{
	FPriority = THREAD_PRIORITY_DEFAULT;
	FShed = FIFO;
	FCPUNum = -1;
	FIsDetached = false;
	MSetRunnig(false);

}
CThread::~CThread()
{
	if (MIsRunning())
	{
		std::cerr << "***Error*** Destructor. Thread still running."
				<< (*this) << std::endl;
		if (MCancel())
			MJoin();
		else
			MKill();
		MSetRunnig(false);
	}
	delete FImpl;
	FImpl = 0;
}

bool CThread::MCreate(const param_t* aParam)
{
	if (MIsRunning())
	{
		std::cerr << "***Error***. Create. Thread already running."
				<< (*this) << std::endl;
		MCancel();
	}
	FImpl->MStart(aParam);
	FImpl->MWaitForCreated();
	return MIsRunning();
}

bool CThread::MSetProcessor(unsigned int cpunum)
{
	if (cpunum > sMNumberOfProcessor() || MIsRunning())
	{
		std::cerr << "***Error***.Set processor error." << std::endl;
		return false;
	}

	FCPUNum = cpunum;
	return true;
}
bool CThread::MTestCancel()
{
	LOG_IF(DFATAL,!MIsRunning())<<"The thread is not running.";
	if (sMThreadId() != MThreadId())
	{
		std::cerr
				<< "***Error***. Test cancel. Current thread ID and thread ID not equal."
				<< std::endl;
		return false;
	}//TODO
	//if(WaitForSingleObject(pd->cancelEvent.get(),0) != WAIT_OBJECT_0) return true;
	return false;
}
bool CThread::MCancel()
{
	if(!MIsRunning())
		return false;
	HANDLE _tmp=FImpl->FPThread;
	FImpl->FPThread=INVALID_HANDLE_VALUE;
	bool _rval =CloseHandle(_tmp)!=FALSE;

//	if (_rval)
//		FIsRunning = false;
	return _rval;
}
void CThread::MDetach()
{
	FIsDetached=true;
}
bool CThread::MJoin(uint64_t aTime)
{
	CRAII<CMutex> _lock(FImpl->FMutex);
	if (!MIsRunning() ||FIsDetached)
		return false;
	FImpl->FCond.MTimedwait(&FImpl->FMutex);
	return true;
}

void CThread::MRun(void)
{
	LOG_IF(DFATAL,!MIsRunning())<<"The thread is not running.";
	if(MIsRunning())
		MCall(NULL);
	if (FImpl->FPThread != INVALID_HANDLE_VALUE)
	{
		HANDLE _tmp=FImpl->FPThread;
		FImpl->FPThread=INVALID_HANDLE_VALUE;
		CloseHandle(_tmp);
	}
	{
		CRAII<CMutex> _lock(FImpl->FMutex);
		FIsRunning = false;
		FImpl->FCond.MBroadcast();
	}
	VLOG(2)<<"Thread closed...";
	_endthreadex(0);
}

void CThread::MCancelCleanUp()
{
	LOG_IF(DFATAL,!MIsRunning())<<"The thread is not running.";
	FCleanUp(this, NULL);
}
bool CThread::MSignal(int signal)
{
	LOG_IF(DFATAL,!MIsRunning())<<"The thread is not running.";
	if (MIsRunning())
	{
		MCancelCleanUp();
		FIsRunning = false;
		return TerminateThread(FImpl->FPThread, signal) != 0;
	}
	return false;
}

void CThread::MKill()
{
	LOG_IF(DFATAL,!MIsRunning())<<"The thread is not running.";
	if(MIsRunning())
	{
		MCancelCleanUp();
		FIsRunning = false;
		TerminateThread(FImpl->FPThread,-1);
	}
}
bool CThread::MSetPriority(eThreadPriority priority)
{
	FPriority = priority;
	if (!MIsRunning())
		return true;
	FImpl->MSetPriority();
	return true;
}
bool CThread::MSetPolicy(eSched aPolicy)
{
	FShed = aPolicy;
	return false; //TODO
}
unsigned CThread::sMNumberOfProcessor()
{
	static unsigned _num=0;
	if (!_num)
	{
		SYSTEM_INFO sysinfo;
		::GetSystemInfo(&sysinfo);
		_num=sysinfo.dwNumberOfProcessors;
	}
	return _num;
}
bool CThread::sMYield()
{
	//boost::thread::yield();
	//return true;//return SwitchToThread()!=FALSE
#if __cplusplus >=201103L
	std::this_thread::yield();
#else
	Sleep(1);
#endif
	return true;
}
unsigned CThread::MThreadId()const
{
	LOG_IF(DFATAL,!MIsRunning())<<"The thread is not running.";
	if (MIsRunning())
		return FImpl->FID;
	return 0;
}
unsigned CThread::sMThreadId()
{
	return GetCurrentThreadId();
}
unsigned CThread::sProcessId()
{
	return GetCurrentProcessId();
}

std::ostream& CThread::MPrint(std::ostream& aVal)const
{
	if (!MIsRunning())
	{
		aVal << "Thread is not running.";
		return aVal;
	}
	aVal << "Thread ID:" << MThreadId() << ". Priority=";

	aVal <<MGetPriority();

	if (FCPUNum >= 0)
		aVal << ". CPU:" << FCPUNum;

	return aVal;
}
} //namespace NSHARE
#endif//#if   defined(_WIN32)

#if   !defined(_WIN32)
#include <deftype>
#include <uclock.h>
#include <UType/CThread.h>
#endif
namespace NSHARE
{
	const NSHARE::CText CThread::NAME="thread";
	NSHARE::CConfig CThread::MSerialize() const
	{
		CConfig _conf(NAME);
		_conf.MAdd("run",MIsRunning());
		if(MIsRunning())
		{
			_conf.MAdd("id",MThreadId());
			_conf.MAdd("pr",MGetPriority());
			_conf.MAdd("cpu",FCPUNum);
		}
		return _conf;
	}
}

