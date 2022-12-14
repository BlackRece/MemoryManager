#pragma once
#include "Heap.h"
#include "Util.h"

class HeapManager
{
public:
	static void		createDefaultHeap();
	static Heap*	getHeap();
	static void		checkHeaps();
	
	static void		createHeap(char heapTag[]);
	static void		addHeaderToHeap(Header* pHeader);
	static void		addHeaderToHeap(Header* pNewHeader, char sHeapTag[]);
	
	static Heap*	getHeap(char tag[]);
	//static void		destroyHeap(int index);
	//static bool		heapExists(std::string tag) { return getHeap(tag) != nullptr; }
	static void		setHeapCount(const int heapCount) { m_iHeapCount = heapCount; }
	
protected:
	
private:
	HeapManager();
	~HeapManager();

	static Heap*	getLastHeap();
	static Heap*	findHeap(char tag[]);
	static int		getHeapCount() { return m_iHeapCount; }
	
	static int		m_iHeapCount;
	
	//container for multiple heaps via linked list
	static Heap*	s_pHeaps;

};