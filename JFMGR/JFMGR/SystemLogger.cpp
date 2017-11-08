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
	/*��ʼ��ϵͳ��־��¼�ṹ��*/
	LOG::initLogInfo(LogInfo);
	/*��ϵͳ��־��¼�ṹ���еĸ�����Ϣ��ֵ*/
	LogInfo->mTime = mTime;
	LogInfo->operationType = operationType;
	LogInfo->isSuccess = isSuccess;
	LogInfo->money = money;
	if (cardID != NULL) {
		strcpy(LogInfo->cardID, cardID);
	}
	/*��������־��¼��Ϣд���ļ��в�����*/
	saveLogInfoToFile(LogInfo);
	return 0;
}

int LOG::showLogImpl() {
	std::cout << "\n-----------------------------------------------------------------------------------\n"
		<< "ϵͳ��־�ļ�������: " << systemLogPath
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "\n��־�ļ���ʽ˵��: ʱ��,��������״̬��,�Ƿ�ɹ�,�������,��ƬID(�����)\n"
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "��������״̬������:\n  "
		<< std::setbase(16)
		<< " 0x" << LOG_SYSINIT        << "  ϵͳ����\n  "
		<< " 0x" << LOG_SYSEXIT        << "  ϵͳ�˳�\n  "
		<< " 0x" << LOG_IMPORTUD       << "  �����������\n  "
		<< " 0x" << LOG_EXPORTUD       << "  �����������\n  "
		<< " 0x" << LOG_ADDNEWCARD     << "  ����¿�Ƭ\n  "
		<< " 0x" << LOG_QUERYCARD      << "  ��ѯ��Ƭ\n  "
		<< " 0x" << LOG_LOGOUTCARD     << "  ע����Ƭ\n  "
		<< " 0x" << LOG_CREATENEWRULES << "  �����¹���\n  "
		<< " 0x" << LOG_CHANGERULES    << "  �������\n  "
		<< " 0x" << LOG_USERLOGIN      << "  �û��ϻ�\n  "
		<< " 0x" << LOG_USERLOGOUT     << "  �û��»�\n  "
		<< " 0x" << LOG_USERCHARGE     << "  �û���ֵ\n  "
		<< " 0x" << LOG_USERREFUND     << "  �û��˷�"
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "�밴�س�������..."
		<< std::endl;
	std::cin.get();
	return 0;
}