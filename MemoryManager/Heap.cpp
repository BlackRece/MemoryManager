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

void Heap::initHeap()
{
	m_nByteCount = 0;
	m_nBytesAdded = 0;
	m_nBytesRemoved = 0;

	m_pNext = nullptr;
	m_pPrev = nullptr;
}

void Heap::initDefaultHeap(Header* pHeader)
{
	initHeap();

	strcpy_s(m_sTag, "Default");
	
	m_pHeader = pHeader;
	addBytes(pHeader->m_nFullSize);

	std::cout << "Default heap initialised.\n";
}

void Heap::initHeap(Header* pHeader, char heapTag[])
{
	initHeap();

	strcpy_s(m_sTag, heapTag);
	
	m_pHeader = pHeader;
	addBytes(pHeader->m_nFullSize);
	
	std::cout << std::endl << m_sTag << " heap initialised.\n";
}

void Heap::addBytes(size_t byteCount) 
{
	size_t nByteAmount = (size_t)std::abs((int)byteCount);
	m_nBytesAdded += nByteAmount;
	m_nByteCount += nByteAmount;
}

void Heap::subBytes(size_t byteCount) 
{
	size_t nByteAmount = (size_t)std::abs((int)byteCount);
	m_nBytesRemoved += nByteAmount;
	m_nByteCount -= nByteAmount;
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

	std::cout
		<< "\n-------------"
		<< "\nHeap Info:"
		<< "\nBytes Added: " << m_nBytesAdded
		<< "\nBytes Minused: " << m_nBytesRemoved
		<< "\n-------------"
		<< "\nByte Tally: " << getBytes()
		<< std::endl;
}

void Heap::clearHeap()
{
	if (m_pHeader == nullptr)
	{
		std::cout << "Heap is empty" << std::endl;
		return;
	}

	char* heapTag = getTag();
	std::cout
		<< "\Clearing heap: " << heapTag
		<< "\n\n address\t\t| bytes"
		<< "\n--------\t\t|------\n";

	Header* pHeader = m_pHeader;
	while (pHeader != nullptr)
	{
		pHeader->validate();

		Footer* pFooter = Util::getFooter(pHeader);
		if (pFooter == nullptr)
			throw "Footer not allocated";

		pFooter->validate();

		std::cout
			<< std::hex << pHeader << "\t| "
			<< std::dec << pHeader->m_nFullSize
			<< std::endl;

		Header* pNextHeader = pHeader->m_pNext;

		if (!isHeapHeader(pHeader))
		{
			delHeader(pHeader);
			free(pHeader);
		}

		pHeader = pNextHeader;
	}
}

bool Heap::isHeapHeader(Header* pHeader)
{
	Heap* pHeap = pHeader->m_pHeap;
	Header* pHeapHeader = pHeap->m_pHeader;

	return pHeader == pHeapHeader;
}

Heap* Heap::setHeader(Header* pHeader)
{
	m_pHeader = pHeader;
	return m_pHeader->m_pHeap;
}

void Heap::addHeader(Header* pHeader)
{
	Header* pTargetHeader = getLastHeader();
	pTargetHeader->m_pNext = pHeader;
	pHeader->m_pPrev = pTargetHeader;
}

void Heap::delHeader(Header* pHeader)
{
	Header* pNextHeader = pHeader->m_pNext;
	Header* pPrevHeader = pHeader->m_pPrev;

	if (pPrevHeader != nullptr)
		pPrevHeader->m_pNext = pNextHeader;

	if (pNextHeader != nullptr)
		pNextHeader->m_pPrev = pPrevHeader;
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

size_t Heap::getBytes() 
{
	size_t nTally = m_nBytesAdded - m_nBytesRemoved;
	if (nTally != m_nByteCount)
	{
		std::cout
			<< std::dec
			<< "\nByte Tally;"
			<< "\n-------------"
			<< "\nexpected =\t" << m_nByteCount
			<< "\ntallied =\t" << nTally
			<< std::endl;

		throw "Error: allocated bytes have not been accounted for!";
	}

	return nTally;
}