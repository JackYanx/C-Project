#include <iostream>

#include "menu.h"
#include "InitializeSystem.h"
#include "SafeExitSystem.h"

using namespace std;

int main(){
	initSys();
	int n;
	do{
		 n = displayMenu();
		 cin.get();
		 cin.get();
		system("cls");  //�����Ļ����
	} while (n != 0);
	exitSys();
	return 0;
}