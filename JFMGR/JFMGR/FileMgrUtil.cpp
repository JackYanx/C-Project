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
		std::cout << "ϵͳ�����ļ�д��ʧ��!��������Ƿ����㹻�ռ�����Ƿ���Ȩ��д���ļ�!\n";
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
		std::cout << "�ļ��򿪳���!\n";
	}
	outFile[0] << "</SystemLog>\n";
	outFile[0].close();
	return 0;
}

int importDataFromFile() {
	system("cls");
	std::cout << "�����������ļ�·��:\n";
	std::string dataPath;
	std::cin >> dataPath;
	char* folderPath = new char[MAX_FILE_FULLPATH];
	initCharArray(folderPath, 0, MAX_FILE_FULLPATH);
	while (listAllFilesInCurrentFolder(dataPath)) {
		system("cls");
		std::cout << "����·����Ч!\n";
		std::cout << "�����������ļ�·��:\n";
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
	
	std::cout << "�����뿨Ƭ�����ļ���:\n";
	std::cin >> sCardDataFile;
	strcat(iCardDataPath, sCardDataFile.c_str());
	std::cout << "������Ʒѹ��������ļ���:\n";
	std::cin >> sRulesDataFile;
	strcat(iRulesDataPath, sRulesDataFile.c_str());
	std::cout << "������ͳ����Ϣ�����ļ���:\n";
	std::cin >> sToSataFile;
	strcat(iToSataPath, sToSataFile.c_str());
	
	std::ifstream inFile[3];
	inFile[0].open(iCardDataPath);
	inFile[1].open(iRulesDataPath);
	inFile[2].open(iToSataPath);

	if (!inFile[0].is_open() || !inFile[1].is_open() || !inFile[2].is_open()) {
		std::cout << "��ѡ����ļ���ʧ��,���������!\n";
		return -1;
	}
	std::string fileHead[3];
	const char* sTag[3] = {"<CardData>\n","<RulesData>\n","<TurnOverStatistics>\n" };
	getline(inFile[0], fileHead[0]);
	getline(inFile[1], fileHead[1]);
	getline(inFile[2], fileHead[2]);
	bool isFileCorrect = true;
	if (!strcmp(fileHead[0].c_str(), sTag[0])) {
		std::cout << "��Ƭ�����ļ���ʽ����,�����ļ�������!\n";
		isFileCorrect = 0;
	}
	if (!strcmp(fileHead[1].c_str(), sTag[1])) {
		std::cout << "�Ʒѹ��������ļ���ʽ����,�����ļ�������!\n";
		isFileCorrect = 0;
	}
	if (!strcmp(fileHead[2].c_str(), sTag[2])) {
		std::cout << "Ӫҵͳ����Ϣ�ļ���ʽ����,�����ļ�������!";
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

	/*��������ȡCardDataFile�е��û�����,�������Card������*/
	/*p.s.Ϊ�˷���,ֻ��ȡ�û�����,�������û����Ѽ�¼*/
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

	/*��������ȡRulesDataFile�еļƷ�����,�������Rule������*/
	/*p.s.Ϊ�˷���,ֻ��ȡ���µļƷѹ���,��������ʷ�Ʒѹ���*/
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


	/*��������ȡTurnOverStatisticsDataFile�е�ͳ������,������������Ϣ��ȫ�ֱ�����*/
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


	/*�ر��ļ����ͷ��ڴ�*/
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
	/*�����ļ�����������*/
	std::fstream outFile[3];
	/*�����xml�ṹ��ǩ*/
	const char* tag_s_card = "<Card>";
	const char* tag_e_card = "</Card>";
	const char* tag_s_ccr = "<CCR>";
	const char* tag_e_ccr = "</CCR>";
	const char* tag_s_latestrule = "<LatestRule>";
	const char* tag_e_latestrule = "</LatestRule>";
	const char* tag_s_historyrule = "<HistoryRule>";
	const char* tag_e_historyrule = "</HstoryRule>";
	/*�ո�����*/
	const char* spaceKey[6] = { ""," ","  ","   ","    ","     " };
	/*������ָ��,����ָ���ļ����ַ���*/
	const char* mCF = NULL;
	const char* mRF = NULL;
	const char* mSF = NULL;
	/*�ж��Ƿ�Ϊ�ֶ����������ļ�*/
	if (isManual) {
		unsigned int cutime = getUnixTime();
		/*���ݵ�ǰʱ�䴴�������ļ������ַ���*/
		mCF = createFileName(CARD_DATA_FILE_NAME, "_manual.dat", cutime);
		mRF = createFileName(RULE_DATA_FILE_NAME, "_manual.dat", cutime);
		mSF = createFileName(TO_STAT_FILE_NAME, "_manual.dat", cutime);
		/*���ļ�,�򿪷�ʽΪ׷��*/
		outFile[0].open(mCF, std::ios_base::app);
		outFile[1].open(mRF, std::ios_base::app);
		outFile[2].open(mSF, std::ios_base::app);
		/*д�������xml��ǩ*/
		outFile[0] << "<CardData>\n";
		outFile[1] << "<RulesData>\n";
		outFile[2] << "<TurnOverStatistics>\n";
	}
	else {
		/*���Ϊ�Զ�����,Ŀ���ļ�Ϊϵͳ����ʱ�Զ������������ļ�*/
		mCF = cardDataPath;
		mRF = rulesDataPath;
		mSF = toSataPath;
		outFile[0].open(mCF, std::ios_base::app);
		outFile[1].open(mRF, std::ios_base::app);
		outFile[2].open(mSF, std::ios_base::app);
	}
	/*׼��Card�����Rule����ͷ�ڵ�*/
	Card* pCard = headCard;
	Rule* pRule = headRule;
	CardConsume* pCCR = NULL;
	/*CardData�������ݴ���*/
	/*ʹ��ѭ��,����Card�����ÿһ���ڵ�*/
	while (pCard != currentCard) {
		/*���ļ�д����xml��ǩ���ݺ���ظ�ʽ,�Լ�ÿһ��Card����ĸ�������*/
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

		/*���ļ�д�뵱ǰCard����ڵ��Ӧ�����Ѽ�¼*/
		pCCR = pCard->headCCR;
		while (pCCR != pCard->currentCCR) {
			/*д�뵱ǰCard�ڵ���CCRָ��ָ���ڴ�����ĸ�������*/
			outFile[0] << spaceKey[3]
				<< pCCR->mTime << ','
				<< pCCR->isSuccess << ','
				<< pCCR->consumeType << ','
				<< pCCR->tLength << ','
				<< pCCR->consumeMoney << ','
				<< std::endl;
			/*�ƶ�CCRָ�뵽��һλ*/
			pCCR = pCCR->next;
		}
		/*д����xmlβ��ǩ,*/
		outFile[0] << spaceKey[2] << tag_e_ccr << std::endl << spaceKey[1] << tag_e_card << std::endl;
		/*�ƶ�Cardָ�뵽��һ���ڵ�*/
		pCard = pCard->next;
	}

	/*ʹ��ѭ��,����Rule�����ÿһ���ڵ�*/
	while (pRule->next != currentRule) {
		/*���ļ�д����xml��ǩ���ݺ���ظ�ʽ,�Լ�ÿһ��Rule����ĸ�������*/
		/*����д�����μƷѹ��������Ϣ*/
		outFile[1] << spaceKey[1] << tag_s_historyrule << std::endl << spaceKey[2]
			<< pRule->rating << ' '
			<< pRule->startTime << ' '
			<< pRule->endTime << ' ' << std::endl
			<< spaceKey[1] << tag_e_historyrule << std::endl;
		/*�ƶ�ָ�뵽��һ��Rule����ڵ�*/
		pRule = pRule->next;
	}
	/*д�뵱ǰ�Ʒѹ�����Ϣ*/
	outFile[1] << spaceKey[1] << tag_s_latestrule << std::endl << spaceKey[2]
		<< pRule->rating << ' '
		<< pRule->startTime << ' '
		<< '0' << std::endl
		<< spaceKey[1] << tag_e_latestrule << std::endl;

	/*���ļ�д�뵱ǰӪҵͳ����Ϣ�ĸ�������*/
	outFile[2] << "currentRuleRating " << currentRuleRating << std::endl
		<< "onlineCount " << onlineCount << std::endl
		<< "maxOnlineCount " << maxOnlineCount << std::endl
		<< "totalCount " << totalCount << std::endl
		<< "initSystemTime " << initSystemTime << std::endl
		<< "totalUserChargeMoney " << totalUserChargeMoney << std::endl
		<< "totalUserConsumeMoney " << totalUserConsumeMoney << std::endl;

	/*д���ļ�ĩβ��ǩ*/
	outFile[0] << "</CardData>\n";
	outFile[1] << "</RulesData>\n";
	outFile[2] << "</TurnOverStatistics>\n";
	/*�ر��ļ���*/
	outFile[0].close();
	outFile[1].close();
	outFile[2].close();
	/*���Ϊ�ֶ�����,���������ļ�·����ṹ����ʾ*/
	if (isManual) {
		std::cout << "��Ƭ�����ļ�������:         " << mCF << std::endl
			<< "�Ʒѹ��������ļ�������:     " << mCF << std::endl
			<< "Ӫҵͳ����Ϣ�����ļ�������: " << mCF << std::endl;
		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "�ֶ�������������ļ������鿴,�޷��ٴε���,�����ٴε���,�뵼�������˳�ϵͳʱ�Զ������������ļ�\n";

		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "��Ƭ�����ļ�����·��: " << mCF
			<< "\n�ļ���ʽ˵��\n"
			<< spaceKey[1] << tag_s_card << '\n' << spaceKey[2] << "�쿨ʱ�� ���һ��ʹ��ʱ�� ע��ʱ��(δע����Ϊ0) �ܳ�ֵ��� �����ѽ�� ����ʣ���� ��ʹ�ô��� ��Ƭ��ǰ״̬ ���Ѽ�¼���� ��ƬID ����\n"
			<< spaceKey[2] << tag_s_ccr << '\n'
			<< spaceKey[3] << "����ʱ��,�Ƿ�ɹ�,��������,�ϻ�ʱ��(���ϻ���Ϊ0),���ѽ��\n"
			<< spaceKey[2] << tag_e_ccr << '\n'
			<< spaceKey[1] << tag_e_card << '\n';
		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "�Ʒѹ��������ļ�����·��: " << mRF
			<< "\n�ļ���ʽ˵��\n"
			<< spaceKey[1] << tag_s_historyrule << '\n'
			<< spaceKey[2] << "��ʷ������� ��ʷ����ʼִ��ʱ�� ��ʷ����ִֹͣ��ʱ��\n"
			<< spaceKey[1] << tag_e_historyrule << '\n'
			<< spaceKey[1] << tag_s_latestrule << '\n'
			<< spaceKey[2] << "��ǰ������� ��ǰ����ʼִ��ʱ�� ��ǰ����ִֹͣ��ʱ��\n"
			<< spaceKey[1] << tag_e_latestrule << '\n';
		std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "Ӫҵͳ����Ϣ�����ļ�����·��: " << mSF
			<< "\n�ļ���ʽ˵��\n"
			<< spaceKey[1] << "��ǰ�Ʒѷ���"
			<< spaceKey[1] << "��ǰ��������"
			<< spaceKey[1] << "���ͬʱ��������"
			<< spaceKey[1] << "ϵͳ����ʱ��"
			<< spaceKey[1] << "�û��ܳ�ֵ���"
			<< spaceKey[1] << "�û������ѽ��\n"
			<< "\n-------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "�밴�س�������...";
		std::cin.get();
	}
	/*��ʱ��������ڴ�*/
	delete[] mCF;
	delete[] mRF;
	delete[] mSF;
	/*��ָ����Ϊ��*/
	mCF = NULL;
	mRF = NULL;
	mSF = NULL;
	return 0;
}

int saveLogInfoToFile(SYSLOG* LogInfo) {
	/*������־��¼�ļ���*/
	std::fstream logFile;
	/*ʹ����־��¼�ṹ���е�ʱ��õ���Ӧ��ʽ�����ʱ���ַ���*/
	char* ct = getFormattedTime(LogInfo->mTime);
	/*���ļ�*/
	logFile.open(systemLogPath,std::ios::app);
	/*�������ļ�д��LogInfo�ṹ���еĸ�����Ϣ*/
	logFile << ct << ','
		<< std::hex << "0x" <<LogInfo->operationType << ','
		<< std::dec << LogInfo->isSuccess << ','
		<< std::setw(9) << LogInfo->money << ','
		<< std::setw(20) << LogInfo->cardID << std::endl;
	/*�ر��ļ���*/
	logFile.close();
	/*�����ڴ�,��ֹ�ڴ����*/
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
	/*�����ļ����*/
	long mFile = 0;
	/*�������ڴ洢�ļ���Ϣ�ṹ��*/
	struct _finddata_t fHandle;
	/*�жϴ�����ַ������һλ�Ƿ�Ϊ'\\',���������'\\',ȷ�����ļ���·��*/
	if (*getLastCharOfString(folderPath) != '\\') {
		folderPath.append("\\");
	}
	/*�ı䵱ǰ����Ŀ¼Ϊ�����ַ�����ָĿ¼*/
	_chdir(folderPath.c_str());
	/*ʹ����غ���,���Ҹ�Ŀ¼����"*.*"��ʽ��ƥ����ļ�,�������ļ�,����-1L��ʾ����ʧ��*/
	if ((mFile = _findfirst("*.*", &fHandle)) == -1L) {
		std::cout << "��Ŀ¼���ļ�����û��Ȩ�޷���!\n";
		exit(0);
		return 0x01;
	}
	std::cout << "Ŀ¼�����ļ�����:\n";
	printf("%s\n", fHandle.name);
	/*������Ŀ¼�µ������ļ�,������ļ���*/
	while (_findnext(mFile, &fHandle) == 0) {
		printf("%s\n", fHandle.name);
	}
	/*�ر��ļ����*/
	if (_findclose(mFile)) {
		std::cout << "ɨ��Ŀ¼ʱ����,���Ժ�����!\n";
		exit(0);
		return 0;
	}
	return 0;
}