#pragma once

#ifndef ACCOUNTINGUTILITY_H
#define ACCOUNTINGUTILITY_H
#define _CRT_SECURE_NO_WARNINGS

#include "global.h"
/*该模块初始化菜单*/
int accImpl(int);
/*用户充值*/
int userCharge(Card*);
/*用户退款*/
int userRefund(Card*);
/*用户上机*/
int userLogin(Card*);
/*用户下机*/
int userLogout(Card*, bool);
/*系统退出时将全部用户下机*/
int userAllLogout();
/*通过卡片ID获取ID对应卡片的节点地址,不存在时返回NULL*/
Card* getCardByID(const char*);
/*判断用户是否处于上机状态*/
int isUserOnline(Card*);

#endif