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
		? heapTag = ""//DEFAULT_HEAP_TAG
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
	while (!pHeap->hasTag())
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
	size_t nHeadSize = sizeof(Header);
	size_t nHeapSize = sizeof(Heap);
	size_t nFootSize = sizeof(Footer);
	size_t nRequestedBytes = nHeadSize + nHeapSize + nFootSize;
	char* pMem = (char*)malloc(nRequestedBytes);
	
	Heap* pHeap = (Heap*)(pMem + nHeadSize);
	s_pHeaps = pHeap;
	
	//Header* pHeader = s_pHeaps->getHeader();
	Header* pHeader = (Header*)pMem;
	pHeader->init(nRequestedBytes);
	pHeader->m_pHeap = s_pHeaps;

	//Footer* pFooter = pHeader->getFooter();
	Footer* pFooter = (Footer*)(pMem + nHeadSize + nHeapSize);
	pFooter->init();

	s_pHeaps->CreateDefaultHeap(pHeader);

	std::cout
		<< "new heap initialised \n at address : "
		<< std::hex << s_pHeaps << std::endl;
}

void HeapManager::checkHeaps()
{
	//walk the heap
	Heap* pHeap = (Heap*)s_pHeaps;

	//bool isDefault = false;
	
	while (pHeap != nullptr)
	{
		//if (!s_pHeaps->hasTag())
		//{
		//	if (isDefault)
		//	{
		//		//throw error
		//		std::cout
		//			<< "ERROR: Default header already set!";

		//		return;
		//	}

		//	std::cout
		//		<< "Default Heap has No Tag!\n"
		//		<< "Checking Heap : [Default]\n";

		//	isDefault = true;
		//}
		//else
		//{
		//	std::cout 
		//		<< "Checking Heap : " << s_pHeaps->getTag() << std::endl;
		//}

		pHeap->checkHeap();
		pHeap = pHeap->getNext();
	}
}