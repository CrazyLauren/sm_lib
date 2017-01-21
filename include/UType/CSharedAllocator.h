/*
 * CSharedAllocator.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 10.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CSHAREDALLOCATER_H_
#define CSHAREDALLOCATER_H_

namespace NSHARE
{
class SHARE_EXPORT CSharedAllocator: NSHARE::CDenyCopying
{
public:
	typedef uint32_t offset_t;
	typedef uint32_t block_size_t;
	typedef uint32_t pid_type;
	typedef uint16_t index_type;

	static const NSHARE::CText NAME;
	static const index_type NULL_INDEX;
	static const offset_t NULL_OFFSET;// max 2GB
	static bool sMIsNullOffset(const offset_t& aWhat);

	COMPILE_ASSERT(sizeof(NULL_OFFSET)==4,InvalidSizeNullOffset);

	struct memory_info_t
	{
		enum eType
		{
			E_FREE,
			E_ALLOCATED,
		};
		offset_t FOffset;
		size_t FBlockSize;
		eType FType;
		NSHARE::CConfig FAdditionalInfo;
	};
	typedef std::vector<memory_info_t> shared_info_t;

	struct clean_up_t
	{
		struct _erased_block_t
		{
			offset_t FOffset;
			size_t FSize;
		};
		pid_type FPid;
		smart_field_t<_erased_block_t> FBlock;
	};
	typedef std::vector<clean_up_t> clean_up_resources_t;

	typedef std::vector<pid_type> leak_processes_t;

	typedef int (*clean_up_f_t)(CSharedAllocator* WHO, /*clean_up_resources_t*/void* WHAT, void* YOU_DATA);

	static block_size_t const BLOCK_ALLOCATED_BIT;
	static const double PROCESS_ARRAY_FACTOR;
	static const block_size_t DEF_PROCESS_SIZE;
	static const uint8_t MINIMAL_OFFSET;

	explicit CSharedAllocator(void * aBase = NULL);
	~CSharedAllocator();
	bool MInitFromCreatedHeap(void*,bool aCleanUp=true,size_t aReserv=0);
	bool MReleaseHeap();	//true -  the heap has been destroyed
	//uninit
	void MCreateHeap(void* aBase, block_size_t aSize,size_t aReserv=0);
	bool MIsInited()const;

	void* MMalloc(block_size_t const xWantedSize,bool aBlock=false,bool aFromReserv=false);
	//aRefOffset is   offset relative to heap begin
	void* MMallocTo(block_size_t const xWantedSize, offset_t aRefOffset);
	void* MGetIfMalloced(offset_t aRefOffset);

	void* MReallocate(void* ,block_size_t aSize,bool aBlock=false,bool aFromReserv=false);
	size_t MFree(void *aP);	//return count
	bool MIsAllocated(void *aP) const;

	//there are two type of offset.
	//The first offset is offset relative to "aBase"(void MCreateHeap(...)).
	//The second offset is offset relative to heap begin.
	//usually The heap offset is used.
	offset_t MOffsetOfBase(void*) const;
	void* MPointerRefBaseOf(	offset_t) const;

	offset_t MOffset(void*) const;
	void* MPointer(offset_t) const;


	block_size_t MFreeHeapSize() const;
	block_size_t MBufSize() const;

	bool MIsWatchDog() const;
	bool MCleanUpResourceByWatchDog(clean_up_f_t, void *aData);//warning!!!The function clean_up_f_t has been own 2 inner mutex (may be dead lock)!!
	void MCleanUpResource();
	bool MIsNeedCleanUpResource();
	void MResetWatchDog();

	bool MIsMemoryUsed();

	size_t MGetNumberOfAllocations() const;
	void MGetInfo(shared_info_t &) const;
	void MSerialize(NSHARE::CConfig&) const;
	struct block_node_t;
	struct process_node_t;
	struct heap_head_t;
	struct pid_offset_t;
	//struct free_index_t;
	typedef  uint32_t free_index_t;
private:
	bool MLock() const;
	bool MUnlock() const;

	typedef std::pair<process_node_t *, process_node_t *> nodes_proc_t;
	typedef std::pair<block_node_t *, block_node_t *> nodes_block_t;

	template<class T>
	static offset_t sMOffsetFromBase(T const* const aFrom, void const * const aBase);
	template<class T>
	inline static T* sMPointerFromBase(offset_t aOffset, void* aBase);
	template<class T>
	static void* sMNextCoorectAddr(void* aAddr);
	template<class T>
	static void* sMPrevCoorectAddr(void* aAddr);

	offset_t MConvertOffsetToBase(heap_head_t const* aHeap,offset_t aOffset) const;
	offset_t MConvertOffsetToHead(heap_head_t const* aHeap,offset_t aOffset) const;

	void* MMallocImpl(heap_head_t* const _p_head, block_size_t const xWantedSize,
			offset_t aOffset,bool aUseReserv);
	process_node_t * const MGetOrCreateProcessNode(
			heap_head_t* const aHead, //pointer to head
			int aCount //the number of the new blocks
			) const;

	process_node_t * const MGetOrRealocateProcessNode(process_node_t *aProccess,//
			heap_head_t* const aHead, //pointer to head
			int aCount //the number of the new blocks
			) const;

	process_node_t * const MCreateProcessNode(
			heap_head_t* const aHead
			) const;
	block_node_t * const MCreateReservForProcess(
			process_node_t*  ,heap_head_t* const aHead
			) const;

	bool MIsAllocatedImpl(offset_t const aBaseOffset) const;


	//first the node,second -prev
	nodes_proc_t MSearchProcessNode(heap_head_t* const aHead,
			unsigned aPid) const;
	process_node_t * MSearchProcessOfBlockNode(heap_head_t* const aHead,
			block_node_t * aNode) const;

	nodes_proc_t& MInsertProcessNode(heap_head_t* const aHead,
			nodes_proc_t&) const;
	nodes_proc_t& MEraseProcessNode(heap_head_t* const aHead,
			nodes_proc_t&) const;
	void *MMallocBlock(heap_head_t* const aHead,
			block_size_t const xWantedSize, bool aFromEnd,
			offset_t aOffset = 0) const;
	void * MMallocBlockFromReserv( heap_head_t* const _p_head,process_node_t * const, block_size_t const xWantedSize) const;

	nodes_block_t MGetFreeBlockFromBegin(offset_t const aOffset,
			uint32_t const _alligment_size, heap_head_t* const _p_head) const;
	nodes_block_t MGetFreeBlockFromEnd(uint32_t _alligment_size,
			heap_head_t* const _p_head) const;

	size_t MFreeBlock(
			heap_head_t* const _p_head, //pointer to head
			void *aP //the pointer it has to be freed
			) const;
	void MEraseNodeFromFreeList(const nodes_block_t& _nodes,
			heap_head_t* const _p_head) const;
	void MInsertIntoFreeList(
			heap_head_t* const aHead, //pointer to head
			block_node_t *aInsertBlock, //pointer for the inserting block
			block_node_t *aPrev //pointer to the previous block of the free list
			) const;
	void MSplitBlockAndUpdateList(nodes_block_t& _nodes, uint32_t _alligment_size,
			bool aFromEnd, heap_head_t* const _p_head) const;
	block_node_t* MSplitInto2Block(block_node_t *& aWho,uint32_t _alligment_size,
			bool aFromEnd,
			heap_head_t* const _p_head) const;
	static block_node_t* sMGetBlockNode(void * const aPointer);
	static void * sMGetPointerOfBlockNode(block_node_t* aNode);
	block_node_t* MGetBlockNode(offset_t  aBaseOffset) const;

	static heap_head_t* const sMGetHead(void* const aBase);
	void MCleaunUp( clean_up_t const& _cleanup);
	void MCleaunUpBlock( heap_head_t* const _p_head,
			clean_up_t const& aProc,process_node_t *);
	size_t MFreeImpl(void* aP,
			heap_head_t* const _p_head,process_node_t* _p);
	void MFreeReservedBlock(const offset_t _offset, block_node_t* _p_node, process_node_t* _p);

	void MCheckResources(clean_up_resources_t &);
	void MGetLeakResources(leak_processes_t const&,clean_up_resources_t &);
	void MGetLeakProcesses(leak_processes_t &);
	void MCleanUpMemoryImpl( clean_up_resources_t const& _list);
	void MCleanUpMemoryImpl( leak_processes_t const& _list);
	void MCleanUpImpl();
	bool MIsWatchDogLive(heap_head_t* const _p_head,leak_processes_t const& _list);
	void MCleanUpByWatchDogImpl(leak_processes_t const& _list);
	void MResetWatchDogImpl(heap_head_t* const _p_head);
	bool MWatchDogLock() const;
	void MRemoveWatchDog(heap_head_t*const  _p_head);

	void MInitProcessNode(heap_head_t* const _p_head);
	void MFillInfo(memory_info_t &,heap_head_t* const _p_head) const;
	void MFillInfo(memory_info_t &,process_node_t* const _p_head) const;
	void MFillInfo(memory_info_t &,block_node_t* const _p_node) const;
	void MGetInfoImpl(shared_info_t &) const;
	void MSerializeImpl(NSHARE::CConfig&,shared_info_t const&) const;
	static std::string  sMPrintAsXml(CSharedAllocator const* aFrom);
	bool MSafetyLockImpl(heap_head_t* const _p_head) const;
	bool MLockImpl(heap_head_t* const _p_head) const;
	bool MUnlockImpl(heap_head_t* const _p_head) const;
	void MInitIfNeedFreeSem(heap_head_t* const _p_head);
	void MInformMemFreed(heap_head_t* const _p_head);
	bool MWaitFreeOperation( heap_head_t*const _p_head);
	void MKeepBlock(block_node_t * _alloc, process_node_t*const  _process) const;
	void MUnkeepBlock(block_node_t * _alloc, process_node_t*const  _process) const;


	void* FBase;
	mutable process_node_t* FCurentProcess;
	mutable NSHARE::CIPCSem FSem;
	mutable NSHARE::CIPCSem FFreeSem;//signaling when the allocated memory has been freed,
	//thereafter the other 'user' can try allocate the memory again
	//не надёжно - можно зависнуть в цикле если Post !=  Wait
	mutable size_t FReserv;


	friend class CRAII<CSharedAllocator>;
};
template<> class SHARE_EXPORT CRAII<CSharedAllocator> : public CDenyCopying
{
public:
	explicit CRAII(CSharedAllocator const& aSem) :
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
	CSharedAllocator const &FSem;
	volatile bool FIsLock;
};
} /* namespace NSHARE */
#endif /* CSHAREDALLOCATER_H_ */
