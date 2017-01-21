/*
 * CThread.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 10.02.2014
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef _CTHREAD_H_
#define _CTHREAD_H_

namespace NSHARE
{
class SHARE_EXPORT CThread:public CEvent<>,CDenyCopying
{
public:
	static const NSHARE::CText NAME;
	struct sporadic_t//TODO
	{
		;
	};
	enum eThreadPriority 
	{
        THREAD_PRIORITY_DEFAULT,
        THREAD_PRIORITY_MAX=1,
        THREAD_PRIORITY_HIGH,    
        THREAD_PRIORITY_NOMINAL,  
        THREAD_PRIORITY_LOW,      
        THREAD_PRIORITY_MIN
	};
	enum eSched
	{
			FIFO = 1, RR = 2,
			SPORADIC=3,
	} ;
	struct  param_t
	{
		sporadic_t sporadic;
		eThreadPriority FPrior;
		eSched	FShed;
	};
	CThread();//todo from conf
	explicit CThread(CB_t const&);
	virtual ~CThread();

	bool MCreate(param_t const* = NULL);
	void MKill();
	bool MCancel(); 
	bool MTestCancel();
	void MDetach();
	bool MIsDetached()const;
	bool MSignal(int signal);
	bool MJoin(uint64_t aTime = 0); //ns

	bool MSetPriority(eThreadPriority priority);
	eThreadPriority MGetPriority()const;

	bool MSetPolicy(eSched aPolicy);
	eSched MGetSchedulePolicy()const;

	void MSetCleanUp(const CB_t& );

	static unsigned sProcessId();
	static unsigned sMNumberOfProcessor();
	bool MSetProcessor( unsigned int cpunum );

	static bool sMYield();
	bool MIsRunning(void) const;

	static unsigned sMThreadId();
	static unsigned sMPid(){
		return sProcessId();
	}
	unsigned MThreadId()const;

	virtual std::ostream& MPrint(std::ostream& aVal)const;
	NSHARE::CConfig MSerialize() const;
protected:
	struct CImpl;
	virtual void MRun(void);
	virtual void MCancelCleanUp(void);//Event TODO

private:
	void MSetRunnig(bool aVal);
	inline void MInit();
	CImpl* FImpl;
	CB_t FCleanUp;
	volatile bool FIsRunning;
	volatile bool FIsDetached;
	volatile int FCPUNum;
	volatile eThreadPriority FPriority;
	volatile eSched FShed;
};
inline bool CThread::MIsRunning() const
{
	return FIsRunning;
}
inline bool CThread::MIsDetached() const
{
	return FIsDetached;
}
inline void CThread::MSetRunnig(bool aVal)
{
	FIsRunning=aVal;
}
inline void CThread::MSetCleanUp(const CB_t& aVal)
{
	FCleanUp = aVal;
}
inline CThread::eThreadPriority CThread::MGetPriority()const
{
	return FPriority;
}
inline CThread::eSched CThread::MGetSchedulePolicy()const
{
	return FShed;
}
}//namespace USHARE
namespace NSHARE
{
SHARED_DEPRECATED_F( inline unsigned thread_id()
{
	return CThread::sMThreadId();
});
}

namespace std
{
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::CThread const& aThread)
{
	return aThread.MPrint(aStream);
}
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::CThread::eThreadPriority const& aPrior)
{
	switch (aPrior)
		{
			case NSHARE::CThread::THREAD_PRIORITY_MAX:
				aStream << "Max";
				break;
			case NSHARE::CThread::THREAD_PRIORITY_HIGH:
				aStream << "High";
				break;
			case NSHARE::CThread::THREAD_PRIORITY_NOMINAL:
				aStream << "Normal";
				break;
			case NSHARE::CThread::THREAD_PRIORITY_LOW:
				aStream << "Low";
				break;
			case NSHARE::CThread::THREAD_PRIORITY_MIN:
				aStream << "Min";
				break;
			default:
				aStream << "Normal";
				break;
		}
	return aStream;
}
inline std::istream& operator>>(std::istream & aStream,
		NSHARE::CThread::eThreadPriority& aPrior)
{
	std::string _str;
	aStream >> _str;
	CHECK(!aStream.fail());

	std::string::iterator _it=_str.begin();

	for (; _it != _str.end(); ++_it)
		*_it = ::tolower(*_it);
	if(_str=="max")
		aPrior=NSHARE::CThread::THREAD_PRIORITY_MAX;
	else if(_str=="high")
		aPrior=NSHARE::CThread::THREAD_PRIORITY_HIGH;
	else if(_str=="normal")
		aPrior=NSHARE::CThread::THREAD_PRIORITY_NOMINAL;
	else if(_str=="low")
		aPrior=NSHARE::CThread::THREAD_PRIORITY_LOW;
	else if(_str=="min")
		aPrior=NSHARE::CThread::THREAD_PRIORITY_MIN;
	else
		aStream.setstate(std::istream::failbit);
	return aStream;
}
}
#endif // #ifndef _CTHREAD_H_
