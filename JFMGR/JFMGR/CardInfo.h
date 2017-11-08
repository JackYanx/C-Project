/*
Created by YWT
2017.2.27 15:00
*/

#pragma once

#ifndef CARDINFO_H
#define CARDINFO_H

/*无特殊情况,所有金额记录单位均为分(人民币)*/

/*一张卡的消费记录*/
typedef struct CardConsume{
	/*该次消费记录时间*/
	unsigned int mTime;
	/*该次上机时长*/
	unsigned int tLength;
	/*该次消费金额*/
	unsigned int consumeMoney;
	/*该次操作是否成功,0为失败,1为成功*/
	bool isSuccess;
	/*是否为话花费记录,0为消费,1为充值,2为退费*/
	int consumeType;
	/*指向下一次记录的指针*/
	CardConsume* next;
}CardConsume;

/*卡基本信息*/
typedef struct Card{
	///*用户唯一标识*///
	//char UID[20];
	/*卡号*/
	char cardID[20];
	/*卡密*/
	char cardPassword[20];
	/*卡创建时间*/
	unsigned int createTime;
	/*卡最后一次使用时间*/
	unsigned int lastUsageTime;
	/*卡注销时间*/
	unsigned int logOutTime;
	/*卡当总充值金额*/
	unsigned int totalChargeMoney;
	/*卡当总消费金额*/
	unsigned int totalConsumeMoney;
	/*卡当前总金额*/
	unsigned int remainingMoney;
	/*共计使用次数*/
	unsigned int totalUsageTimes;
	/*卡当前状态，0为未在使用，1为正在使用，2为已注销，3为异常失效,4为系统退出时余额不足待充值*/
	int cStatus;
	/*消费记录数目*/
	int CCRcount;
	/*该指针指向该卡消费信息头结构体*/
	CardConsume* headCCR;
	/*该指针指向该卡消费信息当前结构体*/
	CardConsume* currentCCR;
	/*该指针指向下一张卡结构体*/
	Card* next;
}Card;


/*在线用户列表结构体*/
typedef struct OnlineUser {
	/*开始上机时间*/
	unsigned int sTime;
	/*指向对应卡片的指针*/
	Card* card;
	/*指向下一个在线用户结构体的指针*/
	OnlineUser* next;
} OnlineUser;

#endif