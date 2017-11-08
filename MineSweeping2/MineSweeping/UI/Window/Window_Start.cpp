//#include <pthread.h>

#include "Window_Start.h"
#include "Window_GameOption.h"
#define INIT_DELAY_TIME 5

//bool volatile bThreadOn = true;
void _cdecl wndSwitch(PVOID param);
void _cdecl wndSwitch(PVOID param) {
	while (time(0) < cTime + 5);
	PostMessage(hwnd[0], WM_CLOSE, 0, 0);
}
// �����ڻ�ͼ����
void onDraw() {

}

// ���ڴ�����Ϣ����
LRESULT CALLBACK WindowProc_Start(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
	{
		hwnd[0] = phwnd;
		Image image(L"D:\\MineSweeperStartS.bmp");
		//���ش���ͼ��
		int iWidth = image.GetWidth();
		int iHeight = image.GetHeight();
		HDC hdcScreen = GetDC(hwnd[0]);
		HDC hdcMem = CreateCompatibleDC(hdcScreen);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, iWidth, iHeight);
		HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMem, hBitmap);
		Graphics gp(hdcMem);
		//�����ｨ�����ڵ�ͼ��,�����ô���������
		//GraphicsPath graphicspath;
		//SolidBrush brush(Color(255, 175, 0, 0));
		//CreateRoundRectangle(Rect(0, 0, iWidth, iHeight), 20, &graphicspath);//����Բ�Ǿ���·��
		//gp.FillPath(&brush, &graphicspath);//���·��----ȥ��ע�Ͳ鿴Ч��
		gp.DrawImage(&image, 0,0,1000,625);//��pngͼ����Ƶ���̨DC��
		BLENDFUNCTION blend = { 0 };
		blend.BlendOp = AC_SRC_OVER;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;//��ͨ�����
		POINT	pPos = {460, 188};
		POINT	pSrc = { 0, 0 };
		SIZE	sizeWnd = { iWidth, iHeight };
		//ʹ��UpdateLayeredWindow()�������·ֲ㴰��
		UpdateLayeredWindow(hwnd[0], hdcScreen, &pPos, &sizeWnd, hdcMem, &pSrc, NULL, &blend, ULW_ALPHA);
		//��β������
		SelectObject(hdcMem, hBitmapOld);
		DeleteObject(hBitmap);
		DeleteDC(hdcMem);
		ReleaseDC(hwnd[0], hdcScreen);

		/*������һ���߳�,������ʱ�ȴ�һ��ʱ��ر�����ҳ��,�Զ���ת����һ������*/
		_beginthread(wndSwitch, 0, NULL);
		/*CreateThread�����̲߳�֪��Ϊʲô��ʧ��,����_beginthread����*/
		//hTimer = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)wndSwitch(NULL), NULL, 0, NULL);
		//CloseHandle(hTimer);

		/*
		HMENU menubar = CreateMenu();
		HMENU menuPop = CreatePopupMenu();
		AppendMenu(menuPop, MF_STRING, (UINT_PTR)PS_SOLID, L"ʵ��");
		AppendMenu(menuPop, MF_STRING, (UINT_PTR)PS_DASH, L"����");
		AppendMenu(menuPop, MF_STRING, (UINT_PTR)PS_DOT, L"����");
		AppendMenu(menuPop, MF_STRING, (UINT_PTR)PS_DASHDOT, L"������");
		AppendMenu(menubar, MF_STRING | MF_POPUP, (UINT_PTR)menuPop, L"ѡ������");
		SetMenu(hwnd, menubar);
		*/

	}
	// ���ڻ�����Ϣ
	/*ʹ��WS_EX_LAYERED��񴰿ڲ���� WM_PAINT ��Ϣ������Ӧ,��ͼ������WM_CREATE״̬�µ�UpdateLayeredWindow()��������*/
	case WM_PAINT:
		/*
		* ����ֻ��Ҫ������������ǵ� GDI ���ƺ����Ϳ��ԣ������ط�����������
		*/
		onDraw();
		break;
		// ���ڹر���Ϣ
	case WM_CLOSE:
		DestroyWindow(hwnd[0]);
		break;
		// ����������Ϣ
	case WM_DESTROY:
		//CloseHandle(hTimer);
		CreateWindow_GameOption(initInstance, initnCmdShow);
		//PostQuitMessage(0); // �����뿪��Ϣ��ϵͳ
		break;
	case WM_SIZE:
	{
		break;
	}
		//set_window_size(hwnd, 1000, 625);
		// ������Ϣ
	default:
		// pass ��ϵͳ���۲���
		return DefWindowProc(phwnd, msg, wParam, lParam);
	}
	return 0;
}

// ע�ᴰ����
void RegisterWindow_Start(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	// 1)���ô�������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_IME | CS_DBLCLKS;
	wc.lpfnWndProc = WindowProc_Start; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName[0];
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// 2)ע��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"����ע��ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
}

/*��������*/
HWND CreateWindow_Start(HINSTANCE hInstance, int nCmdShow)
{
	hwnd[0] = CreateWindowEx(
		WS_EX_LAYERED,
		regClassName[0],
		wndTitle[0],
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP,
		wga[0].X, wga[0].Y, wga[0].nWidth, wga[0].nHeight, // �������� x,y,��� �߶� 
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"���ڴ���ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
	// ��ʾ����
	ShowWindow(hwnd[0], SW_SHOW);
	UpdateWindow(hwnd[0]);
	return hwnd[0];
}
