#pragma once

#define HEAD_VALUE 0xDEADC0DE
#define FOOT_VALUE 0xDEADBEEF

class Heap;

struct Footer
{
	int m_iCheckValue;

	bool isValid() { return m_iCheckValue == FOOT_VALUE; }
	void init() { m_iCheckValue = FOOT_VALUE; }
};

struct Header
{
	size_t m_nSize;
	size_t m_dataSize;
	int m_iCheckValue;
	Heap* m_pHeap;
	Header* m_pNext;
	Header* m_pPrev;
	
	bool isValid() { return m_iCheckValue == HEAD_VALUE; }
	void init(size_t size)
	{
		m_nSize = size;
		m_dataSize = size - sizeof(Header) - sizeof(Footer);
		
		m_iCheckValue = HEAD_VALUE;
		
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	
	void init(size_t size, Heap* pHeap)
	{
		m_pHeap = pHeap;
		init(size);
	}

	Footer* getFooter()
	{
		return (Footer*)((char*)this + sizeof(Header) + m_dataSize);
	}
};

struct ObjectExample
{
	size_t size;
	void* headPtr;
	void* tailPtr;
};

