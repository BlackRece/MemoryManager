#include "MemoryManager.h"

Heap* MemoryManager::s_pRootHeap = nullptr;
bool MemoryManager::m_bDebugMode = true;
bool MemoryManager::m_bPoolingMode = true;

void* operator new(size_t nSize)
{
	if (!MemoryManager::isDebugEnabled())
		return malloc(nSize);
	
	std::cout
		<< "global operator new called ... \n";
	
	void* pStartMemBlock = MemoryManager::isPoolingEnable()
		? MemoryManager::allocToPool(nSize)
		: MemoryManager::allocToHeap(nSize);

	return pStartMemBlock;
}

void* operator new (size_t nSize, char pHeapTag[])
{
	if (!MemoryManager::isDebugEnabled())
		return malloc(nSize);

	Str sTag; sTag.set(pHeapTag);

	std::cout
		<< "global operator new called ..."
		<< "\nwith size: " << nSize
		<< "\nfor heap: " << sTag.str
		<< std::endl;

	void* pStartMemBlock = MemoryManager::isPoolingEnable()
		? MemoryManager::allocToPool(nSize, &sTag)
		: MemoryManager::allocToHeap(nSize, &sTag);

	return pStartMemBlock;
}

void operator delete(void* pMem)
{
	// TODO: this operator method only deallocates from the heap.
	// Amend this method to account for the use of the memory pool found on the heap.

	if (!MemoryManager::isDebugEnabled())
	{
		free(pMem);
		return;
	}

	std::cout 
		<< "global operator delete called \n"
		<< "for address : " << std::hex << pMem
		<< std::endl;
		
	if (MemoryManager::isPoolingEnable())
	{
		MemoryManager::freeFromPool(pMem);
		return;
	}
	
	MemoryManager::freeFromHeap(pMem);
}

void MemoryManager::init(bool bDebugMobe)
{
	MemoryManager::m_bDebugMode = bDebugMobe;

	if (!isDebugEnabled())
	{
		std::cout
			<< "Memory Manager not available in release mode.\n";

		return;
	}

	if (s_pRootHeap != nullptr)
		return;
	
	s_pRootHeap = newHeap();
}

Heap* MemoryManager::addHeap(char sHeapTag[])
{
	Str sTag; sTag.set(sHeapTag);

	Heap* pTargetHeap = findHeap(&sTag);
	
	if (pTargetHeap == nullptr)
		pTargetHeap = newHeap(&sTag);

	Heap* pLastHeap = s_pRootHeap->getLast();
		
	if (pTargetHeap != pLastHeap)
	{
		pTargetHeap->setPrevHeap(pLastHeap);
		pLastHeap->setNextHeap(pTargetHeap);
	}
	
	return pTargetHeap;
}

Heap* MemoryManager::newHeap(Str* sTag)
{
	size_t nHeapSize = sizeof(Heap);

	char* pMem = Util::allocBytes(nHeapSize);

	Heap* pHeap = (Heap*)Util::getPointer(pMem);

	Header* pHeader = Util::getHeader(pHeap);
	pHeader->init(nHeapSize);
	pHeader->m_pHeap = pHeap;

	Footer* pFooter = Util::getFooter(pHeap);
	pFooter->init();

	Str sValidTag = getValidTag(sTag);
	Str* sHeapTag = pHeap->init(pHeader, &sValidTag);

	std::cout
		<< std::endl << sHeapTag->str
		<< " heap created" << std::hex
		<< "\naddress : " << pHeap
		<< "\nheap header : " << pHeader
		<< "\nheap footer : " << pFooter
		<< std::endl;

	return pHeap;
}

Heap* MemoryManager::findHeap(Str* sHeapTag)
{
	Str sTargetTag = getValidTag(sHeapTag);
	std::cout
		<< "MemoryManager - finding \"" << sTargetTag.str
		<< "\" Heap from heap list...\n";

	if(s_pRootHeap != nullptr)
		return s_pRootHeap->findHeap(sTargetTag);
	
	return nullptr;
}

void MemoryManager::delHeap(Str* heapTag)
{
	Heap* pHeap = findHeap(heapTag);
	if (pHeap == nullptr)
		return;
	
	pHeap->clear();

	Header* pHeader = pHeap->getHeapHeader();
	pHeap->delHeader(pHeader);
	free(pHeader);
}

void MemoryManager::checkHeaps()
{
	Heap* pHeap = s_pRootHeap;

	while (pHeap != nullptr)
	{
		pHeap->check();
		pHeap = pHeap->getNextHeap();
	}
}

void MemoryManager::clearHeaps()
{
	Heap* pHeap = (Heap*)s_pRootHeap;

	while (pHeap != nullptr)
	{
		pHeap->clear();
		pHeap = pHeap->getNextHeap();
	}
}

void MemoryManager::clearHeap(Str* heapTag)
{
	Heap* pHeap = findHeap(heapTag);
	
	if(pHeap != nullptr)
		pHeap->clear();
}

void MemoryManager::addHeader(Header* pHeader, Str* sHeapTag)
{
	Heap* pHeap = findHeap(sHeapTag);
	
	if (pHeap == nullptr)
		pHeap = MemoryManager::s_pRootHeap;
	
	pHeap->addHeader(pHeader);
}

void MemoryManager::delItem(Header* pHeader)
{
	Heap* pHeap = pHeader->m_pHeap;
	pHeap->delHeader(pHeader);
}

Str MemoryManager::getValidTag(Str* tag)
{
	char sDefaultTag[] = DEFAULT_TAG;
	Str sTag; sTag.set(sDefaultTag);

	if (tag == nullptr)
		return sTag;

	if (tag->isEmpty())
		tag->set(sDefaultTag);

	return *tag;
}

void* MemoryManager::allocFrame(size_t nSize, Str* sHeapTag)
{
	char* pMem = Util::allocBytes(nSize);

	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize);

	Str sTag = getValidTag(sHeapTag);

	MemoryManager::addHeader(pHeader, &sTag);

	Footer* pFooter = Util::getFooter(pHeader);
	pFooter->init();

	void* pStartMemBlock = Util::getDataPtr(pHeader);

	std::cout
		<< "\non selected heap: " << sTag.str
		<< "\naddress selected: "
		<< std::hex << (void*)pMem
		<< "\nheader address: "
		<< std::hex << pHeader
		<< "\n  data address: "
		<< std::hex << pStartMemBlock
		<< "\nfooter address: "
		<< std::hex << pFooter
		<< std::endl;

	return pStartMemBlock;
}

void* MemoryManager::allocToHeap(size_t nSize, Str* sHeapTag)
{
	return MemoryManager::allocFrame(nSize, sHeapTag);
}

void* MemoryManager::allocToPool(size_t nSize, Str* sHeapTag)
{
	Heap* pHeap = findHeap(sHeapTag);

	std::cout
		<< "MemoryManager - allocating "
		<< std::dec << nSize
		<< " bytes to pool on heap "
		<< pHeap->getTag() << std::endl;

	Pool* pPool = pHeap->getPoolWithBytesFree(nSize);
	
	if (pPool == nullptr)
	{
		size_t nPoolSize = MemoryPool::calcPoolSize(nSize);

		pPool = (Pool*)MemoryManager::allocFrame(nPoolSize, sHeapTag);
		pPool->init(nPoolSize);
		
		pHeap->addPool(pPool);
	}
	
	return pPool->addItem(nSize);
}

void MemoryManager::freeFromHeap(void* pMem)
{
	Header* pHeader = Util::getHeader(pMem);
	size_t nFullSize = pHeader->m_nFullSize;
	std::cout
		<< "header captured at address: "
		<< std::hex << pHeader << std::endl;
	pHeader->validate();

	Footer* pFooter = Util::getFooter(pMem);
	std::cout
		<< "footer captured at address: "
		<< std::hex << pFooter << std::endl;
	pFooter->validate();

	MemoryManager::delItem(pHeader);

	free(pHeader);
	std::cout
		<< "object deleted : bytes freed = "
		<< std::dec << nFullSize << std::endl;
}

void MemoryManager::freeFromPool(void* pMem)
{
	Item* pItem = Util::getItem(pMem);
	//pItem->
	//
	//size_t nFullSize = pHeader->m_nFullSize;
	//std::cout
	//	<< "header captured at address: "
	//	<< std::hex << pHeader << std::endl;
	//pHeader->validate();

	//Footer* pFooter = Util::getFooter(pMem);
	//std::cout
	//	<< "footer captured at address: "
	//	<< std::hex << pFooter << std::endl;
	//pFooter->validate();

	//MemoryManager::delItem(pHeader);
}