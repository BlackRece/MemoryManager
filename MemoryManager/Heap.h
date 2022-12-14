#pragma once
#include <cmath>
#include <string.h>
#include "Util.h"

#define TAG_LENGTH 30

class Heap
{
public:
	Heap(char heapTag[]);
	~Heap();
	
	void				initDefaultHeap(Header* pHeader);
	void				initHeap(Header* pHeader, char sHeapTag[]);
	void				checkHeap();
	
	Heap*				setHeader(Header* pHeader);
	void				addNextHeader(Header* pHeader);

	//void				addBytes(size_t size) { m_iByteCount += size; }
	//void				delBytes(size_t size) { m_iByteCount -= size; }
	//size_t				getBytes() { return m_iByteCount; }
	
	void				addBytes(size_t byteCount) { m_nBytesAdded += std::abs((int)byteCount); }
	void				subBytes(size_t byteCount) { m_nBytesRemoved += std::abs((int)byteCount); }
	size_t				getBytes() { return m_nBytesAdded - m_nBytesRemoved; }

	const bool			hasTag() { return m_sTag != ""; }
	char*				getTag() { return m_sTag; }
	
	// this header
	Header*				getHeader();
	
	// linked list of heaps
	void				addHeap(Heap* pHeap);
	Heap*				getNextHeap() { return m_pNext; }
	void				setNextHeap(Heap* pNext) { m_pNext = pNext; }
	
	Heap*				getPrev() { return m_pPrev; }
	void				setPrevHeap(Heap* pPrev) { m_pPrev = pPrev; }
	
	// linked list of headers
	Header*				getNextHeader() { return m_pHeader->m_pNext; }
	void				setNextHeader(Header* pNextHeader) { m_pHeader->m_pNext = pNextHeader; }
	
private:	
	// heap info
	char				m_sTag[TAG_LENGTH];
	Heap*				m_pNext;
	Heap*				m_pPrev;
	
	size_t				m_nByteCount;
	size_t				m_nBytesAdded;
	size_t				m_nBytesRemoved;
	
	// header info
	Header*				m_pHeader;
	Header*				getLastHeader();
};