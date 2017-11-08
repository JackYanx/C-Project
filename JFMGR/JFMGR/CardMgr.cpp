/*
Created by YWT
2017.2.27 15:00
*/

/*��Ƭ�������ģ��*/

#include "CardMgr.h"
#include "initVariable.h"
#include "AccountingUtility.h"
#include "SystemLogger.h"
#include "ToolUtils.h"

using namespace std;

string s;
char cID[20];
string cardStatusList[4] = {
	"״̬����,δ��ʹ��",
	"״̬����,����ʹ��",
	"��ע��",
	"�쳣ʧЧ",
};

int addNewCard() {
	/*initCard���������ʼ����ǰ��Ƭ*/
	initCard(currentCard);

	/*isIllegal�洢�����Ƿ�Ϸ�*/
	register bool isIllegal = 0;

	/*���뿨�Ų���*/
	do {
		cout << "�����뿨��:(���18λ)\n-->";
		cin >> s;
		if (s.length() > 19) {
			cout << "���볤�ȳ������ƣ������ԣ�\n";
			isIllegal = 1;
			continue;
		}
		if (getCardByID(s.c_str()) != NULL) {
			cout << "����Ŀ����Ѵ���,����������:\n";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
		strcpy(currentCard->cardID, s.c_str());
	} while (isIllegal);

	/*�����������*/
	cout << "����������:(���18λ)\n-->";
	s = getPassword();
	strcpy(currentCard->cardPassword, s.c_str());

	/*��¼����ʱ��*/
	currentCard->createTime = getUnixTime();
	totalCount++;
	LOG::localLogger(currentCard->createTime, LOG_ADDNEWCARD, 1, 0, currentCard->cardID);
	/*��ֵ*/
	cout << "��һ��ʹ������г�ֵ\n";
	userCharge(currentCard);
	/*��cardָ���ƶ�����һλ*/
	currentCard->next = new Card;
	currentCard = currentCard->next;
	currentCard->next = NULL;
	return 0;
}
int queryCard() {
	system("cls");
	system("MODE con: COLS=132 LINES=30");
	cout<<"\n---------------------------------------------------------��Ƭ��Ϣ��ѯ----------------------------------------------------------\n";
	register bool isIllegal = 0;
	do{
		cout << "�����뿨��:(���18λ)\n-->";
		cin>>s;
		if(s.length()>19){
			cout<<"���볤�ȳ������ƣ������ԣ�\n";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
		initCharArray(cID,0,20);
		strcpy(cID,s.c_str());
	}while(isIllegal);
	Card* res = getCardByID(s.c_str());
	if(res == NULL){
		cout<<"��ѯ�޹�!\n";
		LOG::localLogger(getUnixTime(), LOG_QUERYCARD, 0, 0, s.c_str());
		cout << "�밴�س�������...";
		return 0;
	}
	displayCardInfo(res);
	LOG::localLogger(getUnixTime(), LOG_QUERYCARD, 1, 0, res->cardID);
	cout << "�밴�س�������...";
	return 0;
}
int logoutCard() {
	Card* card;
	register bool isIllegal = 0;
	do {
		card = NULL;
		cout << "������Ҫע���Ŀ���:(���18λ)\n-->";
		cin >> s;
		if (s.length()>19) {
			cout << "���볤�ȳ������ƣ������ԣ�\n";
			isIllegal = 1;
			continue;
		}
		card = getCardByID(s.c_str());
		if (card == NULL) {
			cout << "����Ŀ��Ų�����,����������:\n";
			LOG::localLogger(getUnixTime(), LOG_LOGOUTCARD, 0, 0, s.c_str());
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
	} while (isIllegal);

	cout << "����������:(���18λ)\n-->";
	s = getPassword();
	if (strcmp(card->cardPassword,s.c_str()) != 0) {
		cout << "�������,���Ժ�����!\n";
		LOG::localLogger(getUnixTime(), LOG_LOGOUTCARD, 0, 0, card->cardID);
		return 1;
	}
	LOG::localLogger(getUnixTime(), LOG_LOGOUTCARD, 1, 0, card->cardID);
	userRefund(card);
	return 0;
}

/*���·��������ʼ��һ�ſ�Ƭ�������Ϣ*/
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
	cout << "����Ϊ:  "
		<< card->cardID << "  �������Ϣ����:\n"
		<< "       ��Ƭ����ʱ��        ���һ��ʹ��ʱ��      �ܳ�ֵ���      �����ѽ��      ʣ����      ʹ�ô���      ��Ƭ��ǰ״̬\n"
		<< "-------------------------------------------------------------------------------------------------------------------------------\n\n"
		<< ct << "     " << lt
		<< setfill(' ')
		<< setw(11) << setiosflags(ios::right)
		<< card->totalChargeMoney / 100 << '.'
		<< setfill('0') << setw(2)
		<< card->totalChargeMoney % 100 << "Ԫ"

		<< setfill(' ')
		<< setw(11) << setiosflags(ios::right)
		<< card->totalConsumeMoney / 100 << '.'
		<< setfill('0') << setw(2)
		<< card->totalConsumeMoney % 100 << "Ԫ"

		<< setfill(' ')
		<< setw(9) << setiosflags(ios::right)
		<< card->remainingMoney / 100 << '.'
		<< setfill('0') << setw(2)
		<< card->remainingMoney % 100 << "Ԫ "

		<< setfill(' ')
		<< setw(12)
		<< card->totalUsageTimes << "��      "
		<< cardStatusList[card->cStatus]
		<< "\n\n-------------------------------------------------------------------------------------------------------------------------------\n";
	delete[] ct;
	delete[] lt;
}

