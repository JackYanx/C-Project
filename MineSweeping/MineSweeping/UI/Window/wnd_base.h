#ifndef WND_BASE_H
#define WND_BASE_H

#pragma once
#include <Windows.h>
#include <atlimage.h>
#include <gdiplus.h>
#include <time.h>
#include <stdio.h>
#include <ShellScalingAPI.h> //Windows 8及以上版本可使用该头文件
#include <CommCtrl.h> //CommCtrl.h用于开启控件视觉特效
#include "../BitmapUtil/BitmapHelper.h"
#include "../FontsUtil/XFonts.h"
#include "../../Utils/Log.h"
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "Comctl32.lib")
// 开启控件视觉效果
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
// 设备上下文
extern HDC hdc[WND_NUM];
// 本窗口绘图信息结构
extern PAINTSTRUCT ps[WND_NUM];
// 用于注册的窗口类名
extern LPCWSTR regClassName[WND_NUM];
// 本窗口标题
extern LPCWSTR wndTitle[WND_NUM];
// 本窗口基本位置信息,X,Y,宽度,高度
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


