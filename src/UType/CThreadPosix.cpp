// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CThreadPosix.cpp
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 10.02.2014
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#if   defined(__QNX__)||defined(unix)
#include <deftype>
#include <uclock.h>
#include <UType/CThread.h>
#include <cassert>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#if   defined(__QNX__)
#include <sys/syspage.h>
#elif defined(__MINGW32__)
#include <winbase.h>
#endif
namespace NSHARE
{
extern void add(struct timespec* aTo, double const& aFrom); //s

struct CThread::CImpl
{
	typedef pthread_attr_t attr_t;

	CImpl(CThread& aThis) :
			FID(pthread_t()),FThis(aThis), FMutex(CMutex::MUTEX_NORMAL)
	{

	}

	static void* sMThreadFunc(void* p);
	static void sMCleanUpHandler(void* arg);

	inline void MStart(const param_t* aParam);
	inline void MConvert(attr_t* aTo, const param_t&);
	void MWaitForCreated();
private:
	void MSetCpuNum(attr_t*& aTo);
	void MSetSchedulePolicy(attr_t*& aTo);
	void MSetPriority(attr_t*& aTo);

	pthread_t FID;
	CThread& FThis;
	CMutex FMutex;
	CCondvar FCondvar;
	friend class CThread;
};
void CThread::CImpl::MWaitForCreated()
{
	NSHARE::CRAII<CMutex> _block(FMutex);
	FCondvar.MTimedwait(&FMutex);
}
void CThread::CImpl::MSetCpuNum(attr_t*& aTo)
{
	if (sMNumberOfProcessor() == 1)
		return;
#if !defined(__QNX__) && !defined(__MINGW32__)
	CHECK_LE(FThis.FCPUNum, static_cast<int>(sMNumberOfProcessor()));
	VLOG(2)<<"The Cpu number is "<<FThis.FCPUNum;
	cpu_set_t cpus;
	CPU_ZERO(&cpus);

	if (FThis.FCPUNum >= 0)
	CPU_SET(FThis.FCPUNum, &cpus);
	else
	{
		for (unsigned i = 0; i < sMNumberOfProcessor(); ++i)
		{
			CPU_SET(i, &cpus);
		}
	}
	int _rval=pthread_attr_setaffinity_np(aTo, sizeof(cpu_set_t), &cpus);
	(void)_rval;
	LOG_IF(FATAL,_rval)<<strerror(_rval);
#endif

}

void CThread::CImpl::MSetSchedulePolicy(attr_t*& aTo)
{
	VLOG(2) << "Setting thread policy: " << FThis.MGetSchedulePolicy();
	struct sched_param my_param;
	int my_policy;
	int _rval = pthread_getschedparam(pthread_self(), &my_policy, &my_param);
	(void) _rval;
	LOG_IF(FATAL,_rval) << strerror(_rval);

#ifdef __linux__
	if(sysconf(_POSIX_THREAD_PRIORITY_SCHEDULING)>0)
	{
#endif
	switch (FThis.MGetSchedulePolicy())
	{

		case CThread::FIFO:
			my_policy = SCHED_FIFO;
			break;

		case CThread::RR:
			my_policy = SCHED_RR;
			break;

		case CThread::SPORADIC:
#ifdef __QNX__
			_rval = pthread_attr_setschedpolicy(aTo, SCHED_SPORADIC);
			//		aTo->param.sched_ss_low_priority=; //TODO
			//		timespec budget=
			//		{	0, 1/ *1000*1000*1000};
			//		memcpy(&_attr.param.sched_ss_init_budget, &budget, sizeof(budget));
			//		memcpy(&_attr.param.sched_ss_repl_period, &it->repl, sizeof(it->repl));
			//		_attr.param.sched_ss_max_repl = 1;
			//TODO
#endif
			my_policy = SCHED_RR;
			break;

		default:
			my_policy = SCHED_RR;
#ifdef __QNX__
			pthread_attr_setschedpolicy(aTo, SCHED_RR);
#else
			my_policy=SCHED_FIFO;
#endif
			break;
	};
#ifdef __linux__
}
else
VLOG(1)<<"Setting thread priority is forbidden(banned).";
#endif
	_rval = pthread_attr_setschedpolicy(aTo, my_policy);
	LOG_IF(DFATAL,_rval) << strerror(_rval);
}

void CThread::CImpl::MSetPriority(attr_t*& aTo)
{
	int _max, _normal, _min;
	int inheritsched = -1;
	VLOG(2) << "Setting thread priority: " << FThis.MGetPriority();
	int _rval = pthread_attr_getschedpolicy(aTo, &inheritsched);
	(void) _rval;
	LOG_IF(DFATAL,_rval) << strerror(_rval);
	_max = sched_get_priority_max(inheritsched);
	_min = sched_get_priority_min(inheritsched);
	VLOG(2)
			<< "The Min, max thread priority is  " << _min << ", " << _max
					<< " respectively.";
#ifdef __QNX__
	_normal = 10;
#elif defined(__linux__)
	_normal = (_max-_min)/2;
#else
#error Target is not supported
#endif
	struct sched_param _sp;
	if (FThis.MGetSchedulePolicy() != CThread::SPORADIC)
		switch (FThis.MGetPriority())
		{
			case CThread::THREAD_PRIORITY_MAX:
				_sp.sched_priority = _max;
				break;
			case CThread::THREAD_PRIORITY_HIGH:
				_sp.sched_priority = (_max + _normal) / 2;
				break;
			case CThread::THREAD_PRIORITY_NOMINAL:
				_sp.sched_priority = _normal;
				break;
			case CThread::THREAD_PRIORITY_LOW:
				_sp.sched_priority = (_min + _normal) / 2;
				break;
			case CThread::THREAD_PRIORITY_MIN:
				_sp.sched_priority = _min;
				break;
			default:
				_sp.sched_priority = _normal;
				break;
		}

	_rval = pthread_attr_setschedparam(aTo, &_sp);
	LOG_IF(DFATAL,_rval) << strerror(_rval);
}

inline void CThread::CImpl::MConvert(attr_t* aTo, const param_t& aParam)
{
	memset(aTo, 0, sizeof(attr_t));
	pthread_attr_init(aTo);
	pthread_attr_setinheritsched(aTo, PTHREAD_EXPLICIT_SCHED);
	MSetSchedulePolicy(aTo);
	MSetPriority(aTo);
	MSetCpuNum(aTo);

	if (FThis.MIsDetached())
	{
		VLOG(2) << "The thread is detached.";
		int _rval = pthread_attr_setdetachstate(aTo, PTHREAD_CREATE_DETACHED);
		(void) _rval;
		LOG_IF(DFATAL,_rval) << strerror(_rval);
	}
}
inline void CThread::CImpl::MStart(const param_t* aP)
{
	attr_t _attr;
	MConvert(&_attr, *aP);
	int _rval = pthread_create(&FID, &_attr, CThread::CImpl::sMThreadFunc,
			this);
	(void) _rval;
	LOG_IF(DFATAL,_rval) << strerror(_rval);
}

void* CThread::CImpl::sMThreadFunc(void* aData)
{
	VLOG(1) << "The thread " << sMThreadId() << " is started";
	CThread::CImpl* _pThis = static_cast<CThread::CImpl*>(aData);
	pthread_cleanup_push(&CThread::CImpl::sMCleanUpHandler, aData)
		;
		_pThis->FThis.MSetRunnig(true);
		{
			NSHARE::CRAII<CMutex> _block(_pThis->FMutex);
			_pThis->FCondvar.MBroadcast();
		}
		_pThis->FThis.MRun();
		_pThis->FThis.MSetRunnig(false);
		pthread_cleanup_pop(0);
	return 0;
}

void CThread::CImpl::sMCleanUpHandler(void* arg)
{
	CThread::CImpl* _cu = static_cast<CThread::CImpl*>(arg);
	_cu->FThis.MSetRunnig(false);
	_cu->FThis.MCancelCleanUp();
}

CThread::CThread() :
		FImpl(new CImpl(*this))
{
	VLOG(2) << "Create CThread: " << this;
	MInit();
}

CThread::CThread(const CB_t& aCB) :
		FImpl(new CImpl(*this))
{
	VLOG(2) << "Create CThread: " << this;
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
	VLOG(2) << "Destruct CThread: " << this;
	if (MIsRunning())
	{
		VLOG(1) << "Thread still running." << (*this);

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
	VLOG(2) << "Create thread. Param=" << aParam << ":" << this;
	if (MIsRunning())
	{
		LOG(ERROR)<< "The Thread already running." << (*this);
		MCancel();
	}
	FImpl->MStart(aParam);
	FImpl->MWaitForCreated();
	return MIsRunning();
}

bool CThread::MSetProcessor(unsigned int cpunum)
{
	VLOG(2) << "Selecting  " << cpunum << " processor";
	if (cpunum > sMNumberOfProcessor() || MIsRunning())
	{
		LOG(ERROR)<< "Selecting processor error. Invalid number of CPU or the Thread is running.";
		return false;
	}

	FCPUNum = cpunum;
	return true;
}
bool CThread::MTestCancel()
{
	CHECK(MIsRunning());
	if (sMThreadId() != MThreadId())
	{
		LOG(DFATAL)<< "Test cancel. The current thread ID and thread ID not equal.";
		return false;
	}
	pthread_testcancel();
	return true;
}
bool CThread::MCancel()
{
	VLOG(2) << "Canceling thread";
	if (!MIsRunning())
		return false;

	int _rval = pthread_cancel(FImpl->FID);
	(void) _rval;
	LOG_IF(ERROR,_rval) << strerror(_rval);

	bool _is = _rval == 0;
	if (_is)
		FIsRunning = false;
	return _is;
}
void CThread::MDetach()
{
	VLOG(2) << "Detaching thread";
	if (MIsDetached())
		return;
	FIsDetached = true;
	if (MIsRunning())
	{
		int _rval = pthread_detach(FImpl->FID);
		(void) _rval;
		LOG_IF(ERROR,_rval) << strerror(_rval);
	}
}
bool CThread::MJoin(uint64_t aTime)
{
	VLOG(2) << "Join " << aTime;
	if (!MIsRunning())
		return false;
	if (aTime)
	{
#if   defined(__QNX__)
		struct timespec _ts;
		get_time(&_ts);
		add(&_ts, aTime);
		return !pthread_timedjoin(FImpl->FID, NULL, &_ts);
#else
		LOG(DFATAL)<<"Time join is not supported.";
		return false;
#endif
	} //if(aTime)
	else
	{
		int _rval = pthread_join(FImpl->FID, NULL);
		(void) _rval;
		LOG_IF(ERROR,_rval) << strerror(_rval);
		return _rval == 0;
	}
}

void CThread::MRun(void)
{
	CHECK(MIsRunning());
	MCall(NULL);
}

void CThread::MCancelCleanUp()
{
	if (MIsRunning())
	{
		FCleanUp(this, NULL);
	}
}
bool CThread::MSignal(int signal)
{
	VLOG(2) << "Signal " << signal;
	CHECK(MIsRunning());
	int _rval = pthread_kill(FImpl->FID, signal);
	(void) _rval;
	LOG_IF(ERROR,_rval) << strerror(_rval);
	return _rval == 0;
}

void CThread::MKill()
{
	VLOG(2) << "Killing";
	CHECK(MIsRunning());
	MSignal(0);
	FIsRunning = false;
}
bool CThread::MSetPriority(eThreadPriority priority)
{
	VLOG(2) << "Setting priority " << priority;
	if (!MIsRunning())
	{
		FPriority = priority;
		return true;
	}
	else
		LOG(WARNING)<<"RT Setting priority is not supported";
	return false; //TODO
}
bool CThread::MSetPolicy(eSched aPolicy)
{
	VLOG(2) << "Setting Policy " << aPolicy;
	if (!MIsRunning())
	{
		FShed = aPolicy;
		return true;
	}
	else
		LOG(WARNING)<<"RT Setting Policy is not supported";
	return false; //TODO

}
unsigned CThread::sMNumberOfProcessor()
{
#if  defined(__linux__)
	static int _cpus = sysconf(_SC_NPROCESSORS_ONLN);
	return _cpus;
#elif  defined(__FreeBSD__) || defined(__NetBSD__)
	int numCPU;
	int mib[4];
	size_t len = sizeof(numCPU);

	/* set the mib for hw.ncpu */
	mib[0] = CTL_HW;
	mib[1] = HW_AVAILCPU; // alternatively, try HW_NCPU;

	/* get the number of CPUs from the system */
	sysctl(mib, 2, &numCPU, &len, NULL, 0);

	if( numCPU < 1 )
	{
		mib[1] = HW_NCPU;
		sysctl( mib, 2, &numCPU, &len, NULL, 0 );

		if( numCPU < 1 )
		{
			numCPU = 1;
		}
	}
	return numCPU;
#elif defined(__QNX__)
	return _syspage_ptr->num_cpu;
#elif defined(__MINGW32__)
	static unsigned _num = 0;
	if (!_num)
	{
		SYSTEM_INFO sysinfo;
		::GetSystemInfo(&sysinfo);
		_num = sysinfo.dwNumberOfProcessors;
	}
	return _num;
#else
	return 1;
#endif
}
unsigned CThread::MThreadId() const
{
	MASSERT(MIsRunning(), true);
#if defined(__QNX__)
	return FImpl->FID;
#elif defined(__MINGW32__)
#	ifdef WIN_PTHREADS_H//���� ���������� ������������
	return (unsigned) FImpl->FID;
#	else
	return (unsigned) FImpl->FID.p;
#endif
#elif defined(unix)
	return (unsigned) FImpl->FID;
#endif

}
bool CThread::sMYield()
{
	return !sched_yield();
}
unsigned CThread::sMThreadId()
{
#if defined(__QNX__)
	return pthread_self();
#elif defined(__MINGW32__)
#	ifdef WIN_PTHREADS_H//���� ���������� ������������
	return (unsigned) pthread_self();
#	else
	return (unsigned) pthread_self().p;
#endif
#elif defined(unix)
	return (unsigned) pthread_self();
#endif
}
unsigned CThread::sProcessId()
{
#if defined(__QNX__)
	return getpid();
#elif defined(__MINGW32__)
#	ifdef WIN_PTHREADS_H//���� ���������� ������������
	return (unsigned) getpid();
#	else
	return (unsigned) getpid().p;
#	endif
#elif defined(unix)
	return (unsigned)getpid();
#endif
}
std::ostream& CThread::MPrint(std::ostream& aVal) const
{
	if (!MIsRunning())
	{
		aVal << "Thread is not running.";
		return aVal;
	}
	aVal << "Thread ID:" << MThreadId() << ". Priority=";

	aVal << MGetPriority();

	aVal << "Schedule:";
	switch (MGetSchedulePolicy())
	{

		case CThread::FIFO:
			aVal << "FIFO";
			break;

		case CThread::RR:
			aVal << "RR";
			break;

		case CThread::SPORADIC:
			aVal << "SPORADIC";
			break;

		default:
#ifdef __QNX__
			aVal << "RR";
#else
			aVal << "FIFO";
#endif
			break;
	};
	if (FCPUNum >= 0)
		aVal << ". CPU:" << FCPUNum;
	if (FIsDetached)
		aVal << ". Detached";

	return aVal;
}

} //namespace NSHARE

#endif//#if   defined(__QNX__)||defined(unix) || defined(__MINGW32__)
