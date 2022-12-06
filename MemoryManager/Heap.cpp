#include "Heap.h"
#include <iostream>

Heap::Heap()
{ 
	m_sTag = "";// DEFAULT_HEAP_TAG;
	
	m_nByteCount = 0;
	m_nBytesAdded = 0;
	m_nBytesRemoved = 0;
	
	m_pHeader = nullptr;

	m_pNext = nullptr;
	m_pPrev = nullptr;
	
	std::cout << "heap initialised : " << m_sTag << std::endl;
}

//void* Heap::operator new(size_t size)
//{
//	//return ::operator new(size, HeapManager::getHeap());
//	return ::operator new(size);
//}
//
//void Heap::operator delete(void* pMem, size_t size)
//{
//	std::cout
//		<< "heap operator delete called \n"
//		<< "with size : " << size << std::endl
//		<< "and pointer : " << std::hex << pMem << std::endl;
//	::operator delete(pMem);
//}

void Heap::CreateDefaultHeap(Header* pHeader)
{
	//if tag is null, then heap is default
	//m_sTag = "";

	//m_sTag = (std::string)DEFAULT_HEAP_TAG;
	
	m_nByteCount = 0;
	m_nBytesAdded = 0;
	m_nBytesRemoved = 0;
	
	m_pHeader = pHeader;

	m_pNext = nullptr;
	m_pPrev = nullptr;

	std::cout 
		<< "heap initialised : " 
		<< m_sTag << std::endl;
}

void Heap::CreateHeap(std::string tag)
{
	m_sTag = tag;

	m_nByteCount = 0;

	m_pHeader = nullptr;

	m_pNext = nullptr;
	m_pPrev = nullptr;

	std::cout << "heap initialised : " << std::endl;
}


Heap* Heap::initHeap(std::string tag)
{
	std::cout
		<< "tag: " << tag << std::endl;

	size_t nHeaderSize = sizeof(Header);
	size_t nHeapSize = sizeof(Heap);
	size_t nRequestedBytes = nHeaderSize + nHeapSize;
	char* pMem = (char*)malloc(nRequestedBytes);
	
	Heap* pHeap = (Heap*)pMem + nHeaderSize;
	pHeap->CreateHeap(tag);

	Header* pHeader = (Header*)pMem;
	pHeader->init(nRequestedBytes, pHeap);

	//pHeader->init(nRequestedBytes, (Heap*)pMem + nHeaderSize);
	//pHeader->m_pHeap = (Heap*)pMem + nHeaderSize;
	std::cout
		<< "new heap initialised \n at address : "
		<< pMem << std::endl;
	
	
	
	/*m_iByteCount = 0;
	m_sTag = "";
	m_pHeader = nullptr;

	m_pNext = nullptr;
	m_pPrev = nullptr;*/
	return pHeader->m_pHeap;
}

//void* Heap::allocHeap(std::string tag)
//{
//	initHeap();
//	m_sTag = tag;
//	Log::msg("heap allocated with tag: " + tag);
//	
//	size_t nSize = sizeof(Heap) + sizeof(Header) + sizeof(Footer);
//	char* pMem = (char*)malloc(nSize);
//	
//	Header* pHeader = (Header*)pMem;
//	pHeader->m_nSize = nSize;
//	pHeader->m_iCheckValue = HEAD_VALUE;
//	pHeader->m_pHeap = (Heap*)pMem + sizeof(Header);
//	
//	//return pHeader->m_pHeap;
//}

void Heap::checkHeap()
{
	//TODO: Heap is empty at this point
	//check if heap is empty
	if (m_pHeader == nullptr)
	{
		std::cout << "Heap is empty" << std::endl;
		return;
	}
	
	//check if heap is valid
	Header* pHeader = m_pHeader;
	while (pHeader != nullptr)
	{
		if (!pHeader->isValid())
		{
			std::cout << "Header is invalid" << std::endl;
			return;
		}
		
		std::cout << "Header is valid" << std::endl;

		Footer* pFooter = pHeader->getFooter();
		if (pFooter != nullptr)
		{
			if (!pFooter->isValid())
			{
				std::cout << "Footer is invalid" << std::endl;
				return;
			}
			
			std::cout << "Footer is valid" << std::endl;
		}
		
		std::cout 
			//<< "Footer is null\n" 
			<< std::dec
			<< "ByteCount = " << pHeader->m_nSize << std::endl;
		
		pHeader = pHeader->m_pNext;
	}
}

Header* Heap::getHeader()
{
	return m_pHeader == nullptr
		? (Header*)(char*)this - sizeof(Header)
		: m_pHeader;
}

Heap* Heap::setHeader(Header* pHeader)
{
	m_pHeader = pHeader;
	return m_pHeader->m_pHeap;
}

void Heap::addNextHeader(Header* pHeader)
{
	Header* pTargetHeader = getLastHeader();
	pTargetHeader->m_pNext = pHeader;
	pHeader->m_pPrev = pTargetHeader;
}

Header* Heap::getLastHeader()
{
	Header* pParentHeader = m_pHeader;
	Header* pCurrentHeader = pParentHeader->m_pNext;

	int headerCount = 0;
	while (pCurrentHeader != nullptr)
	{
		pParentHeader = pCurrentHeader;
		pCurrentHeader = pParentHeader->m_pNext;
		headerCount++;
	}
	
	std::cout << "Header Count = " << headerCount << std::endl;
	return pParentHeader;
}