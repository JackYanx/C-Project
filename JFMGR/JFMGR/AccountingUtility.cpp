#include "AccountingUtility.h"
#include "SystemLogger.h"
#include "initVariable.h"
#include "ToolUtils.h"

using namespace std;

Card* card;

/*以下四个方法只限AccountingUtility模块使用*/
/*创建新的OnlineUser节点,卡片指针和时间为参数*/
int addToOUList(Card*, unsigned int);

/*从OnlieUser列表中剔除对应的具有Card指针的OU节点*/
unsigned int removeFromOUList(Card*);

/*初始化卡片消费记录结构体*/
void initCCR(CardConsume*);

/*获取开始上机时间并从OU列表中删除具有该card指针对应的节点*/
unsigned int getStartTimeAndRemoveFromOUList(Card*);

int accImpl(int status) {
	string s;
	/*isIllegal存储输入是否合法*/
	register bool isIllegal = 0;

	/*输入卡号操作*/
	do {
		card = NULL;
		cout << "请输入卡号:(最大18位)\n-->";
		cin >> s;
		if (s.length()>19) {
			cout << "输入长度超出限制，请重试！\n";
			isIllegal = 1;
			continue;
		}
		card = getCardByID(s.c_str());
		if (card == NULL) {
			cout << "输入的卡号不存在,请重新输入:\n-->";
			isIllegal = 1;
			continue;
		}
		isIllegal = 0;
	} while (isIllegal);
	if (card->cStatus == 4) {
		cout << "上次系统退出进行结算时您的余额不足,请充值!\n";
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
		cout << "操作无效,请稍后重试!\n-->";
		//cin.get();
		return -1;
	}
	if (card->cStatus == 3) {
		cout << "卡片异常,请配合公安机关的调查!(滑稽~)\n-->";
		//cin.get();
	}
	if (card->cStatus == 2) {
		cout << "该卡片已注销,是否充值以重新启用卡片?(Y/N)\n-->";
		char c;
		cin >> c;
		if (c == 'Y' || c == 'y') {
			card->cStatus = 0;
		}
		else {
			cout << "操作取消!";
			//cin.get();
			return -1;
		}
	}
	cout<<"请输入充值金额:(单位:元)\n-->";
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
	cout << "充值成功!金额为:" << money / 100 << '.' << money % 100 << "元\n";
	LOG::localLogger(card->lastUsageTime, LOG_USERCHARGE, 1, money, card->cardID);
	cout << "请按回车键继续...";
	return 0;
}

int userRefund(Card* card) {
	if (card == NULL) {
		cout << "操作无效,请稍后重试!\n";
		//cin.get();
		return -1;
	}
	if (card->cStatus != 0) {
		if (card->cStatus == 1) {
			cout << "当前卡片处于上机状态,正在下机结算...\n";
			userLogout(card,1);
		}
		else if(card->cStatus == 2){
			cout << "该卡片已注销!\n";
			//cin.get();
			return -1;
		}
		else if (card->cStatus == 3) {
			cout << "该卡片数据异常,请配合公安机关进行调查!(彩蛋~)\n";
			//cin.get();
			return -1;
		}
		else {
			cout << "操作无效!\n";
			//cin.get();
			return -1;
		}
	}
	cout << "当前卡中剩余金额为: " << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "元.\n";
	cout << "您确实要注销该卡片吗?(Y/N)\n-->";
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
		cout << "退款金额为: " << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "元.\n";
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
		cout << "请按回车键继续...";
		return 0;
	}
	else {
		cout << "操作取消!";
		LOG::localLogger(getUnixTime(), LOG_USERREFUND, 0, 0, card->cardID);
		return -1;
	}
	return 0;
}

int userLogin(Card* card) {
	if (card == NULL) {
		cout << "操作无效,请稍后重试!\n";
		//cin.get();
		return -1;
	}
	if (card->cStatus != 0) {
		if (card->cStatus == 1) {
			cout << "当前卡片处于上机状态,您可以直接使用!\n";
			//cin.get();
			return -1;
		}
		else if (card->cStatus == 2) {
			cout << "该卡片已注销,充值后即可恢复正常使用!\n";
			//cin.get();
			return -1;
		}
		else if (card->cStatus == 3) {
			cout << "该卡片数据异常,请配合公安机关进行调查!(彩蛋~)\n";
			//cin.get();
			return -1;
		}
		else {
			cout << "操作无效!";
			//cin.get();
			return -1;
		}
	}
	
	register bool isIllegal = 0;
	string s;
	cout << "请输入密码:(最大18位)\n-->";
	s = getPassword();
	if (strcmp(card->cardPassword, s.c_str()) != 0) {
		cout << "密码错误,请稍后重试!\n";
		return 1;
	}

	if (card->remainingMoney < currentRuleRating) {
		cout << "当前余额为:" << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "元.\n余额不足,请充值后进行操作!\n";
		char c;
		cout << "是否进行充值?(Y/N)\n-->";
		cin >> c;
		if (c == 'Y' || c == 'y') {
			userCharge(card);
		}
		else {
			cout << "金额不足,上机操作取消!\n";
			LOG::localLogger(getUnixTime(), LOG_USERLOGIN, 0, 0, card->cardID);
			return -1;
		}
	}
	unsigned int stime = getUnixTime();
	addToOUList(card,stime);
	card->cStatus = 1;
	char* ct = getFormattedTime(stime);
	cout << "上机成功!开始时间: ";
	cout << ct;
	delete[] ct;
	onlineCount++;
	maxOnlineCount = (onlineCount > maxOnlineCount) ? onlineCount : maxOnlineCount;
	LOG::localLogger(stime, LOG_USERLOGIN, 1, 0, card->cardID);
	cout << "\n请按回车键继续...";
	return 0;
}

int userLogout(Card* card, bool isManual = 1) {
	/*判断传入的Card地址是否为空*/
	if (card == NULL) {
		cout << "操作无效,请稍后重试!\n";
		return -1;
	}
	/*判断当前卡片是否处于未在使用状态或者其他非上机状态*/
	if (card->cStatus != 1 && isManual) {
		if (card->cStatus == 1) {
			cout << "当前卡片处于离线状态,无需下机!\n";
			return -1;
		}
		else if (card->cStatus == 2) {
			cout << "该卡片已注销,充值后即可恢复正常使用!\n";
			return -1;
		}
		else if (card->cStatus == 3) {
			cout << "该卡片数据异常,请配合公安机关进行调查!(彩蛋~)\n";
			return -1;
		}
		else {
			cout << "操作无效!";
			return -1;
		}
	}
	/*将该卡片对应的OU节点从OnlineUser链表中删除并获取开始上机的时间*/
	unsigned int stime = getStartTimeAndRemoveFromOUList(card);
	/*判断是否能正常下机并正常获取到时间*/
	if (stime == 0 && isManual) {
		cout << "下机出错,请稍后重试!\n";
		card->cStatus = 0;
		return -1;
	}
	/*下机后将该卡片状态置为0(状态正常,未上机)*/
	card->cStatus = 0;
	char c;
	/*获取当前时间(下机时间)*/
	unsigned int loTime = getUnixTime();
	/*计算得到上机时间长度(秒)*/
	unsigned int onlineLength = loTime - stime;
	/*将其按照最小单位半小时分割*/
	unsigned int halfHourLength = onlineLength / 1800;
	/*不满半小时按照半小时计费*/
	halfHourLength += (onlineLength % 1800 == 0) ? 0 : 1;
	/*计算得到本次上机费用*/
	unsigned cMoney = currentRuleRating / 2 * halfHourLength;
	/*用户总消费金额增加cMoney*/
	totalUserConsumeMoney += cMoney;
	/*当前在线用户数目减1*/
	onlineCount--;
	/*在正常(手动)下机的情况下,判断卡中余额是否足以支付本次上机费用,不足则提示用户进行充值
	用户不充值则将卡片状态置为3(卡片数据异常)*/
	while (cMoney > card->remainingMoney && isManual) {
		cout << "你卡中余额不足,请先充值后再进行结算!\n"
			<< "是否充值?(Y/N)\n-->";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			userCharge(card);
			continue;
		}
		cout << "您确定不进行充值么?(Y/N)\n-->";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			cout << "您需要为此承担法律责任!\n";
			card->cStatus = 3;
			break;
		}
	}
	/*在批量自动下机的情况下, 忽略余额不足, 将该卡片置为状态4(退出系统余额不足待充值)*/
	if (!isManual && cMoney > card->remainingMoney) {
		card->cStatus = 4;
	}
	/*将本次上机消费金额从剩余金额中减去,剩余金额不足则置为0*/
	card->remainingMoney -= (card->cStatus == 3) ? card->remainingMoney : cMoney;
	/*用户总消费金额增加*/
	card->totalConsumeMoney += cMoney;
	/*将该卡片最后一次使用时间更新为本次下机时间*/
	card->lastUsageTime = loTime;
	/*将该卡片总使用次数加1*/
	card->totalUsageTimes++;
	/*将该卡片消费记录数目加1*/
	card->CCRcount++;
	/*初始化该卡片结构体成员中的currentCCR指针指向的消费记录结构体*/
	initCCR(card->currentCCR);
	/*向本次消费记录写入对应时间*/
	card->currentCCR->mTime = loTime;
	/*写入对应上机时长*/
	card->currentCCR->tLength = onlineLength;
	/*写入对应上机消费金额*/
	card->currentCCR->consumeMoney = cMoney;
	/*写入消费类型为0(花费)*/
	card->currentCCR->consumeType = 0;
	/*写入消费状态:成功*/
	card->currentCCR->isSuccess = 1;
	/*为currentCCR的next指针分配内存空间*/
	card->currentCCR->next = new CardConsume;
	/*将该卡片对应的currentCCR指针移动到下一位*/
	card->currentCCR = card->currentCCR->next;
	/*将CCR指针指向的结构体额next指针置为空*/
	card->currentCCR->next = NULL;
	/*如果下机操作为正常(手动)下机,进行相关信息提示,如果为批量下机操作,不进行提示*/
	if (isManual) {
		/*获取loTime格式化后的时间字符串*/
		char* ct = getFormattedTime(loTime);
		cout << "下机成功,下机时间为: " << ct
			<< "\n本次上机时长为:" << onlineLength / 60 + 1 << "分钟.\n"
			<< "消费金额为: " << cMoney / 100 << '.' << cMoney % 100 << "元\n"
			<< "剩余金额为: " << card->remainingMoney / 100 << '.' << card->remainingMoney % 100 << "元\n";
		/*及时回收内存空间,防止内存泄漏*/
		delete[] ct;
		cout << "请按回车键继续...";
	}
	/*记录本次下机操作日志*/
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
	/*判断ID是否对应头节点*/
	if (!strcmp(headCard->cardID, cID)) {
		return headCard;
	}
	/*判断头节点的next指针是否为NULL*/
	else if (headCard->next == NULL) {
		return NULL;
	}
	/*判断第二个节点的next指针是否为空*/
	else if (headCard->next->next == NULL) {
		return NULL;
	}
	Card* p = headCard->next;
	/*从链表第二个节点开始遍历并判断ID是否匹配,
	*若匹配则返回对应节点首地址,遍历完成后无匹配结果则返回NULL*/
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
	/*判断传入Card地址是否为OU链表头节点地址*/
	if (card == headOU->card) {
		/*如果相一致,将p指向头节点*/
		q = headOU;
		/*获取上机时间*/
		stime = headOU->sTime;
		/*将头指针移动到其next成员对应的下一个节点*/
		headOU = headOU->next;
		/*判断当前空白OU节点是否为头节点(即判断OU链表中是否无上机用户)*/
		currentOU = (currentOU == q) ? headOU : currentOU;
		/*释放原头节点指向的内存空间*/
		delete q;
		/*为了安全,使用完成后将q指针置为空*/
		q = NULL;
		/*判断删除后head是否指向空*/
		if (headOU == NULL) {
			/*如果指向空,则重新进行内存分配
			*并将currentOU置为与头指针指向同一个地址*/
			headOU = new OnlineUser;
			currentOU = headOU;
			headOU->next = NULL;
		}
		/*返回用户上机开始时间*/
		return stime;
	}
	OnlineUser* p = headOU->next;
	q = headOU;
	/*从OU链表第二个节点开始遍历并判断传入的Card地址与其是否相匹配*/
	while (p->next != NULL) {
		if (card == p->card) {
			/*若匹配,则删除对应节点并重新连接OU链表*/
			stime = p->sTime;
			q->next = q->next->next;
			delete p;
			return stime;
		}
		/*移动p和q指针*/
		p = p->next;
		q = q->next;
	}
	/*未找到对应OU节点返回0*/
	return 0;
}

void initCCR(CardConsume* ccr){
	ccr->mTime = 0;
	ccr->consumeMoney = 0;
	ccr->consumeType = 0;
	ccr->isSuccess = 0;
	ccr->tLength = 0;
}
