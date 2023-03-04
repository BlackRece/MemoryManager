#include "BaseObject.h"
#include "MemoryManager.h"

//void* operator new(size_t nSize, char pHeapTag[])
//{
//	Str sTag; sTag.set(pHeapTag);
//	
//	std::cout
//		<< "global operator new called ..."
//		<< "\nwith size: " << nSize
//		<< "\nfor heap: " << sTag.str
//		<< std::endl;
//
//	void* pStartMemBlock = MemoryManager::isPoolingEnable()
//		? MemoryManager::allocToPool(nSize, &sTag)
//		: MemoryManager::allocToHeap(nSize, &sTag);
//
//	return pStartMemBlock;
//}

BaseObject::BaseObject()
{
	std::cout << "BaseObject :: constructor \n";
}

BaseObject::~BaseObject()
{
	std::cout << "BaseObject :: destructor \n";
}

void BaseObject::aMethod()
{
	std::cout << "BaseObject :: aMethod \n";
}

void* BaseObject::operator new(size_t nSize)
{
	std::cout 
		<< "class operator new called \n"
		<< "with size : " << nSize << std::endl;
	
	Str sTag; sTag.set((char*)"ClassSpecific");
	
	return MemoryManager::isDebugEnabled()
		? MemoryManager::allocFrame(nSize, &sTag)
		: ::operator new(nSize);
}

void BaseObject::operator delete(void* pMem, size_t size)
{
	std::cout
		<< "class operator delete called \n"
		<< "with size : " << size << std::endl
		<< "and pointer : " << std::hex << pMem << std::endl;

	::operator delete(pMem);
}