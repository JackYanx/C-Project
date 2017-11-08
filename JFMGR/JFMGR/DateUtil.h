/*
Created by YWT
2017.2.27 15:00
*/

#ifndef DATEUTIL_H
#define DATEUTIL_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <string>

/*���ַ����еĴ�д�ַ�ȫ����ΪСд�ַ�*/
void changeToLowercase(const char*);
/*�ж�����Ƿ�Ϊ����*/
int isLeapYear(unsigned int);
/*��ȡ��ǰ��׼Unixʱ��*/
unsigned int getUnixTime();
/*������ʽ��ʱ���ַ���,��������Ϊʱ��,��ʽ(yyyy.mm.dd),��������(en-US,zh-CN)*/
char* createFormattedTime(unsigned int, const char*, const char*);

/*�������صĺ���,���ٴ���ʱ�����,���ظ�ʽ���ַ���,Ĭ�ϸ�ʽΪ yyyy.mm.dd hh:mm:ss
 *ʹ����ɺ�Ӧ��ʱ�����ڴ�
 */
char* getFormattedTime(unsigned int);
char* getFormattedTime(unsigned int, const char*);
char* getFormattedTime(unsigned int, const char*, const char*);


/*
��֧��ʾ����ʽ����
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

���ĸ�ʽ(�ð汾��δ֧��,�����ں�������֧��)
2017��11��17�� 15ʱ36��0��
11��17��2017�� 15ʱ36��0��
17��11��2017�� 15ʱ36��0��
*/

#endif

#pragma once