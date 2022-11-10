#include "MemoryManager.h"

void* operator new(size_t size)
{
	//Log::msg("global operator new called with size : " + size);
	//Log::log("global operator new called with size : " + size);
	std::cout << "global operator new called with size : " << size << std::endl;
	void* pMem = allocBytes(size);


	Header* pHeader = (Header*)pMem;
	pHeader->m_nSize = size;
	pHeader->m_iCheckValue = HEAD_VALUE;
	//pHeader->m_pHeap = HeapManager::getHeap();

	//Log::msg("CheckValue: " + Log::toHex(HEAD_VALUE));
	//std::cout << std::hex << "CheckValue: " << HEAD_VALUE << std::endl;
	//pHeader->DebugOutput();

	void* FooterAddress = (char*)pMem + sizeof(Header) + size;
	Footer* pFooter = (Footer*)FooterAddress;

	// TODO: set some values in the footer
	pFooter->iCheckValue = FOOT_VALUE;



	void* pStartMemBlock = (char*)pMem + sizeof(Header);
	return pStartMemBlock;
}

void* operator new (size_t nSize, Heap* pHeap)
{
	void* pMem = allocBytes(nSize);
	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize, pHeap);
	pHeader->m_iCheckValue = HEAD_VALUE;
	
	//pHeap->addBytes(nSize);
	
	
	void* pStartMemBlock = (char*)pMem + sizeof(Header);
	return pStartMemBlock;

	Log::msg(
		"global operator new called ..."
		"with size: " + nSize);
	//Log::msg("with heap: " + pHeap->getTag());
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
	std::cout << "global operator delete called \n"
		<< "for address : " << std::hex << pMem
		<< std::endl;
	//Log::msg("global operator delete called at address" + Log::toHex((unsigned int)pMem));
		
	Header* pHeader = getHead(pMem);
	
	// why do I need to get the footer?
	// especially when I don't use it?
	size_t nSize = pHeader->m_nSize;
	Footer* pFooter = (Footer*)(char*)getData(pMem) + nSize;
	
	//Heap* pHeap = pHeader->m_pHeap;
	//pHeap->delBytes(nSize);
	free(pHeader);
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