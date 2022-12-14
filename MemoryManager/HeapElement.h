#pragma once
#include "Structures.h"

class HeapElement
{
public:
	HeapElement();
	~HeapElement();
	
	Header* getHeader() { return (Header*)((char*)m_pData - sizeof(Header)); }
	Footer* getFooter() { return (Footer*)((char*)m_pData + m_pHeader->m_nDataSize); }
	

private:
	size_t	m_nSize;
	Header* m_pHeader;
	void*	m_pData;
	Footer* m_pFooter;
	
	HeapElement* m_pNext;
	HeapElement* m_pPrev;
};
