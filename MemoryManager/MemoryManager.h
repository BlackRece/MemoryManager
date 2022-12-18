#pragma once

#include "Util.h"
#include "HeapManager.h"
#include <iostream>

void* operator new(size_t nSize);
void* operator new(size_t size, char pHeapTag[]);

void operator delete(void* ptr);

class MemoryManager
{
public:
	MemoryManager() {}
	~MemoryManager() {}
	
private:
};
