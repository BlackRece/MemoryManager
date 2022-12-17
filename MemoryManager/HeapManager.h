#pragma once
#include "Heap.h"
#include "Util.h"

class HeapManager
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
	
protected:
	
private:
	HeapManager();
	~HeapManager();

	static Heap*	getHeap() { return s_pHeaps; }
	static Heap*	getHeap(char tag[]);
	static Heap*	getLastHeap();

	static bool		m_bDebugMode;
	
	//container for multiple heaps via linked list
	static Heap*	s_pHeaps;

};