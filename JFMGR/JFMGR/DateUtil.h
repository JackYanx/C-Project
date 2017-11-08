/*
Created by YWT
2017.2.27 15:00
*/

#ifndef DATEUTIL_H
#define DATEUTIL_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <string>

/*将字符串中的大写字符全部换为小写字符*/
void changeToLowercase(const char*);
/*判断年份是否为闰年*/
int isLeapYear(unsigned int);
/*获取当前标准Unix时间*/
unsigned int getUnixTime();
/*创建格式化时间字符串,参数依次为时间,格式(yyyy.mm.dd),语言设置(en-US,zh-CN)*/
char* createFormattedTime(unsigned int, const char*, const char*);

/*可以重载的函数,至少传入时间参数,返回格式化字符串,默认格式为 yyyy.mm.dd hh:mm:ss
 *使用完成后应及时回收内存
 */
char* getFormattedTime(unsigned int);
char* getFormattedTime(unsigned int, const char*);
char* getFormattedTime(unsigned int, const char*, const char*);


/*
所支持示例格式如下
yyyy/mm/dd hh:mm:ss
2017/11/17 15:36:00
2017.11.17 15:36:00
2017-11-17 15:36:00

mm/dd/yyyy hh:mm:ss
11/17/2017 15:36:00
11.17.2017 15:36:00
11-17-2017 15:36:00

dd/mm/yyyy hh:mm:ss
17/11/2017 15:36:00
17.11.2017 15:36:00
17-11-2017 15:36:00

中文格式(该版本暂未支持,将会在后续加入支持)
2017年11月17日 15时36分0秒
11月17日2017年 15时36分0秒
17日11月2017年 15时36分0秒
*/

#endif

#pragma once