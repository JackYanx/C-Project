#include "SafeExitSystem.h"
#include "initVariable.h"
#include "AccountingUtility.h"

using namespace std;

void exitSys() {
	system("cls");
	cout << "\n-----------------------------------------------------------------------------------\n"
		<< "���ڽ��ϻ��û���Ϊ�»�״̬";
	for (int i = 0; i < 6;i++) {
		Sleep(900);
		cout << '.';
	}
	cout << endl;
	userAllLogout();
	LOG::localLogger(getUnixTime(), LOG_SYSEXIT, 1, 0, NULL);
	cout << "���ڵ����û�����";
	for (int i = 0; i < 6; i++) {
		Sleep(900);
		cout << '.';
	}
	cout << endl;
	cout << "\n-----------------------------------------------------------------------------------\n";
	exportDataToFile(0);
	cout << "\n-----------------------------------------------------------------------------------\n";
	cout << "                                   ��ӭ�´�ʹ��~                                   \n";
	configFilesSaveTail();
}