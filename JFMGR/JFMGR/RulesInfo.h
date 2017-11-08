/*
Created by YWT
2017.2.27 15:00
*/

#ifndef RULESINFO_H
#define RULESINFO_H

/*无特殊情况,所有金额记录单位均为分(人民币)*/

/*执行的计费规则结构体*/
typedef struct Rule{
	/*计费规则开始执行时间*/
	unsigned int startTime;
	/*计费规则结束执行时间*/
	unsigned int endTime;
	/*该规则状态，0为无效，1为正在使用*/
	int rStatus;
	/*计费费率，单位 元/小时 */
	int rating;
	/*指向下一条计费规则的指针*/
	Rule* next;
}Rule;

#endif