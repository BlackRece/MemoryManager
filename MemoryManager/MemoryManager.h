#pragma once

#include "Structures.h"
#include "HeapManager.h"
#include <iostream>


void* operator new(size_t size);
//void* operator new(size_t size, std::string tag = "Default");

void operator delete(void* ptr);

static Header*	getHead(void* ptr) { return (Header*)((char*)ptr - sizeof(Header)); }
static Footer*	getFoot(void* ptr) { return (Footer*)((char*)ptr + getHead(ptr)->m_nSize); }
static void*	getData(void* ptr) { return (void*)((char*)ptr + sizeof(Header)); }

static void* allocBytes(size_t size);

static void logHeader(void* ptr);
static void setHeapCount(int heapCount) { HeapManager::setHeapCount(heapCount); }

class MemoryPool
{
public:
	MemoryPool(size_t iObjectSize);
	~MemoryPool();

	void* allocate(size_t iSize);
	void deallocate(void* pointer, size_t iSize);
};