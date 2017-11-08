#include "SystemLogger.h"
#include "initVariable.h"
#include "ToolUtils.h"

void LOG::initLogInfo(SYSLOG* LogInfo) {
	LogInfo->mTime = 0;
	LogInfo->operationType = 0;
	LogInfo->isSuccess = 0;
	LogInfo->money = 0;
	initCharArray(LogInfo->cardID,0,20);
}

void LOG::showLogInfo() {

}

int LOG::localLogger(unsigned int mTime, unsigned int operationType, unsigned int isSuccess, unsigned int money, const char* cardID) {
	/*初始化系统日志记录结构体*/
	LOG::initLogInfo(LogInfo);
	/*对系统日志记录结构体中的各项信息赋值*/
	LogInfo->mTime = mTime;
	LogInfo->operationType = operationType;
	LogInfo->isSuccess = isSuccess;
	LogInfo->money = money;
	if (cardID != NULL) {
		strcpy(LogInfo->cardID, cardID);
	}
	/*将本次日志记录信息写入文件中并保存*/
	saveLogInfoToFile(LogInfo);
	return 0;
}

int LOG::showLogImpl() {
	std::cout << "\n-----------------------------------------------------------------------------------\n"
		<< "系统日志文件保存在: " << systemLogPath
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "\n日志文件格式说明: 时间,操作类型状态码,是否成功,操作金额,卡片ID(如果有)\n"
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "操作类型状态码如下:\n  "
		<< std::setbase(16)
		<< " 0x" << LOG_SYSINIT        << "  系统启动\n  "
		<< " 0x" << LOG_SYSEXIT        << "  系统退出\n  "
		<< " 0x" << LOG_IMPORTUD       << "  导入相关数据\n  "
		<< " 0x" << LOG_EXPORTUD       << "  导出相关数据\n  "
		<< " 0x" << LOG_ADDNEWCARD     << "  添加新卡片\n  "
		<< " 0x" << LOG_QUERYCARD      << "  查询卡片\n  "
		<< " 0x" << LOG_LOGOUTCARD     << "  注销卡片\n  "
		<< " 0x" << LOG_CREATENEWRULES << "  创建新规则\n  "
		<< " 0x" << LOG_CHANGERULES    << "  变更规则\n  "
		<< " 0x" << LOG_USERLOGIN      << "  用户上机\n  "
		<< " 0x" << LOG_USERLOGOUT     << "  用户下机\n  "
		<< " 0x" << LOG_USERCHARGE     << "  用户充值\n  "
		<< " 0x" << LOG_USERREFUND     << "  用户退费"
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "请按回车键继续..."
		<< std::endl;
	std::cin.get();
	return 0;
}