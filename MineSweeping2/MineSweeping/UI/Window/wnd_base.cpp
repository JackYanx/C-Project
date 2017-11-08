#include "wnd_base.h"
HWND hwnd[WND_NUM];
// 
HINSTANCE hInstance[WND_NUM];
// �豸������
HDC hdc[WND_NUM];
// �����ڻ�ͼ��Ϣ�ṹ
PAINTSTRUCT ps[WND_NUM];
// ����ע��Ĵ�������
LPCWSTR regClassName[WND_NUM] = { L"WindowClass_Start", L"Window_GameOption", L"Window_GameMain" };
// �����ڱ���
LPCWSTR wndTitle[WND_NUM] = { L"MineSweeper", L"��������", L"ɨ��" };
// �����ڻ���λ����Ϣ,X,Y,���,�߶�
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


