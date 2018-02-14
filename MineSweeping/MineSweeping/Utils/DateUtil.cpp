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

/*中国为东八区，需要加上8个小时(即28800秒)才是北京时间*/
/*
unsigned int getZh_cnUnixTime() {
return (unsigned int)time(0) + 28800;
}
*/

char* createFormattedTime(char* buf, unsigned int unixTime, const char* format, const char* lang) {
	/*输出格式化时间一律为北京时间*/
	if (unixTime == 0) {
		memcpy_s(buf, 30, "1970.01.01 08:00:00", 20);
		return buf;
	}
	/*输出格式化时间一律为北京时间,北京时间比UTC时间多8个小时,需要加上28800秒*/
	unixTime += 28800;
	/*目标时间各变量*/
	unsigned int year = 1970;
	unsigned int month = 1;
	unsigned int day = 1;
	unsigned int hour = 0;
	unsigned int minute = 0;
	unsigned int second = 0;
	/*两时间差值各变量*/
	unsigned int dYear = 0;
	unsigned int dMonth = 0;
	unsigned int dDay = 0;
	/*以四年为一组*/
	unsigned int year4group = 0;
	bool tagOfLeap = 0;
	/*处理时分秒,运用除法和取余得到时分秒的整数值*/
	dDay = unixTime / 86400;
	second = unixTime % 86400;
	hour = second / 3600;
	second %= 3600;
	minute = second / 60;
	second %= 60;
	/*处理日期*/
	/*从一月份进行天数累计*/
	unsigned int sumMonthDay[12] = { 31,59,90,120,151,181,212,243,273,304,334,365 };
	/*以4年为一组,方便处理闰年,从标准Unix时间0秒开始进行,第一组为
	*1970~1973年,四年为一组,每组年份中第三个是闰年,需要特殊处理*/
	year4group = dDay / 1461;
	year += year4group * 4;
	dDay %= 1461;
	/*表示目标年份是y4g中的第一个*/
	if (dDay < 365) {
	}
	/*表示目标年份是y4g中的第二个*/
	else if (dDay > 364 && dDay < 730) {
		year += 1;
		dDay -= 365;
	}
	/*表示目标年份是y4g中的第四个*/
	else if (dDay > 1095) {
		year += 3;
		dDay -= 1096;
	}
	/*表示目标年份是y4g中的第三个,闰年需要特殊处理*/
	else {
		year += 2;
		tagOfLeap = 1;
		sumMonthDay[1]++;
		dDay -= 730;
	}
	/*以上处理后将剩余天数变为一个小于365的数字*/
	/*以下处理从剩余天数中依次获取月和日*/
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

	/*以下负责构建格式化时间字符串*/
	/*分配一个大小为30个char类型的内存空间*/
	char* res = new char[30];
	char* p = res;
	/*定义一个指向年份开始地址的指针*/
	char* yy = NULL;
	/*定义一个指向月份开始地址的指针*/
	char* mm = NULL;
	/*定义一个指向日份开始地址的指针*/
	char* dd = NULL;
	dYear = year;
	/*将格式参数字符串全部转为小写*/
	changeToLowercase(format);
	/*初始化新分配的内存空间全部为0*/
	memset(res, 0, 30);
	//initCharArray(res, 0, 30);
	/*将格式参数字符串复制到新分配的内存空间中去*/
	strcpy(res, format);
	/*判断格式字符串是哪一种格式*/
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
	/*开始将时间转化为年月日部分*/
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
	/*将时分秒转化为对应的字符串,用':'分割*/
	*(p + 1) = (char)(hour / 10 + 48);
	*(p + 2) = (char)(hour % 10 + 48);
	*(p + 3) = ':';
	*(p + 4) = (char)(minute / 10 + 48);
	*(p + 5) = (char)(minute % 10 + 48);
	*(p + 6) = ':';
	*(p + 7) = (char)(second / 10 + 48);
	*(p + 8) = (char)(second % 10 + 48);
	/*返回格式化完成后的字符串首地址*/
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
