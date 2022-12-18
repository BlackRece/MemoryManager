#pragma once

#include <iostream>

#include "Util.h"
#include "Heap.h"

void* operator new(size_t nSize);
void* operator new(size_t size, char pHeapTag[]);

void operator delete(void* ptr);

class MemoryManager
{
public:
	static bool		isDebugEnabled() { return m_bDebugMode; };

	static void		initDefaultHeap(bool bDebugMobe = true);

	static void		addHeap(char heapTag[]);
	static void		delHeap(char heapTag[]);
	static void		checkHeaps();
	static void		clearHeaps();
	static void		clearHeap(char heapTag[]);

	static void		addHeaderToHeap(Header* pHeader);
	static void		addHeaderToHeap(Header* pNewHeader, char sHeapTag[]);
	static void		delHeaderFromHeap(Header* pHeader);

private:
	MemoryManager() {}
	~MemoryManager() {}

	static Heap*	getHeap() { return s_pHeaps; }
	static Heap*	getHeap(char tag[]);
	static Heap*	getLastHeap();

	static bool		m_bDebugMode;

	static Heap*	s_pHeaps;
};
