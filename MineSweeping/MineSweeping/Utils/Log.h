#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>

extern std::ofstream* mLogFile;
extern std::ostream* outputstream;
bool setlogfile(char*);
bool lexit();
//bool errlog(char*);

bool errlog(char*...);
//bool inflog(char*);

bool inflog(char*...);
#endif // !LOG_H