#include "DateUtil.h"
#include "ToolUtil.h"

void changeToLowercase(const char* src) {
	char* p = (char*)src;
	while (*p != 0) {
		if (*p > 64 && *p < 91) {
			*p += 32;
		}
		p++;
	}
}

int isLeapYear(unsigned int year) {
	bool a = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	if (!a) {
		return 0;
	}
	return 1;
}

unsigned int getUnixTime() {
	return (unsigned int)time(0);
}

/*�й�Ϊ����������Ҫ����8��Сʱ(��28800��)���Ǳ���ʱ��*/
/*
unsigned int getZh_cnUnixTime() {
return (unsigned int)time(0) + 28800;
}
*/

char* createFormattedTime(char* buf, unsigned int unixTime, const char* format, const char* lang) {
	/*�����ʽ��ʱ��һ��Ϊ����ʱ��*/
	if (unixTime == 0) {
		memcpy_s(buf, 30, "1970.01.01 08:00:00", 20);
		return buf;
	}
	/*�����ʽ��ʱ��һ��Ϊ����ʱ��,����ʱ���UTCʱ���8��Сʱ,��Ҫ����28800��*/
	unixTime += 28800;
	/*Ŀ��ʱ�������*/
	unsigned int year = 1970;
	unsigned int month = 1;
	unsigned int day = 1;
	unsigned int hour = 0;
	unsigned int minute = 0;
	unsigned int second = 0;
	/*��ʱ���ֵ������*/
	unsigned int dYear = 0;
	unsigned int dMonth = 0;
	unsigned int dDay = 0;
	/*������Ϊһ��*/
	unsigned int year4group = 0;
	bool tagOfLeap = 0;
	/*����ʱ����,���ó�����ȡ��õ�ʱ���������ֵ*/
	dDay = unixTime / 86400;
	second = unixTime % 86400;
	hour = second / 3600;
	second %= 3600;
	minute = second / 60;
	second %= 60;
	/*��������*/
	/*��һ�·ݽ��������ۼ�*/
	unsigned int sumMonthDay[12] = { 31,59,90,120,151,181,212,243,273,304,334,365 };
	/*��4��Ϊһ��,���㴦������,�ӱ�׼Unixʱ��0�뿪ʼ����,��һ��Ϊ
	*1970~1973��,����Ϊһ��,ÿ������е�����������,��Ҫ���⴦��*/
	year4group = dDay / 1461;
	year += year4group * 4;
	dDay %= 1461;
	/*��ʾĿ�������y4g�еĵ�һ��*/
	if (dDay < 365) {
	}
	/*��ʾĿ�������y4g�еĵڶ���*/
	else if (dDay > 364 && dDay < 730) {
		year += 1;
		dDay -= 365;
	}
	/*��ʾĿ�������y4g�еĵ��ĸ�*/
	else if (dDay > 1095) {
		year += 3;
		dDay -= 1096;
	}
	/*��ʾĿ�������y4g�еĵ�����,������Ҫ���⴦��*/
	else {
		year += 2;
		tagOfLeap = 1;
		sumMonthDay[1]++;
		dDay -= 730;
	}
	/*���ϴ����ʣ��������Ϊһ��С��365������*/
	/*���´����ʣ�����������λ�ȡ�º���*/
	for (int i = 0; i < 12; i++) {
		if (tagOfLeap && i == 3) {
			dDay -= 1;
		}
		if (sumMonthDay[i] <= dDay) {
			continue;
		}
		dDay -= sumMonthDay[i - 1];
		month += i;
		day = dDay + 1;
		break;
	}

	/*���¸��𹹽���ʽ��ʱ���ַ���*/
	/*����һ����СΪ30��char���͵��ڴ�ռ�*/
	char* res = new char[30];
	char* p = res;
	/*����һ��ָ����ݿ�ʼ��ַ��ָ��*/
	char* yy = NULL;
	/*����һ��ָ���·ݿ�ʼ��ַ��ָ��*/
	char* mm = NULL;
	/*����һ��ָ���շݿ�ʼ��ַ��ָ��*/
	char* dd = NULL;
	dYear = year;
	/*����ʽ�����ַ���ȫ��תΪСд*/
	changeToLowercase(format);
	/*��ʼ���·�����ڴ�ռ�ȫ��Ϊ0*/
	memset(res, 0, 30);
	//initCharArray(res, 0, 30);
	/*����ʽ�����ַ������Ƶ��·�����ڴ�ռ���ȥ*/
	strcpy(res, format);
	/*�жϸ�ʽ�ַ�������һ�ָ�ʽ*/
	switch (*p) {
	case 'y':
		yy = p;
		mm = p + 5;
		dd = p + 8;
		break;
	case 'm':
		yy = p + 6;
		mm = p;
		dd = p + 3;
		break;
	case 'd':
		yy = p + 6;
		mm = p + 3;
		dd = p;
		break;
	}
	/*��ʼ��ʱ��ת��Ϊ�����ղ���*/
	*yy = (char)(dYear / 1000 + 48);
	dYear %= 1000;
	*(yy + 1) = (char)(dYear / 100 + 48);
	dYear %= 100;
	*(yy + 2) = (char)(dYear / 10 + 48);
	*(yy + 3) = (char)(dYear % 10 + 48);
	*mm = (char)(month / 10 + 48);
	*(mm + 1) = (char)(month % 10 + 48);
	*dd = (char)(day / 10 + 48);
	*(dd + 1) = (char)(day % 10 + 48);
	p += 10;
	*p = ' ';
	/*��ʱ����ת��Ϊ��Ӧ���ַ���,��':'�ָ�*/
	*(p + 1) = (char)(hour / 10 + 48);
	*(p + 2) = (char)(hour % 10 + 48);
	*(p + 3) = ':';
	*(p + 4) = (char)(minute / 10 + 48);
	*(p + 5) = (char)(minute % 10 + 48);
	*(p + 6) = ':';
	*(p + 7) = (char)(second / 10 + 48);
	*(p + 8) = (char)(second % 10 + 48);
	/*���ظ�ʽ����ɺ���ַ����׵�ַ*/
	memcpy_s(buf, 30, res, strnlen(res, 64));
	delete res;
	res = NULL;
	return buf;
}

char* getFormattedTime(char* buf, unsigned int unixTime) {
	return createFormattedTime(buf, unixTime, "yyyy.mm.dd", "en-US");
}

char* getFormattedTime(char* buf, unsigned int unixTime, const char* format) {
	return createFormattedTime(buf, unixTime, format, "en-US");
}

char* getFormattedTime(char* buf, unsigned int unixTime, const char* format, const char* lang) {
	return createFormattedTime(buf, unixTime, format, lang);
}
