#pragma once
#include "Heap.h"
//#include "Logger.h"

class HeapManager
{
public:
	static void		initHeap(std::string tag);
	static Heap*	getHeap();
	static Heap*	getHeap(std::string tag);
	static Heap*	getHeap(Heap* pHeap);
	//static void		destroyHeap(int index);
	//static Heap*	createHeap(std::string tag);
	//static bool		heapExists(std::string tag) { return getHeap(tag) != nullptr; }
	static void		setHeapCount(const int heapCount) { m_iHeapCount = heapCount; }
	
protected:
	
private:
	HeapManager();
	~HeapManager();

	static Heap*	findHeap(std::string tag);
	static int		getHeapCount() { return m_iHeapCount; }

	static int		m_iHeapCount;
	
	//container for multiple heaps via linked list
	static			Heap* s_pHeaps;

};