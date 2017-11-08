#include "wnd_base.h"
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
	{ 900,  400,  300,  300},
	{ 800,  300,  200,  200}
};
HINSTANCE initInstance;
HINSTANCE inithPrevInstance;
LPSTR initlpCmdLine;
int initnCmdShow;
int FullScreenWidth;
int FullScreenHeight;
time_t cTime = time(0);
HANDLE hTimer;
DWORD dwThreadID = 0;
void set_window_size(HWND hWnd, int width, int height)
{
	RECT rcWindow, rcClient;
	int border_width, border_height;
	GetWindowRect(hWnd, &rcWindow);
	GetClientRect(hWnd, &rcClient);
	border_width = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
	border_height = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);
	SetWindowPos(hWnd, 0, 0, 0, border_width + width, border_height + height, SWP_NOMOVE | SWP_NOZORDER);
}


