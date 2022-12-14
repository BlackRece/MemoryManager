#pragma once

#include "Util.h"
#include "HeapManager.h"
#include <iostream>

void* operator new(size_t nSize);
void* operator new(size_t size, char pHeapTag[]);

void operator delete(void* ptr);

static void logHeader(void* ptr);
static void setHeapCount(int heapCount) { HeapManager::setHeapCount(heapCount); }

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();
	
private:
};

class MemoryPool
{
public:
	MemoryPool(size_t iObjectSize);
	~MemoryPool();

	void deallocate(void* pointer, size_t iSize);
};