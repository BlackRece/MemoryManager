#include "MemoryManager.h"

void* operator new(size_t nSize)
{
	std::cout 
		<< "global operator new called ... \n"
		<< "with size : " << nSize << std::endl;
	
	void* pMem = allocBytes(nSize);
	std::cout
		<< nSize << " bytes allocated at address : "
		<< std::hex << pMem << std::endl;

	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize, nullptr);
	
	Footer* pFooter = getFoot(pMem);
	pFooter->init();

	void* pStartMemBlock = (char*)pMem + sizeof(Header);
	return pStartMemBlock;
}

void* operator new (size_t nSize, Heap* pHeap)
{
	std::cout
		<< "global operator new called ..."
		<< "with size: " << nSize << std::endl;

	void* pMem = allocBytes(nSize);

	std::cout
		<< nSize << " bytes allocated at address : " 
		<< std::hex << pMem << std::endl;
	
	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize, pHeap);
	std::cout << "header initialised" << std::endl;
	
	//pHeap->addBytes(nSize);
	
	Footer* pFooter = getFoot(pMem);
	pFooter->init();
	std::cout << "footer initialised" << std::endl;

	//void* pStartMemBlock = (char*)pMem + sizeof(Header);
	void* pStartMemBlock = getData(pMem);
	std::cout 
		<< "data pointer allocated at : " 
		<< std::hex << pStartMemBlock << std::endl;
	
	return pStartMemBlock;
}

//void* operator new(size_t size, std::string tag)
//{
//	//Log::msg("global operator new called with size: " + size);
//	std::cout
//		<< "global operator new called\n"
//		<< "with size : " << size << std::endl
//		<< "and tag : " << tag << std::endl;
//	
//	//if (!HeapManager::heapExists(tag))
//	//	HeapManager::initHeap(tag);
//
//	//Heap* pHeap = (Heap*)HeapManager::getHeap(tag);
//
//	void* pMem = allocBytes(size);
//		
//	Header* pHeader = getHead(pMem);
//	//pHeader->init(size, pHeap);
//	pHeader->m_iCheckValue = HEAD_VALUE;
//	
//	//Log::msg("CheckValue: " + Log::toHex(pHeader->m_iCheckValue));
//	//pHeader->DebugOutput();
//
//	Footer* pFooter = getFoot(pMem);
//	
//	// TODO: set some values in the footer
//	pFooter->iCheckValue = FOOT_VALUE;
//
//	void* pStartMemBlock = getData(pMem);
//	return pStartMemBlock;
//}

void operator delete(void* pMem)
{
	std::cout 
		<< "global operator delete called \n"
		<< "for address : " << std::hex << pMem
		<< std::endl;
		
	Header* pHeader = getHead(pMem);
	size_t nSize = pHeader->m_nSize;
	std::cout 
		<< nSize << "bytes header captured at address: " 
		<< std::hex << pHeader << std::endl;
	
	// why do I need to get the footer?
	// especially when I don't use it?
	Footer* pFooter = getFoot(pMem);
	std::cout 
		<< "footer captured at address: " 
		<< std::hex << pFooter << std::endl;
	
	//Heap* pHeap = pHeader->m_pHeap;
	//pHeap->delBytes(nSize);
	free(pHeader);
	std::cout 
		<< "header deleted : bytes freed = "
		<< nSize << std::endl;
}

void* allocBytes (size_t size)
{
	size_t totalSize = size + sizeof(Header) + sizeof(Footer);
	return malloc(totalSize);
}

void logHeader(void* ptr)
{
	Header* pHeader = (Header*)ptr;
	Log::msg("Size: " + pHeader->m_nSize);
	Log::msg("CheckValue: " + Log::toHex(pHeader->m_iCheckValue));
	Log::msg("Next Header: " + Log::toHex((int)pHeader->m_pNext));
	Log::msg("Prev Header: " + Log::toHex((int)pHeader->m_pPrev));
}