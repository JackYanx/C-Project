#include "wnd_base.h"
#include <assert.h>
HWND hwnd[WND_NUM];
// 
HINSTANCE hInstance[WND_NUM];
// 设备上下文
HDC hdc[WND_NUM];
// 本窗口绘图信息结构
PAINTSTRUCT ps[WND_NUM];
// 用于注册的窗口类名
LPCWSTR regClassName[WND_NUM] = { L"WindowClass_Start", L"Window_GameOption", L"Window_GameMain" };
// 本窗口标题
LPCWSTR wndTitle[WND_NUM] = { L"MineSweeper", L"参数设置", L"扫雷" };
// 本窗口基本位置信息,X,Y,宽度,高度
wndGeoAttr wga[WND_NUM] = {
	{   0,    0,    0,    0},
	{ 660,  340,  600,  400},
	{ 800,  300,  200,  200}
};
HINSTANCE initInstance;
HINSTANCE inithPrevInstance;
LPWSTR initlpCmdLine;
int initnCmdShow;
int FullScreenWidth;
int FullScreenHeight;
time_t cTime = time(0);
HANDLE hTimer;
DWORD dwThreadID = 0;
void set_window_size(HWND hWnd, int width, int height)
{
	if (width > FullScreenWidth || height > FullScreenHeight || width < 1 || height < 1) {
		assert(0);
	}

	/*
	RECT rcWindow, rcClient;
	int border_width, border_height;
	GetWindowRect(hWnd, &rcWindow);
	GetClientRect(hWnd, &rcClient);
	border_width = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
	border_height = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);
	*/
	/*
	wstring str;
	TCHAR buf[16] = { 0 };
	_itow_s(FullScreenWidth, buf, 16, 10);
	str.append(L"FW: ");
	str.append(buf);
	str.append(L" ");

	_itow_s(FullScreenHeight,buf,16,10);
	str.append(L"FH: ");
	str.append(buf);
	str.append(L" \n");
	
	_itow_s(width, buf, 16, 10);
	str.append(L"w: ");
	str.append(buf);
	str.append(L" ");

	_itow_s(height, buf, 16, 10);
	str.append(L"h: ");
	str.append(buf);
	str.append(L" \n");

	_itow_s((FullScreenWidth - width) / 2, buf, 16, 10);
	str.append(L"X: ");
	str.append(buf);
	str.append(L" ");

	_itow_s((FullScreenHeight - height) / 2, buf, 16, 10);
	str.append(L"Y: ");
	str.append(buf);
	str.append(L" ");

	MessageBox(hWnd, str.c_str(), 0, 0);
	*/
	//SetWindowPos(hWnd, 0, (FullScreenWidth - width) / 2, (FullScreenHeight - height) / 2, width, height, SWP_NOMOVE | SWP_NOZORDER);
	MoveWindow(hWnd, (FullScreenWidth - width) / 2, (FullScreenHeight - height) / 2, width, height, false);
}


