#include <iomanip>

#include "StatisticsShow.h"
#include "initVariable.h"
#include "DateUtil.h"
#include "AccountingUtility.h"

using namespace std;

char* ssct;
char* successEnum[2] = {"否","是"};
char* consumeStatus[3] = {"消费","充值","退费"};

void showCCRImpl() {
	cout << "";
	string s;
	Card* card;
	/*isIllegal存储输入是否合法*/
	register bool isIllegal = 0;

	/*输入卡号操作*/
	do {
		card = NULL;
		cout << "请输入卡号:(最大18位)\n";
		cin >> s;
		if (s.length()>19) {
			cout << "输入长度超出限制，请重试！\n";
			isIllegal = 1;
			continue;
		}
		card = getCardByID(s.c_str());
		if (card == NULL) {
			cout << "输入的卡号不存在,请重新输入:\n";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
	} while (isIllegal);
	cout << "           消费时间        消费类型        是否成功        上机时长        消费金额\n";
	cout << "-----------------------------------------------------------------------------------\n\n";
	CardConsume* p = card->headCCR;
	int ccrct = 0;
	while (p->next != NULL) {
		showCCR(p);
		ccrct++;
		p = p->next;
	}
	cout << "\n-----------------------------------------------------------------------------------";
	cout << "\n共查询到" << ccrct <<"条记录,请按回车键继续";
	cin.get();
}

void showCCR(CardConsume* CCR) {
	ssct = getFormattedTime(CCR->mTime);
	unsigned int tlength = CCR->tLength / 60;
	tlength += (CCR->tLength % 60 == 0) ? 0 : 1;
	cout <<ssct << "            "
		<< consumeStatus[CCR->consumeType] << "              "
		<< successEnum[CCR->isSuccess]
		<< setw(12) << setiosflags(ios::right)
		<< tlength << "分钟"
		<< setw(11) << setiosflags(ios::right)
		<< CCR->consumeMoney / 100 << '.' 
		<< setfill('0') << setw(2)
		<< CCR->consumeMoney % 100 << "元"
		<< endl;
	cout << setfill(' ');
	delete[] ssct;
	ssct = NULL;
}

void showStatisticsInfo() {
	char* st = getFormattedTime(initSystemTime,"yyyy/mm/dd", "en-US");
	char* ct = getFormattedTime(getUnixTime(), "yyyy/mm/dd", "en-US");
	unsigned int depositMoney = totalUserChargeMoney - totalUserConsumeMoney;
	cout << "系统启动时间: " << st << endl
		<< "系统当前时间: " << ct << endl
		<< "总注册用户数: " << totalCount << endl
		<< "当前在线人数: " << onlineCount << endl
		<< "最高同时在线人数: " << maxOnlineCount << endl
		<< "当前计费规则: " << currentRuleRating / 100 << '.' << currentRuleRating % 100 << "元/小时." << endl
		<< "用户总充值金额: " << totalUserChargeMoney / 100 << '.' << totalUserChargeMoney % 100 << "元" << endl
		<< "用户总消费金额: " << totalUserConsumeMoney / 100 << '.' << totalUserConsumeMoney % 100 << "元" << endl
		<< "系统沉淀资金: " << depositMoney / 100 << '.' << depositMoney % 100 << "元." << endl;
	cout << "请按回车键继续...";
	delete[] st;
	delete[] ct;
	st = NULL;
	ct = NULL;
	cin.get();
}