#pragma once

#ifndef INITVARIABLE_H
#define INITVARIABLE_H

#include "CardInfo.h"
#include "RulesInfo.h"
#include "DateUtil.h"
#include "SystemLog.h"


/*需要初始化的相关全局变量*/
extern Card* headCard;
extern Card* currentCard;
extern OnlineUser* headOU;
extern OnlineUser* currentOU;
extern Rule* headRule;
extern Rule* currentRule;
extern SYSLOG* LogInfo;
/*当前费率*/
extern unsigned currentRuleRating;
/*当前在线人数统计*/
extern int onlineCount;
/*系统最高同时在线人数*/
extern int maxOnlineCount;
/*总人数统计*/
extern int totalCount;
/*系统启动时间*/
extern unsigned int initSystemTime;
/*用户总充值金额*/
extern unsigned int totalUserChargeMoney;
/*用户总消费金额*/
extern unsigned int totalUserConsumeMoney;
/*储存卡片信息文件目录*/
extern char* cardDataPath;
/*储存计费规则信息文件目录*/
extern char* rulesDataPath;
/*储存统计信息文件目录*/
extern char* toSataPath;
/*储存系统日志文件目录*/
extern char* systemLogPath;
#endif
