#include "SafeExitSystem.h"
#include "initVariable.h"
#include "AccountingUtility.h"

using namespace std;

void exitSys() {
	system("cls");
	cout << "\n-----------------------------------------------------------------------------------\n"
		<< "正在将上机用户置为下机状态";
	for (int i = 0; i < 6;i++) {
		Sleep(900);
		cout << '.';
	}
	cout << endl;
	userAllLogout();
	LOG::localLogger(getUnixTime(), LOG_SYSEXIT, 1, 0, NULL);
	cout << "正在导出用户数据";
	for (int i = 0; i < 6; i++) {
		Sleep(900);
		cout << '.';
	}
	cout << endl;
	cout << "\n-----------------------------------------------------------------------------------\n";
	exportDataToFile(0);
	cout << "\n-----------------------------------------------------------------------------------\n";
	cout << "                                   欢迎下次使用~                                   \n";
	configFilesSaveTail();
}