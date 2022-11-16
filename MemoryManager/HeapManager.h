#pragma once
#include "Heap.h"
#include "Logger.h"


#define DEFAULT_HEAP_TAG "Default"

class HeapManager
{
public:
	static void		initHeap(std::string tag);
	static Heap*	getHeap(std::string tag = DEFAULT_HEAP_TAG);
	//static void		destroyHeap(int index);
	//static Heap*	createHeap(std::string tag);
	//static bool		heapExists(std::string tag) { return getHeap(tag) != nullptr; }
	//static Heap*	findHeap(std::string tag);
	static void		setHeapCount(const int heapCount) { m_iHeapCount = heapCount; }
	
protected:
	
private:
	HeapManager();
	~HeapManager();

	static int getHeapCount() { return m_iHeapCount; }

	static int m_iHeapCount;
	
	//container for multiple heaps
	static Heap* s_pHeaps;

};