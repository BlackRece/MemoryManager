#pragma once

#include <iostream>
#include "BaseObject.h"

void* operator new(size_t size);

void operator delete(void* ptr);

struct Header
{
	size_t size;
	int checkValue;
	Tracker* pTracker;
	Header* pNext;
	Header* pPrev;
};

struct Footer
{
	size_t size;
	int checkValue;
	Tracker* pTracker;
};

class MemoryPool
{
public:
	MemoryPool(size_t iObjectSize);
	~MemoryPool();

	void* allocate(size_t iSize);
	void deallocate(void* pointer, size_t iSize);
};