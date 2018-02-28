#pragma once  
#ifndef BITMAPHELPER_H
#define BITMAPHELPER_H

#include <Windows.h>

/********************************************************************************
BitmapHelper ��ͼ����
����������
����λͼ�ļ�������λͼ�ļ����벢����ָ�����ڣ�Ϊ���Ч�ʶ����ڲ�һֱ
��������ڴ��BITMAP������ֻ�ڵ�һ����ͼʱ��Ҫ���ⲿ�ļ���ȡ��

ʹ��˵����
ÿһ��λͼ�ļ���Ӧһ��BitmapHelper�����ʹ��������

BitmapHelper *pBmp = new BitmapHelper(L"D:\\�羰_100-300.bmp");
pBmp->ShowOnWindow(this->m_hWnd);

delete pBmp;  // �������������Ҫ���λͼʱ��ɾ��
********************************************************************************/
class BitmapHelper
{
public:
	BitmapHelper(TCHAR* file);
	~BitmapHelper();

protected:
	TCHAR fileName[256]; // λͼ�ļ���  
	HBITMAP hBitmap;      // λͼ���  
	HDC memHDC;
	int desX;             // Ŀ��x����  
	int desY;             // Ŀ��y����  
protected:
	void ShowOnWindow(HWND hwnd, int x, int y);   // ��ָ����������ʾ  
public:
	HBITMAP CreateBitmapObjectFromDibFile(HDC hdc); //���ļ��л�ȡDDB  
	void ShowOnWindow(HWND hwnd);
	void ShowOnDevice(HDC dc, int x, int y);

};
#endif // !BITMAPHELPER_H
