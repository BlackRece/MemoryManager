#include "BaseObject.h"

#include <iostream>

using namespace std;

BaseObject::BaseObject()
{
	cout << "BaseObject :: constructor \n";
}

BaseObject::~BaseObject()
{
	cout << "BaseObject :: destructor \n";
}

void BaseObject::aMethod()
{
	cout << "BaseObject :: aMethod \n";
}

void* BaseObject::operator new(size_t size)
{
	return ::operator new(size);
}

void* operator new(size_t size, Tracker* pTracker)
{
	return ::operator new(size, pTracker);
}

void BaseObject::operator delete(void* p, size_t size)
{
	::operator delete(p);
}