#include "BaseObject.h"

BaseObject::BaseObject()
{
	Log::log("BaseObject :: constructor \n");
}

BaseObject::~BaseObject()
{
	Log::log("BaseObject :: destructor \n");
}

void BaseObject::aMethod()
{
	Log::log("BaseObject :: aMethod \n");
}

void* BaseObject::operator new(size_t size)
{
	std::cout 
		<< "class operator new called \n"
		<< "with size : " << size << std::endl;
	return ::operator new(size);
}

//void* operator new(size_t size, Heap* pTracker)
//{
//	return ::operator new(size, pTracker);
//}

void BaseObject::operator delete(void* p, size_t size)
{
	std::cout
		<< "class operator delete called \n"
		<< "with size : " << size << std::endl
		<< "and pointer : " << std::hex << p << std::endl;
	::operator delete(p);
}