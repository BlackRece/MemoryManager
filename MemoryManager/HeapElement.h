#pragma once
#include "Structures.h"

class HeapElement
{
	//NOTE: footer doesn't seem to be assigned from global new operator ...
public:
	HeapElement();
	~HeapElement();

private:
	size_t size;
	Header* m_pHeader;
	Footer* m_pFooter;
};
