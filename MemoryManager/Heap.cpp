#include "Heap.h"
#include <iostream>

Heap::Heap(char heapTag[])
{ 
	m_nByteCount = 0;
	m_nBytesAdded = 0;
	m_nBytesRemoved = 0;
	
	m_pHeader = nullptr;

	m_pNext = nullptr;
	m_pPrev = nullptr;

	strcpy_s(m_sTag, heapTag);
	
	std::cout << "heap initialised : " << m_sTag << std::endl;
}

Heap::~Heap()
{
	//TODO: empty heap before deleting.
}

void Heap::initDefaultHeap(Header* pHeader)
{
	strcpy_s(m_sTag, "Default");

	m_nByteCount = 0;
	m_nBytesAdded = 0;
	m_nBytesRemoved = 0;
	
	m_pHeader = pHeader;

	m_pNext = nullptr;
	m_pPrev = nullptr;

	std::cout << "Default heap initialised.\n";
}

void Heap::initHeap(Header* pHeader, char heapTag[])
{
	strcpy_s(m_sTag, heapTag);
	
	m_nByteCount = 0;
	m_nBytesAdded = 0;
	m_nBytesRemoved = 0;

	m_pHeader = pHeader;

	m_pNext = nullptr;
	m_pPrev = nullptr;

	std::cout << std::endl << m_sTag << " heap initialised.\n";
}

void Heap::checkHeap()
{
	if (m_pHeader == nullptr)
	{
		std::cout << "Heap is empty" << std::endl;
		return;
	}
	
	int nCount = 0;
	int nBytes = 0;

	char* heapTag = getTag();
	std::cout
		<< "\nWalking the heap..."
		<< "\nHeap tag: " << heapTag
		<< "\n\n address\t\t| bytes"
		<< "\n--------\t\t|------\n";
	
	//check if heap is valid
	Header* pHeader = m_pHeader;
	while (pHeader != nullptr)
	{
		pHeader->validate();
		
		Footer* pFooter = Util::getFooter(pHeader);
		if (pFooter == nullptr)
			throw "Footer not allocated";
		
		pFooter->validate();
		
		nCount++;
		nBytes += (int)pHeader->m_nFullSize;
		
		std::cout
			<< std::hex << pHeader << "\t| " 
			<< std::dec << pHeader->m_nFullSize
			<< std::endl;
		
		pHeader = pHeader->m_pNext;
	}
	
	std::cout 
		<< "\nByteCount = " 
		<< std::dec	<< nBytes
		<< "\nvariable count = "
		<< std::dec << nCount
		<< std::endl;
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

void Heap::addHeap(Heap* pHeap)
{
	setNextHeap(pHeap);
	pHeap->setPrevHeap(this);
}