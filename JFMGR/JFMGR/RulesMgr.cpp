#include "RulesMgr.h"
#include "initVariable.h"
#include "SystemLogger.h"

using namespace std;

int createNewRules(bool isFirst = 0) {
	cout<<"创建计费规则:\n请输入计费标准(元/小时):";
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
	cout << "请按回车键继续...";
	return 0;
}

int queryRules() {
	Rule* p = getLatestRule();
	char* fmtTimeStr = getFormattedTime(p->startTime);
	cout << "当前计费规则为:\n"
		<< p->rating/100 << "元/小时\n"
		<< "规则开始使用时间:" << fmtTimeStr<<endl;
	delete[] fmtTimeStr;
	cout<< "-----------------------------------------------------------------------------------\n";
	if(headRule->next->next == NULL){
		cout<<"无更多记录!\n";
		cout << "请按回车键继续...";
		cin.get();
		return 0;
	}
	cout<<"以下为历史计费规则:\n";
	int i = 1;
	p = headRule;
	char* rStartTime = NULL;
	char* rEndTime = NULL;
	while(p->next->next != NULL){
		rStartTime = getFormattedTime(p->startTime);
		rEndTime = getFormattedTime(p->endTime);
		cout<<"第"<<i<<"条:\n"
			<<"费率:"<<p->rating / 100<<endl
			<<"开始使用时间:"<<rStartTime<<endl
			<<"结束使用时间:"<<rEndTime<<endl;
		delete[] rStartTime;
		delete[] rEndTime;
		p = p->next;
		i++;
	}
	cout << "请按回车键继续...";
	cin.get();
	return 0;
}

int changeRules() {
	Rule* p = getLatestRule();
	char* fmtTimeStr = getFormattedTime(p->startTime);
	cout << "当前计费规则为:\n"
		<< p->rating/100 << "元/小时"
		<< "规则开始使用时间:" << fmtTimeStr<<endl;
	delete[] fmtTimeStr;
	cout<<"是否确定要变更当前记录?(Y/N)\n-->";
	char c;
	cin>>c;
	if(c != 'y' && c != 'Y'){
		cout<<"操作取消!\n";
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