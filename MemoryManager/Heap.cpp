#include "Heap.h"
#include "HeapManager.h"
#include "Logger.h"
#include <iostream>

void* Heap::operator new(size_t size)
{
	//return ::operator new(size, HeapManager::getHeap());
	return ::operator new(size);
}

void Heap::operator delete(void* pMem, size_t size)
{
	::operator delete(pMem);
	std::cout << "Heap :: deleted size = " << size << std::endl;
}

//void Heap::initHeap()
//{
//	Log::msg("heap initialised.");
//	m_iByteCount = 0;
//	m_sTag = "";
//	m_pHeader = nullptr;
//
//	m_pNext = nullptr;
//	m_pPrev = nullptr;
//}
//
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