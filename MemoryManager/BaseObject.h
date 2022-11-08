#pragma once
#include "Tracker.h"

class Tracker;

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	static void* operator new(size_t size);
	static void* operator new(size_t size, Tracker* pTracker);
	static void operator delete(void* p, size_t size);

public:
	void aMethod();

};

