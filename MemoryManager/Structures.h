#pragma once
#include <exception>
#include <string.h>

#define HEAD_VALUE 0xDEADC0DE
#define FOOT_VALUE 0xDEADBEEF

#define TAG_LENGTH 30
#define DEFAULT_TAG "Default"

class Heap;

struct Str
{
	char str[TAG_LENGTH];
	int len;

	bool isEmpty() { return len == 0; }
	bool cmp(Str src) { return len == src.len && strcmp(str, src.str) == 0; }
	void set(char string[])
	{
		if (string == nullptr)
			return;

		strcpy_s(str, string);
		len = (int)strlen(string);
	}
	//strcpy_s(sTag, TAG_LENGTH, tag);
};

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

struct Item
{
public:
	size_t			m_nSize;
	void*			m_pData;
	
	Item*		m_pNext;
	Item*		m_pPrev;

	void init(size_t nSize)
	{
		m_nSize = nSize;
		m_pData = this + sizeof(Item);
		
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}

	bool isFree() { return m_nSize == 0; }

	Item* getLast() { return m_pNext == nullptr ? this : m_pNext->getLast(); }
};