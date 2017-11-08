#include "RulesMgr.h"
#include "initVariable.h"
#include "SystemLogger.h"

using namespace std;

int createNewRules(bool isFirst = 0) {
	cout<<"�����Ʒѹ���:\n������Ʒѱ�׼(Ԫ/Сʱ):";
	unsigned int moneyPerHour = 0;
	unsigned int sTime = getUnixTime();
	cin>>moneyPerHour;
	moneyPerHour *= 100;
	currentRuleRating = moneyPerHour;
	initRule(currentRule);
	currentRule->startTime = sTime;
	currentRule->rating = moneyPerHour;
	currentRule->rStatus = 1;
	currentRule->next = new Rule;
	currentRule = currentRule->next;
	currentRule->next = NULL;
	if (isFirst) {
		LOG::localLogger(sTime, LOG_CREATENEWRULES, 1, 0, NULL);
	}
	else {
		LOG::localLogger(sTime, LOG_CHANGERULES, 1, 0, NULL);
	}
	cout << "�밴�س�������...";
	return 0;
}

int queryRules() {
	Rule* p = getLatestRule();
	char* fmtTimeStr = getFormattedTime(p->startTime);
	cout << "��ǰ�Ʒѹ���Ϊ:\n"
		<< p->rating/100 << "Ԫ/Сʱ\n"
		<< "����ʼʹ��ʱ��:" << fmtTimeStr<<endl;
	delete[] fmtTimeStr;
	cout<< "-----------------------------------------------------------------------------------\n";
	if(headRule->next->next == NULL){
		cout<<"�޸����¼!\n";
		cout << "�밴�س�������...";
		cin.get();
		return 0;
	}
	cout<<"����Ϊ��ʷ�Ʒѹ���:\n";
	int i = 1;
	p = headRule;
	char* rStartTime = NULL;
	char* rEndTime = NULL;
	while(p->next->next != NULL){
		rStartTime = getFormattedTime(p->startTime);
		rEndTime = getFormattedTime(p->endTime);
		cout<<"��"<<i<<"��:\n"
			<<"����:"<<p->rating / 100<<endl
			<<"��ʼʹ��ʱ��:"<<rStartTime<<endl
			<<"����ʹ��ʱ��:"<<rEndTime<<endl;
		delete[] rStartTime;
		delete[] rEndTime;
		p = p->next;
		i++;
	}
	cout << "�밴�س�������...";
	cin.get();
	return 0;
}

int changeRules() {
	Rule* p = getLatestRule();
	char* fmtTimeStr = getFormattedTime(p->startTime);
	cout << "��ǰ�Ʒѹ���Ϊ:\n"
		<< p->rating/100 << "Ԫ/Сʱ"
		<< "����ʼʹ��ʱ��:" << fmtTimeStr<<endl;
	delete[] fmtTimeStr;
	cout<<"�Ƿ�ȷ��Ҫ�����ǰ��¼?(Y/N)\n-->";
	char c;
	cin>>c;
	if(c != 'y' && c != 'Y'){
		cout<<"����ȡ��!\n";
		LOG::localLogger(getUnixTime(), LOG_CHANGERULES, 0, 0, NULL);
		return 0;
	}
	getLatestRule()->endTime = getUnixTime();
	createNewRules(0);
	return 0;
}

void initRule(Rule* rule){
	rule->startTime = 0;
	rule->endTime = 0;
	rule->rStatus = 0;
	rule->rating = 0;
}

Rule* getLatestRule(){
	if(currentRule == headRule){
		return headRule;
	}
	Rule* p = headRule;
	while(p->next->next != NULL){
		p = p->next;
	}
	return p;
}

int getLatestRating(){
	Rule* p = getLatestRule();
	return p->rating;
}