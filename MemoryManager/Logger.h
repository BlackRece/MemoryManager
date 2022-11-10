#pragma once
#include <iostream>
#include <sstream>

class Log
{
public:
	static void msg(std::string text) { *m_pStream << text << std::endl; }
	static void show(std::ostream* pStream ) { m_pStream = pStream; }
	static void hide() { m_pStream = nullptr; }
	
	static std::string toHex(const unsigned int i) 
	{
		return (static_cast<std::stringstream const&>(std::stringstream() << "0x" << std::hex << i)).str();
	}

private:
	Log() {};
	~Log() {};
	
	static std::ostream* m_pStream;
};
