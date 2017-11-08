/*
Created by YWT
2017.2.27 15:00
*/

/*卡片管理相关模块*/

#include "CardMgr.h"
#include "initVariable.h"
#include "AccountingUtility.h"
#include "SystemLogger.h"
#include "ToolUtils.h"

using namespace std;

string s;
char cID[20];
string cardStatusList[4] = {
	"状态正常,未在使用",
	"状态正常,正在使用",
	"已注销",
	"异常失效",
};

int addNewCard() {
	/*initCard方法负责初始化当前卡片*/
	initCard(currentCard);

	/*isIllegal存储输入是否合法*/
	register bool isIllegal = 0;

	/*输入卡号操作*/
	do {
		cout << "请输入卡号:(最大18位)\n-->";
		cin >> s;
		if (s.length() > 19) {
			cout << "输入长度超出限制，请重试！\n";
			isIllegal = 1;
			continue;
		}
		if (getCardByID(s.c_str()) != NULL) {
			cout << "输入的卡号已存在,请重新输入:\n";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
		strcpy(currentCard->cardID, s.c_str());
	} while (isIllegal);

	/*输入密码操作*/
	cout << "请输入密码:(最大18位)\n-->";
	s = getPassword();
	strcpy(currentCard->cardPassword, s.c_str());

	/*记录创建时间*/
	currentCard->createTime = getUnixTime();
	totalCount++;
	LOG::localLogger(currentCard->createTime, LOG_ADDNEWCARD, 1, 0, currentCard->cardID);
	/*充值*/
	cout << "第一次使用需进行充值\n";
	userCharge(currentCard);
	/*将card指针移动到下一位*/
	currentCard->next = new Card;
	currentCard = currentCard->next;
	currentCard->next = NULL;
	return 0;
}
int queryCard() {
	system("cls");
	system("MODE con: COLS=132 LINES=30");
	cout<<"\n---------------------------------------------------------卡片信息查询----------------------------------------------------------\n";
	register bool isIllegal = 0;
	do{
		cout << "请输入卡号:(最大18位)\n-->";
		cin>>s;
		if(s.length()>19){
			cout<<"输入长度超出限制，请重试！\n";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
		initCharArray(cID,0,20);
		strcpy(cID,s.c_str());
	}while(isIllegal);
	Card* res = getCardByID(s.c_str());
	if(res == NULL){
		cout<<"查询无果!\n";
		LOG::localLogger(getUnixTime(), LOG_QUERYCARD, 0, 0, s.c_str());
		cout << "请按回车键继续...";
		return 0;
	}
	displayCardInfo(res);
	LOG::localLogger(getUnixTime(), LOG_QUERYCARD, 1, 0, res->cardID);
	cout << "请按回车键继续...";
	return 0;
}
int logoutCard() {
	Card* card;
	register bool isIllegal = 0;
	do {
		card = NULL;
		cout << "请输入要注销的卡号:(最大18位)\n-->";
		cin >> s;
		if (s.length()>19) {
			cout << "输入长度超出限制，请重试！\n";
			isIllegal = 1;
			continue;
		}
		card = getCardByID(s.c_str());
		if (card == NULL) {
			cout << "输入的卡号不存在,请重新输入:\n";
			LOG::localLogger(getUnixTime(), LOG_LOGOUTCARD, 0, 0, s.c_str());
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
	} while (isIllegal);

	cout << "请输入密码:(最大18位)\n-->";
	s = getPassword();
	if (strcmp(card->cardPassword,s.c_str()) != 0) {
		cout << "密码错误,请稍后重试!\n";
		LOG::localLogger(getUnixTime(), LOG_LOGOUTCARD, 0, 0, card->cardID);
		return 1;
	}
	LOG::localLogger(getUnixTime(), LOG_LOGOUTCARD, 1, 0, card->cardID);
	userRefund(card);
	return 0;
}

/*以下方法负责初始化一张卡片的相关信息*/
void initCard(Card* card){
	initCharArray(card->cardID,0,20);
	initCharArray(card->cardPassword,0,20);
	initCharArray(card->cardID,0,20);
	card->createTime = 0;
	card->logOutTime= 0;
	card->totalChargeMoney = 0;
	card->totalConsumeMoney = 0;
	card->remainingMoney = 0;
	card->totalUsageTimes = 0;
	card->lastUsageTime = 0;
	card->cStatus = 0;
	card->CCRcount = 0;
	card->headCCR = new CardConsume;
	card->currentCCR = card->headCCR;

}

void displayCardInfo(Card* card){
	char* ct = getFormattedTime(card->createTime);
	char* lt = getFormattedTime(card->lastUsageTime);
	cout << "卡号为:  "
		<< card->cardID << "  的相关信息如下:\n"
		<< "       卡片办理时间        最后一次使用时间      总充值金额      总消费金额      剩余金额      使用次数      卡片当前状态\n"
		<< "-------------------------------------------------------------------------------------------------------------------------------\n\n"
		<< ct << "     " << lt
		<< setfill(' ')
		<< setw(11) << setiosflags(ios::right)
		<< card->totalChargeMoney / 100 << '.'
		<< setfill('0') << setw(2)
		<< card->totalChargeMoney % 100 << "元"

		<< setfill(' ')
		<< setw(11) << setiosflags(ios::right)
		<< card->totalConsumeMoney / 100 << '.'
		<< setfill('0') << setw(2)
		<< card->totalConsumeMoney % 100 << "元"

		<< setfill(' ')
		<< setw(9) << setiosflags(ios::right)
		<< card->remainingMoney / 100 << '.'
		<< setfill('0') << setw(2)
		<< card->remainingMoney % 100 << "元 "

		<< setfill(' ')
		<< setw(12)
		<< card->totalUsageTimes << "次      "
		<< cardStatusList[card->cStatus]
		<< "\n\n-------------------------------------------------------------------------------------------------------------------------------\n";
	delete[] ct;
	delete[] lt;
}

