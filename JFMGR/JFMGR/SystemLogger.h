#pragma once

#ifndef SYSTEMLOGGER_H
#define SYSTEMLOGGER_H

#define LOG_SYSINIT         0x1
#define LOG_SYSEXIT         0x2
#define LOG_IMPORTUD        0x3
#define LOG_EXPORTUD        0x4
#define LOG_ADDNEWCARD      0x5
#define LOG_QUERYCARD       0x6
#define LOG_LOGOUTCARD      0x7
#define LOG_CREATENEWRULES  0x8
#define LOG_CHANGERULES     0x9
#define LOG_USERLOGIN       0xA
#define LOG_USERLOGOUT      0xB
#define LOG_USERCHARGE      0xC
#define LOG_USERREFUND      0xD

#include "global.h"
#include "FileMgrUtil.h"

namespace LOG {
	void initLogInfo(SYSLOG*);
	void showLogInfo();
	int localLogger(unsigned int, unsigned int,unsigned int,unsigned int,const char*);
	int showLogImpl();
} 

#endif // !SYSTEMLOGGER_H




