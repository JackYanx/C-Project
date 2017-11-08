#pragma once

#ifndef INITVARIABLE_H
#define INITVARIABLE_H

#include "CardInfo.h"
#include "RulesInfo.h"
#include "DateUtil.h"
#include "SystemLog.h"


/*��Ҫ��ʼ�������ȫ�ֱ���*/
extern Card* headCard;
extern Card* currentCard;
extern OnlineUser* headOU;
extern OnlineUser* currentOU;
extern Rule* headRule;
extern Rule* currentRule;
extern SYSLOG* LogInfo;
/*��ǰ����*/
extern unsigned currentRuleRating;
/*��ǰ��������ͳ��*/
extern int onlineCount;
/*ϵͳ���ͬʱ��������*/
extern int maxOnlineCount;
/*������ͳ��*/
extern int totalCount;
/*ϵͳ����ʱ��*/
extern unsigned int initSystemTime;
/*�û��ܳ�ֵ���*/
extern unsigned int totalUserChargeMoney;
/*�û������ѽ��*/
extern unsigned int totalUserConsumeMoney;
/*���濨Ƭ��Ϣ�ļ�Ŀ¼*/
extern char* cardDataPath;
/*����Ʒѹ�����Ϣ�ļ�Ŀ¼*/
extern char* rulesDataPath;
/*����ͳ����Ϣ�ļ�Ŀ¼*/
extern char* toSataPath;
/*����ϵͳ��־�ļ�Ŀ¼*/
extern char* systemLogPath;
#endif
