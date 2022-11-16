#pragma once
#include "Structures.h"
#include <string>

class Heap
{
public:
	//Heap() {};
	Heap(std::string tag);
	//~Heap() {};
	
	//static int getBytesInUse() { return m_iByteCount; }

	//static void* operator new(size_t size);
	//static void* operator new(size_t size, Heap* heap);
	//static void operator delete(void* pMem, size_t size);
	//void* operator new(size_t size, std::string tag);
	//void operator delete(void* pMem);

	void	CreateHeap();
	static Heap*		initHeap(std::string tag);
	//void*				allocHeap(std::string tag);

	//void				addBytes(size_t size) { m_iByteCount += size; }
	//void				delBytes(size_t size) { m_iByteCount -= size; }
	//size_t				getBytes() { return m_iByteCount; }

	const bool			hasTag(std::string nameTag) { return m_sTag == nameTag; }
	void				setTag(const std::string nameTag) { m_sTag = nameTag; }
	const std::string	getTag() { return m_sTag; }
	
	// linked list of heaps
	Heap*				getNext() { return m_pNext; }
	void				setNext(Heap* pNext) { m_pNext = pNext; }
	
	Heap*				getPrev() { return m_pPrev; }
	void				setPrev(Heap* pPrev) { m_pPrev = pPrev; }
	
private:
	size_t				m_iByteCount;
	std::string			m_sTag;
	
	Header*				m_pHeader;
	
	Heap*				m_pNext;
	Heap*				m_pPrev;
};

