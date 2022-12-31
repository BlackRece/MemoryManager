#include "Heap.h"

Str* Heap::init(Header* pHeader, Str* sHeapTag)
{
	m_nByteCount = 0;
	m_nBytesAdded = 0;
	m_nBytesRemoved = 0;

	m_pNext = nullptr;
	m_pPrev = nullptr;

	m_pPool = nullptr;

	m_sTag.set(sHeapTag->str);
	
	m_pRootHeader = pHeader;
	addBytes(pHeader->m_nFullSize);
	
	std::cout << std::endl << m_sTag.str << " heap initialised.\n";
	
	return &m_sTag;
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

void Heap::check()
{
	if (m_pRootHeader == nullptr)
	{
		std::cout << "Heap is empty" << std::endl;
		return;
	}
	
	int nCount = 0;
	int nBytes = 0;

	std::cout
		<< "\nWalking the heap..."
		<< "\nHeap tag: " << m_sTag.str
		<< "\n\n address\t\t| bytes"
		<< "\n--------\t\t|------\n";
	
	Header* pHeader = m_pRootHeader;
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

void Heap::clear()
{
	if (m_pRootHeader == nullptr)
	{
		std::cout << "Heap is empty" << std::endl;
		return;
	}

	std::cout
		<< "\Clearing heap: " << m_sTag.str
		<< "\n\n address\t\t| bytes"
		<< "\n--------\t\t|------\n";

	Header* pHeader = m_pRootHeader;
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
			delHeader(pHeader);

		pHeader = pNextHeader;
	}
}

bool Heap::isHeapHeader(Header* pHeader)
{
	Heap* pHeap = pHeader->m_pHeap;
	Header* pHeapHeader = pHeap->m_pRootHeader;

	return pHeader == pHeapHeader;
}

Heap* Heap::setHeader(Header* pHeader)
{
	m_pRootHeader = pHeader;
	return m_pRootHeader->m_pHeap;
}

void Heap::addHeader(Header* pHeader)
{
	Header* pTargetHeader = getLastHeader();
	pTargetHeader->m_pNext = pHeader;
	
	pHeader->m_pPrev = pTargetHeader;
	pHeader->m_pHeap = pTargetHeader->m_pHeap;
	
	addBytes(pHeader->m_nFullSize);
}

void Heap::delHeader(Header* pHeader)
{
	Header* pNextHeader = pHeader->m_pNext;
	Header* pPrevHeader = pHeader->m_pPrev;

	if (pPrevHeader != nullptr)
		pPrevHeader->m_pNext = pNextHeader;

	if (pNextHeader != nullptr)
		pNextHeader->m_pPrev = pPrevHeader;
	
	subBytes(pHeader->m_nFullSize);
	free(pHeader);
}

Header* Heap::getLastHeader()
{
	Header* pCurrentHeader = m_pRootHeader;
	Header* pNextHeader = pCurrentHeader->m_pNext;

	int headerCount = 1;
	while (pNextHeader != nullptr)
	{
		pCurrentHeader = pNextHeader;
		pNextHeader = pCurrentHeader->m_pNext;
		headerCount++;
	}
	
	std::cout << "Header Count = " << headerCount << std::endl;
	return pCurrentHeader;
}

void Heap::addHeap(Heap* pHeap)
{
	setNextHeap(pHeap);
	pHeap->setPrevHeap(this);
}

Heap* Heap::findHeap(Str sTag)
{
	if (hasTag(sTag))
		return this;
	
	if (m_pNext != nullptr)
		return m_pNext->findHeap(sTag);
	
	return nullptr;
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

Pool* Heap::getPoolWithBytesFree(size_t nSize)
{
	Pool* pPool = m_pPool;

	while (pPool != nullptr)
	{
		if (pPool->hasBytesFree(nSize))
			return pPool;

		pPool = pPool->getNext();
	}

	return pPool;
}

void Heap::addPool(Pool* pPool)
{
	if (m_pPool == nullptr)
	{
		m_pPool = pPool;
		return;
	}

	Pool* pLast = m_pPool->getLast();

	pLast->setNext(pPool);
	pPool->setPrev(pLast);
}
