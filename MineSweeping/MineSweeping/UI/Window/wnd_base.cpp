#include "wnd_base.h"
#include <assert.h>
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


