#pragma once
#include <iostream>
#include <sstream>

class Log
{
public:
	static void log(const std::string text) { std::cout << text << std::endl; }
	static void log(const std::stringstream text) { std::cout << text.str() << std::endl; }
	static std::string input() { std::string s; std::cin >> s; return s; }
	
	static void msg(const std::string text) { *m_pStream << text << std::endl; }
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
