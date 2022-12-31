#include "Pool.h"

void Pool::init(size_t nSize)
{
	m_nSize = nSize;
	m_nFree = m_nSize - sizeof(Pool);
	m_nUsed = m_nSize - m_nFree;
	
	m_pNext = nullptr;
	m_pPrev = nullptr;
	
	m_pItem = nullptr;
		
	std::cout
		<< "PoolObject created size: "
		<< std::dec << m_nSize << std::endl;
}

void* Pool::addItem(size_t nSize)
{
	Item* pItem = newItem(nSize);
	
	subBytes(nSize);
	
	return pItem->m_pData;
}

void* Pool::add(Item* pItem)
{
	if (m_pItem == nullptr)
	{
		m_pItem = pItem;
		
		m_nFree -= pItem->m_nSize;
		m_nUsed += pItem->m_nSize;
		
		return pItem->m_pData;
	}
	
	Item* pLast = m_pItem->getLast();
	
	pLast->m_pNext = pItem;
	pItem->m_pPrev = pLast;
	
	m_nFree -= pItem->m_nSize;
	m_nUsed += pItem->m_nSize;
	
	return pItem->m_pData;
}

Item* Pool::getFreeItem()
{
	// TODO: when removing an Item, 
	// setting size of Item to zero will cause issues
	// so find alternative. try removing item from the list
	Item* pItem = m_pItem;

	while (pItem != nullptr)
	{
		if (pItem->isFree())
			break;
		
		pItem = pItem->m_pNext;
	}
	
	return pItem;
}

Item* Pool::newItem(size_t nSize)
{
	if (m_pItem == nullptr)
	{
		Item*  pRoot = (Item*)(this + sizeof(Pool));
		pRoot->init(nSize);
		
		m_pItem = pRoot;
		return pRoot;
	}
	
	Item* pLast = m_pItem->getLast();

	Item* pItem = (Item*)(pLast + sizeof(Item) + pLast->m_nSize);
	pItem->init(nSize);
	
	pItem->m_pPrev = pLast;
	pLast->m_pNext = pItem;
	
	return pItem;
}
