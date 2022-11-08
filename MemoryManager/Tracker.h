#pragma once
#include <string>

class Tracker
{
public:
	Tracker();
	Tracker(std::string name);
	~Tracker();

	int getBytesInUse() { return m_iByteCount; }
	
private:
	int m_iByteCount;
	std::string m_sName;
};

