#include <iomanip>

#include "StatisticsShow.h"
#include "initVariable.h"
#include "DateUtil.h"
#include "AccountingUtility.h"

using namespace std;

char* ssct;
char* successEnum[2] = {"��","��"};
char* consumeStatus[3] = {"����","��ֵ","�˷�"};

void showCCRImpl() {
	cout << "";
	string s;
	Card* card;
	/*isIllegal�洢�����Ƿ�Ϸ�*/
	register bool isIllegal = 0;

	/*���뿨�Ų���*/
	do {
		card = NULL;
		cout << "�����뿨��:(���18λ)\n";
		cin >> s;
		if (s.length()>19) {
			cout << "���볤�ȳ������ƣ������ԣ�\n";
			isIllegal = 1;
			continue;
		}
		card = getCardByID(s.c_str());
		if (card == NULL) {
			cout << "����Ŀ��Ų�����,����������:\n";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
	} while (isIllegal);
	cout << "           ����ʱ��        ��������        �Ƿ�ɹ�        �ϻ�ʱ��        ���ѽ��\n";
	cout << "-----------------------------------------------------------------------------------\n\n";
	CardConsume* p = card->headCCR;
	int ccrct = 0;
	while (p->next != NULL) {
		showCCR(p);
		ccrct++;
		p = p->next;
	}
	cout << "\n-----------------------------------------------------------------------------------";
	cout << "\n����ѯ��" << ccrct <<"����¼,�밴�س�������";
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
		<< tlength << "����"
		<< setw(11) << setiosflags(ios::right)
		<< CCR->consumeMoney / 100 << '.' 
		<< setfill('0') << setw(2)
		<< CCR->consumeMoney % 100 << "Ԫ"
		<< endl;
	cout << setfill(' ');
	delete[] ssct;
	ssct = NULL;
}

void showStatisticsInfo() {
	char* st = getFormattedTime(initSystemTime,"yyyy/mm/dd", "en-US");
	char* ct = getFormattedTime(getUnixTime(), "yyyy/mm/dd", "en-US");
	unsigned int depositMoney = totalUserChargeMoney - totalUserConsumeMoney;
	cout << "ϵͳ����ʱ��: " << st << endl
		<< "ϵͳ��ǰʱ��: " << ct << endl
		<< "��ע���û���: " << totalCount << endl
		<< "��ǰ��������: " << onlineCount << endl
		<< "���ͬʱ��������: " << maxOnlineCount << endl
		<< "��ǰ�Ʒѹ���: " << currentRuleRating / 100 << '.' << currentRuleRating % 100 << "Ԫ/Сʱ." << endl
		<< "�û��ܳ�ֵ���: " << totalUserChargeMoney / 100 << '.' << totalUserChargeMoney % 100 << "Ԫ" << endl
		<< "�û������ѽ��: " << totalUserConsumeMoney / 100 << '.' << totalUserConsumeMoney % 100 << "Ԫ" << endl
		<< "ϵͳ�����ʽ�: " << depositMoney / 100 << '.' << depositMoney % 100 << "Ԫ." << endl;
	cout << "�밴�س�������...";
	delete[] st;
	delete[] ct;
	st = NULL;
	ct = NULL;
	cin.get();
}