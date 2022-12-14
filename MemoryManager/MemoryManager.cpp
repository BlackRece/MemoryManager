#include "MemoryManager.h"

void* operator new(size_t nSize)
{
	//TODO: increase heap's byte counter by size of new object
	std::cout
		<< "global operator new called ... \n";
		//<< "with size : " << std::dec << nSize << std::endl;
	
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
	//TODO: increase heap's byte counter by size of new object
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
	//TODO: remove header from heap's linked list
	//TODO: subtract freed bytes from heap's counters
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
		
	free(pHeader);
	std::cout 
		<< "object deleted : bytes freed = "
		<< std::dec << nFullSize << std::endl;
}


MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
}
