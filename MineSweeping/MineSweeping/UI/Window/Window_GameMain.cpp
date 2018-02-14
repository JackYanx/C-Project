#include "Window_GameMain.h"

static BitmapHelper bitmap_empty(L"res\\bitmap\\msg-empty.bmp");
static BitmapHelper bitmap_flagabove(L"res\\bitmap\\msg-flagabove.bmp");
static BitmapHelper bitmap_mine(L"res\\bitmap\\msg-mine.bmp");
static BitmapHelper bitmap_mineexploded(L"res\\bitmap\\msg-mineexploded.bmp");
static BitmapHelper bitmap_nomine(L"res\\bitmap\\msg-nomine.bmp");
static BitmapHelper bitmap_num1(L"res\\bitmap\\msg-num1.bmp");
static BitmapHelper bitmap_num2(L"res\\bitmap\\msg-num2.bmp");
static BitmapHelper bitmap_num3(L"res\\bitmap\\msg-num3.bmp");
static BitmapHelper bitmap_num4(L"res\\bitmap\\msg-num4.bmp");
static BitmapHelper bitmap_num5(L"res\\bitmap\\msg-num5.bmp");
static BitmapHelper bitmap_num6(L"res\\bitmap\\msg-num6.bmp");
static BitmapHelper bitmap_num7(L"res\\bitmap\\msg-num7.bmp");
static BitmapHelper bitmap_num8(L"res\\bitmap\\msg-num8.bmp");
static BitmapHelper bitmap_uncovered(L"res\\bitmap\\msg-uncovered.bmp");
static BitmapHelper bitmap_unknown(L"res\\bitmap\\msg-unknown.bmp");

/*ʹ��˫���弼��,���ƹ��̹��ڸ���,��ֹ������ٶȲ��㵼�µĴ���������˸
 *����ԭ��: ����һ���־û���DC,
 *
 *
 */

/*��̨�����豸������*/
HDC backgroundDC = NULL;
/*��ΪbackgroundDC����ѡ����*/
HBITMAP backgroundBitmap = NULL;
/*������DC���ش�С,��Ҫ������Ϸ��ʼ���ݽ��и���*/
int cxClient, cyClient;

// ���ڴ�����Ϣ����(�ص�����)
LRESULT CALLBACK WindowProc_GameMain(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//CreateCompatibleBitmap()
	switch (msg)
	{

		/*
		WM_CREATE �ڴ�������(����CreateWindow����)ʱ������ֻ����һ�Ρ�
		WM_PAINT����Ҫ�ػ�(����UpdateWindow����)ʱ���ã�����δ�����
		WM_CREATE����WM_PAINT
		*/
	case WM_CREATE:
	{
		cxClient = 0;
		cyClient = 0;
		hwnd[2] = phwnd;
		set_window_size(phwnd, 900, 600);
		HDC hdc = GetDC(phwnd);
		backgroundDC = CreateCompatibleDC(hdc);
		backgroundBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);
		ReleaseDC(phwnd, hdc);
		SelectObject(backgroundDC, backgroundBitmap);
		//onDraw2();
		/*
		break������Ҫ!!!
		break������Ҫ!!!
		break������Ҫ!!!
		��Ҫ�Ļ�˵����
		*/
		break;
	}
	// ���ڻ�����Ϣ
	/*ʹ��WS_EX_LAYERED��񴰿ڲ���� WM_PAINT ��Ϣ������Ӧ,��ͼ������WM_CREATE״̬�µ�UpdateLayeredWindow()��������*/
	case WM_PAINT: {
		PAINTSTRUCT ps;
		/*��ӦWM_PAINTʱ���������������BeginPaint��EndPaint,����WM_PAINT�ᵼ����Ч����ı���������;����������HDC��ͼ������*/
		HDC hdc = BeginPaint(hwnd[2], &ps);

		/*
		* ���ݻ���
		*/
		bitmap_num5.ShowOnDevice(hdc,100,100);


		/*������ͼ,�ͷŻ�ͼ��*/
		EndPaint(hwnd[2], &ps);
		break;
	}

	case WM_COMMAND:
	{

		switch (wParam) {
		
		}

		break;
	}
	// ���ڹر���Ϣ
	case WM_CLOSE:
		DestroyWindow(hwnd[2]);
		break;
		// ����������Ϣ
	case WM_DESTROY:
		PostQuitMessage(0); // �����뿪��Ϣ��ϵͳ
		break;
		//case WM_SIZE:
		//{
		//	break;
		//}
		//set_window_size(hwnd, 1000, 625);
		// ������Ϣ
	default:
		// pass ��ϵͳ���۲���
		return DefWindowProc(phwnd, msg, wParam, lParam);
	}
	//return DefWindowProc(phwnd, msg, wParam, lParam);
	return 0;
}


void RegisterWindow_GameMain(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	// 1)���ô�������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc_GameMain; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName[2];
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 2)ע��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"����ע��ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
}
HWND CreateWindow_GameMain(HINSTANCE hInstance, int nCmdShow) {
	hwnd[2] = CreateWindow(
		regClassName[2],
		wndTitle[2],
		WS_OVERLAPPEDWINDOW,
		wga[2].X, wga[2].Y, wga[2].nWidth, wga[2].nHeight, // �������� x,y,��� �߶� 
		NULL, NULL, hInstance, NULL);
	if (hwnd[2] == NULL)
	{
		MessageBox(NULL, L"���ڴ���ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
	// ��ʾ����
	ShowWindow(hwnd[2], SW_SHOW);
	UpdateWindow(hwnd[2]);
	return hwnd[2];
}