#pragma once

#define HEAD_VALUE 0xDEADC0DE
#define FOOT_VALUE 0xDEADBEEF

class Heap;

struct Header
{
	size_t m_nSize;
	int m_iCheckValue;
	Heap* m_pHeap;
	Header* m_pNext;
	Header* m_pPrev;
	
	//Header(void* )

	bool hasChanged() { return m_iCheckValue != HEAD_VALUE; }
	void init(size_t size, Heap* pHeap)
	{
		m_nSize = size;
		m_pHeap = pHeap;
		
		m_iCheckValue = HEAD_VALUE;
		
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	
	void DebugOutput();
};

struct Footer
{
	int m_iCheckValue;
	
	bool hasChanged(int footValue) { return m_iCheckValue != footValue; }
	void init()	{ m_iCheckValue = FOOT_VALUE;	}
};

struct ObjectExample
{
	size_t size;
	void* headPtr;
	void* tailPtr;
};
