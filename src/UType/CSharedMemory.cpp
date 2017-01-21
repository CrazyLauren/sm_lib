/*
 * CSharedMemory.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 13.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#include <deftype>
#include <crc8.h>
#include <tasks.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
using namespace boost::interprocess;
#include <UType/CSharedAllocator.h>
#include <UType/CSharedMemory.h>

#ifndef NDEBUG
//	#define CHECK_ALLOCATION
#endif
namespace NSHARE
{

SHARED_PACKED(
		struct CSharedMemory::mem_info_t
		{
			typedef NSHARE::crc8_t<0x96> crc_t;
			mem_info_t() :
			FCrc(0x1),FPIDOfLockedMutex(0),FPIDOfLockedAllocMutex(0), FSize(0),FPidOffCreator(NSHARE::CThread::sMPid())
			{
				FSharedMutex[0] = '\0';
				FAllocMutex[0]='\0';
			}
			crc_t::type_t FCrc;
			int8_t FSharedMutex[32 - sizeof(crc_t::type_t)];
			int8_t FAllocMutex[32];
			uint32_t FPIDOfLockedMutex;
			uint32_t FPIDOfLockedAllocMutex;
			uint32_t FSize;
			const uint32_t FPidOffCreator;
			bool MUpdateCRC();
			bool MCheckCRC()const;
		});
bool CSharedMemory::mem_info_t::MUpdateCRC()
{
	const mem_info_t::crc_t::type_t* _begin =
			(mem_info_t::crc_t::type_t*) (this);
	FCrc = crc_t::sMCalcCRCofBuf(_begin + 1,
			_begin + sizeof(FSharedMutex) / sizeof(mem_info_t::crc_t::type_t));
	return true;
}

bool CSharedMemory::mem_info_t::MCheckCRC() const
{
	if (FSharedMutex[0] == '\0')
		return false;

	const mem_info_t::crc_t::type_t* _begin =
			(mem_info_t::crc_t::type_t*) (this);
	crc_t::type_t _crc = crc_t::sMCalcCRCofBuf(_begin + 1,
			_begin + sizeof(FSharedMutex) / sizeof(mem_info_t::crc_t::type_t));
	return _crc == FCrc;
}
class CSharedAllocatorImpl: public IAllocater
{
public:
	typedef uint8_t common_allocater_t;
	//COMPILE_ASSERT((sizeof(NULL_OFFSET)>=sizeof(CSharedAllocator::NULL_OFFSET)),InvalidNullOffsetofSM);

	CSharedAllocatorImpl(struct CSharedMemory::CImpl&);
	virtual ~CSharedAllocatorImpl();
	virtual void* MAllocate(size_type aSize, uint8_t aAlignment = 4,eAllocatorType = ALLOCATE_FROM_COMMON);
	virtual void* MReallocate(void* p, size_type aSize, uint8_t aAlignment = 4,eAllocatorType = ALLOCATE_FROM_COMMON);
	virtual void MDeallocate(void* p, size_type aSize);
	virtual size_type MMaxSize() const;
	virtual size_t MGetUsedMemory() const;
	virtual size_t MGetNumberOfAllocations() const;

	virtual offset_pointer_t MOffset(void* aP) const
	{
		if(!aP)
			return NULL_OFFSET;
		
		CSharedAllocator::offset_t const _offset=FAllocater.MOffset(aP);
		
		if(CSharedAllocator::sMIsNullOffset(_offset))
			return NULL_OFFSET;
		return _offset;
	}

	virtual void* MPointer(offset_pointer_t aOffset) const
	{
		if(aOffset==NULL_OFFSET)
			return NULL;

		CHECK_LE(aOffset, std::numeric_limits<CSharedAllocator::offset_t>::max());

		void* _p = FAllocater.MPointer(static_cast<CSharedAllocator::offset_t>(aOffset));
		return _p;
	}

	virtual bool MIsAllocated(void* aP) const
	{
		return FAllocater.MIsAllocated(aP);
	}

	virtual bool MLock(void* p) const;

	virtual bool MUnlock(void* p) const;

	CSharedAllocator FAllocater;
	CSharedMemory::CImpl& FThis;
};

inline CSharedAllocatorImpl::CSharedAllocatorImpl(CSharedMemory::CImpl& aThis) :
		FThis(aThis)
{
}

inline CSharedAllocatorImpl::~CSharedAllocatorImpl()
{
}
inline void* CSharedAllocatorImpl::MReallocate(void* p, size_type aSize,uint8_t aAlignment,eAllocatorType aType)
{
	void* _p=NULL;
	switch(aType)
	{
	case ALLOCATE_FROM_COMMON:
		_p = FAllocater.MReallocate(p,static_cast<CSharedAllocator::block_size_t>(aSize),true,false);//fixme to config
		break;
	case ALLOCATE_FROM_COMMON_AND_RESERV:
		_p = FAllocater.MReallocate(p, static_cast<CSharedAllocator::block_size_t>(aSize),true,true);//fixme to config
			break;
	};
	return _p;
}
inline void* CSharedAllocatorImpl::MAllocate(size_type aSize,
		uint8_t aAlignment,eAllocatorType aType)
{
	if (0 == aSize)
		return NULL;
	void* _p=NULL;
	switch(aType)
	{
	case ALLOCATE_FROM_COMMON:
		_p = FAllocater.MMalloc(aSize,true,false);//fixme to config
		break;
	case ALLOCATE_FROM_COMMON_AND_RESERV:
		_p = FAllocater.MMalloc(aSize,true,true);//fixme to config
			break;
	};

	return _p;
}

inline void CSharedAllocatorImpl::MDeallocate(void* _p, size_type aSize)
{
	if (!_p)
		return;

	FAllocater.MFree(_p);
}
inline CSharedAllocatorImpl::size_type CSharedAllocatorImpl::MMaxSize() const
{
	return FAllocater.MBufSize();
	//return FAllocater.MFreeHeapSize();
}

inline size_t CSharedAllocatorImpl::MGetUsedMemory() const
{
	return 0;
}

inline size_t CSharedAllocatorImpl::MGetNumberOfAllocations() const
{
	return FAllocater.MGetNumberOfAllocations();
}



struct CSharedMemory::CImpl
{
	CImpl(const NSHARE::CText& aName, size_t aSize,size_t aReserv) :
			FIsInited(false), //
			FInfo(NULL), //
			FUserData(NULL), //
			FUserCb(NULL), //
			FAllocater(*this),//
			FShedMem(open_or_create, aName.c_str(), read_write)//thank you the boost for User-friendly interface!!!
	{
		VLOG(2)<<"Start to  initialize the ShM "<<aName<<" Size ="<<aSize;
		MInit(aName, aSize,true,aReserv);
	}

	CImpl(const NSHARE::CText& aName,bool aIsCleanUp,size_t aReserv) :
			FIsInited(false), //
			FInfo(NULL), //
			FUserData(NULL), //
			FUserCb(NULL), //
			FAllocater(*this),//
			FShedMem(open_only, aName.c_str(), read_write)//thank you the boost for User-friendly interface!!!
	{
		VLOG(2)<<"Start to  initialize the ShM "<<aName;
		MInit(aName, 0,aIsCleanUp,aReserv);
	}

	~CImpl()
	{
		MFree();
	}

	bool MFree();
	size_t MGetSize();
	bool MInitAllocate(void* aTo, bool _is_allocater, size_t aSize,bool aIsCleanUp,size_t aReserv);
	bool MInit(const NSHARE::CText& aName, size_t aSize,bool aIsCleanUp,size_t aReserv);
	static int sMCleanUp(CSharedAllocator* WHO, void* WHAT, void* YOU_DATA);
	bool MCleanUp(CSharedAllocator::clean_up_f_t WHO, void* YOU_DATA);
	bool MCleanUpShareSem();
	bool MLock() const;
	bool MUnlock() const;
	bool MLockAlloc() const;
	bool MUnlockAlloc() const;

//private:
	bool FIsInited;
	mem_info_t* FInfo;
	void* FUserData;
	CSharedAllocator::clean_up_f_t FUserCb;
	mapped_region FRegion;
	CSharedAllocatorImpl FAllocater;
	mutable NSHARE::CIPCSem FShareSem;
	mutable NSHARE::CIPCSem FAllocaterSem;

	shared_memory_object FShedMem;

};
template<> class CRAII<CSharedMemory> : public CDenyCopying
{
public:
	explicit CRAII(CSharedMemory::CImpl& aSem) :
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
		FIsLock = true;
	}

	CSharedMemory::CImpl& FSem;
	volatile bool FIsLock;
};
bool CSharedAllocatorImpl::MLock(void* p) const
{
	//NSHARE::CRAII<NSHARE::CMutex> _block(FMutex);
	//return FAllocater.MLock();//fixme use another mutex for lock CBuffer
	return FThis.MLockAlloc();
}

bool CSharedAllocatorImpl::MUnlock(void* p) const
{
	//NSHARE::CRAII<NSHARE::CMutex> _block(FMutex);
	return FThis.MUnlockAlloc();
}
bool CSharedMemory::CImpl::MLock() const
{

	bool _is = FShareSem.MWait();
	if (_is)
	{
		CHECK_NOTNULL (FInfo);
		const unsigned _pid = NSHARE::CThread::sMPid();
		VLOG(2) << "Lock Sem by " << _pid << "; previous="
				<< FInfo->FPIDOfLockedMutex;
		FInfo->FPIDOfLockedMutex = _pid;
		//FInfo->MUpdateCRC();
	}
	return _is;
}
bool CSharedMemory::CImpl::MUnlock() const
{
	CHECK_NOTNULL (FInfo);
	CHECK_EQ(FInfo->FPIDOfLockedMutex, NSHARE::CThread::sMPid());
	FInfo->FPIDOfLockedMutex = 0;
	return FShareSem.MPost();
}
bool CSharedMemory::CImpl::MLockAlloc() const
{
	bool _is = FAllocaterSem.MWait();
	if (_is)
	{
		CHECK_NOTNULL(FInfo);
		if (FInfo)
		{
			const unsigned _pid = NSHARE::CThread::sMPid();
			VLOG(2) << "Lock Sem by " << _pid << "; previous="
				<< FInfo->FPIDOfLockedAllocMutex;
			FInfo->FPIDOfLockedAllocMutex = _pid;
		}
	}
	return _is;
}
bool CSharedMemory::CImpl::MUnlockAlloc() const
{
	CHECK_NOTNULL(FInfo);
	if (FInfo)
	{
		CHECK_EQ(FInfo->FPIDOfLockedAllocMutex, NSHARE::CThread::sMPid());
		FInfo->FPIDOfLockedAllocMutex = 0;
	}
	return FAllocaterSem.MPost();
}
bool CSharedMemory::CImpl::MFree()
{
	if (!FIsInited)
	{
		VLOG(2) << "Cannot free Shm";
		return false;
	}

	bool _is = false;
	{
		CRAII < CSharedMemory > _block(*this);
		if (FAllocater.FAllocater.MIsInited())
			_is = FAllocater.FAllocater.MReleaseHeap();
	}
	if (_is)
	{
		LOG(INFO) << "The allocator has been destroyed.";
		FShareSem.MFree();
		FAllocaterSem.MFree();
		FShedMem.remove(FShedMem.get_name());
	}
	FInfo = NULL;
	FIsInited = false;
	return _is;
}

size_t CSharedMemory::CImpl::MGetSize()
{
	offset_t _val = 0;
	bool _is = FShedMem.get_size(_val);
	VLOG_IF(2, !_is) << "Cannot get size " << _val;
	if (_is)
		return _val;

	return 0;
}
bool CSharedMemory::CImpl::MInit(const NSHARE::CText& aName, size_t aSize,bool aIsCleanUp,size_t aReserv)
{
	VLOG(2) << "Open shared memory " << aName<<" Size "<<aSize;
	FIsInited=false;
	bool _is_new_header=false;
	bool _is_creator_exist=false;
	bool _was_exist=false;
	uint8_t* _r_addr=NULL;
	void* _allocate_to=NULL;

	{
		VLOG(2)<<"Initialize Shared memory "<<aName<<" path "<<FShedMem.get_name();
		offset_t _size = 0;
		bool const _is = FShedMem.get_size(_size);
		VLOG_IF(2, _is) << "Shared memory size " << _size;
		if (_is)
		{
			_was_exist=_size>0;
			if(!_was_exist)
			{
				if(aSize == 0)
				{
					VLOG(2) << "Cannot create ShM as is not exist " << aSize;
					goto error;
				}else
				{
					LOG(INFO)<< "Create for the first time.";

					FShedMem.truncate(aSize);
					_is_new_header = true;
				}
			}else if(aSize > 0 && aSize !=_size)
			{
				LOG(WARNING)<<"The Shm "<<aName<<" has been created already.";

				mapped_region const _region= mapped_region(FShedMem, read_only);

				uint8_t* _addr = (uint8_t*) _region.get_address();

				if(!_addr)
					goto error;

				mem_info_t const* _info = (mem_info_t const*) (_addr);
				const bool _is_valid =is_process_exist(_info->FPidOffCreator);

				if(_is_valid)
				{
					LOG(DFATAL)<<" The Shm "<<aName<<" is using by "<<_info->FPidOffCreator;
					goto error;
				}
				else
				{
					VLOG(2)<<"Change size of SM "<<aSize;
					FShedMem.truncate(aSize);
					_is_new_header = true;
				}

			}
		}else if(aSize>0)
		{
			VLOG(2)<<"Change size of SM "<<aSize;
			FShedMem.truncate(aSize);
			_is_new_header = true;
		}
		FRegion = mapped_region(FShedMem, read_write);
		FRegion.flush();
		VLOG(2)<<"Region size "<<FRegion.get_size();
	}
	 _r_addr = (uint8_t*) FRegion.get_address();
	CHECK_NOTNULL(_r_addr);
	if(!_r_addr)
		goto error;

	FInfo = (mem_info_t*) (_r_addr);
	_allocate_to = _r_addr	+ sizeof(mem_info_t);

	if (_is_new_header)
	{
		VLOG(2)
				<< "The new shared memory " << aName << " is new.";

		FInfo = new (_r_addr) mem_info_t();
		FInfo->FSize = MGetSize();

		//creating shared mutex
		//The shared mutex name is consist of two part:
		//the first is - pid, the second random string
		{
			NSHARE::CText _rand;
			_rand=get_random_str(10);
			char _mutex_name[1024];
			sprintf(_mutex_name,"shmem_%d_%s", NSHARE::CThread::sMPid(),
					_rand.c_str());
			size_t _name_len = strlen(_mutex_name);
			_name_len =
					_name_len <= (sizeof(FInfo->FSharedMutex) - 1) ?
							_name_len : (sizeof(FInfo->FSharedMutex) - 1);
			memcpy(FInfo->FSharedMutex, _mutex_name, _name_len);
			FInfo->FSharedMutex[_name_len] = '\0';
		}
		{
			NSHARE::CText _rand;
			_rand=get_random_str(10);
			char _mutex_name[1024];
			sprintf(_mutex_name, "shmem_%d_al_%s", NSHARE::CThread::sMPid(),
					_rand.c_str());
			size_t _name_len = strlen(_mutex_name);
			_name_len =
					_name_len <= (sizeof(FInfo->FAllocMutex) - 1) ?
							_name_len : (sizeof(FInfo->FAllocMutex) - 1);
			memcpy(FInfo->FAllocMutex, _mutex_name, _name_len);
			FInfo->FAllocMutex[_name_len] = '\0';
		}

		if (!FShareSem.MInit((char const*) FInfo->FSharedMutex, 1,
				CIPCSem::E_HAS_TO_BE_NEW)
				|| !FAllocaterSem.MInit((char const*) FInfo->FAllocMutex, 1,
						CIPCSem::E_HAS_TO_BE_NEW))
		{
			LOG(DFATAL) << "Cannot create Sems "<<FInfo->FSharedMutex<<" and "<<FInfo->FAllocMutex;
			goto error;
		}
		CRAII<CSharedMemory> _block(*this);
		FAllocater.FAllocater.MCreateHeap(_allocate_to,
				aSize - sizeof(mem_info_t), aReserv);


		FInfo->MUpdateCRC();
	}
	else
	{
		VLOG (2) << "The new shared memory " << aName << " is exist.";
		VLOG(2) << "Initialize shared memory head from " << _r_addr;
		const bool _is_valid = FInfo->MCheckCRC()
				&& (FInfo->FSize == MGetSize()) /*&& is_process_exist(FInfo->FPidOffCreator)*/;

		VLOG(1) << "Sm Valid = " << _is_valid;

		if (!_is_valid)
		{
			VLOG(2)<<"The ShM head is not valid";
			return false;
		}
		if (!FShareSem.MInit((char const*) FInfo->FSharedMutex, 1,
				CIPCSem::E_HAS_EXIST)
				|| !FAllocaterSem.MInit((char const*) FInfo->FAllocMutex, 1,
						CIPCSem::E_HAS_EXIST))
		{
			VLOG(2) << "Cannot init Sems";
			goto error;
		}
		MCleanUpShareSem();

		CRAII < CSharedMemory > _block(*this);

		if(!FAllocater.FAllocater.MInitFromCreatedHeap(_allocate_to,aIsCleanUp,aReserv))
		{
			VLOG(2) << "Cannot init allocator";
			_block.MUnlock();
			goto error;
		}
	}

	VLOG(2)<<"The ShM is full valid";

	FIsInited = true;
	return true;

error:
	VLOG(2)<<"Clean up ShM";

	FShareSem.MFree();
	FAllocaterSem.MFree();
	if (aSize>0 && !_was_exist)
		FShedMem.remove(FShedMem.get_name());
	FInfo = NULL;
	FIsInited = false;

	return false;
}
bool CSharedMemory::CImpl::MCleanUpShareSem()
{
	unsigned _process = FInfo->FPIDOfLockedMutex;
	unsigned _count=0;
	if (_process)
		if (!is_process_exist(_process))
		{
			LOG(ERROR)<<"Process "<<_process<<"is not exist, but the mutex "<<FShareSem.MName()
			<<"still is locked by"<< FInfo->FPIDOfLockedMutex<<". Unlocking immediately ...";
			FInfo->FPIDOfLockedMutex= 0;
			FShareSem.MPost();
			++_count;
		}

	_process = FInfo->FPIDOfLockedAllocMutex;
	if (_process)
		if (!is_process_exist(_process))
		{
			LOG(ERROR)<<"Process "<<_process<<"is not exist, but the mutex "<<FAllocaterSem.MName()
			<<"still is locked by"<< FInfo->FPIDOfLockedAllocMutex<<". Unlocking immediately ...";
			FInfo->FPIDOfLockedAllocMutex= 0;
			FAllocaterSem.MPost();
			++_count;
		}
	return _count>0;
}
int CSharedMemory::CImpl::sMCleanUp(CSharedAllocator* WHO, void* aWHAT,
		void* YOU_DATA)
{
	CSharedMemory::CImpl* _p = (CSharedMemory::CImpl*) (YOU_DATA);
	CHECK_NOTNULL(_p);
	CSharedAllocator::clean_up_resources_t* _res =
			(CSharedAllocator::clean_up_resources_t*) (aWHAT);
	CSharedAllocator::clean_up_resources_t::const_iterator _it = _res->begin();
	for (; _it != _res->end(); ++_it)
	{
		if (_it->FPid == _p->FInfo->FPIDOfLockedMutex)
		{
			LOG(ERROR) << "The Mutex is locked.";
			_p->FInfo->FPIDOfLockedMutex = NSHARE::CThread::sMPid();
			_p->MUnlock();
		}
		if (_it->FPid == _p->FInfo->FPIDOfLockedAllocMutex)
		{
			LOG(ERROR) << "The Mutex is locked.";
			_p->FInfo->FPIDOfLockedAllocMutex = NSHARE::CThread::sMPid();
			_p->MUnlockAlloc();
		}
	}
	if (_p->FUserCb != NULL)
		return (_p->FUserCb)(WHO, aWHAT, _p->FUserData);

	return 0;
}

bool CSharedMemory::CImpl::MCleanUp(CSharedAllocator::clean_up_f_t WHO,
		void* YOU_DATA)
{
	FUserCb = WHO;
	FUserData = YOU_DATA;
	return FAllocater.FAllocater.MCleanUpResourceByWatchDog(&sMCleanUp, this);
}

CSharedMemory::CSharedMemory() :
		FImpl(NULL)
{
}

CSharedMemory::~CSharedMemory()
{
	delete FImpl;
}
bool CSharedMemory::MOpen(const NSHARE::CText& aName,bool aIsCleanUp,size_t aReserv)
{
	VLOG(2) << "Open shared memory " << aName;
	CHECK(!FImpl);
	try
	{
		FImpl=NULL;
		FImpl = new CImpl(aName,aIsCleanUp,aReserv);
	} catch (...)
	{
		LOG(ERROR) << "Cannot open " << aName << " shared memory.";
		CHECK(!FImpl);
	}
	bool _is=MIsOpened();
	if (!_is && FImpl)
	{
		delete FImpl;
		FImpl = NULL;
	}
	return _is;
}
bool CSharedMemory::MIsOpened() const
{
	return FImpl && FImpl->FIsInited;
}
bool CSharedMemory::MOpenOrCreate(const NSHARE::CText& aName, size_t aSize,size_t aReserv)
{
	VLOG(2) << "Open shared memory " << aName<<" Size = "<<aSize;
	CHECK(!FImpl);
	try
	{
		FImpl=NULL;
		FImpl = new CImpl(aName, aSize,aReserv);
	} catch (...)
	{
		LOG(ERROR) << "Cannot open " << aName << " shared memory.";
		CHECK(!FImpl);
	}
	bool _is=MIsOpened();
	if (!_is && FImpl)
	{
		delete FImpl;
		FImpl = NULL;
	}
	return _is;
}

bool CSharedMemory::MFree()
{
	if(FImpl)
	{ 
		CHECK_NOTNULL (FImpl);
		bool _is= FImpl->MFree();
		delete FImpl;
		FImpl=NULL;
		return _is;
	}
	return false;
}

size_t CSharedMemory::MGetSize() const
{
	return FImpl->MGetSize();
}

IAllocater* CSharedMemory::MGetAllocator() const
{
	if (!FImpl)
		return NULL;

	return &FImpl->FAllocater;
}

void* CSharedMemory::MMallocTo(const uint32_t xWantedSize, IAllocater::offset_pointer_t aRefOffset)
{
	CHECK_NOTNULL (FImpl);
	return FImpl->FAllocater.FAllocater.MMallocTo(xWantedSize, static_cast<CSharedAllocator::offset_t>(aRefOffset));
}

void* CSharedMemory::MGetIfMalloced(IAllocater::offset_pointer_t aRefOffset)
{
	CHECK_NOTNULL (FImpl);
	return FImpl->FAllocater.FAllocater.MGetIfMalloced(static_cast<CSharedAllocator::offset_t>(aRefOffset));
}

void CSharedMemory::MCleanUp()
{
	CHECK_NOTNULL (FImpl);
	FImpl->FAllocater.FAllocater.MCleanUpResource();
}

bool CSharedMemory::MIsNeedCleanUpResource()
{
	CHECK_NOTNULL (FImpl);
	return FImpl->FAllocater.FAllocater.MIsNeedCleanUpResource();
}

void CSharedMemory::MFinishCleanUp()
{
	CHECK_NOTNULL (FImpl);
	if (FImpl->FAllocater.FAllocater.MIsWatchDog())
		FImpl->FAllocater.FAllocater.MResetWatchDog();
}
bool CSharedMemory::MCleanUpResourceByWatchDog(
		int (*aF)(CSharedAllocator* WHO, void* WHAT, void* YOU_DATA),void *YOU_DATA)
{
	CHECK_NOTNULL(FImpl);
	return FImpl->MCleanUp(aF,YOU_DATA);
}
void CSharedMemory::MSerialize(NSHARE::CConfig& _conf) const
{
	CHECK_NOTNULL(FImpl);
	_conf.MAdd("smname", FImpl->FShedMem.get_name());
	NSHARE::CConfig _to;
	FImpl->FAllocater.FAllocater.MSerialize(_to);
	_conf.MAdd(_to);
}
bool CSharedMemory::sMRemove(NSHARE::CText const& aName)
{
	return shared_memory_object::remove(aName.c_str());
}
} /* namespace NSHARE */
