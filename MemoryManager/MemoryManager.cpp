#include "MemoryManager.h"
#include "Structures.h"


void* operator new(size_t size)
{
	std::cout << "global operator new called with size: " << size << std::endl;
	size_t nRequestedBytes = size + sizeof(Header) + sizeof(Footer);
	char* pMem = (char*)malloc(nRequestedBytes);

	Header* pHeader = (Header*)pMem;
	pHeader->size = size;
	pHeader->checkValue = HEAD_VALUE;

	void* FooterAddress = (void*)(pMem + sizeof(Header) + size);
	Footer* pFooter = (Footer*)FooterAddress;
	pFooter->checkValue = FOOT_VALUE;

	// TODO: set some values in the footer


	
	void* pStartMemBlock = pMem + sizeof(Header);
	return pStartMemBlock;
}

void operator delete(void* ptr)
{
	std::cout << "global operator delete called at address" << std::hex << (int*)ptr << std::endl;
	Header* pHeader = (Header*)((char*)ptr - sizeof(Header));
	
	
	Footer* pFooter = (Footer*)((char*)ptr + pHeader->size);


	
	free(pHeader);
}