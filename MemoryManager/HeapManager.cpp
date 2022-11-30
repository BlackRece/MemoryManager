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


Heap* HeapManager::getHeap(const std::string tag)
{
	//Heap* pHeap = findHeap(tag);
	std::cout
		<< "HeapManager - getHeap from heap tag...\n";

	Heap* pHeap = nullptr;

	if (HeapManager::s_pHeaps == nullptr)
	{
		HeapManager::s_pHeaps = new (nullptr) Heap();
		return HeapManager::s_pHeaps;
	}
	
	pHeap = findHeap(tag);
	
	return pHeap;
}

Heap* HeapManager::getHeap(Heap* pHeap)
{
	std::cout
		<< "HeapManager - getHeap from heap pointer...\n";
	
	std::string heapTag = pHeap == nullptr 
		? heapTag = DEFAULT_HEAP_TAG
		: heapTag = pHeap->getTag();
		
	return getHeap(heapTag);
}

Heap* HeapManager::findHeap(std::string tag)
{
	std::cout
		<< "HeapManager - findHeap...\n";

	if (s_pHeaps == nullptr)
		return getHeap(tag);
	
	Heap* pHeap = s_pHeaps;
	
	//while (pHeap != nullptr)
	while (!pHeap->hasTag(tag))
	{
		if (pHeap->getNext() == nullptr)
			return getHeap(tag);
		
		pHeap = pHeap->getNext();
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

void HeapManager::initHeap(std::string tag)
{
	s_pHeaps = Heap::initHeap(tag);
}

void HeapManager::initHeap()
{
	size_t nHeaderSize = sizeof(Header);
	size_t nHeapSize = sizeof(Heap);
	size_t nRequestedBytes = nHeaderSize + nHeapSize;
	char* pMem = (char*)malloc(nRequestedBytes);

	s_pHeaps = (Heap*)pMem + nHeaderSize;
	s_pHeaps->CreateDefaultHeap();

	Header* pHeader = (Header*)pMem;
	pHeader->init(nRequestedBytes, s_pHeaps);

	std::cout
		<< "new heap initialised \n at address : "
		<< std::hex << pMem << std::endl;
}

void HeapManager::checkHeap()
{
	
}