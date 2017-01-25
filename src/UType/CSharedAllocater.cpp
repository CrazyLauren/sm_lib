// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * CSharedAllocator.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 10.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#include <deftype>
#include <crc8.h>
#include <tasks.h>
#include <boost/version.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <UType/CSharedAllocator.h>

//todo refractor
//fixme bug Clean up logic error
//The block node can be hold by a few processes, but the about it information
//is not kept. Therefore if the block is used by two process and one of them  dies
//The block will removed although it's used by the other process.
//To avoid this, The info has to be kept.
//Instead of offset every the process node is to be kept info about the block
//in The structure which consists of the node offset,
//offsets array index for next and previous process node being kept the info
//Then the block will cleaned up only if it's kept by only one process
//In other case the block info  will moved to the other process node
//todo если резерв полон то можно его двигать(дефрагментация)
namespace NSHARE
{
const NSHARE::CText CSharedAllocator::NAME="shm_alloc";
const CSharedAllocator::index_type CSharedAllocator::NULL_INDEX=std::numeric_limits<CSharedAllocator::index_type>::max();
const CSharedAllocator::offset_t CSharedAllocator::NULL_OFFSET = ((CSharedAllocator::offset_t) 1) << ((sizeof(CSharedAllocator::offset_t) * 8) - 1);

static unsigned const& get_pid_optimized()
{
	static unsigned _pid =NSHARE::CThread::sMPid();
	return _pid;
}
#if (BOOST_VERSION / 100000 >=1) &&(BOOST_VERSION / 100 % 1000<=47)
using namespace boost::interprocess::detail;
#else
using namespace boost::interprocess::ipcdetail;
#endif

inline void atomic_add(volatile boost::uint32_t *mem, int val)
{
#ifdef _WIN32
	boost::uint32_t   _nval;
	boost::uint32_t   _old;
	do
	{
		_old=atomic_read32(mem);
		_nval=_old+val;
		//atomic_write32(mem,_nval);
	}while(atomic_cas32(mem,_nval,*mem)!=_old);
#else
	atomic_add32(mem,val);
#endif
}
typedef CSharedAllocator::block_size_t block_size_t;

bool CSharedAllocator::sMIsNullOffset(const offset_t& aWhat) 
{
	return (aWhat&CSharedAllocator::NULL_OFFSET) != 0;
}
static inline bool is_null_offset( const CSharedAllocator::offset_t& aWhat)
{
	return CSharedAllocator::sMIsNullOffset(aWhat);
}
SHARED_PACKED(struct CSharedAllocator::pid_offset_t
{
	pid_offset_t():FNextNode(NULL_OFFSET)
	{

	}
	union
	{
		offset_t FNextNode; //The next free block
		//pid_type FPid; //The process id  allocated memory.

		SHARED_PACKED(struct//using in process_node_t when pid_offset_t is free(NULL) and in block_node_t when it's mallocated
		{
			index_type FIndexOfOffset;	//The pid array index of process node.
			//The index of pid array is holded instead of process id  as
			// in both cases the process node is to be looked for by field
			// FIndexOfOffset or FPid   respectively. But in the second case
			//the pid array index is necessary  looked for additionally.
			//It's slower than the first method.
			index_type FIndexOfAlias:13;//reserved for the future
			index_type FReserveFree:1;
			index_type FReservedFlag:1;//true If It's block has been reserved
			index_type FNullOffsetFlag:1;
		});
	};
});

COMPILE_ASSERT(sizeof(CSharedAllocator::free_index_t) == sizeof(uint32_t),
		IVALID_SIZEOF_FREE_INDEX);
//Define the linked list structure.  This is used to link free blocks in order
// of their memory address.
SHARED_PACKED(
struct CSharedAllocator::block_node_t:pid_offset_t
{
	block_node_t() :
		FBlockSize(0)
	{

	}
	inline struct block_node_t *MNext(void* aBaseAddr) const;
	inline offset_t MSetNextNode(offset_t const&);
	void MSetBlockSize(block_size_t const& aVal)
	{
		VLOG(2) << "Set new block size equal " << aVal;
		FBlockSize = aVal;
	}
	void MSerialize(NSHARE::CConfig& aConfig) const;

	block_size_t FBlockSize; //The size of the free block //fixme 64 bit
});
COMPILE_ASSERT(sizeof(CSharedAllocator::block_node_t) == (sizeof(CSharedAllocator::offset_t)+sizeof(CSharedAllocator::block_size_t)),
		IVALID_SIZEOF_BLOCK_NODE);
void CSharedAllocator::block_node_t::MSerialize(NSHARE::CConfig& aConfig) const
{
	aConfig.MAdd("BeginVolume", sizeof(block_node_t));
	aConfig.MAdd("SizeOfUsableVolume", FBlockSize&(~BLOCK_ALLOCATED_BIT));

	if (FBlockSize & BLOCK_ALLOCATED_BIT)
	{
		aConfig.MAdd("Type", "Allocated");
		//aConfig.MAdd("PID", FPid);
		aConfig.MAdd("PIDoffset", FIndexOfOffset);
		aConfig.MAdd("PIDAliasoffset", FIndexOfAlias);
		aConfig.MAdd<bool>("IsReserv", FReservedFlag);
		aConfig.MAdd<bool>("ReservFree", FReserveFree);
	}
	else
	{
		aConfig.MAdd("Type", "Free");
		if(is_null_offset(FNextNode))
			aConfig.MAdd("NextBlockNode", "null");
		else
			aConfig.MAdd("NextBlockNode", FNextNode);
	}
}

inline std::ostream& operator<<(std::ostream& aStream,
		CSharedAllocator::block_node_t const& aVal)
{
	return aStream << "Block size=" << aVal.FBlockSize << " next="
			<< aVal.FNextNode;
}
static const uint32_t RESERV_IS_NOT_ALLOCATED=(uint32_t)-1;
//Define the list structure.  This is used to link process allocated data  in order
// of their pid.
SHARED_PACKED(
struct CSharedAllocator::process_node_t
{
	inline explicit process_node_t(pid_type aPid, block_size_t  aMemorySize,size_t aReserv);
	inline explicit process_node_t(process_node_t const* aRht, block_size_t  aMemorySize);

	inline struct process_node_t *MNext(void* aBaseAddr) const;
	inline offset_t MSetNextNode(offset_t const&);

	inline offset_t MPutOffset(offset_t aOffset);
	//void MPopOffset(offset_t aOffset);
	inline void MPopOffsetById(offset_t aOffset);
	inline bool MIsOffset(offset_t aOffsetInArray,offset_t aOffset);
	size_t MSizeOf()const
	{
		const size_t _size=FArraySize*sizeof(FOffsets[0])+sizeof(process_node_t);
		return _size;
	}
//	bool MIsReservAllocated() const;
//	void MSetReservAllocated( bool aVal);
	void MSerialize(NSHARE::CConfig& aConfig) const;
	offset_t FNextNode; //The next process node
	pid_type const FPid; //Process id
	volatile free_index_t FMinFreeIndex;//used to hold the index below which no a free number.
	//FMinFreeIndex - is the first node of 'free index' linked list
	volatile uint32_t FCount; //The number of Object being kept hold
	uint32_t const FArraySize; // is used to hold the array size
	uint32_t  FSizeOfReserv; // is used to hold the reserv size
	uint32_t FUsedUpReserv; // is used to hold the size of used reserv if -1 when not allocated
	volatile uint32_t FAlloactionCount; //is used to hold the number of the memory blocks was allocated by process
	pid_offset_t FOffsets[0]; //array of allocated memory addresses
});
CSharedAllocator::process_node_t::process_node_t(pid_type aPid,
		block_size_t aMemorySize,size_t aReserv) :
		FNextNode(NULL_OFFSET), //
		FPid(aPid), //
		FMinFreeIndex(0),//
		FCount(0), //
		FArraySize(
				(aMemorySize - sizeof(process_node_t)) / sizeof(FOffsets[0])), //
		FSizeOfReserv(static_cast<uint32_t>(aReserv)),//
		FUsedUpReserv(RESERV_IS_NOT_ALLOCATED),//
		FAlloactionCount(0) //
{
	CHECK_GT(aMemorySize, sizeof(process_node_t));
	LOG_IF(FATAL,FArraySize>=NULL_INDEX)<<"Cannot allocate the process node for storing "<<FArraySize<<" offsets as "
			" the max number of offsets which can be stored  is  "<<NULL_INDEX<<" The value limitation is related of "
			"the array index limitation.";

	for (unsigned i = 0; i < FArraySize; ++i)
	{
		FOffsets[i].FNextNode = NULL_OFFSET;
		FOffsets[i].FIndexOfOffset=NULL_INDEX;
	}
}
CSharedAllocator::process_node_t::process_node_t(process_node_t const* aRht,
		block_size_t aMemorySize) :
		FNextNode(aRht->FNextNode), //
		FPid(aRht->FPid), //
		//FMinFreeIndex(/*aRht->FMinFreeIndex*/0),//fixme
		FMinFreeIndex(aRht->FMinFreeIndex),//
		FCount(aRht->FCount), //
		FArraySize(
				(aMemorySize - sizeof(process_node_t)) / sizeof(FOffsets[0])), //
		FSizeOfReserv(aRht->FSizeOfReserv),//
		FUsedUpReserv(aRht->FUsedUpReserv),//
		FAlloactionCount(aRht->FAlloactionCount) //
{
	LOG_IF(FATAL,FArraySize>=NULL_INDEX)<<"Cannot allocate the process node for storing "<<FArraySize<<" offsets as "
			" the max number of offsets which can be stored  is  "<<NULL_INDEX<<" The value limitation is related of "
			"the array index limitation.";

	CHECK_GT(aMemorySize, sizeof(process_node_t));
	memcpy(FOffsets, aRht->FOffsets,aRht->FArraySize * sizeof(FOffsets[0]));
	CHECK_LT((unsigned)FAlloactionCount,FArraySize);
	for (unsigned i = aRht->FArraySize; i < FArraySize; ++i)
	{
		FOffsets[i].FNextNode = NULL_OFFSET;
		FOffsets[i].FIndexOfOffset = NULL_INDEX;
	}
}
//bool CSharedAllocator::process_node_t::MIsReservAllocated() const
//{
//	;
//}
//void MSetReservAllocated(bool aVal)
//{
//	;
//}

bool CSharedAllocator::process_node_t::MIsOffset(offset_t aOffsetInArray,
		offset_t aOffset)
{
	if(FArraySize<=aOffsetInArray)
		return false;
	return atomic_read32(&FOffsets[aOffsetInArray].FNextNode)==aOffset;//fixme проверить не в списке свободных
}
CSharedAllocator::offset_t CSharedAllocator::process_node_t::MPutOffset(offset_t aOffset)
{
	CHECK_NE((unsigned)FAlloactionCount, FArraySize);
	CHECK_LE(aOffset, (offset_t)(NULL_INDEX << (sizeof(offset_t)/sizeof(index_type)-1)*sizeof(index_type)*8));
//	free_index_t _min=atomic_read32(&FMinFreeIndex.FVal);
//	unsigned i = _min.FIndex;
	free_index_t _min=atomic_read32(&FMinFreeIndex);
	unsigned i = _min;

	CHECK_NE(i,NULL_INDEX);
	CHECK_LE(i, FArraySize);
	for (;
			i < FArraySize
					&& !is_null_offset(atomic_read32(&FOffsets[i].FNextNode));
			++i)
		;
	//LOG_IF(DFATAL,i!=_min.FIndex)<<"The free index is founded in "<<i<<" position, but The free pos has to be in "<<_min.FIndex;
	LOG_IF(DFATAL,i!=_min)<<"The free index is founded in "<<i<<" position, but The free pos has to be in "<<_min;
/*	if (i == FArraySize)
	{
		i = 0;
		for (; i < _min && atomic_read32(&FOffsets[i].FNextNode) != NULL_OFFSET; ++i)
			;
	}*/
	VLOG(5) << "Put the offset to the array: " << aOffset<<" i="<<i<<" this="<<this;
	CHECK_NE(i, FArraySize);

//	CHECK_EQ(atomic_read32(&FMinFreeIndex.FVal),_min.FVal);//thread safety
//
//	if(_min.FNext == NULL_INDEX )
//		++_min.FIndex;
//	else
//	{
//		_min.FNext =FOffsets[_min.FNext].FIndexOfOffset;
//		_min.FIndex=_min.FNext;
//	}
//
//	atomic_write32(&FMinFreeIndex.FVal,_min.FVal);

	CHECK_EQ(atomic_read32(&FMinFreeIndex),_min);//thread safety

	if (FOffsets[_min].FIndexOfOffset == NULL_INDEX) //next free index
	{
		VLOG(5)<<"Next index.";
		++_min;
	}
	else
	{
		VLOG(5)<<"Next index ="<<FOffsets[_min].FIndexOfOffset<< " cur="<<_min;
		_min =FOffsets[_min].FIndexOfOffset;
	}
	VLOG(5)<<"Min Free index = "<<_min;
	atomic_write32(&FMinFreeIndex,_min);


	atomic_write32(&FOffsets[i].FNextNode,aOffset);
	atomic_inc32(&FAlloactionCount);


	VLOG(5)<<"value "<<FOffsets[i].FNextNode;
	return i;
}
//void CSharedAllocator::process_node_t::MPopOffset(offset_t aOffset)
//{
//	VLOG(2) << "Pop the offset to the array: " << aOffset<<" this="<<this;
//	CHECK_NE(aOffset, NULL_OFFSET);
//	unsigned i = 0;
//	for (; i < FArraySize && atomic_read32(&FOffsets[i].FNextNode) != aOffset; ++i)
//		VLOG(5)<<"i="<<i<<"; val="<<FOffsets[i].FNextNode;
//	CHECK_NE(i, FArraySize);
//	MPopOffsetById(i);
//}
void CSharedAllocator::process_node_t::MPopOffsetById(offset_t aOffset)
{
	free_index_t _min=atomic_read32(&FMinFreeIndex);
	VLOG(5)<<"Prev index = "<<_min<<" new = "<<aOffset;
	pid_offset_t _offset;
	_offset.FIndexOfOffset=_min;
	_min=aOffset;

	atomic_write32(&FOffsets[aOffset].FNextNode,_offset.FNextNode);
	atomic_write32(&FMinFreeIndex, _min);

	LOG_IF(FATAL,!is_null_offset(atomic_read32(&FOffsets[_min].FNextNode)))<<_offset.FNextNode;
	atomic_dec32(&FAlloactionCount);


	//_min.FNext
//	if (aOffset < _val)
//	{
//		atomic_write32(&FMinFreeIndex, aOffset);
//	}

	//CHECK_EQ(atomic_read32(&FMinFreeIndex),aOffset);

}
void CSharedAllocator::process_node_t::MSerialize(NSHARE::CConfig& aConfig) const
{
	aConfig.MAdd("PID",FPid);
	aConfig.MAdd("Counter",(unsigned)FCount);
	aConfig.MAdd("NumberOfAllocation",(unsigned)FAlloactionCount);
	aConfig.MAdd("Reserv",(unsigned)FSizeOfReserv);
	aConfig.MAdd("UsedReserv",(unsigned)FUsedUpReserv);

	if(is_null_offset(FNextNode))
		aConfig.MAdd("NextProcessNode", "null");
	else
		aConfig.MAdd("NextProcessNode", FNextNode);

	unsigned i = 0;
	for (; i < FArraySize; ++i)
		if (!is_null_offset(FOffsets[i].FNextNode))
			aConfig.MAdd("AllocatedBlock", FOffsets[i].FNextNode-sizeof(block_node_t));
}
static inline unsigned contoling_type_size()
{
	return sizeof(CSharedAllocator::offset_t)
			+ sizeof(CSharedAllocator::block_size_t)
			+ sizeof(CSharedAllocator::index_type);
}
//head of heap
SHARED_PACKED(
struct CSharedAllocator::heap_head_t
{
	enum
	{
		WACTH_DOG_PRIORITY=0x1<<0,
		TRY_LOCK_MUTEX=0x1<<1,
		TRY_UNLOCK_MUTEX=0x1<<2,
		WAIT_FOR_FREE=0x1<<3,
	};
	typedef NSHARE::crc8_t<0x97> crc_t;
	heap_head_t(block_size_t aSize) :
		FMutexFlags(0),//
		FCrc8(0x1),//
		FFreeBytesRemaining(0),//
		FMaxSize(aSize),//
		FOffsetToProcessNode(NULL_OFFSET),//
		FFOffsetFirstNode(NULL_OFFSET),//
		FPIDOfLockedMutex(0),//
		FLockedMutexCounter(0),//
		FTIDOfLockedMutex(0),//
		FWacthDogPid(0),//
		FWacthDogTid(0),//
		FNumberOfWaitingFor(0),//
		FPostCount(0),//
		FControlingTypeSize(contoling_type_size()),
		FNumUserAllocation(0)
	{
		memset(FSharedMutex,0,sizeof(FSharedMutex));
		memset(FFreeSem,0,sizeof(FFreeSem));
		memset(FWatchDogSem,0,sizeof(FWatchDogSem));
	}
	uint8_t FSharedMutex[CIPCSem::eReguredBufSize];
	uint8_t FFreeSem[CIPCSem::eReguredBufSize];
	uint8_t FWatchDogSem[CIPCSem::eReguredBufSize];
	uint8_t FMutexFlags;//
	uint8_t FCrc8; //is used to control the head integrity
	block_size_t FFreeBytesRemaining; //the number of free bytes remaining
	block_size_t const FMaxSize; //size of allocated buffer
	offset_t FOffsetToProcessNode; //is used to hold pointer to the first item in the pid list;
	offset_t FFOffsetFirstNode; //is used to hold a pointer to the first item in the list of free blocks
	pid_type FPIDOfLockedMutex;//is used to hold the process pid which keep on locking the mutex.
	uint32_t FLockedMutexCounter;//is used to realize recursive mutex
	pid_type FTIDOfLockedMutex;//It's used for paranoic checking
	uint32_t FWacthDogPid;//is used to hold the mutex name (hex value of pid and tid) which is started watch dog clean up function
	uint32_t FWacthDogTid;
	uint32_t FNumberOfWaitingFor;//The number of threads wait for free memory will be called
	uint32_t FPostCount;
	uint32_t const FControlingTypeSize:8;//sizeof(offset_t) + sizeof(block_size_t) + sizeof(pid_type)+sizeof(index_type)+...
	uint32_t :24;
	mutable uint32_t FNumUserAllocation;
	//int8_t FWacthDogMutex[16];

	bool MIsWatchDogExist()const;
	inline void MSetFirstNode(offset_t aNode);
	inline struct process_node_t *MFirstProcessNode(void* aBaseAddr);
	inline struct block_node_t *MFirstBlockNode(void* aBaseAddr);
	void MFillCRC();
	bool MCheckCrc() const; //checking the head integrity;
	void MSerialize(NSHARE::CConfig& ) const;
	bool MIsWaitFree() const;
	bool MIsValidTypeSize()const;
	void MIncUserAllocation();
	void MDecUserAllocation();
	bool MIsCanBeMAllocated() const;
	//void MSetWaitFree(bool aVal);
});
COMPILE_ASSERT(sizeof(CSharedAllocator::heap_head_t) == (3*CIPCSem::eReguredBufSize+ 2 + 13 * 4),
		IVALID_SIZEOF_HEAD);
void CSharedAllocator::heap_head_t::MIncUserAllocation()
{
	atomic_inc32(&FNumUserAllocation);
}
void CSharedAllocator::heap_head_t::MDecUserAllocation()
{
	atomic_dec32(&FNumUserAllocation);
}
bool CSharedAllocator::heap_head_t::MIsCanBeMAllocated() const
{
	return atomic_read32(&FNumUserAllocation)!=0;
}
bool CSharedAllocator::heap_head_t::MIsValidTypeSize() const
{
	return contoling_type_size()==FControlingTypeSize;
}
bool CSharedAllocator::heap_head_t::MIsWatchDogExist()const
{
	return FWacthDogPid>0;
}
void CSharedAllocator::heap_head_t::MSerialize(NSHARE::CConfig& aConfig) const
{
	aConfig.MAdd("Mutex",reinterpret_cast<const char*>(FSharedMutex));
	aConfig.MAdd("FreeSem",reinterpret_cast<const char*>(FFreeSem));
	aConfig.MAdd("Crc",FCrc8);
	aConfig.MAdd("FreeBytesRemaining",FFreeBytesRemaining);
	aConfig.MAdd("MaxSize",FMaxSize);
	aConfig.MAdd("OffsetToProcessNode",FOffsetToProcessNode);
	aConfig.MAdd("FOffsetFirstNode",FFOffsetFirstNode);
	aConfig.MAdd("LockedPID",FPIDOfLockedMutex);
	aConfig.MAdd("LockedTID",FTIDOfLockedMutex);
	aConfig.MAdd("FLockedMutexCounter",FLockedMutexCounter);
	aConfig.MAdd("WatchDogPID",FWacthDogPid);
	aConfig.MAdd("WatchDogTID",FWacthDogTid);
	aConfig.MAdd("WaitNum",FNumberOfWaitingFor);
	aConfig.MAdd("PostCount",FPostCount);

	aConfig.MAdd("TypeSize",FControlingTypeSize);
	aConfig.MAdd("NumUserAllocation",FNumUserAllocation);
}
void CSharedAllocator::heap_head_t::MSetFirstNode(offset_t aNode)
{
	VLOG(2) << "Set first node " << aNode;
	FFOffsetFirstNode = aNode;
}
bool CSharedAllocator::heap_head_t::MIsWaitFree() const
{
	//return FMutexFlags &WAIT_FOR_FREE;
	return FNumberOfWaitingFor>0;
}
//void CSharedAllocator::heap_head_t::MSetWaitFree(bool aVal)
//{
//	if (aVal)
//		FMutexFlags |= WAIT_FOR_FREE;
//	else
//		FMutexFlags &= ~WAIT_FOR_FREE;
//}

struct CSharedAllocator::process_node_t *CSharedAllocator::heap_head_t::MFirstProcessNode(
		void* aBaseAddr)
{
	CHECK_GE(FOffsetToProcessNode, sizeof(heap_head_t));
	return sMPointerFromBase<process_node_t>(FOffsetToProcessNode, aBaseAddr);
}
struct CSharedAllocator::block_node_t *CSharedAllocator::heap_head_t::MFirstBlockNode(
		void* aBaseAddr)
{
	CHECK_GE(FFOffsetFirstNode, sizeof(heap_head_t));
	block_node_t * const _p = sMPointerFromBase<block_node_t>(FFOffsetFirstNode,
			aBaseAddr);
	if (!_p)
		return _p;
	CHECK_LT(_p->FBlockSize, FMaxSize);
	return _p;
}
void CSharedAllocator::heap_head_t::MFillCRC()
{
	crc_t::type_t* const _crc_begin = (crc_t::type_t*)&FMaxSize;
	FCrc8 = crc_t::sMCalcCRCofBuf(_crc_begin,_crc_begin + sizeof(FMaxSize));
}
bool CSharedAllocator::heap_head_t::MCheckCrc() const //checking the head integrity
{
	crc_t::type_t* const _crc_begin = (crc_t::type_t*)&FMaxSize;
	uint8_t const _crc = crc_t::sMCalcCRCofBuf(_crc_begin, _crc_begin +sizeof(FMaxSize)); 
	return _crc == FCrc8 &&FMaxSize>0 && FControlingTypeSize>0;
}

struct CSharedAllocator::block_node_t *CSharedAllocator::block_node_t::MNext(
		void* aBaseAddr) const
{
	CHECK_GE(FNextNode, FBlockSize);
	CHECK_GE(FNextNode, sizeof(heap_head_t));
	return sMPointerFromBase<block_node_t>(FNextNode, aBaseAddr);
}
CSharedAllocator::offset_t CSharedAllocator::block_node_t::MSetNextNode(offset_t const& aVal)
{
	CHECK_GT(aVal, sizeof(heap_head_t));
	VLOG(2) << "Set next node = " << aVal;
	FNextNode = aVal;
	return FNextNode;
}

struct CSharedAllocator::process_node_t * CSharedAllocator::process_node_t::MNext(
		void* aBaseAddr) const
{
	CHECK_GE(FNextNode, sizeof(heap_head_t) + sizeof(block_node_t));
	return sMPointerFromBase<process_node_t>(FNextNode, aBaseAddr);
}
CSharedAllocator::offset_t CSharedAllocator::process_node_t::MSetNextNode(offset_t const& aVal)
{
	CHECK_GT(aVal, sizeof(heap_head_t) + sizeof(block_node_t));
	VLOG(2) << "Set next proc node = " << aVal;
	FNextNode = aVal;
	return FNextNode;
}

//When this bit in the FBlockSize is set then the block is been allocated,
// otherwise the block is part of the free heap space.
block_size_t const CSharedAllocator::BLOCK_ALLOCATED_BIT = ((block_size_t) 1)
		<< ((sizeof(block_size_t) * 8) - 1);
const double CSharedAllocator::PROCESS_ARRAY_FACTOR = 1.5;
const block_size_t CSharedAllocator::DEF_PROCESS_SIZE = (sizeof(process_node_t)
		+ 30 * sizeof(CSharedAllocator::offset_t)) / sizeof(process_node_t)
		* sizeof(process_node_t);

const uint8_t CSharedAllocator::MINIMAL_OFFSET = sizeof(block_node_t);

template<class T>
CSharedAllocator::offset_t CSharedAllocator::sMOffsetFromBase(T const* const aFrom,
		void const * const aBase)
{
	if (!aFrom)
		return NULL_OFFSET;
	CHECK_GE((uint8_t* ) aFrom, (uint8_t* ) aBase);
	return static_cast<offset_t>((uint8_t*) aFrom - (uint8_t*) aBase);
}
template<class T>
T* CSharedAllocator::sMPointerFromBase(offset_t aOffset, void* aBase)
{
	VLOG_IF(2,!aBase) << "Base addr is null.!";
	VLOG_IF(5,aBase) << "Base addr is " << aBase << " offset = " << aOffset;
	return (!aBase || is_null_offset(aOffset))?NULL: reinterpret_cast<T *>((uint8_t*)aBase + aOffset);
}
template<class T>
void* CSharedAllocator::sMNextCoorectAddr(void* aAddr)
{
	const uint32_t _alligment = __alignof(T);
	const uintptr_t _offset = (uintptr_t) aAddr % _alligment;
	if (_offset)
		return (void*) ((uintptr_t) aAddr + _alligment - _offset);
	else
		return aAddr;
}
template<class T>
void* CSharedAllocator::sMPrevCoorectAddr(void* aAddr)
{
	const uint32_t _alligment = __alignof(T);
	const uint64_t _offset = (uint64_t) aAddr % _alligment;
	if (_offset)
		return (void*) ((uint64_t) aAddr - _alligment + _offset);
	else
		return aAddr;
}
void * CSharedAllocator::sMGetPointerOfBlockNode(block_node_t* aNode)
{
	return ++aNode;
}
CSharedAllocator::block_node_t* CSharedAllocator::sMGetBlockNode(void  * const aPointer)
{
	CHECK_NOTNULL(aPointer);
	block_node_t* _p_node=reinterpret_cast<block_node_t*>((uint8_t*) (aPointer)
			- sizeof(block_node_t));
	CHECK_NOTNULL(_p_node);
	VLOG_IF(2,(_p_node->FBlockSize & BLOCK_ALLOCATED_BIT) == 0) << "Warning! Node "
																			<< aPointer
																			<< " is not allocated.";
	return  _p_node;
}

CSharedAllocator::CSharedAllocator(void * aBase) :
		FCurentProcess(NULL)
{
	FReserv=0;
	if(aBase)
		MInitFromCreatedHeap(aBase);
}
CSharedAllocator::~CSharedAllocator()
{
	if (FCurentProcess)
		MReleaseHeap();
}

bool CSharedAllocator::MInitFromCreatedHeap(void* aVal,bool aCleanUp,size_t aReserv)
{
	VLOG(2) << "Init from heap " << aVal;
	LOG_IF(ERROR,!aVal)<<"The ShM allocator is initialized from NULL pointer";
	FBase = aVal;
	FReserv=aReserv;
	if (FBase)
	{
		//init the shared mutex
		heap_head_t* const _p_head = sMGetHead(FBase);
		//checking the head integrity
	//	CHECK_EQ(_p_head->MCheckCrc(), true);
		if (!_p_head->MIsValidTypeSize() || !_p_head->MCheckCrc())
		{
			LOG_IF(DFATAL,!_p_head->MIsValidTypeSize())<<"Invalid heap types size. Cannot initialize it.";
			LOG(DFATAL)<<"The head integrity checking  has ended with failure.";
			FBase = NULL;
			return false;
		}
		else
		{
			//The semaphore with value 1 is a mutex.
			FSem.MInit(_p_head->FSharedMutex, sizeof(_p_head->FSharedMutex), 1,CIPCSem::E_HAS_EXIST);
			MInitIfNeedFreeSem(_p_head);
			if (aCleanUp)
			{
				MSafetyLockImpl(_p_head);
				MCleanUpImpl();
				MUnlockImpl(_p_head);
			}
			if(aReserv)
				MInitProcessNode(_p_head);
		}
	}
	return FBase!=NULL;
}


void CSharedAllocator::MInitProcessNode(heap_head_t* const _p_head)
{
	if (FCurentProcess)
		return;
	CHECK_NOTNULL(FBase);
	//filing process node
	process_node_t* const _process = MGetOrCreateProcessNode( _p_head, 0);
	LOG_IF(DFATAL,!_process) << "Cannot create the process node for "
										<< get_pid_optimized();
	(void)_process;
}

void CSharedAllocator::MCreateHeap(void* aBase, block_size_t aSize,size_t aReserv)
{
	VLOG(2) << "Create heap " << aBase << "; Size=" << aSize;
	CHECK_NOTNULL(aBase);
	if (!aBase)
		return;
	FBase = aBase;
	FReserv=aReserv;
	CHECK_GT(aSize, 2 * sizeof(block_node_t));
	uintptr_t const _heap_addr = (uintptr_t) FBase;
	// Ensure the heap starts on a correctly aligned boundary.
	uintptr_t const _cor_heap_addr = (uintptr_t) sMNextCoorectAddr<heap_head_t>(
			FBase);
	block_size_t const _heap_offset = static_cast<block_size_t>(_cor_heap_addr - _heap_addr);

	LOG_IF(WARNING,_heap_offset) << "Invalid memory alligment. "
											<< _heap_offset;

	heap_head_t* const _p_head = new ((void*) _cor_heap_addr) heap_head_t(
			aSize);

	block_size_t const _buf_size = aSize - _heap_offset - sizeof(heap_head_t)
			- sizeof(block_node_t);
	uintptr_t const _buf_addr = _cor_heap_addr + sizeof(heap_head_t);
	//filling first node
	block_node_t* const _first_node = new ((void*) _buf_addr) block_node_t();
	_first_node->MSetBlockSize(_buf_size);

	//creating shared mutex
	//The shared mutex name is consist of two part:
	//the first is - pid, the second random string
	{
		bool _is = FSem.MInit( _p_head->FSharedMutex,sizeof(_p_head->FSharedMutex), 1,
				CIPCSem::E_HAS_TO_BE_NEW);
		CHECK(_is);
		(void) _is;
	}
	{
		bool _is = FFreeSem.MInit(_p_head->FFreeSem, sizeof(_p_head->FFreeSem),
				CIPCSem::MAX_VALUE, CIPCSem::E_HAS_TO_BE_NEW, 0);
		CHECK(_is);
		(void) _is;
	}
	//filling heap_head_t struct
	_p_head->MSetFirstNode(sMOffsetFromBase<void>((void*) _buf_addr, FBase));
	_p_head->FFreeBytesRemaining = _first_node->FBlockSize;
	//paranoic check of fisrt node addr
	CHECK_EQ(
			(uintptr_t )sMNextCoorectAddr<heap_head_t>(FBase)
					+ sizeof(heap_head_t),
			(uintptr_t )sMPointerFromBase<block_node_t>(_p_head->FFOffsetFirstNode,
					FBase));
	//paranoic check of size free bloks
	CHECK_EQ(_first_node->FBlockSize,
			_heap_addr + aSize - _buf_addr - sizeof(block_node_t));
	//filing process node
	MInitProcessNode(_p_head);
	_p_head->MFillCRC();
}
CSharedAllocator::nodes_proc_t	//
CSharedAllocator::MSearchProcessNode(
		heap_head_t* const aHead, unsigned aPid) const
{
	nodes_proc_t _rval;
	process_node_t * _p = aHead->MFirstProcessNode(FBase);
	process_node_t * _p_prev = NULL;
	for (; _p != NULL && _p->FPid != aPid;)
	{
		_p_prev = _p;
		_p = _p->MNext(FBase);
	}
	_rval.first = _p;
	_rval.second = _p_prev;
	return _rval;
}
CSharedAllocator::process_node_t *	//
CSharedAllocator::MSearchProcessOfBlockNode(
		heap_head_t* const aHead,block_node_t * aNode) const
{
	offset_t const _offset_in_array=aNode->FIndexOfOffset;
	offset_t const _offset= sMOffsetFromBase(sMGetPointerOfBlockNode(aNode), FBase);

	process_node_t * _p = aHead->MFirstProcessNode(FBase);
	for (; _p != NULL && !_p->MIsOffset(_offset_in_array,_offset);)
	{
		_p = _p->MNext(FBase);
	}
	return _p;
}

CSharedAllocator::process_node_t * const CSharedAllocator::MCreateProcessNode(
		heap_head_t* const aHead) const
{
	const unsigned _pid = get_pid_optimized();
	nodes_proc_t _prs = MSearchProcessNode(aHead, _pid);
	LOG_IF(DFATAL,_prs.first) << "The process node has been malloced.";
	LOG_IF(INFO,!_prs.first) << "The new process is mallocing memory.";

	//create new process node
	void *_new_p = MMallocBlock(aHead, DEF_PROCESS_SIZE, true);
	LOG_IF(ERROR, !_new_p) << "Can not allocate memory for process struct.";
	if (!_new_p)
		return NULL;
	else
	{
		CHECK_NOTNULL(_new_p);
		_prs.first = new (_new_p) process_node_t(_pid, DEF_PROCESS_SIZE,
				FReserv);
		if (FReserv > 0)
		{
			block_node_t *_reserv=MCreateReservForProcess(_prs.first,aHead);
			if(!_reserv)
			{
				LOG(FATAL)<<"Cannot create reserv for "<<_prs.first->FPid;
				//todo add info to head, and malloc the free method called
			}else
				_prs.first->FUsedUpReserv=0;
		}
		MInsertProcessNode(aHead, _prs);
		return _prs.first;
	}

}
CSharedAllocator::block_node_t * const CSharedAllocator::MCreateReservForProcess(
		process_node_t* aProc,heap_head_t* const aHead) const
{
	VLOG(2) << "Allocate reserv for " << aProc->FPid << " equal of "
						<< aProc->FSizeOfReserv;
	CHECK_EQ(aProc->FUsedUpReserv,(uint32_t) -1);

	void *_new_p = MMallocBlock(aHead, aProc->FSizeOfReserv/*+sizeof(block_node_t)*/, true);
	if(!_new_p)
		return NULL;
	offset_t const _offset = sMOffsetFromBase(_new_p, FBase);
	VLOG(2) << "Pid of reserv Offset=" << sMOffsetFromBase(_new_p, FBase);
	//		_process->MPutOffset(_offset);
	block_node_t* _node = sMGetBlockNode(_new_p);
	_node->FIndexOfOffset = aProc->MPutOffset(_offset);
	_node->FReservedFlag=true;
	_node->FReserveFree=true;
	return _node;
}
CSharedAllocator::nodes_proc_t& CSharedAllocator::MEraseProcessNode(
		heap_head_t* const aHead, nodes_proc_t& _proc) const
{
	if (_proc.second)
		_proc.second->MSetNextNode(_proc.first->FNextNode);
	else
		//it's the first node
		aHead->FOffsetToProcessNode = _proc.first->FNextNode;
	return _proc;
}

CSharedAllocator::nodes_proc_t& CSharedAllocator::MInsertProcessNode(
		heap_head_t* const aHead, nodes_proc_t& _prs) const
{
	offset_t const _offset = sMOffsetFromBase(_prs.first, FBase);

	if (!_prs.second) //if the first process node
		aHead->FOffsetToProcessNode = _offset;
	else
		_prs.second->MSetNextNode(_offset);
	return _prs;
}
CSharedAllocator::process_node_t * const CSharedAllocator::MGetOrRealocateProcessNode(process_node_t *aProccess, heap_head_t* const aHead, int aCount) const
{
	CHECK_NOTNULL(FBase);
	if (aCount > 0
			&& (aProccess->FAlloactionCount + aCount)
					> aProccess->FArraySize)
	{
		process_node_t *_old_node=aProccess;
		VLOG(2) << "realocate process node.";
		//The allocation memory for the new process node is
		//similar to resize  of vector.
		block_size_t const _requred_memory =
				sizeof(process_node_t)
						+ static_cast<block_size_t>((static_cast<double>(_old_node->FAlloactionCount
								+ aCount) * sizeof(_old_node->FOffsets[0]))
								* PROCESS_ARRAY_FACTOR);
		void *_new_p = MMallocBlock(aHead, _requred_memory, true);

		//create the new process node and fill it
		aProccess = new (_new_p) process_node_t(
				_old_node, _requred_memory);

		//replace the old process node to the new in the process list
		nodes_proc_t _prs = MSearchProcessNode(aHead, _old_node->FPid);
		_prs.first = aProccess;
		MInsertProcessNode(aHead, _prs);

		//Give back the memory of the old process node.
		//The pid of the process node is reseted to zero for safety only.
		*const_cast<pid_type*>(&_old_node->FPid) = 0;
		MFreeBlock(aHead, _old_node);
	}

	return aProccess;
}
CSharedAllocator::process_node_t * const CSharedAllocator::MGetOrCreateProcessNode( heap_head_t* const aHead, int aCount) const
{
	CHECK_NOTNULL(FBase);
	//The Process node has to been looked every time as
	//It can be relocated by the other object of current process.
	if (FCurentProcess)
		return FCurentProcess = MGetOrRealocateProcessNode(FCurentProcess,
				aHead, aCount);//fixme the node

	const unsigned _pid = get_pid_optimized();
	nodes_proc_t _prs = MSearchProcessNode(aHead, _pid);

	//if the node is not exist, it's to be created
	if (!_prs.first)
		_prs.first=MCreateProcessNode(aHead);
	else
	{
		VLOG(2)<<"SizeOf reserv "<<_prs.first->FSizeOfReserv<<" used "<<_prs.first->FUsedUpReserv;
	}
	CHECK_NOTNULL(_prs.first);

	//If the function is called for the first time,
	//it increase the number of process node holders(smart pointer for node)
	atomic_inc32(&_prs.first->FCount);
	VLOG(2) << "Increase counter for " << _prs.first->FPid << " counter="
						<< (unsigned) _prs.first->FCount;



	//if the new offset is added and there is not free space in the array.
	FCurentProcess=MGetOrRealocateProcessNode(_prs.first,aHead,aCount);
	CHECK_NOTNULL(FCurentProcess);

	CHECK_EQ(get_pid_optimized(),FCurentProcess->FPid);

	return FCurentProcess;
}

CSharedAllocator::heap_head_t* const CSharedAllocator::sMGetHead(
		void* const aBase)
{
	// Ensure the heap starts on a correctly aligned boundary.
	const uint64_t _cor_heap_addr = (uintptr_t) (sMNextCoorectAddr<heap_head_t>(
			aBase));
	heap_head_t* const _p_head =
			reinterpret_cast<struct heap_head_t*>(_cor_heap_addr);
	return _p_head;
}
void* CSharedAllocator::MMallocTo(block_size_t const xWantedSize,
		offset_t aRefOffset)
{
	LOG_IF(ERROR,!xWantedSize) << "The size is null.";
	if (xWantedSize == 0)
		return NULL;
	VLOG(2) << "MMalloc is called for " << xWantedSize;

	CRAII<CSharedAllocator> _block(*this);
	CHECK_NOTNULL(FBase);
	heap_head_t* const _p_head = sMGetHead(FBase);
	offset_t const _offset = MConvertOffsetToBase(_p_head, aRefOffset);

	//try to malloc
	void *_pmemory = MMallocImpl(_p_head, xWantedSize, _offset,false);
	VLOG_IF(2,_pmemory) << "The memory was malloced to " << aRefOffset;
	return _pmemory;
}
void* CSharedAllocator::MGetIfMalloced(offset_t aRefOffset)
{
	VLOG(2) << "MGetIfMalloced is called for " << aRefOffset;

	CRAII<CSharedAllocator> _block(*this);
	CHECK_NOTNULL(FBase);
	heap_head_t* const _p_head = sMGetHead(FBase);
	offset_t const _offset = MConvertOffsetToBase(_p_head, aRefOffset);
	//locking for memory
	if(MIsAllocatedImpl(_offset))
		return sMPointerFromBase<void*>(_offset, FBase);

	VLOG(2)<<"The memory "<<aRefOffset<<" is not founded.";
	return NULL;

}
std::string  CSharedAllocator::sMPrintAsXml(CSharedAllocator const* aFrom)
{
	NSHARE::CConfig _conf;
	shared_info_t _shared_info;
	aFrom->MGetInfoImpl(_shared_info);
	//as the mutex will be locked in MSerialize function , it  cannot be used
	aFrom->MSerializeImpl(_conf,_shared_info);
	std::stringstream _buf;
	_conf.MToXML(_buf,true);
	return _buf.str();
}
void CSharedAllocator::MInitIfNeedFreeSem(heap_head_t* const _p_head)
{
	if (!FFreeSem.MIsInited())
	{
		FFreeSem.MInit(_p_head->FFreeSem,sizeof(_p_head->FFreeSem), CIPCSem::MAX_VALUE,CIPCSem::E_HAS_EXIST);
		CHECK(FFreeSem.MIsInited());
		if (FFreeSem.MGetType() == CIPCSem::E_HAS_TO_BE_NEW)//It has been created
		{
			//DCHECK_EQ(atomic_read32(&_p_head->FNumberOfWaitingFor), atomic_read32(&_p_head->FPostCount));
			atomic_write32(&_p_head->FNumberOfWaitingFor, 0);
			atomic_write32(&_p_head->FPostCount, 0);
		}
	}

}
void* CSharedAllocator::MReallocate(void* aPtr,block_size_t aSize,bool aBlock,bool aFromReserv)
{
	if(aPtr==NULL)
		return MMalloc(aSize,aBlock,aFromReserv);
	if(aSize==0)
	{
		MFree(aPtr);
		return NULL;
	}
	block_node_t* const _p_node = sMGetBlockNode(aPtr);
	size_t const _size = _p_node->FBlockSize&~BLOCK_ALLOCATED_BIT;

	if(_size>=aSize)//fixme
		return aPtr;

	void* _p=MMalloc(aSize,aBlock,aFromReserv);//fixme
	if(!_p)
		return _p;

	memcpy(_p,aPtr,_size);
	MFree(aPtr);
	return _p;
}
void* CSharedAllocator::MMalloc(block_size_t const xWantedSize,bool aBlock,bool aFromReserv)
{
	LOG_IF(ERROR,!xWantedSize) << "The size is null.";
	if (xWantedSize == 0)
		return NULL;
	VLOG(2) << "MMalloc is called for " << xWantedSize;
	void* _p=NULL;


	CRAII<CSharedAllocator> _block(*this);
	do
	{

		CHECK_NOTNULL(FBase);
		heap_head_t* const _p_head = sMGetHead(FBase);

		if (xWantedSize > _p_head->FMaxSize)
		{
			LOG(ERROR)<<"The required size "<<xWantedSize<<" bytes is more than max available size of SM "<<_p_head->FMaxSize<<" bytes";
			break;
		}

		_p = MMallocImpl(_p_head, xWantedSize, 0,aFromReserv);

		if (aBlock && !_p)
		{
			VLOG(5) << sMPrintAsXml(this);
			aBlock = _p_head->MIsCanBeMAllocated() || (aFromReserv&&FReserv >= xWantedSize );//Usually always true
			if (aBlock)
			{
				VLOG(1) << "The number of waiting for "
									<< _p_head->FNumberOfWaitingFor
									<< " post = " << _p_head->FPostCount;

				aBlock = MWaitFreeOperation(_p_head);
			}
			LOG_IF(INFO,!aBlock) << "Cannot allocate " << xWantedSize
											<< " info " << sMPrintAsXml(this);
		}
		else if (!_p)
		{
			LOG(INFO)<<"Cannot allocate "<<xWantedSize<<" info "<<sMPrintAsXml(this);
		}
	}while( aBlock && !_p);
	return _p;
}
bool CSharedAllocator::MWaitFreeOperation(heap_head_t* const _p_head)
{
	//fixme check for windows
//			const int _val = FFreeSem.MValue();
//			if (_val == 0)
	atomic_inc32(&_p_head->FNumberOfWaitingFor);
	volatile const uint32_t _old= atomic_read32(&_p_head->FPostCount);
//			else
//				LOG(ERROR)<<"Wtf? The semaphore value is not zero.Value="<<_val;

	//fixme wait for the memory will be freed
	if (MUnlock())
	{
		bool _is=false;
		do
		{
			_is=FFreeSem.MWait();
		} while (_is&&_old == atomic_read32(&_p_head->FPostCount));//if is not locked on Sem then FPostCount don't changed
		LOG_IF(FATAL,!_is)<<"Cannot wait sem "<<FFreeSem.MName();
		//atomic_dec32(&_p_head->FNumberOfWaitingFor);
		MLock();
	}
	else
	{
		atomic_dec32(&_p_head->FNumberOfWaitingFor);
		LOG(ERROR)<<"Cannot unlock the semaphore.  ignoring blocking mode.";
		return false;
	}
	return true;
}
//inform the other thread what  the memory has been freed
void CSharedAllocator::MInformMemFreed(heap_head_t* const _p_head)
{
	CHECK_LE(_p_head->FPostCount, _p_head->FNumberOfWaitingFor);
	unsigned _num = atomic_read32(&_p_head->FNumberOfWaitingFor)
			- atomic_read32(&_p_head->FPostCount);
	CHECK_LT((int )_num, CIPCSem::MAX_VALUE);
	for (; _num; --_num)
	{
		atomic_inc32(&_p_head->FPostCount);
		bool const _is=FFreeSem.MPost();
		LOG_IF(FATAL,!_is)<<"Cannot post sem "<<FFreeSem.MName();
		VLOG(5) << "Posted free semaphore. "<<_num<<" Waiters:" << _p_head->FNumberOfWaitingFor;
	}
	//DLOG_IF(ERROR,FFreeSem.MValue()>0)<<"Wtf? The semaphore value is greater of zero.";
}
void CSharedAllocator::MUnkeepBlock(block_node_t * _node,
		process_node_t* const _process) const
{
	_process->MPopOffsetById(_node->FIndexOfOffset);
}
void CSharedAllocator::MKeepBlock(block_node_t * _node, process_node_t*const  _process) const
{
	offset_t const _offset = sMOffsetFromBase(sMGetPointerOfBlockNode(_node),
			FBase);
	_node->FIndexOfOffset = _process->MPutOffset(_offset);
}
void* CSharedAllocator::MMallocImpl(heap_head_t* const _p_head,
		block_size_t const xWantedSize, offset_t aOffset, bool aUseReserv)
{
	VLOG_IF(2,xWantedSize > _p_head->FFreeBytesRemaining)
																	<< "There is not free memory. Remain "
																	<< _p_head->FFreeBytesRemaining;
	if (xWantedSize > _p_head->FMaxSize)
	{
		LOG(ERROR)<<"The required size "<<xWantedSize<<" bytes is more than max available size of SM "<<_p_head->FMaxSize<<" bytes";
		return NULL;
	}
	void *_pmemory = NULL;
	//MInitProcessNode(_p_head);
	process_node_t * const _process = MGetOrCreateProcessNode(_p_head, 1);
	if (!_process)
	{
		VLOG(2) << "Cannot allocate process node";
		return NULL;
	}
	VLOG_IF(5,xWantedSize > _p_head->FFreeBytesRemaining)
																	<< "no free memory for "
																	<< xWantedSize
																	<< " remain= "
																	<< _p_head->FFreeBytesRemaining;
	if (xWantedSize <= _p_head->FFreeBytesRemaining)
	{
		_pmemory = MMallocBlock(_p_head, xWantedSize, false, aOffset);
		LOG_IF(INFO,_pmemory) << "The " << xWantedSize
										<< " bytes memory is  allocated succesfully for "
										<< _process->FPid << ". Remain "
										<< _p_head->FFreeBytesRemaining
										<< " bytes." << " Ponter = "
										<< _pmemory;
		LOG_IF(WARNING,!_pmemory) << "There are not memory if allocating "
											<< xWantedSize
											<< " bytes by offset =" << aOffset
											<< ". Remain "
											<< _p_head->FFreeBytesRemaining;
		if (_pmemory)
		{
			MKeepBlock(sMGetBlockNode(_pmemory),_process);
			_p_head->MIncUserAllocation();
		}
	}
	if (_pmemory == NULL && aUseReserv
			&& _process->FUsedUpReserv != RESERV_IS_NOT_ALLOCATED
			&& _process->FSizeOfReserv > 0)
	{
		CHECK_LE(_process->FUsedUpReserv, _process->FSizeOfReserv);
		const uint32_t _remain = _process->FSizeOfReserv
				- _process->FUsedUpReserv;
		VLOG(2) << "Trying allocate memory to reserve. Reserv=" << _remain
							<< " What size=" << xWantedSize;
		if (_remain >= xWantedSize)
		{
			VLOG(2) << "Ok the reserve is exist.";
			_pmemory = MMallocBlockFromReserv(_p_head, _process,
					xWantedSize);

			LOG_IF(INFO,_pmemory) << "The " << xWantedSize
											<< " bytes memory is  allocated from reserve for "
											<< _process->FPid << ". Remain "
											<< (_process->FSizeOfReserv
													- _process->FUsedUpReserv)
											<< " bytes." << " Ponter = "
										<< _pmemory;
		}
	}

	return _pmemory;
}

size_t CSharedAllocator::MFreeImpl(void* aP, heap_head_t* const _p_head,
		process_node_t* _p)
{
	//The memory being freed  have an block_node_t structure before it.
	block_node_t* const _p_node = sMGetBlockNode(aP);
	offset_t const _offset = sMOffsetFromBase(aP, FBase);
	// Check if the block is actually allocated.
	LOG_IF(FATAL,(_p_node->FBlockSize & BLOCK_ALLOCATED_BIT)== 0) << " The "
																			<< MOffset(
																					aP)
																			<< " is not allocated. Pid "
																			<< MSearchProcessOfBlockNode(
																					_p_head,
																					_p_node);

	//looking for the process node for the block
	if (!_p)
		_p = MSearchProcessOfBlockNode(_p_head, _p_node);
	else
		LOG_IF(DFATAL,!_p->MIsOffset(_p_node->FIndexOfOffset,_offset))
																				<< "Invalid pid of node ";

	CHECK_NOTNULL(_p);
//	CHECK_EQ(_p->FPid,_pid);
	size_t _rval=0;
	if (!_p_node->FReservedFlag
			|| _p_node->FReserveFree/*remove reserve forever*/)
	{
		//Now The process is not hold the memory
		VLOG(5) << "Pid Offset=" << sMOffsetFromBase(_p, FBase);
		MUnkeepBlock(_p_node,_p);

		//_p->MPopOffset(_offset);

		if (_p_node->FReserveFree)
			_p->FSizeOfReserv = 0;
		else
			_p_head->MDecUserAllocation();

		//The memory is freed
		_rval = MFreeBlock(_p_head, aP);
		VLOG(1)<<"The "<<FBase<<" pointer being allocated by "<<_p->FPid
		<<" is deallocated successfully by " <<get_pid_optimized()
		<<". Remain "<<_p_head->FFreeBytesRemaining<<" bytes.";
	}
	else
		MFreeReservedBlock(_offset, _p_node, _p);
	return _rval;
}
void CSharedAllocator::MFreeReservedBlock(const offset_t _offset,
		block_node_t* _p_node, process_node_t* _p)
{
	VLOG(2) << "Free reserved memory.";
	CHECK(!_p_node->FReserveFree);

	block_node_t* _prev = NULL;
	block_node_t* _next = NULL;

	for (unsigned i = 0; i < _p->FArraySize && _next == NULL; ++i)
		if (!is_null_offset(_p->FOffsets[i].FNextNode))
		{
			VLOG(2) << "Allocated offset " << _p->FOffsets[i].FNextNode;
			block_node_t* _node = MGetBlockNode(_p->FOffsets[i].FNextNode);
			DCHECK_EQ(_node->FIndexOfOffset, i);
			DCHECK_NE((_node->FBlockSize & BLOCK_ALLOCATED_BIT), 0);

			if (_node->FIndexOfOffset == i && _node->FReservedFlag
					&& _node->FReserveFree)
			{
				if (_offset > _p->FOffsets[i].FNextNode)
				{
					_prev = _node;
				}
				else if (_offset < _p->FOffsets[i].FNextNode)
				{
					_next = _node;
				}

			}
		}
	//for safety reset flags
	_p_node->FBlockSize &= (~BLOCK_ALLOCATED_BIT);
	if (_prev)
		_prev->FBlockSize &= (~BLOCK_ALLOCATED_BIT);
	if (_next)
		_next->FBlockSize &= (~BLOCK_ALLOCATED_BIT);

	VLOG(2) << "Cur reserv=" << _p->FUsedUpReserv << " add "
						<< _p_node->FBlockSize << " prev=" << _prev << " next="
						<< _next;

	atomic_add(&_p->FUsedUpReserv, 0 - _p_node->FBlockSize);
	//merge
	if (_prev
			&& (((uint8_t *) _prev + sizeof(block_node_t) + _prev->FBlockSize)
					== (uint8_t *) _p_node))
	{
		VLOG(2)
							<< "Create one big reserve block from the two reserve blocks.";
		MUnkeepBlock(_p_node,_p);
		_prev->MSetBlockSize(
				_prev->FBlockSize + _p_node->FBlockSize + sizeof(block_node_t));
		_p_node = _prev;
		_prev = NULL;
		atomic_add(&_p->FUsedUpReserv, 0 - sizeof(block_node_t));
		//remove from
	}
	if (_next
			&& (((uint8_t *) _p_node + sizeof(block_node_t)
					+ _p_node->FBlockSize) == (uint8_t *) _next))
	{
		VLOG(2)
							<< "Create one big reserve block from the two reserve blocks.";
		MUnkeepBlock(_next,_p);
		_p_node->MSetBlockSize(
				_p_node->FBlockSize + _next->FBlockSize + sizeof(block_node_t));
		_next = NULL;
		atomic_add(&_p->FUsedUpReserv, 0 - sizeof(block_node_t));
	}

	_p_node->FReserveFree = 1;
	_p_node->FBlockSize |= (BLOCK_ALLOCATED_BIT);
	if (_prev)
		_prev->FBlockSize |= (BLOCK_ALLOCATED_BIT);
	if (_next)
		_prev->FBlockSize |= (BLOCK_ALLOCATED_BIT);
}
size_t CSharedAllocator::MFree(void *aP)
{
	LOG_IF(ERROR,!aP) << "Try to free memory of null pointer.";
	if (!aP)
		return 0;
	CHECK_NOTNULL(FBase);
	CRAII<CSharedAllocator> _block(*this);
	heap_head_t* const _p_head = sMGetHead(FBase);
	if (aP <= FBase
			|| _p_head->FMaxSize < (size_t) ((uint8_t*) aP - (uint8_t*) FBase))
	{
		LOG(DFATAL)<<"Segmentation failed "<<aP;
		return 0;
	}
	VLOG(2) << "Free " << aP << " (" << MOffset(aP) << ")";

	const size_t _size=MFreeImpl(aP, _p_head, NULL);
	MInformMemFreed(_p_head);
	return _size;
}
//nodes_block_t
CSharedAllocator::nodes_block_t CSharedAllocator::MGetFreeBlockFromBegin(
		offset_t const aOffset, uint32_t const _alligment_size,
		heap_head_t* const _p_head) const
{
	// If !aOffset traverse the list from the start	(lowest address) block until
	// one	of adequate size is found.
	//in the other case try to insert a new block to list from the  fixed offset
	VLOG(2) << "Allocate memory from begin.Alligment Size="
						<< _alligment_size << ";aOffset=" << aOffset;

	nodes_block_t _nodes(_p_head->MFirstBlockNode(FBase), NULL);
	VLOG_IF(2,_nodes.first) << "Start block " << _nodes.first << " "
									<< *_nodes.first;
	VLOG_IF(2,!_nodes.first) << "Start block is null.";

	if (!aOffset)
		for (; _nodes.first && (_nodes.first->FBlockSize < _alligment_size);)
		{
			_nodes.second = _nodes.first;
			VLOG(2) << "Prev block " << *_nodes.second;
			_nodes.first = _nodes.first->MNext(FBase);

			VLOG(2) << "NEXT block " << _nodes.first;
			CHECK_EQ(sMNextCoorectAddr<block_node_t>(_nodes.first),
					(void* )_nodes.first);
			CHECK(
					!_nodes.first
							|| (uint8_t* )_nodes.first
									>= (uint8_t* )(_p_head + 1));
		}
	else
	{
		block_node_t* _it = _nodes.first;
		_nodes.first = NULL;
		//locking for the first block which The offset is more then requirement.
		for (; _it; _it = _it->MNext(FBase))
		{
			CHECK_EQ(sMNextCoorectAddr<block_node_t>(_it), (void* )_it);
			CHECK_LT(_it->FBlockSize, _p_head->FMaxSize);
			VLOG(2) << "NEXT block " << _it;

			if (sMOffsetFromBase(_it, FBase) < aOffset)
			{
				_nodes.second = _nodes.first;
				_nodes.first = _it;
				VLOG_IF(2,_nodes.second) << "Prev block " << *_nodes.second;
				VLOG(2) << "The block " << *_nodes.first;
			}
		}
		//if founded block offset is not equal of requirement offset
		//the new block is created.
		if (_nodes.first
				&& (sMOffsetFromBase(_nodes.first, FBase) + sizeof(block_node_t))
						!= aOffset)
		{
			VLOG(2) << "The block offset is not equal of requirement offset."
								<< _nodes.first << "; "
								<< sMOffsetFromBase(_nodes.first, FBase)
								<< " >> " << aOffset;
			const offset_t _buf_offset = sMOffsetFromBase(_nodes.first, FBase)
					+ sizeof(block_node_t);
			CHECK_GE(aOffset, _buf_offset);

			//check for the new block can be inserted into the free list
			if ((_buf_offset + sizeof(block_node_t)) > aOffset)
			{
				_nodes.first = NULL;
				return _nodes;
			}

			//check for enough memory
			block_size_t const _req_size = aOffset - _buf_offset
					+ _alligment_size + sizeof(block_node_t);
			if (_req_size > _nodes.first->FBlockSize)
			{
				_nodes.first = NULL;
				return _nodes;
			}

			const size_t _block_size = _nodes.first->FBlockSize;
			(void) _block_size;

			//The new block is  inserting into the free  block list behind _nodes.first
			block_node_t *pxNewBlockLink =
					new (((uint8_t *) _nodes.first) + aOffset - _buf_offset) block_node_t();

			CHECK_EQ(sMNextCoorectAddr<block_node_t>(pxNewBlockLink),
					(void* )pxNewBlockLink);

			pxNewBlockLink->MSetBlockSize(
					_nodes.first->FBlockSize - (aOffset - _buf_offset));
			_nodes.first->MSetBlockSize(
					aOffset - _buf_offset - sizeof(block_node_t));
			pxNewBlockLink->MSetNextNode(_nodes.first->FNextNode);
			_nodes.first->MSetNextNode(sMOffsetFromBase(pxNewBlockLink, FBase));

			CHECK_EQ(sMOffsetFromBase((pxNewBlockLink + 1), FBase), aOffset);

			//now the allocated block is pxNewBlockLink
			//instead of _nodes.first
			_nodes.second = _nodes.first;
			_nodes.first = pxNewBlockLink;

			//paranoid check
			CHECK_EQ(_block_size,
					_nodes.second->FBlockSize + _nodes.first->FBlockSize
							+ sizeof(block_node_t));
			CHECK_EQ(sMOffsetFromBase(_nodes.first + 1, FBase), aOffset);
			CHECK_GE(_nodes.first->FBlockSize, _alligment_size);
		}
		else if (_nodes.first && _nodes.first->FBlockSize < _alligment_size)
		{
			LOG(DFATAL)<<"The block size is less than requrement. "<<_nodes.first->FBlockSize<<" < "<<_alligment_size;
			_nodes.first = NULL;
		}
	}
	return _nodes;
}
CSharedAllocator::nodes_block_t CSharedAllocator::MGetFreeBlockFromEnd(
		uint32_t _alligment_size, heap_head_t* const _p_head) const
{
	//Traverse the list from the start block to the end, and save
	//the latest one of adequate size.
	VLOG(2) << "Allocate memory from end.Size=" << _alligment_size;
	nodes_block_t _result(NULL, NULL);
	nodes_block_t _tmp;
	_tmp.first = _p_head->MFirstBlockNode(FBase);
	_tmp.second = NULL;
	VLOG_IF(2,_tmp.first) << "Start block " << _tmp.first << " " << *_tmp.first;
	VLOG_IF(2,!_tmp.first) << "Start block is null.";
	for (; _tmp.first;
			_tmp.second = _tmp.first, _tmp.first = _tmp.first->MNext(FBase))
	{
		CHECK_EQ(sMNextCoorectAddr<block_node_t>(_tmp.first),
				(void* )_tmp.first);
		CHECK_GE((uint8_t* )_tmp.first, (uint8_t* )(_p_head + 1));
		CHECK_EQ((_tmp.first->FBlockSize & BLOCK_ALLOCATED_BIT), 0);
		CHECK_LT(_tmp.first->FBlockSize, _p_head->FMaxSize);

		VLOG(2) << "NEXT block " << _tmp.first;

		if ((_tmp.first->FBlockSize > _alligment_size))
		{
			_result = _tmp;
			VLOG_IF(2,_tmp.second) << "Prev block " << *_tmp.second;
			VLOG(2) << "The block " << *_tmp.first;
		}
	}
	return _result;
}
void CSharedAllocator::MEraseNodeFromFreeList(const nodes_block_t& _nodes,
		heap_head_t* const _p_head) const
{
	//erase node from the free memory list
	if (_nodes.second)
		_nodes.second->MSetNextNode(_nodes.first->FNextNode);
	else
		//it is not the first node
		//if there is the extra free  memory in the single node
		//the new block will be created.
		//otherwise NULL_OFFSET is indicated that  no free memory
		_p_head->MSetFirstNode(_nodes.first->FNextNode);
	atomic_add(&_p_head->FFreeBytesRemaining, 0 - _nodes.first->FBlockSize);
//	atomic_write32(&_p_head->FFreeBytesRemaining,atomic_read32(&_p_head->FFreeBytesRemaining));
}
CSharedAllocator::block_node_t* CSharedAllocator::MSplitInto2Block(
		block_node_t *& aWho, uint32_t _alligment_size, bool aFromEnd,
		heap_head_t* const _p_head) const
{
	block_node_t* pxNewBlockLink = NULL;
	if (aWho->FBlockSize > (_alligment_size + 2 * sizeof(block_node_t)))
	{
		const block_size_t _size = aWho->FBlockSize - _alligment_size
				- sizeof(block_node_t);
		if (!aFromEnd)
		{
			VLOG(2)
								<< "The new block is inserted into memory from the begin";
			pxNewBlockLink =
					new (
							((uint8_t *) aWho) + _alligment_size
									+ sizeof(block_node_t)) block_node_t();
		}
		else
		{
			VLOG(2) << "The new block is inserted into memory from the end";
			pxNewBlockLink =
					new (
							((uint8_t *) aWho) + aWho->FBlockSize
									- _alligment_size) block_node_t();
			//The block being allocated is inserting into the free list block back.
			//pxNewBlockLink is the "returning" block now.
			std::swap(pxNewBlockLink, aWho);
		}
		pxNewBlockLink->MSetBlockSize(_size);
		aWho->MSetBlockSize(_alligment_size);

		CHECK_EQ(sMNextCoorectAddr<block_node_t>(pxNewBlockLink),
				(void* )pxNewBlockLink);
		LOG_IF(DFATAL,((void*)pxNewBlockLink < (void*)(_p_head+1)) || //
				(_p_head->FMaxSize < (sMOffsetFromBase(pxNewBlockLink,FBase)+pxNewBlockLink->FBlockSize+sizeof(block_node_t)))) //
		<< "Segmentation failed " << pxNewBlockLink; //
	}
	return pxNewBlockLink;
}
void CSharedAllocator::MSplitBlockAndUpdateList(nodes_block_t& _nodes,
		uint32_t _alligment_size, bool aFromEnd,
		heap_head_t* const _p_head) const
{
	VLOG(2) << "This block is to be split into two."
			"Create a new 	block following the number of bytes requested";
	block_node_t * const pxNewBlockLink = MSplitInto2Block(_nodes.first,
			_alligment_size, aFromEnd, _p_head);
	if (pxNewBlockLink)
		MInsertIntoFreeList(_p_head, pxNewBlockLink, _nodes.second);
}
void * CSharedAllocator::MMallocBlockFromReserv(
		heap_head_t* const _p_head, process_node_t * const aProc,
		block_size_t const xWantedSize) const
{
	CHECK_NOTNULL(FBase);
	LOG_IF(ERROR,!xWantedSize) << "The size is null.";
	if (xWantedSize == 0)
		return NULL;
	VLOG(2) << "Requred size " << xWantedSize;
	CHECK_EQ((xWantedSize & BLOCK_ALLOCATED_BIT), 0);

	uint32_t _alligment_size = xWantedSize;
	// Ensure that blocks are always aligned to the required number
	//of bytes.
	const offset_t _offset = (offset_t) _alligment_size
			% __alignof(block_node_t);
	if (_offset > 0)
	{
		_alligment_size += __alignof(block_node_t) - _offset;
		CHECK_EQ(_alligment_size % __alignof(block_node_t), 0);
	}

	if (_alligment_size > aProc->FSizeOfReserv)
		return NULL;
	VLOG(2) << "Alligment block size " << _alligment_size;
	block_node_t * _free_node = NULL;

	for (unsigned i = 0; i < aProc->FArraySize && _free_node == NULL; ++i)
		if (!is_null_offset(aProc->FOffsets[i].FNextNode))
		{
			VLOG(2) << "Allocated offset " << aProc->FOffsets[i].FNextNode;
			block_node_t* _node = MGetBlockNode(aProc->FOffsets[i].FNextNode);
			DCHECK_EQ(_node->FIndexOfOffset, i);
			DCHECK_NE((_node->FBlockSize & BLOCK_ALLOCATED_BIT), 0);

			if (_node->FIndexOfOffset == i && _node->FReservedFlag
					&& _node->FReserveFree)
			{
				size_t const _size = _node->FBlockSize & (~BLOCK_ALLOCATED_BIT);
				VLOG(2) << "There is reserved block "
									<< aProc->FOffsets[i].FNextNode << " Size="
									<< _size;
				if (_size >= _alligment_size)
				{
					VLOG(2) << "Can allocate data to reserve.";
					_free_node = _node;
				}
			}
		}
	if (_free_node == NULL)
	{
		VLOG(2) << "No free reserved block";
		return _free_node;
	}
	_free_node->FBlockSize &= (~BLOCK_ALLOCATED_BIT);	//for safety reset flags

	atomic_add(&aProc->FUsedUpReserv, _free_node->FBlockSize);

	block_node_t* _new_block = MSplitInto2Block(_free_node, _alligment_size,
			false, _p_head);
	if (_new_block)
	{
		VLOG(2) << "The reserved block has been split.";
		atomic_add(&aProc->FUsedUpReserv, 0 - _new_block->FBlockSize);

		_new_block->FReservedFlag = 1;
		_new_block->FReserveFree = 1;
		_new_block->FBlockSize |= BLOCK_ALLOCATED_BIT;

		MKeepBlock(_new_block,aProc);
	}

	_free_node->FReservedFlag = 1;
	_free_node->FReserveFree = 0;
	_free_node->FBlockSize |= BLOCK_ALLOCATED_BIT;

	return sMGetPointerOfBlockNode(_free_node);
}
void *CSharedAllocator::MMallocBlock(heap_head_t* const _p_head,
		block_size_t const xWantedSize, bool aFromEnd, offset_t aOffset) const
{
	CHECK_NOTNULL(FBase);
	LOG_IF(ERROR,!xWantedSize) << "The size is null.";
	if (xWantedSize == 0)
		return NULL;

	VLOG(2) << "Requred size " << xWantedSize;
	CHECK_EQ((xWantedSize & BLOCK_ALLOCATED_BIT), 0);

	block_size_t _alligment_size = xWantedSize;
	// Ensure that blocks are always aligned to the required number
	//of bytes.
	const offset_t _offset = (offset_t) _alligment_size
			% __alignof(block_node_t);
	if (_offset > 0)
	{
		_alligment_size += __alignof(block_node_t) - _offset;
		CHECK_EQ(_alligment_size % __alignof(block_node_t), 0);
	}

	if (_alligment_size > _p_head->FFreeBytesRemaining)
		return NULL;
	VLOG(2) << "Alligment block size " << _alligment_size;
	// If !aFromEnd && !aOffset traverse the list from the start	(lowest address) block until
	// one	of adequate size is found.
	//if "aFromEnd" traverse the list from the start block to the end, and save
	//the latest one of adequate size.
	//in the other case try to insert a new block to list from the  fixed offset

	//first the curent node,second - the prev node
	nodes_block_t _nodes(NULL, NULL);
	if (!aFromEnd)
		_nodes = MGetFreeBlockFromBegin(aOffset, _alligment_size, _p_head);
	else
	{
		CHECK_EQ(aOffset, 0);
		_nodes = MGetFreeBlockFromEnd(_alligment_size, _p_head);
	}
	CHECK_EQ(sMNextCoorectAddr<block_node_t>(_nodes.first),
			(void* )_nodes.first);
	if (!_nodes.first)
	{
		VLOG_IF(1,!aOffset) << "There is not free memory block.";
		LOG_IF(ERROR,aOffset) << "The block by " << aOffset << " is not exist";
		return _nodes.first;
	}
	CHECK_GE((uint8_t* )_nodes.first, (uint8_t* )(_p_head + 1));
	CHECK_GE(_nodes.first->FBlockSize, xWantedSize);

	//if the block is the last It's to handle carefully.
	MEraseNodeFromFreeList(_nodes, _p_head);

	//If allocate additional block in the remaining memory will be possible and reasonable
	if (_nodes.first->FBlockSize > (_alligment_size + 2 * sizeof(block_node_t)))
	{
		//The decreasing memory size is due to the additional block has been allocated
		MSplitBlockAndUpdateList(_nodes, _alligment_size, aFromEnd, _p_head);
	}
	//Return the memory space
	void *pvReturn =
			(void *) (((uint8_t *) _nodes.first) + sizeof(block_node_t));
	LOG_IF(DFATAL,(pvReturn <= FBase) || (_p_head->FMaxSize < ((size_t)pvReturn - (size_t)FBase+_alligment_size)))
																															<< "Segmentation failed "
																															<< pvReturn;

	VLOG(2) << "Allocate = " << _nodes.first->FBlockSize << " offset="
						<< sMOffsetFromBase(_nodes.first, FBase);
	//keep in the memory pid
	//_nodes.first->FPid = get_pid_optimized();
	//masking the size
	_nodes.first->FBlockSize |= BLOCK_ALLOCATED_BIT;
	return pvReturn;
}
void CSharedAllocator::MInsertIntoFreeList(heap_head_t* const aHead,
		block_node_t *pxBlockToInsert, block_node_t *aPrev) const
{
	CHECK_NOTNULL(pxBlockToInsert);
	VLOG(2) << "Insert " << *pxBlockToInsert;
	//increase of the number of free bytes remaining
	atomic_add(&aHead->FFreeBytesRemaining, pxBlockToInsert->FBlockSize);
	//atomic_write32(&aHead->FFreeBytesRemaining,atomic_read32(&aHead->FFreeBytesRemaining)+pxBlockToInsert->FBlockSize);
	if (!aHead->MFirstBlockNode(FBase))
	{
		VLOG(2) << "Insert the new first node." << *pxBlockToInsert;
		pxBlockToInsert->MSetNextNode(NULL_OFFSET);
		aHead->MSetFirstNode(
				sMOffsetFromBase<block_node_t>(pxBlockToInsert, FBase));
		return;
	}
	CHECK_LT(pxBlockToInsert->FBlockSize, aHead->FMaxSize);
	// Iterate through the list until a block is found that has a higher address
	// than the block being inserted
	CHECK_GT(pxBlockToInsert, aPrev);
	if (!aPrev)
		aPrev = aHead->MFirstBlockNode(FBase);
	if (aPrev > pxBlockToInsert)
		aPrev = NULL;
	for (; aPrev;)
	{
		VLOG(2) << "Prev block " << *aPrev;
		block_node_t * const _val = aPrev->MNext(FBase);
		if (_val && _val < pxBlockToInsert)
			aPrev = _val;
		else
			break;
	}
	VLOG_IF(2,!aPrev) << "It's the first.";

	//if aPrev is null then the pxBlockToInsert has not previous node,
	//it means pxBlockToInsert is to be the first node.
	if (!aPrev)
	{
		VLOG(2) << "Is to be the first node";
		pxBlockToInsert->MSetNextNode(aHead->FFOffsetFirstNode);
		aHead->MSetFirstNode(
				sMOffsetFromBase<block_node_t>(pxBlockToInsert, FBase));
		aPrev = pxBlockToInsert;
	}
	else if (((uint8_t *) aPrev + sizeof(block_node_t) + aPrev->FBlockSize)
			== (uint8_t *) pxBlockToInsert)
	// Do the previous block and the block it is being inserted after
	//make a contiguous block of memory?
	{
		VLOG(2) << "Create one big block from the two blocks.";
		aPrev->MSetBlockSize(
				aPrev->FBlockSize + pxBlockToInsert->FBlockSize
						+ sizeof(block_node_t));
		pxBlockToInsert = aPrev;

		atomic_add(&aHead->FFreeBytesRemaining, sizeof(block_node_t));
		//atomic_write32(&aHead->FFreeBytesRemaining,atomic_read32(&aHead->FFreeBytesRemaining)+sizeof(block_node_t));
	}
	else
	{
		VLOG(2) << "The blocks is spliting.";
		pxBlockToInsert->MSetNextNode(aPrev->FNextNode);
	}
	// Do the next block, and the block it is being inserted before
	// make a contiguous block of memory?
	block_node_t* const _next = aPrev->MNext(FBase);
	ssize_t const _diff = static_cast<ssize_t>((uint8_t *) pxBlockToInsert
			- (uint8_t *) _next) + pxBlockToInsert->FBlockSize
			+ sizeof(block_node_t);
	if (_diff == 0)
	{
		VLOG(2) << "It's one big block.";
		if (_next)
		{
			VLOG(2) << "create one big block from the two blocks.:"
								<< pxBlockToInsert->FBlockSize << " + "
								<< _next->FBlockSize;
			pxBlockToInsert->MSetBlockSize(
					pxBlockToInsert->FBlockSize + _next->FBlockSize
							+ sizeof(block_node_t));
			pxBlockToInsert->MSetNextNode(_next->FNextNode);
			atomic_add(&aHead->FFreeBytesRemaining, sizeof(block_node_t));
			//atomic_write32(&aHead->FFreeBytesRemaining,atomic_read32(&aHead->FFreeBytesRemaining)+sizeof(block_node_t));
		}
		else
		{
			VLOG(2) << "Set null offset.";
			pxBlockToInsert->MSetNextNode(NULL_OFFSET);
		}
	}
	if (aPrev != pxBlockToInsert)
		aPrev->MSetNextNode(sMOffsetFromBase(pxBlockToInsert, FBase));
}
size_t CSharedAllocator::MFreeBlock(heap_head_t* const _p_head, void *aP) const
{
	CHECK_NOTNULL(aP);
	//The memory being freed  have an block_node_t structure before it.
	block_node_t* const _p_node = sMGetBlockNode(aP);
	// Check if the block is actually allocated and unmask block zise field
	CHECK_NE((_p_node->FBlockSize & BLOCK_ALLOCATED_BIT), 0);
	_p_node->FBlockSize &= ~BLOCK_ALLOCATED_BIT;
	size_t const _size = _p_node->FBlockSize;
	VLOG(2) << "freed block size = " << _size;
	//Give back The block to the free blocks list.
	MInsertIntoFreeList(_p_head, _p_node, NULL);
	return _size;
}
block_size_t CSharedAllocator::MFreeHeapSize() const
{
	VLOG(2) << "MFreeHeapSize is called";
	CHECK_NOTNULL(FBase);
//	CRAII<CSharedAllocator> _block(*this);

	heap_head_t* const _p_head = sMGetHead(FBase);
	return atomic_read32(&_p_head->FFreeBytesRemaining);
}
block_size_t CSharedAllocator::MBufSize() const
{
	VLOG(2) << "MBufSize is called";
	CHECK_NOTNULL(FBase);
//	CRAII<CSharedAllocator> _block(*this);
	heap_head_t* const _p_head = sMGetHead(FBase);
	return _p_head->FMaxSize;
}
void CSharedAllocator::MCleaunUp(clean_up_t const& _cleanup)
{
	heap_head_t* const _p_head = sMGetHead(FBase);
	if (_cleanup.FBlock.MIs())
	{
		MCleaunUpBlock(_p_head, _cleanup, NULL);
	}
	else if (_cleanup.FPid != 0)
	{
		nodes_proc_t _proc = MSearchProcessNode(_p_head, _cleanup.FPid);
		CHECK_NOTNULL(_proc.first);
		CHECK_EQ((unsigned )_proc.first->FAlloactionCount, 0);
		MEraseProcessNode(_p_head, _proc);
		VLOG(2) << "Deallocate process node being cleaned up.";
		MFreeBlock(_p_head, _proc.first);
	}
}
void CSharedAllocator::MCleaunUpBlock(heap_head_t* const _p_head,
		clean_up_t const& _cleanup, process_node_t * aNode)
{
	const offset_t _base_offset = MConvertOffsetToBase(_p_head,
			_cleanup.FBlock.MGetConst().FOffset);

	block_node_t* _node = MGetBlockNode(_base_offset);
	CHECK_NE((_node->FBlockSize & BLOCK_ALLOCATED_BIT), 0);

	if (!aNode)
		aNode = MSearchProcessOfBlockNode(_p_head, _node);

	CHECK_NOTNULL(aNode);
	if (aNode->FPid == _cleanup.FPid)
	{
		VLOG(2) << "Erase block " << _cleanup.FBlock.MGetConst().FOffset;
		void* _p_data = sMPointerFromBase<void>(_base_offset, FBase);
		MFreeImpl(_p_data, _p_head, aNode);//MInformMemFreed will call in the end. see MCleanUpMemoryImpl
	}
	else
	{
		VLOG(2) << "The block " << _cleanup.FBlock.MGetConst().FOffset
							<< " is relocated to " << _cleanup.FPid;
		CHECK_EQ((_node->FBlockSize & (~BLOCK_ALLOCATED_BIT)),
				_cleanup.FBlock.MGetConst().FSize);
		//remove from old process
		//aNode->MPopOffset(_base_offset);
		MUnkeepBlock(_node,aNode);

		//add into new process
		aNode = MSearchProcessNode(_p_head, _cleanup.FPid).first;
		CHECK_NOTNULL(aNode);
		aNode = MGetOrRealocateProcessNode(aNode, _p_head, 1);
		CHECK_NOTNULL(aNode);

		_node->FIndexOfOffset = aNode->MPutOffset(_base_offset);
	}
}
void CSharedAllocator::MRemoveWatchDog(heap_head_t* const _p_head)
{
	_p_head->FWacthDogPid = 0;
	_p_head->FWacthDogTid = 0;
	_p_head->FMutexFlags &= ~heap_head_t::WACTH_DOG_PRIORITY;
}
bool CSharedAllocator::MIsWatchDogLive(heap_head_t* const _p_head,
		leak_processes_t const& _list)
{
	const unsigned _wpid = _p_head->FWacthDogPid;
	VLOG(2) << "Looking for wd " << _wpid;
	leak_processes_t::const_iterator _it = _list.begin();
	for (; _it != _list.end(); ++_it)
	{
		VLOG(5) << "Process: " << *_it;
		if (_wpid == *_it)
		{
			return false;
		}
	}
	return true;
}
void CSharedAllocator::MCleanUpByWatchDogImpl(leak_processes_t const& _list)
{
	VLOG(2) << "Request cleaning up by the watch dog.";
	heap_head_t* const _p_head = sMGetHead(FBase);
	NSHARE::CIPCSem _wd_sem;

	bool _is = _wd_sem.MInit(_p_head->FWatchDogSem,
			sizeof(_p_head->FWatchDogSem), 1, CIPCSem::E_HAS_EXIST);
	if (!_is)
	{
		LOG(DFATAL)<<"The Watch dog does not have the mutex.";
		MRemoveWatchDog(_p_head);
		return MCleanUpMemoryImpl(_list);
	}
	_p_head->FMutexFlags |= heap_head_t::WACTH_DOG_PRIORITY;
	VLOG(2) << "Unlock Watch dog.";
	_wd_sem.MPost();
	VLOG(2) << "Unlock shared sem.";
	MUnlock();
	VLOG(2) << "Wait For Watch Dog.";
	_wd_sem.MWait();
	VLOG(2) << "Wait For Sem.";
	MLock();
	VLOG(2) << "Watch dog is cleaned up resources.";
}
void CSharedAllocator::MCleanUpImpl()
{
	//if not then the blocks has been allocated by the process will be removed

	//locking for leak process
	leak_processes_t _proc;
	MGetLeakProcesses(_proc);

	if (_proc.empty())
	{
		VLOG(2) << "The cleaning up memory is not necessary.";
		return;
	}

	heap_head_t* const _p_head = sMGetHead(FBase);
	//Checking the watch dog?
	if (_p_head->MIsWatchDogExist())
	{
		if (MIsWatchDogLive(_p_head, _proc))
		{
			VLOG(2) << "The Watch dog is live.";
			return MCleanUpByWatchDogImpl(_proc);
		}
		else
		{
			LOG(ERROR)<<"The Watch dog is dead.";
			MRemoveWatchDog(_p_head);
		}
	}
	LOG_IF(ERROR,(_p_head->FMutexFlags &heap_head_t::WACTH_DOG_PRIORITY))
																					<< "Watch dog mutex error.";
	_p_head->FMutexFlags &= ~heap_head_t::WACTH_DOG_PRIORITY;//it's not necessary.

	MCleanUpMemoryImpl(_proc);
}
void CSharedAllocator::MCleanUpMemoryImpl(leak_processes_t const& _proc)
{
	//looking for leak resources
	clean_up_resources_t _resources;
	MGetLeakResources(_proc, _resources);

	//looking for leak resources
	MCleanUpMemoryImpl(_resources);
}
void CSharedAllocator::MCleanUpMemoryImpl(
		clean_up_resources_t const& _resources)
{
	//now we can remove memory
	clean_up_resources_t::const_iterator _it = _resources.begin(), _it_end(
			_resources.end());
	for (; _it != _it_end; ++_it)
	{
		MCleaunUp(*_it);
	}
	MInformMemFreed(sMGetHead(FBase));
}
void CSharedAllocator::MGetLeakProcesses(leak_processes_t & aResources)
{
	heap_head_t* const _p_head = sMGetHead(FBase);
	process_node_t* _p = _p_head->MFirstProcessNode(FBase);

	for (; _p != NULL; _p = _p->MNext(FBase))
	{
		VLOG(2) << "Looking up " << _p->FPid << " process.";
		if (!is_process_exist(_p->FPid))
			aResources.push_back(_p->FPid);
	}
	if (_p_head->MIsWatchDogExist())
	{
		if (!is_process_exist(_p_head->FWacthDogPid))
			aResources.push_back(_p_head->FWacthDogPid);
	}
}
void CSharedAllocator::MCheckResources(clean_up_resources_t & _resources)
{
	heap_head_t* const _p_head = sMGetHead(FBase);

	clean_up_resources_t::iterator _it = _resources.begin(), _it_end(
			_resources.end());
	for (; _it != _it_end; ++_it)
	{
		clean_up_t& _val=*_it;
		if (_val.FBlock.MIs())
		{
			const offset_t _base_offset = MConvertOffsetToBase(_p_head,
					_val.FBlock.MGetConst().FOffset);

			block_node_t* _node = MGetBlockNode(_base_offset);
			if (!MSearchProcessOfBlockNode(_p_head, _node))
			{
				VLOG(2) << "The block " << _it->FBlock.MGetConst().FOffset
									<< " has been removed.";
				_val.FPid = 0;
				_val.FBlock.MUnSet();
			}
		}
	}

}
void CSharedAllocator::MGetLeakResources(leak_processes_t const & _list,
		clean_up_resources_t & aResources)
{
	heap_head_t* const _p_head = sMGetHead(FBase);
	process_node_t* _p = _p_head->MFirstProcessNode(FBase);

	for (; _p != NULL; _p = _p->MNext(FBase))
	{
		VLOG(2) << "Looking up " << _p->FPid
							<< " process in 'leak structure'.";
		leak_processes_t::const_iterator _it = _list.begin();
		for (; _it != _list.end(); ++_it)
		{
			VLOG(5) << "Process: " << *_it;
			if (_p->FPid == *_it)
				break;
		}
		if (_it != _list.end())
		{
			LOG(ERROR)<<"The process " <<_p->FPid<< " is not exist. Cleaning up the resource.";

			for (unsigned i = 0; i < _p->FArraySize; ++i)
			if (!is_null_offset(_p->FOffsets[i].FNextNode ))
			{
				VLOG(2) << "Put offset " << _p->FOffsets[i].FNextNode;
				clean_up_t _cleanup;
				_cleanup.FBlock.MGet().FOffset=MConvertOffsetToHead(_p_head,_p->FOffsets[i].FNextNode);
				VLOG(2)<<"Head offset="<<_cleanup.FBlock.MGet().FOffset;
				block_node_t* _node=MGetBlockNode(_p->FOffsets[i].FNextNode);

				DCHECK_EQ(_node->FIndexOfOffset,i);

				DCHECK_NE((_node->FBlockSize & BLOCK_ALLOCATED_BIT),0);
				if(_node->FIndexOfOffset==i)//exist
				{
					_cleanup.FBlock.MGet().FSize=_node->FBlockSize&(~BLOCK_ALLOCATED_BIT);
					_cleanup.FPid=_p->FPid;
					aResources.push_back(_cleanup);
				}
			}

			clean_up_t _cleanup;
			_cleanup.FPid=_p->FPid;
			aResources.push_back(_cleanup);
		}
	}
}
bool CSharedAllocator::MCleanUpResourceByWatchDog(clean_up_f_t aFunction,
		void *aData)
{
	VLOG(2) << "CleanUp resources by watch dog";
	CHECK_NOTNULL(FBase);

	CRAII<CSharedAllocator> _block(*this);
	heap_head_t* const _p_head = sMGetHead(FBase);
	const unsigned _pid = get_pid_optimized();
	const unsigned _tid = NSHARE::CThread::sMThreadId();
	if (_p_head->MIsWatchDogExist()
			&& !(_pid == _p_head->FWacthDogPid && _tid == _p_head->FWacthDogTid))
	{
		LOG(WARNING)<<"A New Watch dog is registering.";
		MResetWatchDogImpl(_p_head);
	}
	VLOG(2) << "Initializing  watch dog...";
	_p_head->FWacthDogPid = _pid;
	_p_head->FWacthDogTid = _tid;
	NSHARE::CIPCSem _wd_sem;
	_wd_sem.MInit(_p_head->FWatchDogSem, sizeof(_p_head->FWatchDogSem), 1,
			CIPCSem::E_UNDEF, 0);

	_block.MUnlock();		//!---

	LOG(INFO) << "Watch dog stands guard.";

	CRAII<CIPCSem> _block2(_wd_sem);
	if (!(_pid == _p_head->FWacthDogPid && _tid == _p_head->FWacthDogTid))
	{
		LOG(INFO)<<"The watch dog no longer "<<_pid<<":"<<_tid<<" stand guard...";
		_block2.MUnlock();
		_wd_sem.MFree();
		return false;
	}

	MWatchDogLock();		//!---
	LOG(INFO) << "Clean up by watch dog.";

	leak_processes_t _proc;
	MGetLeakProcesses(_proc);

	clean_up_resources_t _resources;
	MGetLeakResources(_proc, _resources);

	//now call watch dog
	//if the block has not to be removed
	//the pid will be changed to holder pid
	MUnlock();//!---
	(*aFunction)(this, &_resources, aData);

	MLock();//!---
	MCheckResources(_resources);

	MCleanUpMemoryImpl(_resources);
	CHECK_EQ(_p_head->FNumberOfWaitingFor,_p_head->FPostCount);
	LOG(INFO)<<"CleanUp finished. "<<sMPrintAsXml(this);
	MUnlock();//!---
	return true;
}

void CSharedAllocator::MResetWatchDog()
{
	VLOG(2) << "Reset watch dog.";
	CHECK_NOTNULL(FBase);
	CRAII<CSharedAllocator> _block(*this);
	MResetWatchDogImpl(sMGetHead(FBase));
}
void CSharedAllocator::MResetWatchDogImpl(heap_head_t* const _p_head)
{
	MRemoveWatchDog(_p_head);
	NSHARE::CIPCSem _wd_sem;
	if (_wd_sem.MInit(_p_head->FWatchDogSem,sizeof(_p_head->FWatchDogSem), 1, CIPCSem::E_HAS_EXIST))
	{
		VLOG(2) << "Reset Watch dog.";
		_wd_sem.MPost();
	}
	VLOG(2) << "Watch dog is reseted.";
}
bool CSharedAllocator::MIsWatchDog() const
{
	CHECK_NOTNULL(FBase);
	CRAII<CSharedAllocator> _block(*this);
	heap_head_t* const _p_head = sMGetHead(FBase);
	return _p_head->MIsWatchDogExist();
}
void CSharedAllocator::MCleanUpResource()
{
	VLOG(2) << "MCleanUpResource is called";
	CHECK_NOTNULL(FBase);
	heap_head_t* const _p_head = sMGetHead(FBase);
	MSafetyLockImpl(_p_head);
	MCleanUpImpl();
	MUnlockImpl(_p_head);
}
bool CSharedAllocator::MIsNeedCleanUpResource()
{
	VLOG(2) << "MIsNeedCleanUpResource is called";

	unsigned _buf[1024];
	unsigned _number = 0;
	const unsigned _max_count = sizeof(_buf) / sizeof(_buf[0]);
	{
		heap_head_t* const _p_head = sMGetHead(FBase);
		MSafetyLockImpl(_p_head);
		process_node_t* _p = _p_head->MFirstProcessNode(FBase);
		for (; _p != NULL && _number != _max_count; _p = _p->MNext(FBase))
		{
			_buf[_number++] = _p->FPid;
		}

		MUnlockImpl(_p_head);
	}
	CHECK_NE(_max_count, _number);
	bool _need_cleanup = false;
	for (unsigned i = 0; i < _number && !_need_cleanup; ++i)
	{
		if (!is_process_exist(_buf[i]))
		{
			VLOG(2) << "The cleaning up resource is required as The process "
								<< _buf[i] << " is not exist.";
			_need_cleanup = true;
		}
	}

	return _need_cleanup;
}
bool CSharedAllocator::MIsMemoryUsed()
{
	VLOG(2) << "IsMemoryUsed is called";
	CHECK_NOTNULL(FBase);

	unsigned _count = 0;
	bool _need_cleanup = false;
	{
		CRAII<CSharedAllocator> _block(*this);
		heap_head_t* const _p_head = sMGetHead(FBase);
		process_node_t* _p = _p_head->MFirstProcessNode(FBase);
		for (; _p != NULL && !_count; _p = _p->MNext(FBase))
		{
			if (is_process_exist(_p->FPid))
				_count += _p->FAlloactionCount;
			else
				_need_cleanup = true;
		}
	}
	if (_need_cleanup)
	{
		MCleanUpResource();
	}

	return _count != 0;
}
bool CSharedAllocator::MReleaseHeap()
{
	VLOG(2) << "MReleaseHeap is called.";
	CHECK_NOTNULL(FBase);
	bool _is_full_cleanup = false;
	{
		CRAII<CSharedAllocator> _block(*this);
		MCleanUpImpl();
		heap_head_t* const _p_head = sMGetHead(FBase);
		const unsigned _pid = get_pid_optimized();

		process_node_t* _p_process = MSearchProcessNode(_p_head, _pid).first;
		CHECK(!_p_process || _p_process->FPid == _pid);

		if (_p_process)
		{
			if ((_p_process->FCount == 0) || (_p_process->FCount == 1))
			{
				VLOG(2) << "Release heap  for " << _pid << " counter="
									<< (unsigned) _p_process->FCount;
				MCleanUpImpl();
			}
			else if (FCurentProcess)
			{
				atomic_dec32(&_p_process->FCount);//fixme atomic operation has to be early than _p_process->FCount == 1 compare
				VLOG(2) << "Decrease counter for " << _p_process->FPid
									<< " counter="
									<< (unsigned) _p_process->FCount;
			}
		}
		_is_full_cleanup = (_p_head->MFirstProcessNode(FBase) == NULL);
		if (_is_full_cleanup)
		{
			CHECK_GE(_p_head->FMaxSize,
				_p_head->FFreeBytesRemaining+ sizeof(heap_head_t) + sizeof(block_node_t));
			DCHECK_LE(
					_p_head->FMaxSize - _p_head->FFreeBytesRemaining
							- sizeof(heap_head_t) - sizeof(block_node_t),
					__alignof(heap_head_t));	//3 - alligment

			LOG(INFO)<<"The heap has been destroyed.";
			if (_p_head->MIsWatchDogExist())
			{
				MResetWatchDogImpl(_p_head);
				usleep(1);	//wait for reset
			}
			_block.MUnlock();	//force unlock the head as it has been destroyed
			memset(_p_head, 0, sizeof(*_p_head));
		}
		VLOG(2) << "Heap realased";
		FCurentProcess = NULL;
	}
	FBase = NULL;
	if (_is_full_cleanup)
	{
		LOG(INFO)<<"The semaphore has been released.";
		FSem.MFree();
	}
	return _is_full_cleanup;
}
bool CSharedAllocator::MIsAllocatedImpl(offset_t const aBaseOffset) const
{
	//The memory being freed  have an block_node_t structure before it.

	VLOG(2) << "Locking for " << aBaseOffset;
	heap_head_t* const _p_head = sMGetHead(FBase);
	if (aBaseOffset >= _p_head->FMaxSize)
	{
		LOG(DFATAL)<<"Segmentation failed "<<sMPointerFromBase<void>(aBaseOffset,FBase)<<"("<<aBaseOffset<<")";
		return false;
	}
	//The memory being allocated  have an block_node_t structure before it.
	block_node_t* const _p_node = MGetBlockNode(aBaseOffset);

	process_node_t * const _result = MSearchProcessOfBlockNode(_p_head,
			_p_node);
	if (_result)
	{
		VLOG(2) << sMPointerFromBase<void>(aBaseOffset, FBase) << "("
							<< aBaseOffset << ") is founded ";
		return true;
	}
#ifndef NDEBUG
	VLOG(1) << "Probably the memory " << aBaseOffset << " is not allocated.";
	//try to found the pointer in the other process
	process_node_t *_p = _p_head->MFirstProcessNode(FBase);
	for (; _p != NULL; _p = _p->MNext(FBase))
	{
		for (unsigned i = 0; i < _p->FArraySize; ++i)
			if (!is_null_offset(_p->FOffsets[i].FNextNode))
			{
				if (aBaseOffset == _p->FOffsets[i].FNextNode)
				{
//					LOG(ERROR)<<"WTF? The block "<<aBaseOffset<<" is founded in the other process node. Block node="
//					<<_p_node->FPid<<"; In "<<_p->FPid;
					LOG(ERROR)<<"WTF? The block "<<aBaseOffset<<" is founded in the other process node. Block node="
					<<_p_node->FIndexOfOffset<<" in "<<i<<" of "<<_p->FPid;

					VLOG(2) <<sMPointerFromBase<void>(aBaseOffset,FBase)<<"("<<aBaseOffset<<") is founded ";
					return true;
				}
			}
		}
#endif
	VLOG(2) << aBaseOffset << " is not founded.";
	return false;
}
bool CSharedAllocator::MIsAllocated(void *aP) const
{
	LOG_IF(ERROR,!aP) << "Try to find memory of null pointer.";
	if (!aP)
		return false;
	if (aP <= FBase)
	{
		LOG(DFATAL)<<"Segmentation failed "<<aP;
		return false;
	}
	VLOG(2) << "MIsAllocated is called for " << aP;
	CHECK_NOTNULL(FBase);
	CRAII<CSharedAllocator> _block(*this);
	return MIsAllocatedImpl(sMOffsetFromBase(aP, FBase));
}
CSharedAllocator::offset_t CSharedAllocator::MConvertOffsetToBase(
		heap_head_t const* aHeap, offset_t aVal) const
{
	return aVal + sMOffsetFromBase(aHeap + 1, FBase) + MINIMAL_OFFSET;
}
CSharedAllocator::offset_t CSharedAllocator::MOffset(void* aP) const
{
	if (aP <= FBase)
	{
		LOG(DFATAL)<<"Segmentation failed "<<aP;
		return 0;
	}
	//CRAII<CIPCSem> _block(FSem);//fixme for optimization
	CHECK_NOTNULL(FBase);
	offset_t const _from_base= sMOffsetFromBase(aP,FBase);

	heap_head_t* const _p_head = sMGetHead(FBase);
	offset_t const _from_head=MConvertOffsetToHead(_p_head,_from_base);
	VLOG(5)<<"Offset from heap  of "<<aP<<" is "<<_from_head<<" base="<<FBase;
	return _from_head;
}
CSharedAllocator::offset_t CSharedAllocator::MConvertOffsetToHead(
		heap_head_t const* aHeap, offset_t aOffset) const
{
	const offset_t _offset = sMOffsetFromBase(aHeap + 1, FBase)
			+ MINIMAL_OFFSET;

	if (_offset > aOffset || _offset >= aHeap->FMaxSize)
	{
		LOG(DFATAL)<<"Segmentation failed "<<sMPointerFromBase<void>(_offset,FBase);
		return 0;
	}
	return aOffset - _offset;
}
void* CSharedAllocator::MPointer(offset_t aVal) const
{
	if (is_null_offset(aVal))
		return NULL;
	if (!FBase)
	{
		LOG(DFATAL)<<"Segmentation failed Offset="<<aVal<<" FBase=0";
		return NULL;
	}
	heap_head_t* const _p_head = sMGetHead(FBase);

	if ( aVal >= _p_head->FMaxSize)
	{
		LOG(DFATAL)<<"Segmentation failed Offset="<<aVal;
		return 0;
	}
	offset_t const _offset = MConvertOffsetToBase(_p_head,aVal);
	void* _ptr=MPointerRefBaseOf(_offset);
	VLOG(5)<<"Pointer from heap  of "<<aVal<<" is "<<_ptr<<" base="<<FBase;
	return _ptr;
}
CSharedAllocator::offset_t CSharedAllocator::MOffsetOfBase(void* aP) const
{
	if (aP <= FBase)
	{
		LOG(DFATAL)<< "Segmentation failed " << aP;
		return 0;
	}
	return sMOffsetFromBase<void>(aP, FBase);
}
void* CSharedAllocator::MPointerRefBaseOf(offset_t aVal) const
{
	return sMPointerFromBase<void>(aVal, FBase);
}

size_t CSharedAllocator::MGetNumberOfAllocations() const
{
	VLOG(2) << "MGetNumberOfAllocations is called";
	CRAII<CSharedAllocator> _block(*this);
	CHECK_NOTNULL(FBase);
	heap_head_t* const _p_head = sMGetHead(FBase);
	const unsigned _pid = get_pid_optimized();
	process_node_t* const _process = MSearchProcessNode(_p_head, _pid).first;
	if (!_process)
		return 0;
	return _process->FAlloactionCount;
}
void CSharedAllocator::MFillInfo(memory_info_t & _info,
		heap_head_t* const _p_head) const
{
	VLOG(2) << "Fill head info";
	_info.FOffset = sMOffsetFromBase(_p_head, FBase);
	_info.FBlockSize = sizeof(heap_head_t);
	_info.FType = memory_info_t::E_ALLOCATED;
	_info.FAdditionalInfo.MKey() = "head";
	_p_head->MSerialize(_info.FAdditionalInfo);
}
void CSharedAllocator::MFillInfo(memory_info_t & _info,
		process_node_t* const _p_process) const
{
	VLOG(2) << "Fill process info";
	block_node_t* const _p_node = sMGetBlockNode(_p_process);
	memory_info_t _block_info;
	MFillInfo(_block_info, _p_node);

	_info.FBlockSize = _block_info.FBlockSize;
	_info.FOffset = _block_info.FOffset;
	_info.FType = _block_info.FType;

	_info.FAdditionalInfo.MKey() = "process_node";

	_p_process->MSerialize(_info.FAdditionalInfo);
	_info.FAdditionalInfo.MAdd(_block_info.FAdditionalInfo);
}
void CSharedAllocator::MFillInfo(memory_info_t & _info,
		block_node_t* const aP) const
{
	VLOG(5) << "Fill block node info";
	_info.FOffset = sMOffsetFromBase(aP, FBase);
	_info.FBlockSize =(block_size_t) (aP->FBlockSize & (~BLOCK_ALLOCATED_BIT));
	_info.FBlockSize += sizeof(block_node_t);

	_info.FType =
			aP->FBlockSize & BLOCK_ALLOCATED_BIT ?
					memory_info_t::E_ALLOCATED : memory_info_t::E_FREE;
	_info.FAdditionalInfo.MKey() = "block_node";
	aP->MSerialize(_info.FAdditionalInfo);
}
void CSharedAllocator::MSerialize(NSHARE::CConfig& _conf) const
{
	shared_info_t _shared_info;
	MGetInfo(_shared_info);
	MSerializeImpl(_conf, _shared_info);
}
void CSharedAllocator::MSerializeImpl(NSHARE::CConfig& _conf,
		shared_info_t const& _shared_info) const
{

	if (_conf.MKey().empty())
		_conf.MKey() = NAME;

	typedef std::multimap<offset_t, shared_info_t::const_iterator> _maps_t;

	_maps_t _map;
	{
		shared_info_t::const_iterator _it = _shared_info.begin();
		for (; _it != _shared_info.end(); ++_it)
			_map.insert(_maps_t::value_type(_it->FOffset, _it));
	}
	_maps_t::const_iterator _it = _map.begin();
	for (; _it != _map.end(); ++_it)
	{
		memory_info_t const& _info = *_it->second;
		CConfig _tmp("block");
		_tmp.MAdd("BlockSize", _info.FBlockSize);
		_tmp.MAdd("Offset", _info.FOffset);
		switch (_info.FType)
		{
		case memory_info_t::E_ALLOCATED:
			_tmp.MAdd("Type", "Allocated");
			break;
		case memory_info_t::E_FREE:
			_tmp.MAdd("Type", "Free");
			break;
		};
		_tmp.MAdd(_info.FAdditionalInfo);
		_conf.MAdd(_tmp);
	}
}
void CSharedAllocator::MGetInfo(shared_info_t& _shared_info) const
{
	CRAII<CSharedAllocator> _block(*this);
	MGetInfoImpl(_shared_info);
}
void CSharedAllocator::MGetInfoImpl(shared_info_t& _shared_info) const
{
	VLOG(2) << "MGetInfo is called";
	CHECK_NOTNULL(FBase);
	heap_head_t* const _p_head = sMGetHead(FBase);
	CHECK_NOTNULL(_p_head);
	{
		memory_info_t _info;
		MFillInfo(_info, _p_head);
		_shared_info.push_back(_info);
	}
	//filling allocated blocks info
	{
		process_node_t* _p = _p_head->MFirstProcessNode(FBase);
		for (; _p != NULL; _p = _p->MNext(FBase))
		{
			//fixme todo for each
			for (unsigned i = 0; i < _p->FArraySize; ++i)
				if (!is_null_offset(_p->FOffsets[i].FNextNode))
				{
					void* _p_data = sMPointerFromBase<void>(
							_p->FOffsets[i].FNextNode, FBase);
					block_node_t* const _p_node =
							(block_node_t*) (((uint8_t*) (_p_data)
									- sizeof(block_node_t)));

					// Check if the block is actually allocated.
					CHECK_NE((_p_node->FBlockSize & BLOCK_ALLOCATED_BIT), 0);
//					CHECK_EQ(_p_node->FPid, _p->FPid);
					CHECK_EQ(_p_node->FIndexOfOffset, i);
					memory_info_t _info;
					MFillInfo(_info, _p_node);
					_shared_info.push_back(_info);
				}
		}
	}
	//filling free block info
	{
		block_node_t* _it = _p_head->MFirstBlockNode(FBase);
		for (; _it; _it = _it->MNext(FBase))
		{
			CHECK_EQ(sMNextCoorectAddr<block_node_t>(_it), (void* )_it);
			CHECK_LT(_it->FBlockSize, _p_head->FMaxSize);
			VLOG(2) << "NEXT block " << _it;

			memory_info_t _info;
			MFillInfo(_info, _it);
			_shared_info.push_back(_info);
		}
	}
	//filing process info only
	{
		process_node_t* _p = _p_head->MFirstProcessNode(FBase);
		for (; _p != NULL; _p = _p->MNext(FBase))
		{
			VLOG(2) << "Serialize " << _p->FPid << " process.";
			memory_info_t _info;
			MFillInfo(_info, _p);
			_shared_info.push_back(_info);
		}
	}
}
CSharedAllocator::block_node_t* CSharedAllocator::MGetBlockNode(
		offset_t aBaseOffset) const
{
	return sMGetBlockNode(sMPointerFromBase<void>(aBaseOffset, FBase));
}
bool CSharedAllocator::MWatchDogLock() const
{
	CHECK_NOTNULL(FBase);
	heap_head_t* const _p_head = sMGetHead(FBase);
	//if(_p_head->FPIDOfLockedMutex )
	bool _is = MLockImpl(_p_head);
	_p_head->FMutexFlags &= ~heap_head_t::WACTH_DOG_PRIORITY;
	return _is;
}
//if process, which has locked the mutex, is not exist now, the mutex is unlocked.
//Than The process lock the mutex.
bool CSharedAllocator::MSafetyLockImpl(heap_head_t* const _p_head) const
{
	CHECK_NOTNULL(_p_head);
	VLOG(2) << "Safety clean up";
	unsigned _process = _p_head->FPIDOfLockedMutex;
	if (_process)
		if (!is_process_exist(_process))
		{
			LOG(ERROR)<<"Process "<<_process<<"is not exist, but the mutex "<<FSem.MName()
			<<"still is locked by"<<_p_head->FPIDOfLockedMutex<<" "
			<<_p_head->FTIDOfLockedMutex<<". Unlocking immediately ...";
			_p_head->FPIDOfLockedMutex = 0;
			_p_head->FTIDOfLockedMutex = 0;
			FSem.MPost();
		}
	return MLockImpl(_p_head);
}
bool CSharedAllocator::MLockImpl(heap_head_t* const _p_head) const
{
	const unsigned _pid = get_pid_optimized();
	const unsigned _tid = NSHARE::CThread::sMThreadId();
	VLOG(5) << "Try lock " << FSem.MName() << " by " << _pid << " tid "
						<< _tid << " which is locked by pid="
						<< _p_head->FPIDOfLockedMutex << " tid="
						<< _p_head->FTIDOfLockedMutex;
	if (_p_head->FPIDOfLockedMutex == _pid
			&& _tid == _p_head->FTIDOfLockedMutex)
	{
		_p_head->FLockedMutexCounter++;
		VLOG(2) << "Lock counter= " << _p_head->FLockedMutexCounter;
		return true;
	}
	_p_head->FMutexFlags |= heap_head_t::TRY_LOCK_MUTEX;
	bool const _is = FSem.MWait();
	if (_is)
	{
		VLOG(2) << "Lock Sem " << FSem.MName() << " by " << _pid
							<< "; previous=" << _p_head->FPIDOfLockedMutex
							<< " tid=" << _p_head->FTIDOfLockedMutex;
		if (_p_head->FPIDOfLockedMutex == _pid)
		{
			CHECK_EQ(_tid, _p_head->FTIDOfLockedMutex);
			LOG(ERROR)<<"Recursive mutex";
			_p_head->FLockedMutexCounter++;
			VLOG(2) << "Lock counter= " << _p_head->FLockedMutexCounter;
		}
		else
		{
			VLOG(2) << "Prev Lock counter= " << _p_head->FLockedMutexCounter;
			LOG_IF(ERROR,_p_head->FLockedMutexCounter!=0)
																	<< "Lock counter is not zero."
																	<< _p_head->FLockedMutexCounter;
			_p_head->FLockedMutexCounter = 1;
		}
		_p_head->FPIDOfLockedMutex = _pid;
		_p_head->FTIDOfLockedMutex = _tid;	//todo atomic
		_p_head->FMutexFlags &= ~heap_head_t::TRY_LOCK_MUTEX;
	}
	return _is;
}
bool CSharedAllocator::MUnlockImpl(heap_head_t* const _p_head) const
{
	CHECK_NOTNULL(_p_head);
	VLOG(2) << "Unlock Sem " << FSem.MName() << " by " << get_pid_optimized()
						<< "; previous=" << _p_head->FPIDOfLockedMutex
						<< " tid=" << _p_head->FTIDOfLockedMutex;

	CHECK_EQ(_p_head->FPIDOfLockedMutex, get_pid_optimized());
	CHECK_EQ(_p_head->FTIDOfLockedMutex, NSHARE::CThread::sMThreadId());
	CHECK_GT(_p_head->FLockedMutexCounter, 0);
	if (--_p_head->FLockedMutexCounter)
	{
		LOG(ERROR)<<"Recursive mutex";
		VLOG(2) << "Does not unlock mutex " << FSem.MName() << " counter="
		<< _p_head->FLockedMutexCounter;
		return false;
	}
	const pid_type _old_pid=_p_head->FPIDOfLockedMutex;
	const pid_type _old_tid=_p_head->FTIDOfLockedMutex;
	_p_head->FPIDOfLockedMutex = 0;
	_p_head->FTIDOfLockedMutex = 0;
	if(!FSem.MPost())
	{
		_p_head->FPIDOfLockedMutex = _old_pid;
		_p_head->FTIDOfLockedMutex = _old_tid;
		++_p_head->FLockedMutexCounter;
		return false;
	}
	return true;
}
bool CSharedAllocator::MLock() const
{
	CHECK_NOTNULL(FBase);
	bool _is = false;
	heap_head_t* const _p_head = sMGetHead(FBase);
	for (HANG_INIT;;HANG_CHECK)
	{
		_is=MLockImpl(_p_head);
		if(_p_head->FMutexFlags & heap_head_t::WACTH_DOG_PRIORITY)
		{
			CHECK(_p_head->MIsWatchDogExist());
			VLOG_EVERY_N(2, 100) << "Wait For Watch Dog is locked mutex "
			<< FSem.MName();
			MUnlock();
			NSHARE::CThread::sMYield();
		}
		else
		break;
	}

	return _is;
}
bool CSharedAllocator::MUnlock() const
{
	CHECK_NOTNULL(FBase);
	heap_head_t* const _p_head = sMGetHead(FBase);
	return MUnlockImpl(_p_head);
}
bool CSharedAllocator::MIsInited() const
{
	return FBase != NULL;
}
} /* namespace NSHARE */
