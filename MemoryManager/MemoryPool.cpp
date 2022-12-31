#include "MemoryPool.h"

int MemoryPool::s_nDefaultItemCount = 10;

void* MemoryPool::alloc(size_t nSize)
{
	//Pool* pPool = getPoolWithBytesFree(nSize);
	//
	//return pPool->addItem(nSize);
	
	return nullptr;
}

void MemoryPool::dealloc(void* ptr)
{
	//FreeList* pFreeList = (FreeList*)ptr;
	//pFreeList->m_pNext = m_pFreeList;
	//m_pFreeList = pFreeList;
}


//Pool* MemoryPool::addPool(size_t nSize)
//{
//	Pool* pPool = create(nSize);
//	
//	if(m_pPool == nullptr)
//	{
//		m_pPool = pPool;
//		return m_pPool;
//	}
//	
//	Pool* pLast = m_pPool->getLast();
//	
//	pLast->setNext(pPool);
//	pPool->setPrev(pLast);
//	
//	return pPool;
//}
//
//
//Pool* MemoryPool::create(size_t nSize)
//{
//	size_t nPoolSize = s_nDefaultItemCount * (nSize + sizeof(Item));
//
//	Pool* pPool = (Pool*)Util::allocBytes(nPoolSize);
//	pPool->init(nPoolSize);
//
//	return pPool;
//}
