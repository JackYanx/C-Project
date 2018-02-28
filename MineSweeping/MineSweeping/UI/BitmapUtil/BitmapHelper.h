#pragma once  
#ifndef BITMAPHELPER_H
#define BITMAPHELPER_H

#include <Windows.h>

/********************************************************************************
BitmapHelper 贴图助手
功能描述：
根据位图文件名，把位图文件读入并贴到指定窗口，为提高效率对象内部一直
保存读入内存的BITMAP，所以只在第一次贴图时需要从外部文件读取。

使用说明：
每一个位图文件对应一个BitmapHelper类对象。使用样例：

BitmapHelper *pBmp = new BitmapHelper(L"D:\\风景_100-300.bmp");
pBmp->ShowOnWindow(this->m_hWnd);

delete pBmp;  // 程序结束或不再需要这个位图时，删除
********************************************************************************/
class BitmapHelper
{
public:
	BitmapHelper(TCHAR* file);
	~BitmapHelper();

protected:
	TCHAR fileName[256]; // 位图文件名  
	HBITMAP hBitmap;      // 位图句柄  
	HDC memHDC;
	int desX;             // 目的x坐标  
	int desY;             // 目的y坐标  
protected:
	void ShowOnWindow(HWND hwnd, int x, int y);   // 在指定窗口上显示  
public:
	HBITMAP CreateBitmapObjectFromDibFile(HDC hdc); //从文件中获取DDB  
	void ShowOnWindow(HWND hwnd);
	void ShowOnDevice(HDC dc, int x, int y);

};
#endif // !BITMAPHELPER_H
