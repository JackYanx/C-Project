#include <Windows.h>
#include <process.h>
#include "UI\WndSummary.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	setlogfile("D:\\gamelog.log");
	inflog("_APPLICATION INITIALIZING_");
	/*��ʼ���������*/
	initInstance = hInstance;
	inithPrevInstance = hPrevInstance;
	initlpCmdLine = lpCmdLine;
	initnCmdShow = nCmdShow;
	/*����WindowsDPI����,��ֹͼƬ������ģ��,�ú���������win8������ϵͳ��ʹ��*/
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
	FullScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	FullScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	HWND hwnd;
	MSG Msg;
	ULONG_PTR GdiToken;
	GdiplusStartupInput	gin;
	GdiplusStartup(&GdiToken, &gin, NULL);
	// ��һ��,ע�ᴰ����,�м�����ע�Ἰ��,��Ȼ������ܻ���
	RegisterWindow_Start(hInstance);
	RegisterWindow_GameOption(hInstance);
	RegisterWindow_GameMain(hInstance);
	inflog("Window Registion Finish");
	// �ڶ���:��������
	/*������ʾSplashWindow*/
	hwnd = CreateWindow_Start(hInstance, nCmdShow);
	inflog("Splash Window Created");
	/**/
	//hwnd = CreateWindow_GameMain(hInstance, nCmdShow);
	// ������:��Ϣѭ��
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