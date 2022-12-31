// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "MemoryManager.h"
#include "BaseObject.h"

#define _DEBUG_MODE true

int main(int argc, char* argv[])
{
    std::cout <<
        "_.-Memeory Manager Demo-._\n" 
        "==========================\n\n" 
		"Initializing Memory Manager...\n";

    MemoryManager::init(_DEBUG_MODE);

    std::cout <<
        "\nDefault Heap initialised.\n\n"
        "Here are some heap memory tests\n\n";
	
	std::cout << "Check Default Heap\n";
	MemoryManager::checkHeaps();
	
    std::cout << "Create variables:\n\n";

    std::cout << "\ncreate an int." << std::endl;
    int* pLength = new int;
    *pLength = 5;
    std::cout
        << "\nvalue of pLength = \t\t" << std::dec << *pLength << std::endl
        << "address of *pLength = \t\t" << std::hex << pLength << std::endl
        << "size of pLength = \t\t" << std::dec << sizeof &pLength
        << std::endl;

    std::cout << "\ncreate a float." << std::endl;
    float* pHeight = new float;
    *pHeight = 1.2f;
	std::cout 
        << "\nvalue of pHeight = \t\t" << std::dec << *pHeight << std::endl
	    << "address of *pHeight = \t\t" << std::hex << pHeight << std::endl
		<< "size of pHeight = \t\t" << std::dec<< sizeof & pHeight
        << std::endl;

    std::cout << "\nCreate another Heap\n";
	char heapTag[] = "Sample Heap";
    MemoryManager::addHeap(heapTag);
	
    std::cout << "\nCheck Heaps\n";
    MemoryManager::checkHeaps();

    std::cout << "\ncreate a char on second heap." << std::endl;
    char* pCh = new (heapTag) char;
    *pCh = 'x';
    std::cout
        << "\nvalue of pCh = \t\t\t" << std::dec << *pCh << std::endl
        << "address of *pCh = \t\t\t" << std::hex << (void*)pCh << std::endl
        << "size of pCh = \t\t\t" << std::dec << sizeof & pCh
        << std::endl;
    // NOTE: 'std::cout' treats char* as strings

    std::cout << "\ncreate an array of ints." << std::endl;
    const int arraySize = 5;
    int* pInts = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
        pInts[i] = i;

    std::cout
        << "\nvalue of pInts = \t\t" << std::dec << *pInts << std::endl
        << "address of pInts = \t\t" << std::hex << &pInts << std::endl
        << "size of pInts = \t\t" << std::dec << sizeof & pInts
        << std::endl;

    std::cout << "\nCheck Heaps\n";
    MemoryManager::checkHeaps();

    std::cout << "\nCreate variables:\n";

    std::cout << "\ncreate an object." << std::endl;
    BaseObject* pObject = new BaseObject();
    pObject->aMethod();

    std::cout << "\ndelete an int." << std::endl;
    delete pLength;
	
    std::cout << "\nCheck Heaps\n";
    MemoryManager::checkHeaps();

    std::cout << "\ndelete a float." << std::endl;
    delete pHeight;	
	
    std::cout << "\ndelete a char." << std::endl;
    delete pCh;

    std::cout << "\ndelete an array." << std::endl;
    delete[] pInts;

    std::cout << "\ndelete an class object." << std::endl;
	delete pObject;

    std::cout << "\nCheck Heaps\n";
    MemoryManager::checkHeaps();

    std::cout << "\ncreate a double." << std::endl;
    double* pWidth = new (heapTag) double;
    *pWidth = 1.0025;
    std::cout
        << "\nvalue of pWidth = \t\t" << std::dec << *pWidth << std::endl
        << "address of *pWidth = \t\t" << std::hex << pWidth << std::endl
        << "size of pWidth = \t\t" << std::dec << sizeof & pWidth
        << std::endl;

    std::cout << "\nCheck Heaps\n";
    MemoryManager::checkHeaps();

    std::cout << "\nClear Heaps\n";
    MemoryManager::clearHeaps();

    std::cout << "\nCheck Heaps\n";
    MemoryManager::checkHeaps();

    std::cout << "\nEnd Of Demo." << std::endl;
    std::cin.get();
}
