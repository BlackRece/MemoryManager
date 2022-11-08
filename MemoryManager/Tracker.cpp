#include "Tracker.h"

Tracker::Tracker()
{
	m_iByteCount = 0;
	m_sName = "Default";
}

Tracker::Tracker(std::string name)
{
	m_iByteCount = 0;
	m_sName = name;
}

Tracker::~Tracker()
{
}
