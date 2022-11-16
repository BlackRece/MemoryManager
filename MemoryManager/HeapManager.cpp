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

Heap* HeapManager::getHeap(std::string tag)
{
	//Heap* pHeap = findHeap(tag);
	std::cout
		<< "HeapManager - getHeap...\n";

	if (HeapManager::s_pHeaps == nullptr)
		HeapManager::s_pHeaps = Heap::initHeap(tag);
	
	return 	HeapManager::s_pHeaps;
	
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
