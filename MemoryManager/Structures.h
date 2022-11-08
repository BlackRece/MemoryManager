#pragma once


struct Header
{
	size_t size;
	int checkValue;
	Tracker* pTracker;
	Header* pNext;
	Header* pPrev;
	
	bool hasChanged(int headValue) { return checkValue != headValue; }
};

struct Footer
{
	size_t size;
	int checkValue;
	Tracker* pTracker;
	
	bool hasChanged(int footValue) { return checkValue != footValue; }
};

struct ObjectExample
{
	size_t size;
	void* headPtr;
	void* tailPtr;
};
