#include "BaseObject.h"

using namespace std;

BaseObject::BaseObject()
{
	Log::msg("BaseObject :: constructor \n");
}

BaseObject::~BaseObject()
{
	Log::msg("BaseObject :: destructor \n");
}

void BaseObject::aMethod()
{
	Log::msg("BaseObject :: aMethod \n");
}

void* BaseObject::operator new(size_t size)
{
	return ::operator new(size);
}

void* operator new(size_t size, Heap* pTracker)
{
	return ::operator new(size, pTracker);
}

void BaseObject::operator delete(void* p, size_t size)
{
	::operator delete(p);
}