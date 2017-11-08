#include <Windows.h>
#include <process.h>
#include "UI\WndSummary.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
	// ��һ��,ע�ᴰ����
	RegisterWindow_Start(hInstance);
	RegisterWindow_GameOption(hInstance);
	// �ڶ���:��������
	hwnd = CreateWindow_Start(hInstance, nCmdShow);
	// ������:��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	GdiplusShutdown(GdiToken);
	return Msg.wParam;
}