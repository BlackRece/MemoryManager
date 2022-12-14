#pragma once
#include <iostream>

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	static void* operator new(size_t size);
	//static void* operator new(size_t size, Heap* pHeap);
	static void operator delete(void* p, size_t size);

public:
	void aMethod();

};

