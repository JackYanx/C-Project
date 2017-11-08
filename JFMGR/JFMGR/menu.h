#ifndef MENU_H
#define MENU_H

#include "AccountingUtility.h"
#include "CardMgr.h"
#include "FileMgrUtil.h"
#include "RulesMgr.h"
#include "StatisticsShow.h"
#include "SystemLogger.h"

int displayMenu();
int fun_CardMgr();
int fun_RulesMgr();
int fun_AccountingMgr();
int fun_MoneyMgr();
int fun_QueryStatistics();
int fun_ExportFiles();

#endif 
#pragma once
