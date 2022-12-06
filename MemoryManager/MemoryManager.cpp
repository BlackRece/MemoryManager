#include "MemoryManager.h"

void* operator new(size_t nSize)
{
	std::cout 
		<< "global operator new called ... \n"
		<< "with size : " << std::dec << nSize << std::endl;
	
	char* pMem = allocBytes(nSize);
	std::cout
		<< std::dec << nSize << " bytes allocated.\n" << std::hex
		<< "Header at : \t\t" << (void*)pMem 
		<< "Data at : \t\t"
		<< std::endl;
	
	Header* pHeader = (Header*)pMem;
	pHeader->init(nSize);
	//pHeader->m_pHeap = HeapManager::getHeap();
	HeapManager::addHeaderToHeap(pHeader);

	//Footer* pFooter = (Footer*)(pMem + sizeof(Header) + nSize);
	Footer* pFooter = pHeader->getFooter();
	pFooter->init();
	
	void* pStartMemBlock = pMem + sizeof(Header);
	
	std::cout
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

void* operator new (size_t nSize, Heap* pHeap)
{
	std::cout
		<< "global operator new called ..."
		<< "with size: " << nSize << std::endl;

	void* pMem = allocBytes(nSize);

	std::cout
		<< std::dec << nSize << " bytes allocated at address : "
		<< std::hex << (void*)pMem << std::endl;
	
	Header* pHeader = (Header*)pMem;
	std::cout 
		<< "header assigned to address :" 
		<< std::hex << pMem << std::endl;

	pHeader->init(nSize, pHeap);
	std::cout << "header initialised" << std::endl;
	
	pHeader->m_pHeap = HeapManager::getHeap(pHeap);
	//pHeap->addBytes(nSize);
	
	void* pFooterAddress = (char*)pMem + sizeof(Header) + nSize;
	Footer* pFooter = (Footer*)pFooterAddress;
	pFooter->init();
	std::cout << "footer initialised" << std::endl;

	void* pStartMemBlock = (char*)pMem + sizeof(Header);
	//void* pStartMemBlock = getData(pMem);
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
		
	Header* pHeader = (Header*)((char*)pMem - sizeof(Header));
	size_t nSize = pHeader->m_nSize;
	std::cout 
		<< std::dec << nSize 
		<< "bytes header captured at address: " 
		<< std::hex << pHeader << std::endl;
	
	// why do I need to get the footer?
	// especially when I don't use it?
	Footer* pFooter = (Footer*)((char*)pMem + nSize);
	std::cout 
		<< "footer captured at address: " 
		<< std::hex << pFooter << std::endl;

	if (pFooter->isValid())
		std::cout
		<< "Error: Footer check value is invalid!\n";
	else
		std::cout
		<< "Footer check value OK!";
		
	//Heap* pHeap = pHeader->m_pHeap;
	//pHeap->delBytes(nSize);
	//free(pMem);
	free(pHeader);
	std::cout 
		<< "header deleted : bytes freed = "
		<< std::dec << nSize << std::endl;
}

char* allocBytes (size_t size)
{
	size_t nHead = sizeof(Header);
	size_t nFoot = sizeof(Footer);
	size_t totalSize = size + nHead + nFoot;
	std::cout 
		<< std::dec
		<< "requested size: " << size << std::endl
		<< "header size: " << nHead << std::endl
		<< "footer size: " << nFoot << std::endl
		<< "===========" << std::endl
		<< "total size: " << totalSize << std::endl;

	char* pResult = (char*)malloc(totalSize);
	std::cout
		<< "\naddress selected: " 
		<< std::hex << (void*)pResult
		<< std::endl;

	return pResult;
}
MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
}
