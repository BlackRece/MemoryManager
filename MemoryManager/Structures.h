#pragma once
#include <exception>

#define HEAD_VALUE 0xDEADC0DE
#define FOOT_VALUE 0xDEADBEEF

class Heap;

struct Footer
{
	int m_iCheckValue;

	bool isValid() { return m_iCheckValue == FOOT_VALUE; }
	bool validate()
	{
		//FOOT_VALUE = -559038737
		if (m_iCheckValue != FOOT_VALUE)
			throw "invalid footer";

		return true;
	}
	void init() { m_iCheckValue = FOOT_VALUE; }
};

struct Header
{
	size_t	m_nDataSize;
	size_t	m_nFullSize;
	int		m_iCheckValue;
	
	Heap*	m_pHeap;
	
	Header* m_pNext;
	Header* m_pPrev;
	
	bool isValid() { return m_iCheckValue == HEAD_VALUE; }
	bool validate() 
	{
		//HEAD_VALUE = -559038242
		if (m_iCheckValue != HEAD_VALUE)
		{
			throw "invalid header";
			return false;
		}
		
		return true;
	}
	
	void init(size_t dataSize)
	{
		m_nDataSize = dataSize;
		m_nFullSize = dataSize + sizeof(Header) + sizeof(Footer);
		
		m_iCheckValue = HEAD_VALUE;
		
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
};

struct ObjectExample
{
	size_t size;
	void* headPtr;
	void* tailPtr;
};

