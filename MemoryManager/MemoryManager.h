#pragma once

#include "Structures.h"
#include "HeapManager.h"
#include <iostream>


void* operator new(size_t nSize);
void* operator new(size_t nSize, Heap* pHeap);
//void* operator new(size_t size, std::string tag = "Default");

void operator delete(void* ptr);

static char* allocBytes(size_t size);

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

	void* allocate(size_t iSize);
	void deallocate(void* pointer, size_t iSize);
};