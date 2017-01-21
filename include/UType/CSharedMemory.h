/*
 * CSharedMemory.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 13.04.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CSHAREDMEMORY_H_
#define CSHAREDMEMORY_H_

namespace NSHARE
{
class CSharedAllocator;
//CSharedMemoryManager
class SHARE_EXPORT CSharedMemory:NSHARE::CDenyCopying
{
public:
	CSharedMemory();
	~CSharedMemory();
	bool MOpenOrCreate(NSHARE::CText const& aName,size_t aSize=0,size_t aReserv=0);//return true if create
	bool MIsOpened() const;
	bool MOpen(NSHARE::CText const& aName,bool aIsCleanUp=true,size_t aReserv=0);
	bool MFree();//true -  the shared memory has been destroyed

	IAllocater* MGetAllocator() const;
	size_t MGetSize() const;

	IAllocater::offset_pointer_t MOffsetOf(void*) const;
	void* MPointerOf(IAllocater::offset_pointer_t) const;

	void* MMallocTo(uint32_t const xWantedSize, IAllocater::offset_pointer_t aRefOffset);
	void* MGetIfMalloced(IAllocater::offset_pointer_t aRefOffset);
	void MSerialize(NSHARE::CConfig& _conf) const;

	void MCleanUp();
	bool MCleanUpResourceByWatchDog(int (*)(CSharedAllocator* WHO, /*clean_up_resources_t*/void* WHAT, void* YOU_DATA),void *YOU_DATA);
	void MFinishCleanUp();
	bool MIsNeedCleanUpResource();
	static bool sMRemove(NSHARE::CText const& aName);

	struct CImpl;
	struct mem_info_t;
private:
	CImpl* FImpl;
	friend class CSharedAllocaterImpl;
};

} /* namespace NSHARE */
#endif /* CSHAREDMEMORY_H_ */
