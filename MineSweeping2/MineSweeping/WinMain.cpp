#include <sstream>  
#include <Windows.h> 
#include <wingdi.h>
#include <afxwin.h>
#include "BitmapUtil\XBitmap.h"
//��һ�޶���������һ����GUID�ִ�����������������������ظ�  
LPCWSTR CLASS_NAME = TEXT("{198CEAB2-AD78-4ed3-B099-247639080CB0}");

/************************************************************************
�ص����������������յ��κ�Windows��Ϣʱ������
************************************************************************/
LRESULT CALLBACK onMainWndMessage(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0); //����ǡ��������١��¼�����Ӧ������Ϣ������Ͷ��  
		break;              //һ��WM_QUIT��Ϣ��ʹGetMessage()����FALSE  
	default:
		return DefWindowProc(wnd, msg, wParam, lParam);
	}
	return 0;
}

/************************************************************************
�Ǽ��Լ��Ĵ�����
************************************************************************/
bool registerMyClass() {
	WNDCLASSEX  wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.style = CS_VREDRAW | CS_HREDRAW;
	wce.lpfnWndProc = &onMainWndMessage;  //ָ���ص�����  
	wce.hInstance = GetModuleHandle(0);
	wce.hIcon = LoadIcon(0, MAKEINTRESOURCE(IDI_WINLOGO));
	wce.hCursor = LoadCursor(0, MAKEINTRESOURCE(IDC_ARROW));
	wce.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	wce.lpszClassName = CLASS_NAME; //��һ�޶������� 
	wce.hIconSm = wce.hIcon;
	return 0 != RegisterClassEx(&wce);
}

/************************************************************************
��������ʾ������
************************************************************************/
bool createMyWindow(int cmdShow) {
	HWND mainWnd = CreateWindowEx(0, CLASS_NAME, TEXT("Demo"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0, 0, GetModuleHandle(0), 0);
	if (0 != mainWnd) {
		ShowWindow(mainWnd, cmdShow);
		UpdateWindow(mainWnd);
		return true;
	}
	else {
		return false;
	}
}

/************************************************************************
��Ϣѭ��
************************************************************************/
int messageLoop() {
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}

/************************************************************************
WinMain���������
************************************************************************/
int WINAPI WinMain(HINSTANCE, HINSTANCE, char *, int cmdShow) {
	/*
	XBitmap xBitmap;
	xBitmap.decodeXBMFile("D:\\24test.bmp");
	xBitmap.decodeXBMFile("D:\\32test.bmp");
	return 0;


	CRect cRect;

	*/

	if (registerMyClass() && createMyWindow(cmdShow)) {
		return messageLoop();
	}
	else {
		std::ostringstream msg;
		msg << "����������ʧ�ܣ�������룺" << GetLastError();
		MessageBoxA(0, msg.str().c_str(), 0, MB_OK | MB_ICONSTOP);
		return 0;
	}
}
