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
	/*����һ���ַ����鲢ȫ����ʼ��Ϊ0*/
	char fz[20];
	initCharArray(fz,0,20);
	char* p = fz;
	/*_getch()���յ����ַ����ǲ�����ʾ,_putch()������ʾ'*',ͬʱ�����յ����ַ��Ƿ�Ϊ���з����߳����Ƿ񳬹�18,�������ضϲ���*/
	for (i = 0; (ch = _getch()) != '\r' && i != 18; *p++ = ch, _putch('*'), ++i);
	*p = '\0';
	std::cout << std::endl;
	/*����һ�����ַ���ַ��ʼ����string����*/
	return std::string(fz);
}