#pragma once

#include <iostream>

#include "Util.h"
#include "Heap.h"
#include "MemoryPool.h"

void* operator new(size_t nSize);
void* operator new(size_t size, char pHeapTag[]);

void operator delete(void* ptr);

class MemoryManager
{
public:
	static bool			isDebugEnabled() { return m_bDebugMode; };
	static bool			isPoolingEnable() { return m_bPoolingMode; };

	static void			init(bool bDebugMobe = true);
	static void*		allocFrame(size_t nSize, Str* sHeapTag = nullptr);
	static void*		allocToHeap(size_t nSize, Str* sHeapTag = nullptr);
	static void*		allocToPool(size_t nSize, Str* sHeapTag = nullptr);

	static void			freeFromHeap(void* pMem);
	static void			freeFromPool(void* pMem);

	static Heap*		addHeap(char heapTag[] = nullptr);
	static void			delHeap(Str* heapTag);
	static void			checkHeaps();
	static void			clearHeaps();
	static void			clearHeap(Str* heapTag);

	static void			addHeader(Header* pNewHeader, Str* sHeapTag = nullptr);
	static void			delItem(Header* pHeader);

private:
						MemoryManager() {}
						~MemoryManager() {}

	static Heap*		newHeap(Str* sHeapTag = nullptr);
	static Heap*		findHeap(Str* tag);
	
	static Str			getValidTag(Str* sTag);

	static bool			m_bDebugMode;
	static bool			m_bPoolingMode;
	static Heap*		s_pRootHeap;
};
