#include <cstdio>
#include <Windows.h>

int main(int argc, char* argv)
{
	/*
	���� TSKDllInject.dll ���ڴ���
	*/
	printf("\n         ��������������� �⣨����������        \n      ------------BGM: BadApple------------\n\n���������ʼ:>");
	getchar();
	HMODULE dll = LoadLibrary(L"TSKDllInject.dll");
	if (dll == NULL)
	{
		printf("Cannot find DLL");
		getchar();
		return -1;
	}
	else {
		printf("�ɹ�����TSKDllInject.dll,��ʼע��...\n");
		getchar();
		return -1;
	}
}