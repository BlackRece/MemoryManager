#pragma once

#include <iostream>
#include "BaseObject.h"

#define HEAD_VALUE 0xDEADC0DE
#define FOOT_VALUE 0xDEADBEEF

void* operator new(size_t size);

void operator delete(void* ptr);

class MemoryPool
{
public:
	MemoryPool(size_t iObjectSize);
	~MemoryPool();

	void* allocate(size_t iSize);
	void deallocate(void* pointer, size_t iSize);
};