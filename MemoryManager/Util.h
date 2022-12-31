#pragma once
#include <iostream>
#include "Structures.h"

class Util
{
public:
	static char*	allocBytes(size_t nSize);
	
	static char*	getPointer(void* ptr) { return ((char*)ptr +	sizeof(Header)); }
	static char*	getDataPtr(Header* pHead) { return (char*)((char*)pHead + sizeof(Header)); }
	static Footer*	getFooter(Header* pHead) { return (Footer*)((char*)pHead + sizeof(Header) + pHead->m_nDataSize); }
	static Header*	getHeader(void* ptr) { return (Header*)((char*)ptr - sizeof(Header)); }
	static Footer*	getFooter(void* ptr) { return (Footer*)((char*)ptr + getHeader(ptr)->m_nDataSize); }
	static Item*	getItem(void* ptr) { return (Item*)((char*)ptr - sizeof(Item)); }
};

