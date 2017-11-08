#include "menu.h"

using namespace std;

int mStatus = 0;
bool inputValuable = 0;

int displayMenu() {
	int status;
	cout << "\n--------------------------------��ӭʹ�üƷѹ���ϵͳ-------------------------------\n"
		<< "\n-------------------  AMS  �汾: v1.0  Author: y1601 Yan Weitao  -------------------\n"
		<< "\n                    ***************1.��Ƭ�������***************                   \n"
		<< "\n                    ***************2.�Ʒѱ�׼����***************                   \n"
		<< "\n                    **************3.�û��ϻ����»�**************                   \n"
		<< "\n                    ***************4.��Ƭ���ù���***************                   \n"
		<< "\n                    ********5.������Ϣ��ѯ��Ӫҵ���ͳ��********                   \n"
		<< "\n                    ***************6.�����ļ�����***************                   \n"
		<< "\n                    ***************7.�˳�����ϵͳ***************                   \n"
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "��ѡ��:\n-->";



	cin >> status;
	switch (status) {
	case 1:
		system("cls");
		fun_CardMgr();
		//cin.get();
		break;
	case 2:
		system("cls");
		fun_RulesMgr();
		cin.get();
		break;
	case 3:
		system("cls");
		fun_AccountingMgr();
		//cin.get();
		break;
	case 4:
		system("cls");
		fun_MoneyMgr();
		cin.get();
		break;
	case 5:
		system("cls");
		fun_QueryStatistics();
		cin.get();
		break;
	case 6:
		system("cls");
		fun_ExportFiles();
		break;
	case 7:
		return 0;
	default:
		cout << "��������,������!\n";
		cin.get();
		return 1;
	}
	return 1;
}

int fun_CardMgr() {
	do {
		cout << "\n------------------------------------��Ƭ�������-----------------------------------\n"
			<< "\n                    ****************1.����¿�Ƭ****************                   \n"
			<< "\n                    ***************2.��ѯ��Ƭ��Ϣ***************                   \n"
			<< "\n                    *****************3.ע����Ƭ*****************                   \n"
			<< "\n                    ***************4.�����ϼ��˵�***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "��ѡ��:\n-->";

		cin >> mStatus;
		switch (mStatus) {
		case 1:
			addNewCard();
			cin.get();
			cin.get();
			break;
		case 2:
			queryCard();
			cin.get();
			cin.get();
			system("MODE con: COLS=88 LINES=30");
			break;
		case 3:
			logoutCard();
			cin.get();
			cin.get();
			break;
		case 4:
			return 1;
		default:
			cout << "��������,������!\n";
			cin.get();
		}
		//cin.get();
		system("cls");
	} while (1);
}
int fun_RulesMgr() {
	do{
		cout << "\n------------------------------------�Ʒѱ�׼����-----------------------------------\n"
			<< "\n                    ***************1.��ѯ���б�׼***************                   \n"
			<< "\n                    ***************2.�޸ĵ�ǰ��׼***************                   \n"
			<< "\n                    ***************3.�����ϼ��˵�***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "��ѡ��:\n-->";

		cin >> mStatus;
		switch (mStatus) {
		case 1:
			queryRules();
			cin.get();
			cin.get();
			break;
		case 2:
			changeRules();
			cin.get();
			cin.get();
			break;
		case 3:
			return 1;
			break;
		default:
			cout << "��������,������!\n";
			cin.get();
		}
		//cin.get();
		system("cls");
	} while (1);
	return 0;
}
int fun_AccountingMgr() {
	do{
		cout << "\n-----------------------------------�û��ϻ����»�----------------------------------\n"
			<< "\n                    *****************1.�û��ϻ�*****************                   \n"
			<< "\n                    *****************2.�û��»�*****************                   \n"
			<< "\n                    ***************3.�����ϼ��˵�***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "��ѡ��:\n-->";
		cin >> mStatus;
		switch (mStatus) {
		case 1:
			accImpl(3);
			cin.get();
			cin.get();
			break;
		case 2:
			accImpl(4);
			cin.get();
			cin.get();
			break;
		case 3:
			return 1;
			break;
		default:
			cout << "��������,������!\n";
			cin.get();
		}
		cin.get();
		//cin.get();
		system("cls");
	} while (1);
}
int fun_MoneyMgr() {
	do{
		cout << "\n------------------------------------��Ƭ���ù���-----------------------------------\n"
			<< "\n                    *****************1.��Ƭ��ֵ*****************                   \n"
			<< "\n                    *****************2.��Ƭ�˷�*****************                   \n"
			<< "\n                    ***************3.�����ϼ��˵�***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "��ѡ��:\n-->";

		cin >> mStatus;
		switch (mStatus) {
		case 1:
			accImpl(1);
			cin.get();
			cin.get();
			break;
		case 2:
			accImpl(2);
			cin.get();
			cin.get();
			break;
		case 3:
			return 1;
			break;
		default:
			cout << "��������,������!\n";
			cin.get();
		}
		cin.get();
		system("cls");
	} while (1);
}
int fun_QueryStatistics() {
	do{
		cout << "\n-----------------------------------��Ϣ��ѯ��ͳ��----------------------------------\n"
			<< "\n                    ***************1.��ѯ���Ѽ�¼***************                   \n"
			<< "\n                    ***************2.ͳ��Ӫҵ�ܶ�***************                   \n"
			<< "\n                    ***************3.�����ϼ��˵�***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "��ѡ��:\n-->";
		cin >> mStatus;
		switch (mStatus) {
		case 1:
			showCCRImpl();
			cin.get();
			break;
		case 2:
			showStatisticsInfo();
			cin.get();
			break;
		case 3:
			return 1;
			break;
		default:
			cout << "��������,������!\n";
			cin.get();
		}
		
		system("cls");
	} while (1);
}
int fun_ExportFiles() {
	system("MODE con: COLS=88 LINES=30");
	do {
		cout << "\n-----------------------------------�����ļ�����-----------------------------------\n"
			<< "\n                    ***************1.��������ļ�***************                   \n"
			<< "\n                    ***************2.�鿴ϵͳ��־***************                   \n"
			<< "\n                    ***************3.�����ϼ��˵�***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "��ѡ��:\n-->";
		cin >> mStatus;
		switch (mStatus) {
		case 1:
			system("cls");
			system("MODE con: COLS=140 LINES=60");
			exportDataToFile(1);
			LOG::localLogger(getUnixTime(), LOG_EXPORTUD, 1, 0, NULL);
			cin.get();
			system("MODE con: COLS=88 LINES=30");
			break;
		case 2:
			system("cls");
			system("MODE con: COLS=88 LINES=30");
			LOG::showLogImpl();
			cin.get();
			break;
		case 3:
			return 1;
			break;
		default:
			cout << "��������,������!\n";
			cin.get();
		}
		system("cls");
	} while (1);
}