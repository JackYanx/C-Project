#include <iostream>
#include <windows.h>
using namespace std;

DWORD WINAPI Fun(LPVOID lpParamter)
{
	int sum = 0;
	for (int i = 0; i <= 5; i++)
	{
		sum = sum + i;
	}
	while (1)
	{
		printf("%d\n", sum); Sleep(1500);
	}
	return 0;
}

int main(int argc, char* argv[])

{
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	CloseHandle(hThread);
	int sum = 0;
	for (int i = 0; i <= 10; i++)
	{
		sum = sum + i;
	}
	while (1)
	{
		printf("%d\n", sum); Sleep(2000);
	}
	getchar();
	return 0;
}