#include "AccountingUtility.h"
#include "SystemLogger.h"
#include "initVariable.h"
#include "ToolUtils.h"

using namespace std;

Card* card;

/*�����ĸ�����ֻ��AccountingUtilityģ��ʹ��*/
/*�����µ�OnlineUser�ڵ�,��Ƭָ���ʱ��Ϊ����*/
int addToOUList(Card*, unsigned int);

/*��OnlieUser�б����޳���Ӧ�ľ���Cardָ���OU�ڵ�*/
unsigned int removeFromOUList(Card*);

/*��ʼ����Ƭ���Ѽ�¼�ṹ��*/
void initCCR(CardConsume*);

/*��ȡ��ʼ�ϻ�ʱ�䲢��OU�б���ɾ�����и�cardָ���Ӧ�Ľڵ�*/
unsigned int getStartTimeAndRemoveFromOUList(Card*);

int accImpl(int status) {
	string s;
	/*isIllegal�洢�����Ƿ�Ϸ�*/
	register bool isIllegal = 0;

	/*���뿨�Ų���*/
	do {
		card = NULL;
		cout << "�����뿨��:(���18λ)\n-->";
		cin >> s;
		if (s.length()>19) {
			cout << "���볤�ȳ������ƣ������ԣ�\n";
			isIllegal = 1;
			continue;
		}
		card = getCardByID(s.c_str());
		if (card == NULL) {
			cout << "����Ŀ��Ų�����,����������:\n-->";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
	} while (isIllegal);
	if (card->cStatus == 4) {
		cout << "�ϴ�ϵͳ�˳����н���ʱ��������,���ֵ!\n";
		userCharge(card);
	}
	switch (status) {
	case 1:
		userCharge(card);
		break;
	case 2:
		userRefund(card);
		break;
	case 3:
		userLogin(card);
		break;
	case 4:
		userLogout(card, 1);
		break;
	}
	return 0;
}

int userCharge(Card* card){
	if (card == NULL) {
		cout << "������Ч,���Ժ�����!\n-->";
		//cin.get();
		return -1;
	}
	if (card->cStatus == 3) {
		cout << "��Ƭ�쳣,����Ϲ������صĵ���!(����~)\n-->";
		//cin.get();
	}
	if (card->cStatus == 2) {
		cout << "�ÿ�Ƭ��ע��,�Ƿ��ֵ���������ÿ�Ƭ?(Y/N)\n-->";
		char c;
		cin >> c;
		if (c == 'Y' || c == 'y') {
			card->cStatus = 0;
		}
		else {
			cout << "����ȡ��!";
			//cin.get();
			return -1;
		}
	}
	cout<<"�������ֵ���:(��λ:Ԫ)\n-->";
	unsigned int money = 0;
	cin>>money;
	money *= 100;
	card->remainingMoney += money;
	card->totalChargeMoney += money;
	totalUserChargeMoney += money;
	card->totalUsageTimes++;
	card->CCRcount++;
	card->cStatus = 0;
	initCCR(card->currentCCR);
	card->currentCCR->mTime = getUnixTime();
	card->lastUsageTime = card->currentCCR->mTime;
	card->currentCCR->consumeMoney = money;
	card->currentCCR->consumeType = 1;
	card->currentCCR->isSuccess = 1;
	card->currentCCR->next = new CardConsume;
	card->currentCCR = card->currentCCR->next;
	card->currentCCR->next = NULL;
	cout << "��ֵ�ɹ�!���Ϊ:" << money / 100 << '.' << money % 100 << "Ԫ\n";
	LOG::localLogger(card->lastUsageTime, LOG_USERCHARGE, 1, money, card->cardID);
	cout << "�밴�س�������...";
	return 0;
}

int userRefund(Card* card) {
	if (card == NULL) {
		cout << "������Ч,���Ժ�����!\n";
		//cin.get();
		return -1;
	}
	if (card->cStatus != 0) {
		if (card->cStatus == 1) {
			cout << "��ǰ��Ƭ�����ϻ�״̬,�����»�����...\n";
			userLogout(card,1);
		}
		else if(card->cStatus == 2){
			cout << "�ÿ�Ƭ��ע��!\n";
			//cin.get();
			return -1;
		}
		else if (card->cStatus == 3) {
			cout << "�ÿ�Ƭ�����쳣,����Ϲ������ؽ��е���!(�ʵ�~)\n";
			//cin.get();
			return -1;
		}
		else {
			cout << "������Ч!\n";
			//cin.get();
			return -1;
		}
	}
	cout << "��ǰ����ʣ����Ϊ: " << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "Ԫ.\n";
	cout << "��ȷʵҪע���ÿ�Ƭ��?(Y/N)\n-->";
	char cz;
	cin >> cz;
	if (cz == 'Y' || cz == 'y') {
		unsigned int money = card->remainingMoney;
		card->cStatus = 2;
		card->logOutTime = getUnixTime();
		card->totalUsageTimes++;
		card->CCRcount++;
		card->totalChargeMoney -= card->remainingMoney;
		totalUserChargeMoney -= money;
		cout << "�˿���Ϊ: " << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "Ԫ.\n";
		initCCR(card->currentCCR);
		card->currentCCR->mTime = card->logOutTime;
		card->currentCCR->consumeMoney = card->remainingMoney;
		card->currentCCR->consumeType = 2;
		card->currentCCR->isSuccess = 1;
		card->currentCCR->next = new CardConsume;
		card->currentCCR = card->currentCCR->next;
		card->currentCCR->next = NULL;
		card->remainingMoney = 0;
		LOG::localLogger(card->logOutTime, LOG_USERREFUND, 1, money, card->cardID);
		cout << "�밴�س�������...";
		return 0;
	}
	else {
		cout << "����ȡ��!";
		LOG::localLogger(getUnixTime(), LOG_USERREFUND, 0, 0, card->cardID);
		return -1;
	}
	return 0;
}

int userLogin(Card* card) {
	if (card == NULL) {
		cout << "������Ч,���Ժ�����!\n";
		//cin.get();
		return -1;
	}
	if (card->cStatus != 0) {
		if (card->cStatus == 1) {
			cout << "��ǰ��Ƭ�����ϻ�״̬,������ֱ��ʹ��!\n";
			//cin.get();
			return -1;
		}
		else if (card->cStatus == 2) {
			cout << "�ÿ�Ƭ��ע��,��ֵ�󼴿ɻָ�����ʹ��!\n";
			//cin.get();
			return -1;
		}
		else if (card->cStatus == 3) {
			cout << "�ÿ�Ƭ�����쳣,����Ϲ������ؽ��е���!(�ʵ�~)\n";
			//cin.get();
			return -1;
		}
		else {
			cout << "������Ч!";
			//cin.get();
			return -1;
		}
	}
	
	register bool isIllegal = 0;
	string s;
	cout << "����������:(���18λ)\n-->";
	s = getPassword();
	if (strcmp(card->cardPassword, s.c_str()) != 0) {
		cout << "�������,���Ժ�����!\n";
		return 1;
	}

	if (card->remainingMoney < currentRuleRating) {
		cout << "��ǰ���Ϊ:" << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "Ԫ.\n����,���ֵ����в���!\n";
		char c;
		cout << "�Ƿ���г�ֵ?(Y/N)\n-->";
		cin >> c;
		if (c == 'Y' || c == 'y') {
			userCharge(card);
		}
		else {
			cout << "����,�ϻ�����ȡ��!\n";
			LOG::localLogger(getUnixTime(), LOG_USERLOGIN, 0, 0, card->cardID);
			return -1;
		}
	}
	unsigned int stime = getUnixTime();
	addToOUList(card,stime);
	card->cStatus = 1;
	char* ct = getFormattedTime(stime);
	cout << "�ϻ��ɹ�!��ʼʱ��: ";
	cout << ct;
	delete[] ct;
	onlineCount++;
	maxOnlineCount = (onlineCount > maxOnlineCount) ? onlineCount : maxOnlineCount;
	LOG::localLogger(stime, LOG_USERLOGIN, 1, 0, card->cardID);
	cout << "\n�밴�س�������...";
	return 0;
}

int userLogout(Card* card, bool isManual = 1) {
	/*�жϴ����Card��ַ�Ƿ�Ϊ��*/
	if (card == NULL) {
		cout << "������Ч,���Ժ�����!\n";
		return -1;
	}
	/*�жϵ�ǰ��Ƭ�Ƿ���δ��ʹ��״̬�����������ϻ�״̬*/
	if (card->cStatus != 1 && isManual) {
		if (card->cStatus == 1) {
			cout << "��ǰ��Ƭ��������״̬,�����»�!\n";
			return -1;
		}
		else if (card->cStatus == 2) {
			cout << "�ÿ�Ƭ��ע��,��ֵ�󼴿ɻָ�����ʹ��!\n";
			return -1;
		}
		else if (card->cStatus == 3) {
			cout << "�ÿ�Ƭ�����쳣,����Ϲ������ؽ��е���!(�ʵ�~)\n";
			return -1;
		}
		else {
			cout << "������Ч!";
			return -1;
		}
	}
	/*���ÿ�Ƭ��Ӧ��OU�ڵ��OnlineUser������ɾ������ȡ��ʼ�ϻ���ʱ��*/
	unsigned int stime = getStartTimeAndRemoveFromOUList(card);
	/*�ж��Ƿ��������»���������ȡ��ʱ��*/
	if (stime == 0 && isManual) {
		cout << "�»�����,���Ժ�����!\n";
		card->cStatus = 0;
		return -1;
	}
	/*�»��󽫸ÿ�Ƭ״̬��Ϊ0(״̬����,δ�ϻ�)*/
	card->cStatus = 0;
	char c;
	/*��ȡ��ǰʱ��(�»�ʱ��)*/
	unsigned int loTime = getUnixTime();
	/*����õ��ϻ�ʱ�䳤��(��)*/
	unsigned int onlineLength = loTime - stime;
	/*���䰴����С��λ��Сʱ�ָ�*/
	unsigned int halfHourLength = onlineLength / 1800;
	/*������Сʱ���հ�Сʱ�Ʒ�*/
	halfHourLength += (onlineLength % 1800 == 0) ? 0 : 1;
	/*����õ������ϻ�����*/
	unsigned cMoney = currentRuleRating / 2 * halfHourLength;
	/*�û������ѽ������cMoney*/
	totalUserConsumeMoney += cMoney;
	/*��ǰ�����û���Ŀ��1*/
	onlineCount--;
	/*������(�ֶ�)�»��������,�жϿ�������Ƿ�����֧�������ϻ�����,��������ʾ�û����г�ֵ
	�û�����ֵ�򽫿�Ƭ״̬��Ϊ3(��Ƭ�����쳣)*/
	while (cMoney > card->remainingMoney && isManual) {
		cout << "�㿨������,���ȳ�ֵ���ٽ��н���!\n"
			<< "�Ƿ��ֵ?(Y/N)\n-->";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			userCharge(card);
			continue;
		}
		cout << "��ȷ�������г�ֵô?(Y/N)\n-->";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			cout << "����ҪΪ�˳е���������!\n";
			card->cStatus = 3;
			break;
		}
	}
	/*�������Զ��»��������, ��������, ���ÿ�Ƭ��Ϊ״̬4(�˳�ϵͳ�������ֵ)*/
	if (!isManual && cMoney > card->remainingMoney) {
		card->cStatus = 4;
	}
	/*�������ϻ����ѽ���ʣ�����м�ȥ,ʣ���������Ϊ0*/
	card->remainingMoney -= (card->cStatus == 3) ? card->remainingMoney : cMoney;
	/*�û������ѽ������*/
	card->totalConsumeMoney += cMoney;
	/*���ÿ�Ƭ���һ��ʹ��ʱ�����Ϊ�����»�ʱ��*/
	card->lastUsageTime = loTime;
	/*���ÿ�Ƭ��ʹ�ô�����1*/
	card->totalUsageTimes++;
	/*���ÿ�Ƭ���Ѽ�¼��Ŀ��1*/
	card->CCRcount++;
	/*��ʼ���ÿ�Ƭ�ṹ���Ա�е�currentCCRָ��ָ������Ѽ�¼�ṹ��*/
	initCCR(card->currentCCR);
	/*�򱾴����Ѽ�¼д���Ӧʱ��*/
	card->currentCCR->mTime = loTime;
	/*д���Ӧ�ϻ�ʱ��*/
	card->currentCCR->tLength = onlineLength;
	/*д���Ӧ�ϻ����ѽ��*/
	card->currentCCR->consumeMoney = cMoney;
	/*д����������Ϊ0(����)*/
	card->currentCCR->consumeType = 0;
	/*д������״̬:�ɹ�*/
	card->currentCCR->isSuccess = 1;
	/*ΪcurrentCCR��nextָ������ڴ�ռ�*/
	card->currentCCR->next = new CardConsume;
	/*���ÿ�Ƭ��Ӧ��currentCCRָ���ƶ�����һλ*/
	card->currentCCR = card->currentCCR->next;
	/*��CCRָ��ָ��Ľṹ���nextָ����Ϊ��*/
	card->currentCCR->next = NULL;
	/*����»�����Ϊ����(�ֶ�)�»�,���������Ϣ��ʾ,���Ϊ�����»�����,��������ʾ*/
	if (isManual) {
		/*��ȡloTime��ʽ�����ʱ���ַ���*/
		char* ct = getFormattedTime(loTime);
		cout << "�»��ɹ�,�»�ʱ��Ϊ: " << ct
			<< "\n�����ϻ�ʱ��Ϊ:" << onlineLength / 60 + 1 << "����.\n"
			<< "���ѽ��Ϊ: " << cMoney / 100 << '.' << cMoney % 100 << "Ԫ\n"
			<< "ʣ����Ϊ: " << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "Ԫ\n";
		/*��ʱ�����ڴ�ռ�,��ֹ�ڴ�й©*/
		delete[] ct;
		cout << "�밴�س�������...";
	}
	/*��¼�����»�������־*/
	LOG::localLogger(loTime, LOG_USERLOGOUT, 1, cMoney, card->cardID);
	return 0;
}

int userAllLogout() {
	OnlineUser* p = headOU;
	OnlineUser* q = headOU->next;
	while (q != NULL) {
		userLogout(p->card,0);
		p = q;
		q = q->next;
	}
	return 0;
}

Card* getCardByID(const char* cID) {
	/*�ж�ID�Ƿ��Ӧͷ�ڵ�*/
	if (!strcmp(headCard->cardID, cID)) {
		return headCard;
	}
	/*�ж�ͷ�ڵ��nextָ���Ƿ�ΪNULL*/
	else if (headCard->next == NULL) {
		return NULL;
	}
	/*�жϵڶ����ڵ��nextָ���Ƿ�Ϊ��*/
	else if (headCard->next->next == NULL) {
		return NULL;
	}
	Card* p = headCard->next;
	/*������ڶ����ڵ㿪ʼ�������ж�ID�Ƿ�ƥ��,
	*��ƥ���򷵻ض�Ӧ�ڵ��׵�ַ,������ɺ���ƥ�����򷵻�NULL*/
	while (p->next != NULL) {
		if (!strcmp(p->cardID, cID)) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

int addToOUList(Card* card,unsigned int stime) {
	if (card == NULL) {
		return -1;
	}
	if (card->cStatus != 0) {
		return -1;
	}
	currentOU->card = card;
	currentOU->sTime = stime;
	currentOU->next = new OnlineUser;
	currentOU = currentOU->next;
	currentOU->next = NULL;
	return 0;
}
/**/
unsigned int getStartTimeAndRemoveFromOUList(Card* card) {
	if (card == NULL) {
		return 0;
	}
	OnlineUser* q = NULL;
	unsigned int stime;
	/*�жϴ���Card��ַ�Ƿ�ΪOU����ͷ�ڵ��ַ*/
	if (card == headOU->card) {
		/*�����һ��,��pָ��ͷ�ڵ�*/
		q = headOU;
		/*��ȡ�ϻ�ʱ��*/
		stime = headOU->sTime;
		/*��ͷָ���ƶ�����next��Ա��Ӧ����һ���ڵ�*/
		headOU = headOU->next;
		/*�жϵ�ǰ�հ�OU�ڵ��Ƿ�Ϊͷ�ڵ�(���ж�OU�������Ƿ����ϻ��û�)*/
		currentOU = (currentOU == q) ? headOU : currentOU;
		/*�ͷ�ԭͷ�ڵ�ָ����ڴ�ռ�*/
		delete q;
		/*Ϊ�˰�ȫ,ʹ����ɺ�qָ����Ϊ��*/
		q = NULL;
		/*�ж�ɾ����head�Ƿ�ָ���*/
		if (headOU == NULL) {
			/*���ָ���,�����½����ڴ����
			*����currentOU��Ϊ��ͷָ��ָ��ͬһ����ַ*/
			headOU = new OnlineUser;
			currentOU = headOU;
			headOU->next = NULL;
		}
		/*�����û��ϻ���ʼʱ��*/
		return stime;
	}
	OnlineUser* p = headOU->next;
	q = headOU;
	/*��OU����ڶ����ڵ㿪ʼ�������жϴ����Card��ַ�����Ƿ���ƥ��*/
	while (p->next != NULL) {
		if (card == p->card) {
			/*��ƥ��,��ɾ����Ӧ�ڵ㲢��������OU����*/
			stime = p->sTime;
			q->next = q->next->next;
			delete p;
			return stime;
		}
		/*�ƶ�p��qָ��*/
		p = p->next;
		q = q->next;
	}
	/*δ�ҵ���ӦOU�ڵ㷵��0*/
	return 0;
}

void initCCR(CardConsume* ccr){
	ccr->mTime = 0;
	ccr->consumeMoney = 0;
	ccr->consumeType = 0;
	ccr->isSuccess = 0;
	ccr->tLength = 0;
}
