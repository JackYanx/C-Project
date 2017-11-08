#pragma once

#ifndef ACCOUNTINGUTILITY_H
#define ACCOUNTINGUTILITY_H
#define _CRT_SECURE_NO_WARNINGS

#include "global.h"
/*��ģ���ʼ���˵�*/
int accImpl(int);
/*�û���ֵ*/
int userCharge(Card*);
/*�û��˿�*/
int userRefund(Card*);
/*�û��ϻ�*/
int userLogin(Card*);
/*�û��»�*/
int userLogout(Card*, bool);
/*ϵͳ�˳�ʱ��ȫ���û��»�*/
int userAllLogout();
/*ͨ����ƬID��ȡID��Ӧ��Ƭ�Ľڵ��ַ,������ʱ����NULL*/
Card* getCardByID(const char*);
/*�ж��û��Ƿ����ϻ�״̬*/
int isUserOnline(Card*);

#endif