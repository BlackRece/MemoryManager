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
		"Here are some heap memory tests\n\n";

    std::cout << "\ncreate an int." << std::endl;
    int* pLength = new int;
    *pLength = 5;
    std::cout
        << "*pLength = \t\t" << *pLength << std::endl
        << "pLength = \t\t" << std::hex << pLength
        << std::endl;

    std::cout << "\ndelete an int." << std::endl;
    delete pLength;
	
    std::cout << "\ncreate a float." << std::endl;
    float* pHeight = new float;
    *pHeight = 1.2f;
	std::cout 
        << "*pHeight = \t\t" << *pHeight << std::endl
	    << "pHeight = \t\t" << std::hex << pHeight 
        << std::endl;

    std::cout << "\ndelete a float." << std::endl;
    delete pHeight;
	
	std::cout << "\ncreate a char." << std::endl ;
    char* pCh = new char;
    *pCh = 'x';
	std::cout 
        << "*pCh = \t\t\t" << *pCh << std::endl
	    << "pCh = \t\t\t" << std::hex << (void *)pCh 
        << std::endl;
    // NOTE: 'std::cout' treats cahr* as strings

    std::cout << "\ndelete a char." << std::endl;
    delete pCh;

	std::cout << "\ncreate an array." << std::endl;
	const int arraySize = 5;
    int* pInts[arraySize];
    for (size_t i = 0; i < arraySize; i++)
    {
		pInts[i] = new int;
		*pInts[i] = 1;
	}
    std::cout
        << "*pInts[0] = \t\t" << *pInts[0] << std::endl
        << "pInts = \t\t" << std::hex << &pInts
        << std::endl;

    std::cout << "\ndelete an array." << std::endl;
    delete[] pInts;

    std::cout << "\ncreate an object." << std::endl;
	BaseObject* pObject = new BaseObject();
	pObject->aMethod();
	delete pObject;

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
