// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MemoryManager.h"
#include "BaseObject.h"
#include "Logger.h"

//#define DEFAULT_MAX_HEAPS 10

//int getHeapCount(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    /*int heapCount = getHeapCount(argc, argv);
    if (heapCount == 0)
    {
		Log::msg("No heap count specified. Exiting.\n");
        return 1;
    }*/
	
    std::cout <<
        "_.-Memeory Manager Demo-._\n" 
        "==========================\n\n" 
		"Initializing Memory Manager...\n";

    HeapManager::initHeap();

    std::cout <<
        "Deafault Heap initialised.\n\n"
        "Here are some heap memory tests\n\n";
	
	std::cout << "Check Default Heap\n\n";
	HeapManager::checkHeaps();
	
    std::cout << "Create variables:\n\n";

    std::cout << "\ncreate an int." << std::endl;
    int* pLength = new int;
    *pLength = 5;
    std::cout
        << "value of pLength = \t\t" << std::dec << *pLength << std::endl
        << "address of *pLength = \t\t" << std::hex << pLength << std::endl
        << "size of pLength = \t\t" << std::dec << sizeof &pLength
        << std::endl;

    std::cout << "\ncreate a float." << std::endl;
    float* pHeight = new float;
    *pHeight = 1.2f;
	std::cout 
        << "value of pHeight = \t\t" << std::dec << *pHeight << std::endl
	    << "address of *pHeight = \t\t" << std::hex << pHeight << std::endl
		<< "size of pHeight = \t\t" << std::dec<< sizeof & pHeight
        << std::endl;

    std::cout << "\ncreate a char." << std::endl;
    char* pCh = new char;
    *pCh = 'x';
    std::cout
        << "value of pCh = \t\t\t" << std::dec << *pCh << std::endl
        << "address of *pCh = \t\t\t" << std::hex << (void*)pCh << std::endl
        << "size of pCh = \t\t\t" << std::dec << sizeof & pCh
        << std::endl;
    // NOTE: 'std::cout' treats cahr* as strings

    std::cout << "\ncreate an array." << std::endl;
    const int arraySize = 5;
    int* pInts = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
        pInts[i] = i;

    std::cout
        << "value of pInts = \t\t" << std::dec << *pInts << std::endl
        << "address of pInts = \t\t" << std::hex << &pInts << std::endl
        << "size of pInts = \t\t" << std::dec << sizeof & pInts
        << std::endl;

    std::cout << "Check Default Heap\n\n";
    HeapManager::checkHeaps();

    std::cout << "Create variables:\n\n";

    std::cout << "\ncreate an object." << std::endl;
    BaseObject* pObject = new BaseObject();
    pObject->aMethod();

    std::cout << "\ndelete an int." << std::endl;
    delete pLength;
	
    std::cout << "\ndelete a float." << std::endl;
    delete pHeight;	
	
    std::cout << "\ndelete a char." << std::endl;
    delete pCh;

    std::cout << "\ndelete an array." << std::endl;
    delete[] pInts;

	delete pObject;

    std::cout << "\nEnd Of Demo." << std::endl;
    std::cin.get();
}

//std::map<int, std::string> getArgMap(int argc, char* argv[]) {
//    std::map<int, std::string> argMap;
//
//    for (int i = 0; i < argc; i++)
//        argMap[i] = argv[i];
//
//    return argMap;
//}
