#include <iostream>
#include "HeapManager.h"

Heap* HeapManager::s_pHeaps = nullptr;
bool HeapManager::m_bDebugMode = true;

HeapManager::HeapManager()
{
}

HeapManager::~HeapManager()
{
}

void HeapManager::addHeaderToHeap(Header* pHeader)
{
	Heap* pDefaultHeap = s_pHeaps;
	pHeader->m_pHeap = pDefaultHeap;

	pDefaultHeap->addHeader(pHeader);
	pDefaultHeap->addBytes(pHeader->m_nFullSize);
}

void HeapManager::addHeaderToHeap(Header* pHeader, char sHeapTag[])
{
	Heap* pHeap = getHeap(sHeapTag);
	pHeader->m_pHeap = pHeap;

	pHeap->addHeader(pHeader);
	pHeap->addBytes(pHeader->m_nFullSize);
}

void HeapManager::delHeaderFromHeap(Header* pHeader)
{
	Heap* pHeap = pHeader->m_pHeap;
	pHeap->subBytes(pHeader->m_nFullSize);
	pHeap->delHeader(pHeader);
}

Heap* HeapManager::getHeap(char tag[])
{
	std::cout
		<< "HeapManager - getHeap from heap tag...\n";

	Heap* pTargetHeap = HeapManager::getHeap();

	while (pTargetHeap != nullptr)
	{
		int result = strcmp(pTargetHeap->getTag(), tag);
		if (result == 0) return pTargetHeap;

		pTargetHeap = pTargetHeap->getNextHeap();
	}

	return HeapManager::getHeap();
}

void HeapManager::initDefaultHeap(bool bDebugMobe)
{
	HeapManager::m_bDebugMode = bDebugMobe;
	
	if (!isDebugEnabled())
	{
		std::cout
			<< "Memory Manager not available in release mode.\n";

		return;
	}

	if (s_pHeaps != nullptr)
		return;
	
	size_t nHeapSize = sizeof(Heap);
	char* pMem = Util::allocBytes(nHeapSize);

	Heap* pHeap = (Heap*)Util::getPointer(pMem);
	
	Header* pHeader = Util::getHeader(pHeap);
	pHeader->init(nHeapSize);
	pHeader->m_pHeap = pHeap;
	
	Footer* pFooter = Util::getFooter(pHeap);
	pFooter->init();
	
	s_pHeaps = pHeap;
	s_pHeaps->initDefaultHeap(pHeader);
	
	std::cout
		<< "\ndefault heap created at address : "
		<< std::hex << s_pHeaps 
		<< "\nheap header : " << pHeader
		<< "\nheap footer : " << pFooter
		<< std::endl;
}

void HeapManager::addHeap(char sHeapTag[])
{
	if (s_pHeaps == nullptr)
		return;

	size_t nHeapSize = sizeof(Heap);
	char* pMem = Util::allocBytes(nHeapSize);

	Heap* pHeap = (Heap*)Util::getPointer(pMem);

	Header* pHeader = Util::getHeader(pHeap);
	pHeader->init(nHeapSize);
	pHeader->m_pHeap = pHeap;

	Footer* pFooter = Util::getFooter(pHeap);
	pFooter->init();

	pHeap->initHeap(pHeader, sHeapTag);

	std::cout
		<< "\nnew heap created at address : "
		<< std::hex << s_pHeaps
		<< "\nheap header : " << pHeader
		<< "\nheap footer : " << pFooter
		<< std::endl;
	
	Heap* pTargetHeap = getLastHeap();
	
	pTargetHeap->setNextHeap(pHeap);
	pHeap->setPrevHeap(pTargetHeap);
}

void HeapManager::delHeap(char heapTag[])
{
	Heap* pHeap = getHeap(heapTag);
	pHeap->clearHeap();

	Header* pHeader = pHeap->getHeapHeader();
	pHeap->delHeader(pHeader);
	free(pHeader);
}

void HeapManager::checkHeaps()
{
	Heap* pHeap = (Heap*)s_pHeaps;

	while (pHeap != nullptr)
	{
		pHeap->checkHeap();
		pHeap = pHeap->getNextHeap();
	}
}

Heap* HeapManager::getLastHeap()
{
	Heap* pTargetHeap = HeapManager::getHeap();
	Heap* pNextHeap = pTargetHeap->getNextHeap();

	int heapCount = 1;
	while (pNextHeap != nullptr)
	{
		pTargetHeap = pNextHeap;
		pNextHeap = pTargetHeap->getNextHeap();
		heapCount++;
	}

	std::cout << "Heaps Counted = " << heapCount << std::endl;
	return pTargetHeap;
}

void HeapManager::clearHeaps()
{
	Heap* pHeap = (Heap*)s_pHeaps;

	while (pHeap != nullptr)
	{
		pHeap->clearHeap();
		pHeap = pHeap->getNextHeap();
	}
}

void HeapManager::clearHeap(char heapTag[])
{
	Heap* pHeap = getHeap(heapTag);
	pHeap->clearHeap();
}