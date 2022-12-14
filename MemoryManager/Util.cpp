#include "Util.h"

char* Util::allocBytes(size_t nSize)
{
	size_t nHead = sizeof(Header);
	size_t nFoot = sizeof(Footer);
	size_t nTotalSize = nSize + nHead + nFoot;
	std::cout
		<< std::dec
		<< "header size:\t" << nHead << std::endl
		<< "requested size:\t" << nSize << std::endl
		<< "footer size:\t" << nFoot << std::endl
		<< "===========" << std::endl
		<< "total size:\t" << nTotalSize << std::endl;

	char* pResult = (char*)malloc(nTotalSize);
	std::cout
		<< "\nallocated at address: "
		<< std::hex << (void*)pResult
		<< std::endl << std::endl;

	return pResult;
}