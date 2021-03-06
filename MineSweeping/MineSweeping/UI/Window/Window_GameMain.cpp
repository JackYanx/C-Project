#include "Window_GameMain.h"
#include "../../Controller/GameController.h"
#include "../../Utils/Log.h"

char logbuffer[32];

/*使用双缓冲技术,绘制过程过于复杂,防止因计算速度不足导致的窗口内容闪烁
 *基本原理: 创建一个持久化的DC,
 *
 *
 */

/*后台绘制设备上下文*/
//static HDC backgroundDC = NULL;
/*作为backgroundDC的所选对象*/
//static HBITMAP backgroundBitmap = NULL;
/*本窗口DC像素大小,需要根据游戏初始数据进行更改*/
static int cxClientPix, cyClientPix;
static HBITMAP bufferBmp;
static HDC bufferDC = NULL, drawDC = NULL;
static GameController localGameController;

static int mpx = 0;
static int mpy = 0;

static int ldpx = 0;
static int ldpy = 0;

static int rdpx = 0;
static int rdpy = 0;

static int lupx = 0;
static int lupy = 0;

static int rupx = 0;
static int rupy = 0;

static bool lbs = 0;
static bool rbs = 0;

static TCHAR numbuf[20] = { 0 };

void showMousePointerInfo(HDC hdc) {
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, OPAQUE);

	TextOut(hdc, 10, 10, L"MousePosi", lstrlen(L"MousePosi"));
	wsprintf(numbuf, L"X: %4d    ", mpx);
	TextOut(hdc, 10, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", mpy);
	TextOut(hdc, 10, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 130, 10, L"LastLBDPosi", lstrlen(L"LastLBDPosi"));
	wsprintf(numbuf, L"X: %4d    ", ldpx);
	TextOut(hdc, 130, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", ldpy);
	TextOut(hdc, 130, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 250, 10, L"LastRBDPosi", lstrlen(L"LastRBDPosi"));
	wsprintf(numbuf, L"X: %4d    ", rdpx);
	TextOut(hdc, 250, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", rdpy);
	TextOut(hdc, 250, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 370, 10, L"LastLBUPosi", lstrlen(L"LastLBUPosi"));
	wsprintf(numbuf, L"X: %4d    ", lupx);
	TextOut(hdc, 370, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", lupy);
	TextOut(hdc, 370, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 490, 10, L"LastRBUPosi", lstrlen(L"LastRBUPosi"));
	wsprintf(numbuf, L"X: %4d    ", rupx);
	TextOut(hdc, 490, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", rupy);
	TextOut(hdc, 490, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 610, 10, L"PointerStatus", lstrlen(L"PointerStatus"));
	wsprintf(numbuf, L"Left : %d ", lbs);
	TextOut(hdc, 610, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Right: %d ", rbs);
	TextOut(hdc, 610, 50, numbuf, lstrlen(numbuf));


}
// 窗口处理消息过程(回调函数)
LRESULT CALLBACK WindowProc_GameMain(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//CreateCompatibleBitmap()
	switch (msg)
	{

		/*
		WM_CREATE 在创建窗口(调用CreateWindow函数)时触发，只触发一次。
		WM_PAINT在需要重画(调用UpdateWindow函数)时调用，并多次触发。
		WM_CREATE先于WM_PAINT
		*/
	case WM_CREATE:
	{
		/*从上一个窗口获取输入信息*/
		GameInfo gi;
		gi.boardLength = 40;
		gi.boardHeight = 30;
		gi.mineNum = 39;
		gi.playerName = L"TestPlayer";
		gi.gameModel = new MineSweepingGame(40, 30, 39);
		/**/

		cxClientPix = 0;
		cyClientPix = 0;
		hwnd[2] = phwnd;
		/*初始化Canve*/
		localGameController.initialize(&gi, phwnd, hInstance[2],&cxClientPix, &cyClientPix);

		HDC hdc = GetDC(phwnd); //获取设备

		bufferDC = CreateCompatibleDC(hdc); //给设备分配一个内存空间

		drawDC = CreateCompatibleDC(hdc);

		bufferBmp = CreateCompatibleBitmap(hdc, cxClientPix, cyClientPix); //创建一个cxClient, cyClient大小并且适应DC设备环境的位图

		ReleaseDC(phwnd, hdc);

		SelectObject(bufferDC, bufferBmp);

		inflog("GameCanveSize: w:",itoa(cxClientPix, logbuffer, 10),"px | h:", itoa(cyClientPix, logbuffer, 10),"px.");
		/*第一次绘制*/
		//localGameController.draw(phwnd);
		

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
		break语句很重要!!!
		break语句很重要!!!
		break语句很重要!!!
		重要的话说三次
		*/
		break;
	}
	// 窗口绘制消息
	/*使用WS_EX_LAYERED风格窗口不会对 WM_PAINT 消息进行响应,绘图过程由WM_CREATE状态下的UpdateLayeredWindow()函数进行*/
	case WM_PAINT: {
		PAINTSTRUCT ps;
		/*响应WM_PAINT时必须在内容中添加BeginPaint与EndPaint,否则WM_PAINT会导致无效区域的背景被擦除;本函数返回HDC绘图上下文*/
		HDC hdc = BeginPaint(hwnd[2], &ps);
		localGameController.draw(hdc, bufferDC, drawDC, bufferBmp);
		showMousePointerInfo(hdc);
		/*
		HBITMAP hBitmap_num3 = (HBITMAP)LoadImage(hInstance[2], L"res\\bitmap\\msg-num3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//LoadBitmap(hInstance[2], L"res\\bitmap\\msg-num3.bmp");
		SelectObject(drawDC, hBitmap_num3);
		BitBlt(bufferDC, 50, 50, 16, 16, drawDC, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, cxClientPix, cyClientPix, bufferDC, 0, 0, SRCCOPY);
		BitmapHelper te(L"res\\bitmap\\msg-num2.bmp");
		te.ShowOnDevice(hdc,200,200);
		*/
		/*
		* 内容绘制
		*/
		//bitmap_num5.ShowOnDevice(hdc,100,100);

		/*结束绘图,释放绘图区*/
		EndPaint(hwnd[2], &ps);
		break;
	}
				   /*
	case WM_SIZE: {
		HDC hdc = GetDC(phwnd);
		bufferBmp = CreateCompatibleBitmap(hdc, cxClientPix, cyClientPix);
		ReleaseDC(phwnd, hdc);
	}
	*/

	case WM_MOUSEMOVE: {
		memset(numbuf, 0, sizeof(TCHAR) * 20);
		mpx = (int)LOWORD(lParam);
		mpy = (int)HIWORD(lParam);
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_LBUTTONDOWN: {
		lbs = 1;
		ldpx = mpx;
		ldpy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_RBUTTONDOWN: {
		rbs = 1;
		rdpx = mpx;
		rdpy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_LBUTTONUP: {
		lbs = 0;
		lupx = mpx;
		lupy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_RBUTTONUP: {
		rbs = 0;
		rupx = mpx;
		rupy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_COMMAND:
	{

		switch (wParam) {
		
		}

		break;
	}
	// 窗口关闭消息
	case WM_CLOSE:
		DestroyWindow(hwnd[2]);
		break;
		// 窗口销毁消息
	case WM_DESTROY:
		PostQuitMessage(0); // 发送离开消息给系统
		break;
		//case WM_SIZE:
		//{
		//	break;
		//}
		//set_window_size(hwnd, 1000, 625);
		// 其他消息
	default:
		// pass 给系统，咱不管
		return DefWindowProc(phwnd, msg, wParam, lParam);
	}
	//return DefWindowProc(phwnd, msg, wParam, lParam);
	return 0;
}


void RegisterWindow_GameMain(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	// 1)配置窗口属性
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc_GameMain; // 设置第四步的窗口过程回调函数
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;//(HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName[2];
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 2)注册
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"窗口注册失败!", L"错误", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // 进程退出
	}
}
HWND CreateWindow_GameMain(HINSTANCE hInstance, int nCmdShow) {
	hwnd[2] = CreateWindow(
		regClassName[2],
		wndTitle[2],
		WS_OVERLAPPEDWINDOW,
		wga[2].X, wga[2].Y, wga[2].nWidth, wga[2].nHeight, // 出现坐标 x,y,宽度 高度 
		NULL, NULL, hInstance, NULL);
	if (hwnd[2] == NULL)
	{
		MessageBox(NULL, L"窗口创建失败!", L"错误", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // 进程退出
	}
	// 显示窗口
	ShowWindow(hwnd[2], SW_SHOW);
	UpdateWindow(hwnd[2]);
	return hwnd[2];
}