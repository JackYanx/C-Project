#include "Log.h"
#include "DateUtil.h"
#include <stdarg.h>
std::ofstream* mLogFile = NULL;
std::ostream* outputstream = NULL;
static char* ERRTAG = " [ERROR] ";
static char* INFTAG = " [INFO]  ";
static char* SPLITC = "|";
static int MAXNUM = 20;
bool setlogfile(char* fn) {
	if (mLogFile) {
		mLogFile->close();
		delete mLogFile;
		mLogFile = NULL;
		outputstream = &std::cout;
	}
	mLogFile = new std::ofstream();
	mLogFile->open(fn, std::ios::app);
	if (!mLogFile->is_open()) {
		std::cout << "LOGFILE OPEN FAILED! \n USE STDOUT STREAM INSTEAD.\n";
		delete mLogFile;
		mLogFile = NULL;
		outputstream = &std::cout;
		return false;
	}
	outputstream = mLogFile;
	return true;
}
bool lexit() {
	if (mLogFile && mLogFile->is_open()) {
		(*mLogFile) << "\n";
		mLogFile->close();
		delete mLogFile;
		mLogFile = NULL;
		return true;
	}
	return false;
}
char timestrbuf1[30];
bool errlog(char* str) {
	if (!outputstream) {
		std::cout << "OUTPUTSTREAM ERROR!\n";
		return false;
	}
	memset(timestrbuf1, 0, 30);
	getFormattedTime(timestrbuf1, time(0));
	(*outputstream) << timestrbuf1 << ERRTAG << SPLITC << str << std::endl;
	return true;
}
bool errlog(char* strarr...) {
	if (!outputstream) {
		std::cout << "OUTPUTSTREAM ERROR!\n";
		return false;
	}
	memset(timestrbuf1, 0, 30);
	getFormattedTime(timestrbuf1, time(0));
	(*outputstream) << timestrbuf1 << ERRTAG << SPLITC << strarr << std::endl;
	/*
	if (num < 1 || !strarr || num > MAXNUM) {
		//Reserved Position
		return false;
	}
	memset(timestrbuf1, 0, 30);
	getFormattedTime(timestrbuf1, time(0));
	(*outputstream) << timestrbuf1 << ERRTAG;
	for (int i = 0; i < num; i++)
	{
		(*outputstream) << SPLITC << strarr[i];
	}
	(*outputstream) << std::endl;
	*/
	return true;
}
char timestrbuf2[30];
bool inflog(char* str) {
	if (!outputstream) {
		std::cout << "OUTPUTSTREAM ERROR!\n";
		return false;
	}
	memset(timestrbuf2, 0, 30);
	getFormattedTime(timestrbuf2, time(0));
	(*outputstream) << timestrbuf2 << INFTAG << SPLITC << str << std::endl;
	return true;
}
bool inflog(char* strarr...) {
	if (!outputstream) {
		std::cout << "OUTPUTSTREAM ERROR!\n";
		return false;
	}
	memset(timestrbuf2, 0, 30);
	getFormattedTime(timestrbuf2, time(0));
	(*outputstream) << timestrbuf2 << INFTAG << SPLITC << strarr << std::endl;
	//va_list valist;

	/*
	if (num < 1 || !strarr || num > MAXNUM) {
		//Reserved Position
		return false;
	}
	memset(timestrbuf1, 0, 30);
	getFormattedTime(timestrbuf1, time(0));
	(*outputstream) << timestrbuf1 << INFTAG;
	for (int i = 0; i < num; i++)
	{
		(*outputstream) << SPLITC << strarr[i];
	}
	(*outputstream) << std::endl;
	*/
	return true;
}
