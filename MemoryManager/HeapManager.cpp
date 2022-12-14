#include <iostream>
#include "HeapManager.h"

Heap* HeapManager::s_pHeaps = nullptr;

HeapManager::HeapManager()
{
}

HeapManager::~HeapManager()
{
}

//Heap* HeapManager::makeHeap(std::string tag)
//{
//	Heap* pHeap = new Heap();
//	pHeap->initHeap();
//	
//	//m_pHeaps = (Heap*) Heap(tag);
//	pHeap->setTag(tag);
//	return pHeap;
//}

Heap* HeapManager::getHeap()
{
	return HeapManager::s_pHeaps;
}

void HeapManager::addHeaderToHeap(Header* pNewHeader)
{
	// assign header to this heap
	pNewHeader->m_pHeap = s_pHeaps;

	s_pHeaps->addNextHeader(pNewHeader);
}

void HeapManager::addHeaderToHeap(Header* pNewHeader, char sHeapTag[])
{
	Heap* pHeap = getHeap(sHeapTag);
	
	pNewHeader->m_pHeap = pHeap;
	pHeap->addNextHeader(pNewHeader);
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

Heap* HeapManager::findHeap(char tag[])
{
	std::cout
		<< "HeapManager - findHeap...\n";

	if (s_pHeaps == nullptr)
		return getHeap(tag);
	
	Heap* pHeap = s_pHeaps;
	
	//while (pHeap != nullptr)
	while (!pHeap->hasTag())
	{
		if (pHeap->getNextHeap() == nullptr)
			return getHeap(tag);
		
		pHeap = pHeap->getNextHeap();
	}

	return pHeap;
}

//Heap* HeapManager::findHeap(std::string tag)
//{
//	Log::msg("Searching for heap name: " + tag);
//	Heap* pHeap = (Heap*)s_pHeaps;
//	
//	while (pHeap != nullptr)
//	{
//		if (pHeap->hasTag(tag))
//		{
//			Log::msg("Heap " + tag + "found.");
//			return pHeap;
//		}
//		
//		pHeap = pHeap->getNext();
//	}
//	
//	Log::msg("Heap " + tag + "not found");
//	return nullptr;
//}

void HeapManager::createDefaultHeap()
{
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

void HeapManager::checkHeaps()
{
	Heap* pHeap = (Heap*)s_pHeaps;

	while (pHeap != nullptr)
	{
		pHeap->checkHeap();
		pHeap = pHeap->getNextHeap();
	}
}

void HeapManager::createHeap(char sHeapTag[])
{
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