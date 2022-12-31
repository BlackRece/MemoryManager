#pragma once
#include "Util.h"
#include "Pool.h"

class MemoryPool
{
public:
	static void*			alloc(size_t nSize);
	void					dealloc(void* ptr);
	
	static void				setDefaultObjectCount(int nCount) { s_nDefaultItemCount = nCount; }
	
	static size_t			calcPoolSize(size_t nSize) { return s_nDefaultItemCount * (nSize + sizeof(Item)); }
	//static Pool*			getPoolWithBytesFree(size_t nSize);
	//static void				addPool(Pool* pPool);

private:
							MemoryPool(size_t nSize);
							~MemoryPool() {};
						
	//static Pool*			addPool(size_t nSize);
	//static Pool*			create(size_t nSize);
	
	static int				s_nDefaultItemCount;
	Pool*					m_pPool;
};

