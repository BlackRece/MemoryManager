#include "MemoryManager.h"

void* operator new(size_t nSize)
{
	if (!HeapManager::isDebugEnabled())
		return malloc(nSize);
	
	std::cout
		<< "global operator new called ... \n";
	
	char* pMem = Util::allocBytes(nSize);
	
	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize);
	
	HeapManager::addHeaderToHeap(pHeader);

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
	if (!HeapManager::isDebugEnabled())
		return malloc(nSize);

	std::cout
		<< "global operator new called ..."
		<< "with size: " << nSize
		<< "for heap: " << pHeapTag
		<< std::endl;

	void* pMem = Util::allocBytes(nSize);

	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize);

	HeapManager::addHeaderToHeap(pHeader, pHeapTag);

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
	if (!HeapManager::isDebugEnabled())
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
		
	HeapManager::delHeaderFromHeap(pHeader);
	
	free(pHeader);
	std::cout 
		<< "object deleted : bytes freed = "
		<< std::dec << nFullSize << std::endl;
}
