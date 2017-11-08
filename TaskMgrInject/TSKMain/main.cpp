#include <cstdio>
#include <Windows.h>

int main(int argc, char* argv)
{
	/*
	加载 TSKDllInject.dll 到内存中
	*/
	printf("\n         任务管理器播放器 ｂ（￣▽￣）ｄ        \n      ------------BGM: BadApple------------\n\n按任意键开始:>");
	getchar();
	HMODULE dll = LoadLibrary(L"TSKDllInject.dll");
	if (dll == NULL)
	{
		printf("Cannot find DLL");
		getchar();
		return -1;
	}
	else {
		printf("成功加载TSKDllInject.dll,开始注入...\n");
		getchar();
		return -1;
	}
}