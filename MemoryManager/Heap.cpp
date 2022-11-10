#include "Heap.h"
#include "HeapManager.h"
#include "Logger.h"
#include <iostream>

Heap::Heap(std::string tag)
{ 
	m_sTag = tag;
	
	m_iByteCount = 0;
	
	m_pHeader = nullptr;

	m_pNext = nullptr;
	m_pPrev = nullptr;
	
	std::cout << "heap initialised : " << tag << std::endl;
}

//
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