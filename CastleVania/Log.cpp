#include "Log.h"
#include <fstream>
#include <iostream>
using namespace std;

Log* Log::_instance = NULL;

Log * Log::getInstance() {
	if (_instance == NULL)
	{
		_instance = new Log();
	}
	return _instance;
}

bool Log::init() {
	outfile.open("Debug.txt");
	return true;
}

void Log::release() {
	outfile.close();
}

void Log::addLog(std::string a_str) {
	const char *cstr = a_str.c_str();
	outfile << cstr << std::endl;
}

Log::Log() { }

Log::~Log() { }


