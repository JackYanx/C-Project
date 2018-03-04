#ifndef WND_BASE_H
#define WND_BASE_H

#pragma once
#include <Windows.h>
#include <atlimage.h>
#include <gdiplus.h>
#include <time.h>
#include <stdio.h>
#include <ShellScalingAPI.h> //Windows 8�����ϰ汾��ʹ�ø�ͷ�ļ�
#include <CommCtrl.h> //CommCtrl.h���ڿ����ؼ��Ӿ���Ч
#include "../BitmapUtil/BitmapHelper.h"
#include "../FontsUtil/XFonts.h"
#include "../../Utils/Log.h"
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "Comctl32.lib")
// �����ؼ��Ӿ�Ч��
#pragma comment(linker,"\"/manifestdependency:type='win32' name = 'Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")
#define WND_NUM 3
using namespace Gdiplus;
typedef struct WindowGeometricAttributes {
	int X;
	int Y;
	int nWidth;
	int nHeight;
} wndGeoAttr;
extern HWND hwnd[WND_NUM];
// 
extern HINSTANCE hInstance[WND_NUM];
// �豸������
extern HDC hdc[WND_NUM];
// �����ڻ�ͼ��Ϣ�ṹ
extern PAINTSTRUCT ps[WND_NUM];
// ����ע��Ĵ�������
extern LPCWSTR regClassName[WND_NUM];
// �����ڱ���
extern LPCWSTR wndTitle[WND_NUM];
// �����ڻ���λ����Ϣ,X,Y,���,�߶�
extern wndGeoAttr wga[WND_NUM];
extern HINSTANCE initInstance;
extern HINSTANCE inithPrevInstance;
extern LPWSTR initlpCmdLine;
extern int initnCmdShow;
extern int FullScreenWidth;
extern int FullScreenHeight;
extern time_t cTime;
extern HANDLE hTimer;
extern DWORD dwThreadID;
void set_window_size(HWND hWnd, int width, int height);
#endif // !BASE_H


