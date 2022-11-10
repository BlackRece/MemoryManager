// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MemoryManager.h"
#include "BaseObject.h"
#include <map>
#include "Logger.h"

//#define DEFAULT_MAX_HEAPS 10

int getHeapCount(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    /*int heapCount = getHeapCount(argc, argv);
    if (heapCount == 0)
    {
		Log::msg("No heap count specified. Exiting.\n");
        return 1;
    }*/
	
    Log::msg(
        "_.-Memeory Manager Demo-._" 
        "==========================\n\n" 
		"Here are some memory tests\n\n");

    Log::msg("float height = 1.2f");
    float height = 1.2f;
    Log::msg(std::to_string(height));
	
    Log::msg("char ch = 'x'");
    char ch = 'x';
    Log::msg(std::string(1,ch));

    // create pointers to each
    float* pHeight = &height;
    char* pCh = &ch;

    // print the address values
	Log::msg("pHeight: " + Log::toHex(*pHeight));
	Log::msg("pCh: " + Log::toHex(*pCh));

    // we can change values using pointers by dereferencing like so:
    *pHeight = 0.3f;
    *pCh = 'c';
    std::cout << height << ", " << ch << std::endl << std::endl;
    Log::msg("modified height = " + std::to_string(height));
    Log::msg("modified ch = " + std::string(1, ch));
	
	// we can create a new object on the heap
	BaseObject* pObject = new BaseObject();
	pObject->aMethod();
	delete pObject;

}

std::map<int, std::string> getArgMap(int argc, char* argv[]) {
    std::map<int, std::string> argMap;

    for (int i = 0; i < argc; i++)
        argMap[i] = argv[i];

    return argMap;
}
