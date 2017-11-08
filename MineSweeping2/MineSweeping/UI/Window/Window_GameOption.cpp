#include "Window_GameOption.h" 

#include <locale.h>

WCHAR game_rating_drop_down_list_SELECTED_ITEM_NAME[100] = { 0 };
HWND game_rating_drop_down_list;
HWND game_option_confirm_button;
/*
// 声明窗口句柄
HWND hwnd;
// 
HINSTANCE hInstance;
// 设备上下文
HDC hdc;
// 本窗口绘图信息结构
PAINTSTRUCT ps;
// 用于注册的窗口类名
LPCWSTR regClassName = L"WindowClass_GameOption";
// 本窗口标题
LPCWSTR wndTitle = L"参数设置";
// 本窗口基本位置信息,X,Y,宽度,高度
wndGeoAttr wga = { 300,150,1010,635 };
*/
void onDraw2();
void onDraw2() {
	game_rating_drop_down_list = CreateWindow(L"combobox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		190, 20, 80, 100, hwnd[1], (HMENU)3300, hInstance[1], NULL);
	onFontRender(game_rating_drop_down_list,14);
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"初级");
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"中级");
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"高级");
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"自定义");
	
	game_option_confirm_button = CreateWindow(L"button", L"Confirm", BS_PUSHBUTTON | BS_TEXT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 20, 20, 20,20, hwnd[1],(HMENU)3301, hInstance[1], NULL);


	/*
	GetWindowText(game_rating_drop_down_list, game_rating_drop_down_list_SELECTED_ITEM_NAME, 20);
	FILE* tFile = fopen("D:\\12333.txt", "a+");
	fwprintf(tFile, L"%s", game_rating_drop_down_list_SELECTED_ITEM_NAME);
	fwprintf(tFile, L"%s", L"\n");
	fclose(tFile);
	*/
	/*
	CreateWindow(L"Button", L"这玩意儿好",
		BS_PUSHBUTTON | BS_TEXT | BS_DEFPUSHBUTTON | BS_USERBUTTON | BS_AUTORADIOBUTTON | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		10, 10, 150, 28,
		hwnd[1], (HMENU)50001,
		(HINSTANCE)GetWindowLongPtr(hwnd[1], GWLP_HINSTANCE),
		NULL);
		*/
		//BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE

}
// 窗口处理消息过程
LRESULT CALLBACK WindowProc_GameOption(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		hwnd[1] = phwnd;
		onDraw2();
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
	//case WM_PAINT:
		/*
		* 我们只需要在这里调用我们的 GDI 绘制函数就可以，其他地方可以先无视
		*/
		//onDraw2();
	//	break;
	//对用户操作控件(鼠标,键盘)等事件进行响应
	case WM_COMMAND:
	{

	
		//switch (wParam) {
		//case 500013:
			GetWindowText(game_rating_drop_down_list, game_rating_drop_down_list_SELECTED_ITEM_NAME, 100);
			setlocale(LC_ALL, "");
			FILE* tFile = fopen("D:\\12333.txt", "a+");
			fprintf(tFile, "%S", game_rating_drop_down_list_SELECTED_ITEM_NAME);
			fprintf(tFile, "%s", "\n");
			fclose(tFile);
		//}
		break;
	}
		// 窗口关闭消息
	case WM_CLOSE:
		DestroyWindow(hwnd[1]);
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
	return 0;
}

void RegisterWindow_GameOption(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	// 1)配置窗口属性
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc_GameOption; // 设置第四步的窗口过程回调函数
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName[1];
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 2)注册
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"窗口注册失败!", L"错误", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // 进程退出
	}
}
HWND CreateWindow_GameOption(HINSTANCE hInstance, int nCmdShow) {
	hwnd[1] = CreateWindow(
		regClassName[1],
		wndTitle[1],
		WS_OVERLAPPEDWINDOW,
		wga[1].X, wga[1].Y, wga[1].nWidth, wga[1].nHeight, // 出现坐标 x,y,宽度 高度 
		NULL, NULL, hInstance, NULL);
	if (hwnd[1] == NULL)
	{
		MessageBox(NULL, L"窗口创建失败!", L"错误", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // 进程退出
	}
	// 显示窗口
	ShowWindow(hwnd[1], SW_SHOW);
	UpdateWindow(hwnd[1]);
	return hwnd[1];
}