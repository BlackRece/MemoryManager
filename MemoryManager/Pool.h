#pragma once

#include "Util.h"

class Pool
{
public:
	void					init(size_t nSize);
	bool					hasBytesFree(size_t nSize) { return m_nFree >= nSize + sizeof(Item); }
	
	Pool*					getLast() { return m_pNext == nullptr ? this : m_pNext->getLast(); }
	Pool*					getNext() { return m_pNext; }
	Pool*					getPrev() { return m_pPrev; }
	
	void					setNext(Pool* pPool) { m_pNext = pPool; }
	void					setPrev(Pool* pPool) { m_pPrev = pPool; }

	void*					add(Item* pItem);
	void*					addItem(size_t nSize);
	Item*					getFreeItem();
	Item*					newItem(size_t nSize);
	
private:
							Pool() { ; }
							~Pool() { ; }

	Item*					getRootItem() { return m_pItem != nullptr ? m_pItem : (Item*)(this + sizeof(Pool)); }
													
	void					addBytes(size_t nSize) { m_nFree += nSize; m_nUsed -= nSize; }
	void					subBytes(size_t nSize) { m_nFree -= nSize; m_nUsed += nSize; }

	Item*					m_pItem;

	size_t					m_nSize;
	size_t					m_nFree;
	size_t					m_nUsed;

	Pool*					m_pNext;
	Pool*					m_pPrev;
};

