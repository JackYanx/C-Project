#include "FileMgrUtil.h"
#include "ToolUtils.h"
#include "InitVariable.h"
#include "CardMgr.h"
#include "RulesMgr.h"

int configFilesInit(unsigned int cutime) {
	std::fstream outFile[4];
	cardDataPath = createFileName(CARD_DATA_FILE_NAME, ".dat", cutime);
	rulesDataPath = createFileName(RULE_DATA_FILE_NAME, ".dat", cutime);
	toSataPath = createFileName(TO_STAT_FILE_NAME, ".dat", cutime);
	systemLogPath = createFileName(SYSTEMLOG_FILE_NAME, ".log", cutime);
	outFile[0].open(cardDataPath, std::ios_base::out);
	outFile[1].open(rulesDataPath, std::ios_base::out);
	outFile[2].open(toSataPath, std::ios_base::out);
	outFile[3].open(systemLogPath, std::ios_base::out);
	
	if (!outFile[0].is_open() || !outFile[1].is_open() || !outFile[2].is_open() || !outFile[3].is_open()) {
		std::cout << "系统数据文件写入失败!请检查磁盘是否有足够空间或者是否有权限写入文件!\n";
		return -1;
	}
	

	outFile[0] << "<CardData>\n";
	outFile[1] << "<RulesData>\n";
	outFile[2] << "<TurnOverStatistics>\n";
	outFile[3] << "<SystemLog>\n";

	outFile[0].close();
	outFile[1].close();
	outFile[2].close();
	outFile[3].close();
	return 0;
}

int configFilesSaveTail() {
	std::fstream outFile[1];
	outFile[0].open(systemLogPath, std::ios_base::app);
	if (!outFile[0].is_open()) {
		std::cout << "文件打开出错!\n";
	}
	outFile[0] << "</SystemLog>\n";
	outFile[0].close();
	return 0;
}

int importDataFromFile() {
	system("cls");
	std::cout << "请输入配置文件路径:\n";
	std::string dataPath;
	std::cin >> dataPath;
	char* folderPath = new char[MAX_FILE_FULLPATH];
	initCharArray(folderPath, 0, MAX_FILE_FULLPATH);
	while (listAllFilesInCurrentFolder(dataPath)) {
		system("cls");
		std::cout << "输入路径无效!\n";
		std::cout << "请输入配置文件路径:\n";
		std::cin >> dataPath;
	}
	strcat(folderPath,dataPath.c_str());
	if (*getLastCharOfString(dataPath) != '\\') {
		strcat(folderPath, "\\");
	}

	char* iCardDataPath = new char[MAX_FILE_FULLPATH];
	initCharArray(iCardDataPath, 0, MAX_FILE_FULLPATH);
	strcat(iCardDataPath, folderPath);
	char* iRulesDataPath = new char[MAX_FILE_FULLPATH];
	initCharArray(iRulesDataPath, 0, MAX_FILE_FULLPATH);
	strcat(iRulesDataPath, folderPath);
	char* iToSataPath = new char[MAX_FILE_FULLPATH];
	initCharArray(iToSataPath, 0, MAX_FILE_FULLPATH);
	strcat(iToSataPath, folderPath);

	std::string sCardDataFile;
	std::string sRulesDataFile;
	std::string sToSataFile;
	
	std::cout << "请输入卡片数据文件名:\n";
	std::cin >> sCardDataFile;
	strcat(iCardDataPath, sCardDataFile.c_str());
	std::cout << "请输入计费规则数据文件名:\n";
	std::cin >> sRulesDataFile;
	strcat(iRulesDataPath, sRulesDataFile.c_str());
	std::cout << "请输入统计信息数据文件名:\n";
	std::cin >> sToSataFile;
	strcat(iToSataPath, sToSataFile.c_str());
	
	std::ifstream inFile[3];
	inFile[0].open(iCardDataPath);
	inFile[1].open(iRulesDataPath);
	inFile[2].open(iToSataPath);

	if (!inFile[0].is_open() || !inFile[1].is_open() || !inFile[2].is_open()) {
		std::cout << "所选择的文件打开失败,请检查后重试!\n";
		return -1;
	}
	std::string fileHead[3];
	const char* sTag[3] = {"<CardData>\n","<RulesData>\n","<TurnOverStatistics>\n" };
	getline(inFile[0], fileHead[0]);
	getline(inFile[1], fileHead[1]);
	getline(inFile[2], fileHead[2]);
	bool isFileCorrect = true;
	if (!strcmp(fileHead[0].c_str(), sTag[0])) {
		std::cout << "卡片数据文件格式错误,请检查文件后重试!\n";
		isFileCorrect = 0;
	}
	if (!strcmp(fileHead[1].c_str(), sTag[1])) {
		std::cout << "计费规则数据文件格式错误,请检查文件后重试!\n";
		isFileCorrect = 0;
	}
	if (!strcmp(fileHead[2].c_str(), sTag[2])) {
		std::cout << "营业统计信息文件格式错误,请检查文件后重试!";
		isFileCorrect = 0;
	}
	if (!isFileCorrect) {
		inFile[0].close();
		inFile[1].close();
		inFile[2].close();
		delete[] folderPath;
		delete[] iCardDataPath;
		delete[] iRulesDataPath;
		delete[] iToSataPath;
		return -2;
	}

	/*解析并读取CardDataFile中的用户数据,将其存入Card链表中*/
	/*p.s.为了方便,只读取用户数据,不导入用户消费记录*/
	std::string s[3];
	Card* pCard;
	int ccrcount = 0;
	int fz;
	while (!inFile[0].eof() && inFile[0] >> s[0] && s[0] == "<Card>") {
		pCard = currentCard;
		initCard(pCard);
		inFile[0] >> pCard->createTime
			>> pCard->lastUsageTime
			>> pCard->logOutTime
			>> pCard->totalChargeMoney
			>> pCard->totalConsumeMoney
			>> pCard->remainingMoney
			>> pCard->totalUsageTimes
			>> pCard->cStatus
			>> pCard->CCRcount
			>> pCard->cardID
			>> pCard->cardPassword;
		ccrcount = 2 + pCard->CCRcount;
		for (fz = 0; fz < ccrcount;fz++) {
			inFile[0] >> s[1];
		}
		if (s[1] != "</CCR>") {
			std::cout << "ReadFileError!\n";
			return -3;
		}
		currentCard->next = new Card;
		currentCard = currentCard->next;
		currentCard->next = NULL;
		inFile[0] >> s[2];
		if (s[2] == "</Card>") {
			continue;
		}
		else {
			std::cout << "ReadFileError!\n";
			return -3;
		}
	}

	/*解析并读取RulesDataFile中的计费数据,将其存入Rule链表中*/
	/*p.s.为了方便,只读取最新的计费规则,不导入历史计费规则*/
	std::string ss[1];
	inFile[1] >> ss[0];
	while (!inFile[1].eof() && ss[0] != "<LatestRule>") {
		inFile[1] >> ss[0];
	}
	if (ss[0] != "<LatestRule>") {
		std::cout << "ReadRulesDataFileError!\n";
		return -5;
	}
	initRule(currentRule);
	inFile[1] >> currentRule->rating
		>> currentRule->startTime
		>> currentRule->rStatus;
	currentRuleRating = currentRule->rating;
	currentRule->next = new Rule;
	currentRule = currentRule->next;
	currentRule->next = NULL;


	/*解析并读取TurnOverStatisticsDataFile中的统计数据,将其存入基本信息的全局变量中*/
	std::string sss;
	inFile[2] >> sss;
	if (inFile[2].eof() && sss != "currentRuleRating") {
		std::cout << "ReadTurnOverStatisticsDataFileError!\n";
		return -6;
	}
	inFile[2] >> currentRuleRating
		>> sss >> onlineCount
		>> sss >> maxOnlineCount
		>> sss >> totalCount
		>> sss >> sss
		>> sss >> totalUserChargeMoney
		>> sss >> totalUserConsumeMoney;


	/*关闭文件并释放内存*/
	inFile[0].close();
	inFile[1].close();
	inFile[2].close();
	delete[] folderPath;
	delete[] iCardDataPath;
	delete[] iRulesDataPath;
	delete[] iToSataPath;
	return 0;
}

int exportDataToFile(bool isManual) {
	/*声明文件流对象数组*/
	std::fstream outFile[3];
	/*相关类xml结构标签*/
	const char* tag_s_card = "<Card>";
	const char* tag_e_card = "</Card>";
	const char* tag_s_ccr = "<CCR>";
	const char* tag_e_ccr = "</CCR>";
	const char* tag_s_latestrule = "<LatestRule>";
	const char* tag_e_latestrule = "</LatestRule>";
	const char* tag_s_historyrule = "<HistoryRule>";
	const char* tag_e_historyrule = "</HstoryRule>";
	/*空格数组*/
	const char* spaceKey[6] = { ""," ","  ","   ","    ","     " };
	/*声明常指针,用于指向文件名字符串*/
	const char* mCF = NULL;
	const char* mRF = NULL;
	const char* mSF = NULL;
	/*判断是否为手动导出数据文件*/
	if (isManual) {
		unsigned int cutime = getUnixTime();
		/*根据当前时间创建数据文件名称字符串*/
		mCF = createFileName(CARD_DATA_FILE_NAME, "_manual.dat", cutime);
		mRF = createFileName(RULE_DATA_FILE_NAME, "_manual.dat", cutime);
		mSF = createFileName(TO_STAT_FILE_NAME, "_manual.dat", cutime);
		/*打开文件,打开方式为追加*/
		outFile[0].open(mCF, std::ios_base::app);
		outFile[1].open(mRF, std::ios_base::app);
		outFile[2].open(mSF, std::ios_base::app);
		/*写入相关类xml标签*/
		outFile[0] << "<CardData>\n";
		outFile[1] << "<RulesData>\n";
		outFile[2] << "<TurnOverStatistics>\n";
	}
	else {
		/*如果为自动导出,目标文件为系统启动时自动创建的数据文件*/
		mCF = cardDataPath;
		mRF = rulesDataPath;
		mSF = toSataPath;
		outFile[0].open(mCF, std::ios_base::app);
		outFile[1].open(mRF, std::ios_base::app);
		outFile[2].open(mSF, std::ios_base::app);
	}
	/*准备Card链表和Rule链表头节点*/
	Card* pCard = headCard;
	Rule* pRule = headRule;
	CardConsume* pCCR = NULL;
	/*CardData部分数据处理*/
	/*使用循环,遍历Card链表的每一个节点*/
	while (pCard != currentCard) {
		/*向文件写入类xml标签数据和相关格式,以及每一个Card链表的各项数据*/
		outFile[0] << spaceKey[1] << tag_s_card << std::endl << spaceKey[2]
			<< pCard->createTime << ' '
			<< pCard->lastUsageTime << ' '
			<< pCard->logOutTime << ' '
			<< pCard->totalChargeMoney << ' '
			<< pCard->totalConsumeMoney << ' '
			<< pCard->remainingMoney << ' '
			<< pCard->totalUsageTimes << ' '
			<< pCard->cStatus << ' '
			<< pCard->CCRcount << ' '
			<< pCard->cardID << ' '
			<< pCard->cardPassword << std::endl
			<< spaceKey[2] << tag_s_ccr << std::endl;

		/*向文件写入当前Card链表节点对应的消费记录*/
		pCCR = pCard->headCCR;
		while (pCCR != pCard->currentCCR) {
			/*写入当前Card节点中CCR指针指向内存区域的各项数据*/
			outFile[0] << spaceKey[3]
				<< pCCR->mTime << ','
				<< pCCR->isSuccess << ','
				<< pCCR->consumeType << ','
				<< pCCR->tLength << ','
				<< pCCR->consumeMoney << ','
				<< std::endl;
			/*移动CCR指针到下一位*/
			pCCR = pCCR->next;
		}
		/*写入类xml尾标签,*/
		outFile[0] << spaceKey[2] << tag_e_ccr << std::endl << spaceKey[1] << tag_e_card << std::endl;
		/*移动Card指针到下一个节点*/
		pCard = pCard->next;
	}

	/*使用循环,遍历Rule链表的每一个节点*/
	while (pRule->next != currentRule) {
		/*向文件写入类xml标签数据和相关格式,以及每一个Rule链表的各项数据*/
		/*首先写入历次计费规则相关信息*/
		outFile[1] << spaceKey[1] << tag_s_historyrule << std::endl << spaceKey[2]
			<< pRule->rating << ' '
			<< pRule->startTime << ' '
			<< pRule->endTime << ' ' << std::endl
			<< spaceKey[1] << tag_e_historyrule << std::endl;
		/*移动指针到下一个Rule链表节点*/
		pRule = pRule->next;
	}
	/*写入当前计费规则信息*/
	outFile[1] << spaceKey[1] << tag_s_latestrule << std::endl << spaceKey[2]
		<< pRule->rating << ' '
		<< pRule->startTime << ' '
		<< '0' << std::endl
		<< spaceKey[1] << tag_e_latestrule << std::endl;

	/*向文件写入当前营业统计信息的各项数据*/
	outFile[2] << "currentRuleRating " << currentRuleRating << std::endl
		<< "onlineCount " << onlineCount << std::endl
		<< "maxOnlineCount " << maxOnlineCount << std::endl
		<< "totalCount " << totalCount << std::endl
		<< "initSystemTime " << initSystemTime << std::endl
		<< "totalUserChargeMoney " << totalUserChargeMoney << std::endl
		<< "totalUserConsumeMoney " << totalUserConsumeMoney << std::endl;

	/*写入文件末尾标签*/
	outFile[0] << "</CardData>\n";
	outFile[1] << "</RulesData>\n";
	outFile[2] << "</TurnOverStatistics>\n";
	/*关闭文件流*/
	outFile[0].close();
	outFile[1].close();
	outFile[2].close();
	/*如果为手动导出,则进行相关文件路径与结构的提示*/
	if (isManual) {
		std::cout << "卡片数据文件保存在:         " << mCF << std::endl
			<< "计费规则数据文件保存在:     " << mCF << std::endl
			<< "营业统计信息数据文件保存在: " << mCF << std::endl;
		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "手动导出后的数据文件仅供查看,无法再次导入,如需再次导入,请导入正常退出系统时自动导出的数据文件\n";

		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "卡片数据文件保存路径: " << mCF
			<< "\n文件格式说明\n"
			<< spaceKey[1] << tag_s_card << '\n' << spaceKey[2] << "办卡时间 最后一次使用时间 注销时间(未注销则为0) 总充值金额 总消费金额 卡中剩余金额 总使用次数 卡片当前状态 消费记录条数 卡片ID 密码\n"
			<< spaceKey[2] << tag_s_ccr << '\n'
			<< spaceKey[3] << "消费时间,是否成功,消费类型,上机时长(非上机则为0),消费金额\n"
			<< spaceKey[2] << tag_e_ccr << '\n'
			<< spaceKey[1] << tag_e_card << '\n';
		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "计费规则数据文件保存路径: " << mRF
			<< "\n文件格式说明\n"
			<< spaceKey[1] << tag_s_historyrule << '\n'
			<< spaceKey[2] << "历史规则费率 历史规则开始执行时间 历史规则停止执行时间\n"
			<< spaceKey[1] << tag_e_historyrule << '\n'
			<< spaceKey[1] << tag_s_latestrule << '\n'
			<< spaceKey[2] << "当前规则费率 当前规则开始执行时间 当前规则停止执行时间\n"
			<< spaceKey[1] << tag_e_latestrule << '\n';
		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "营业统计信息数据文件保存路径: " << mSF
			<< "\n文件格式说明\n"
			<< spaceKey[1] << "当前计费费率"
			<< spaceKey[1] << "当前在线人数"
			<< spaceKey[1] << "最高同时在线人数"
			<< spaceKey[1] << "系统启动时间"
			<< spaceKey[1] << "用户总充值金额"
			<< spaceKey[1] << "用户总消费金额\n"
			<< "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "请按回车键继续...";
		std::cin.get();
	}
	/*及时回收相关内存*/
	delete[] mCF;
	delete[] mRF;
	delete[] mSF;
	/*将指针置为空*/
	mCF = NULL;
	mRF = NULL;
	mSF = NULL;
	return 0;
}

int saveLogInfoToFile(SYSLOG* LogInfo) {
	/*声明日志记录文件流*/
	std::fstream logFile;
	/*使用日志记录结构体中的时间得到对应格式化后的时间字符串*/
	char* ct = getFormattedTime(LogInfo->mTime);
	/*打开文件*/
	logFile.open(systemLogPath,std::ios::app);
	/*依次向文件写入LogInfo结构体中的各项信息*/
	logFile << ct << ','
		<< std::hex << "0x" <<LogInfo->operationType << ','
		<< std::dec << LogInfo->isSuccess << ','
		<< std::setw(9) << LogInfo->money << ','
		<< std::setw(20) << LogInfo->cardID << std::endl;
	/*关闭文件流*/
	logFile.close();
	/*回收内存,防止内存溢出*/
	delete[] ct;
	return 0;
}

char *createFileName(const char* fn, const char* type, unsigned int cTime) {
	char *fileName = new char[MAX_FILE_FULLPATH];
	initCharArray(fileName, 0, MAX_FILE_FULLPATH);
	char timech[11] = { 0 };
	for (int i = 0; i < 10; i++) {
		timech[9 - i] = cTime % 10 + 48;
		cTime /= 10;
	}
	strcat(fileName, CONFIG_FILE_FOLDER_PATH);
	strcat(fileName, fn);
	strcat(fileName, timech);
	strcat(fileName, type);
	return fileName;
}

int listAllFilesInCurrentFolder(std::string& folderPath){
	/*声明文件句柄*/
	long mFile = 0;
	/*声明用于存储文件信息结构体*/
	struct _finddata_t fHandle;
	/*判断传入的字符串最后一位是否为'\\',不是则添加'\\',确保是文件夹路径*/
	if (*getLastCharOfString(folderPath) != '\\') {
		folderPath.append("\\");
	}
	/*改变当前工作目录为传入字符串所指目录*/
	_chdir(folderPath.c_str());
	/*使用相关函数,查找该目录下与"*.*"格式相匹配的文件,即所有文件,返回-1L表示查找失败*/
	if ((mFile = _findfirst("*.*", &fHandle)) == -1L) {
		std::cout << "该目录无文件或者没有权限访问!\n";
		exit(0);
		return 0x01;
	}
	std::cout << "目录包含文件如下:\n";
	printf("%s\n", fHandle.name);
	/*遍历该目录下的所有文件,并输出文件名*/
	while (_findnext(mFile, &fHandle) == 0) {
		printf("%s\n", fHandle.name);
	}
	/*关闭文件句柄*/
	if (_findclose(mFile)) {
		std::cout << "扫描目录时出错,请稍后重试!\n";
		exit(0);
		return 0;
	}
	return 0;
}