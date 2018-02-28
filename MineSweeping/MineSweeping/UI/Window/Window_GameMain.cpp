#include "Window_GameMain.h"
#include "../../Controller/GameController.h"
#include "../../Utils/Log.h"

char logbuffer[32];

/*ʹ��˫���弼��,���ƹ��̹��ڸ���,��ֹ������ٶȲ��㵼�µĴ���������˸
 *����ԭ��: ����һ���־û���DC,
 *
 *
 */

/*��̨�����豸������*/
//static HDC backgroundDC = NULL;
/*��ΪbackgroundDC����ѡ����*/
//static HBITMAP backgroundBitmap = NULL;
/*������DC���ش�С,��Ҫ������Ϸ��ʼ���ݽ��и���*/
static int cxClientPix, cyClientPix;
static GameController localGameController;
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
		/*����һ�����ڻ�ȡ������Ϣ*/
		GameInfo gi;
		gi.boardLength = 40;
		gi.boardHeight = 20;
		gi.mineNum = 10;
		gi.playerName = L"TestPlayer";
		gi.gameModel = new MineSweepingGame(40, 20, 10);
		/**/

		cxClientPix = 0;
		cyClientPix = 0;
		hwnd[2] = phwnd;
		/*��ʼ��Canve*/
		localGameController.initialize(&gi, phwnd, hInstance[2],&cxClientPix, &cyClientPix);

		inflog("GameCanveSize: w:",itoa(cxClientPix, logbuffer, 10),"px | h:", itoa(cyClientPix, logbuffer, 10),"px.");
		/*��һ�λ���*/
		localGameController.draw(phwnd);

		//set_window_size(phwnd, 900, 600);
		/*
		HDC hdc = GetDC(phwnd);
		HDC backgroundDC = CreateCompatibleDC(hdc);
		HBITMAP backgroundBitmap = CreateCompatibleBitmap(hdc, cxClientPix, cyClientPix);
		ReleaseDC(phwnd, hdc);
		SelectObject(backgroundDC, backgroundBitmap);
		*/

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
		//bitmap_num5.ShowOnDevice(hdc,100,100);


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