#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <fstream>
class Log
{
public:
	static Log *getInstance();
	bool init();
	void release();
	void addLog(std::string a_str);
private:
	static Log* _instance;
	FILE *_file;
	std::ofstream outfile;
	Log();
	~Log();
};

#endif //!__LOG_H__