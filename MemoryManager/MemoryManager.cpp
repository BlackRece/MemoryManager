#include "MemoryManager.h"

Heap* MemoryManager::s_pHeaps = nullptr;
bool MemoryManager::m_bDebugMode = true;

void* operator new(size_t nSize)
{
	if (!MemoryManager::isDebugEnabled())
		return malloc(nSize);
	
	std::cout
		<< "global operator new called ... \n";
	
	char* pMem = Util::allocBytes(nSize);
	
	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize);
	
	MemoryManager::addHeaderToHeap(pHeader);

	Footer* pFooter = Util::getFooter(pHeader);
	pFooter->init();
	
	void* pStartMemBlock = Util::getDataPtr(pHeader);
	
	std::cout
		<< "\non the default heap"
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

void* operator new (size_t nSize, char pHeapTag[])
{
	if (!MemoryManager::isDebugEnabled())
		return malloc(nSize);

	std::cout
		<< "global operator new called ..."
		<< "with size: " << nSize
		<< "for heap: " << pHeapTag
		<< std::endl;

	void* pMem = Util::allocBytes(nSize);

	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize);

	MemoryManager::addHeaderToHeap(pHeader, pHeapTag);

	Footer* pFooter = Util::getFooter(pHeader);
	pFooter->init();
	
	void* pStartMemBlock = Util::getDataPtr(pHeader);

	std::cout
		<< "\non selected heap: " << pHeapTag
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

void operator delete(void* pMem)
{
	if (!MemoryManager::isDebugEnabled())
	{
		free(pMem);
		return;
	}

	std::cout 
		<< "global operator delete called \n"
		<< "for address : " << std::hex << pMem
		<< std::endl;
		
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
		
	MemoryManager::delHeaderFromHeap(pHeader);
	
	free(pHeader);
	std::cout 
		<< "object deleted : bytes freed = "
		<< std::dec << nFullSize << std::endl;
}

void MemoryManager::addHeaderToHeap(Header* pHeader)
{
	Heap* pDefaultHeap = s_pHeaps;
	pHeader->m_pHeap = pDefaultHeap;

	pDefaultHeap->addHeader(pHeader);
	pDefaultHeap->addBytes(pHeader->m_nFullSize);
}

void MemoryManager::addHeaderToHeap(Header* pHeader, char sHeapTag[])
{
	Heap* pHeap = getHeap(sHeapTag);
	pHeader->m_pHeap = pHeap;

	pHeap->addHeader(pHeader);
	pHeap->addBytes(pHeader->m_nFullSize);
}

void MemoryManager::delHeaderFromHeap(Header* pHeader)
{
	Heap* pHeap = pHeader->m_pHeap;
	pHeap->subBytes(pHeader->m_nFullSize);
	pHeap->delHeader(pHeader);
}

Heap* MemoryManager::getHeap(char tag[])
{
	std::cout
		<< "MemoryManager - getHeap from heap tag...\n";

	Heap* pTargetHeap = MemoryManager::getHeap();

	while (pTargetHeap != nullptr)
	{
		int result = strcmp(pTargetHeap->getTag(), tag);
		if (result == 0) return pTargetHeap;

		pTargetHeap = pTargetHeap->getNextHeap();
	}

	return MemoryManager::getHeap();
}

void MemoryManager::initDefaultHeap(bool bDebugMobe)
{
	MemoryManager::m_bDebugMode = bDebugMobe;

	if (!isDebugEnabled())
	{
		std::cout
			<< "Memory Manager not available in release mode.\n";

		return;
	}

	if (s_pHeaps != nullptr)
		return;

	size_t nHeapSize = sizeof(Heap);
	char* pMem = Util::allocBytes(nHeapSize);

	Heap* pHeap = (Heap*)Util::getPointer(pMem);

	Header* pHeader = Util::getHeader(pHeap);
	pHeader->init(nHeapSize);
	pHeader->m_pHeap = pHeap;

	Footer* pFooter = Util::getFooter(pHeap);
	pFooter->init();

	s_pHeaps = pHeap;
	s_pHeaps->initDefaultHeap(pHeader);

	std::cout
		<< "\ndefault heap created at address : "
		<< std::hex << s_pHeaps
		<< "\nheap header : " << pHeader
		<< "\nheap footer : " << pFooter
		<< std::endl;
}

void MemoryManager::addHeap(char sHeapTag[])
{
	if (s_pHeaps == nullptr)
		return;

	size_t nHeapSize = sizeof(Heap);
	char* pMem = Util::allocBytes(nHeapSize);

	Heap* pHeap = (Heap*)Util::getPointer(pMem);

	Header* pHeader = Util::getHeader(pHeap);
	pHeader->init(nHeapSize);
	pHeader->m_pHeap = pHeap;

	Footer* pFooter = Util::getFooter(pHeap);
	pFooter->init();

	pHeap->initHeap(pHeader, sHeapTag);

	std::cout
		<< "\nnew heap created at address : "
		<< std::hex << s_pHeaps
		<< "\nheap header : " << pHeader
		<< "\nheap footer : " << pFooter
		<< std::endl;

	Heap* pTargetHeap = getLastHeap();

	pTargetHeap->setNextHeap(pHeap);
	pHeap->setPrevHeap(pTargetHeap);
}

void MemoryManager::delHeap(char heapTag[])
{
	Heap* pHeap = getHeap(heapTag);
	pHeap->clearHeap();

	Header* pHeader = pHeap->getHeapHeader();
	pHeap->delHeader(pHeader);
	free(pHeader);
}

void MemoryManager::checkHeaps()
{
	Heap* pHeap = (Heap*)s_pHeaps;

	while (pHeap != nullptr)
	{
		pHeap->checkHeap();
		pHeap = pHeap->getNextHeap();
	}
}

Heap* MemoryManager::getLastHeap()
{
	Heap* pTargetHeap = MemoryManager::getHeap();
	Heap* pNextHeap = pTargetHeap->getNextHeap();

	int heapCount = 1;
	while (pNextHeap != nullptr)
	{
		pTargetHeap = pNextHeap;
		pNextHeap = pTargetHeap->getNextHeap();
		heapCount++;
	}

	std::cout << "Heaps Counted = " << heapCount << std::endl;
	return pTargetHeap;
}

void MemoryManager::clearHeaps()
{
	Heap* pHeap = (Heap*)s_pHeaps;

	while (pHeap != nullptr)
	{
		pHeap->clearHeap();
		pHeap = pHeap->getNextHeap();
	}
}

void MemoryManager::clearHeap(char heapTag[])
{
	Heap* pHeap = getHeap(heapTag);
	pHeap->clearHeap();
}