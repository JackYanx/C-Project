#include "ToolUtils.h"
#include <conio.h>

void initIntArray(int *keyInt, int target, int length) {
	int i;
	for (i = 0; i < length; i++) {
		keyInt[i] = target;
	}
}

void initCharArray(char *keyChar, char target, int length) {
	int i;
	for (i = 0; i < length; i++) {
		keyChar[i] = target;
	}
}
char* getLastCharOfString(std::string& str) {
	int sLength = str.length();
	char* p = (char*)str.c_str();
	return (char*)(p + sLength - 1);
}

char* getLastCharOfString(const char* str) {
	char* p = (char*)str;
	while (*p != 0) {
		p++;
	}
	return (char*)(p - 1);
}

std::string getPassword() {
	int ch;
	int i;
	/*声明一个字符数组并全部初始化为0*/
	char fz[20];
	initCharArray(fz,0,20);
	char* p = fz;
	/*_getch()接收单个字符但是不会显示,_putch()负责显示'*',同时检测接收到的字符是否为换行符或者长度是否超过18,如果是则截断操作*/
	for (i = 0; (ch = _getch()) != '\r' && i != 18; *p++ = ch, _putch('*'), ++i);
	*p = '\0';
	std::cout << std::endl;
	/*返回一个用字符地址初始化的string对象*/
	return std::string(fz);
}