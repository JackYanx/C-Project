#include "menu.h"

using namespace std;

int mStatus = 0;
bool inputValuable = 0;

int displayMenu() {
	int status;
	cout << "\n--------------------------------欢迎使用计费管理系统-------------------------------\n"
		<< "\n-------------------  AMS  版本: v1.0  Author: y1601 Yan Weitao  -------------------\n"
		<< "\n                    ***************1.卡片管理相关***************                   \n"
		<< "\n                    ***************2.计费标准管理***************                   \n"
		<< "\n                    **************3.用户上机与下机**************                   \n"
		<< "\n                    ***************4.卡片费用管理***************                   \n"
		<< "\n                    ********5.消费信息查询与营业相关统计********                   \n"
		<< "\n                    ***************6.数据文件导出***************                   \n"
		<< "\n                    ***************7.退出管理系统***************                   \n"
		<< "\n-----------------------------------------------------------------------------------\n"
		<< "请选择:\n-->";



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
		cout << "输入有误,请重试!\n";
		cin.get();
		return 1;
	}
	return 1;
}

int fun_CardMgr() {
	do {
		cout << "\n------------------------------------卡片管理相关-----------------------------------\n"
			<< "\n                    ****************1.添加新卡片****************                   \n"
			<< "\n                    ***************2.查询卡片信息***************                   \n"
			<< "\n                    *****************3.注销卡片*****************                   \n"
			<< "\n                    ***************4.返回上级菜单***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "请选择:\n-->";

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
			cout << "输入有误,请重试!\n";
			cin.get();
		}
		//cin.get();
		system("cls");
	} while (1);
}
int fun_RulesMgr() {
	do{
		cout << "\n------------------------------------计费标准管理-----------------------------------\n"
			<< "\n                    ***************1.查询所有标准***************                   \n"
			<< "\n                    ***************2.修改当前标准***************                   \n"
			<< "\n                    ***************3.返回上级菜单***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "请选择:\n-->";

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
			cout << "输入有误,请重试!\n";
			cin.get();
		}
		//cin.get();
		system("cls");
	} while (1);
	return 0;
}
int fun_AccountingMgr() {
	do{
		cout << "\n-----------------------------------用户上机与下机----------------------------------\n"
			<< "\n                    *****************1.用户上机*****************                   \n"
			<< "\n                    *****************2.用户下机*****************                   \n"
			<< "\n                    ***************3.返回上级菜单***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "请选择:\n-->";
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
			cout << "输入有误,请重试!\n";
			cin.get();
		}
		cin.get();
		//cin.get();
		system("cls");
	} while (1);
}
int fun_MoneyMgr() {
	do{
		cout << "\n------------------------------------卡片费用管理-----------------------------------\n"
			<< "\n                    *****************1.卡片充值*****************                   \n"
			<< "\n                    *****************2.卡片退费*****************                   \n"
			<< "\n                    ***************3.返回上级菜单***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "请选择:\n-->";

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
			cout << "输入有误,请重试!\n";
			cin.get();
		}
		cin.get();
		system("cls");
	} while (1);
}
int fun_QueryStatistics() {
	do{
		cout << "\n-----------------------------------信息查询与统计----------------------------------\n"
			<< "\n                    ***************1.查询消费记录***************                   \n"
			<< "\n                    ***************2.统计营业总额***************                   \n"
			<< "\n                    ***************3.返回上级菜单***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "请选择:\n-->";
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
			cout << "输入有误,请重试!\n";
			cin.get();
		}
		
		system("cls");
	} while (1);
}
int fun_ExportFiles() {
	system("MODE con: COLS=88 LINES=30");
	do {
		cout << "\n-----------------------------------数据文件导出-----------------------------------\n"
			<< "\n                    ***************1.导出相关文件***************                   \n"
			<< "\n                    ***************2.查看系统日志***************                   \n"
			<< "\n                    ***************3.返回上级菜单***************                   \n"
			<< "\n-----------------------------------------------------------------------------------\n"
			<< "请选择:\n-->";
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
			cout << "输入有误,请重试!\n";
			cin.get();
		}
		system("cls");
	} while (1);
}