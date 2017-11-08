#include <iostream>  
#include <process.h>  
#include <windows.h>  

using namespace std;

void ThreadFun1(PVOID param) {
	while (1) {
		Sleep(1000);
		cout << "this is ThreadFun1" << endl;
	}
}

void  ThreadFun2(PVOID param) {
	while (1) {
		Sleep(1000);
		cout << "this is ThreadFun2" << endl;
	}
}

int main() {
	int i = 0;

	_beginthread(ThreadFun1, 0, NULL);
	_beginthread(ThreadFun2, 0, NULL);
	Sleep(30000);
	cout << "end" << endl;
	return 0;
}