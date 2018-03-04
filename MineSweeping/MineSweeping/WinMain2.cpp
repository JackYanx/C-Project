#include <Windows.h>
#include <process.h>
#include "UI\WndSummary.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	setlogfile("D:\\gamelog.log");
	inflog("_APPLICATION INITIALIZING_");
	/*初始化相关数据*/
	initInstance = hInstance;
	inithPrevInstance = hPrevInstance;
	initlpCmdLine = lpCmdLine;
	initnCmdShow = nCmdShow;
	/*禁用WindowsDPI缩放,防止图片和文字模糊,该函数仅能在win8及以上系统中使用*/
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
	FullScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	FullScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	HWND hwnd;
	MSG Msg;
	ULONG_PTR GdiToken;
	GdiplusStartupInput	gin;
	GdiplusStartup(&GdiToken, &gin, NULL);
	// 第一步,注册窗口类,有几个就注册几个,不然后面可能会忘
	RegisterWindow_Start(hInstance);
	RegisterWindow_GameOption(hInstance);
	RegisterWindow_GameMain(hInstance);
	inflog("Window Registion Finish");
	// 第二步:创建窗口
	/*首先显示SplashWindow*/
	hwnd = CreateWindow_Start(hInstance, nCmdShow);
	inflog("Splash Window Created");
	/**/
	//hwnd = CreateWindow_GameMain(hInstance, nCmdShow);
	// 第三步:消息循环
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	GdiplusShutdown(GdiToken);
	inflog("_APPLICATION SHUTDOWN_");
	lexit();
	return Msg.wParam;
}