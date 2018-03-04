#include "Window_GameOption.h" 
#include "Window_GameMain.h"

#include <locale.h>

TCHAR combobox_game_rating_select_ITEM_NAME[100] = { 0 };
TCHAR text_game_rating[] = L"难度等级";
TCHAR text_game_rating_easyyy[] = L"初级";
TCHAR text_game_rating_medium[] = L"中级";
TCHAR text_game_rating_harddd[] = L"高级";
TCHAR text_game_rating_custom[] = L"自定义";
TCHAR text_game_board_length[] = L"BoardLength";
TCHAR text_game_board_height[] = L"BoardHeight";
TCHAR text_game_mine_num[] = L"MineNum";
TCHAR text_button_game_option_confirm[] = L"确定";

int value_game_board_length;
int value_game_board_height;
int value_game_mine_num;


//HWND 
HWND combobox_game_rating_select;

HWND inputbox_game_board_length;
HWND inputbox_game_board_height;
HWND inputbox_game_mine_num;

HWND button_game_option_confirm;


void onDraw2();
void onDraw2() {

	/*创建游戏难度下拉选框*/
	combobox_game_rating_select = CreateWindow(
		L"ComboBox",
		NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		336, 46, 80, 100,
		hwnd[1],
		(HMENU)3300,
		hInstance[1],
		NULL);
	/*渲染字体为微软雅黑,字号14*/
	onFontRender(combobox_game_rating_select,14);

	/*为下拉选框添加四个选项*/
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_easyyy);
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_medium);
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_harddd);
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_custom);
	/*设置默认难度选项为第0项,初级*/
	SendMessage(combobox_game_rating_select, CB_SETCURSEL, 0, 0);


	/*绘制游戏面板长度值输入框*/
	inputbox_game_board_length = CreateWindow(
		L"Edit",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NOHIDESEL,
		336, 121, 194, 30,
		hwnd[1],
		(HMENU)3330,
		hInstance[1],
		NULL);
	/*渲染字体为微软雅黑,字号15*/
	onFontRender(inputbox_game_board_length, 15);



	/*绘制游戏面板高度值输入框*/
	inputbox_game_board_height = CreateWindow(
		L"Edit",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NOHIDESEL,
		336, 181, 194, 30,
		hwnd[1],
		(HMENU)3331,
		hInstance[1],
		NULL);
	/*渲染字体为微软雅黑, 字号15*/
	onFontRender(inputbox_game_board_height, 15);



	/*绘制游戏地雷数输入框*/
	inputbox_game_mine_num = CreateWindow(
		L"Edit",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NOHIDESEL,
		336, 241, 194, 30,
		hwnd[1],
		(HMENU)3332,
		hInstance[1],
		NULL);
	/*渲染字体为微软雅黑, 字号15*/
	onFontRender(inputbox_game_mine_num, 15);

	/*设置三个输入框默认为不可更改状态*/
	SendMessage(inputbox_game_board_length, EM_SETREADONLY, 1, 0);
	SendMessage(inputbox_game_board_height, EM_SETREADONLY, 1, 0);
	SendMessage(inputbox_game_mine_num, EM_SETREADONLY, 1, 0);
	SendMessage(inputbox_game_board_length, WM_SETTEXT, 0, (LPARAM)L"16");
	SendMessage(inputbox_game_board_height, WM_SETTEXT, 0, (LPARAM)L"9");
	SendMessage(inputbox_game_mine_num, WM_SETTEXT, 0, (LPARAM)L"10");

	/*绘制游戏选项确认按钮*/
	button_game_option_confirm = CreateWindow(
		L"Button",
		L"Confirm",
		BS_PUSHBUTTON | BS_TEXT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		202, 293, 169, 40,
		hwnd[1],
		(HMENU)3301,
		hInstance[1],
		NULL);
	/*渲染字体为微软雅黑, 字号15*/
	onFontRender(button_game_option_confirm, 15);

}

// 窗口处理消息过程(回调函数)
LRESULT CALLBACK WindowProc_GameOption(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	/*
	WM_CREATE 在创建窗口(调用CreateWindow函数)时触发，只触发一次。
	WM_PAINT在需要重画(调用UpdateWindow函数)时调用，并多次触发。
	WM_CREATE先于WM_PAINT 
	*/
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
	case WM_PAINT: {
		PAINTSTRUCT ps;
		/*响应WM_PAINT时必须在内容中添加BeginPaint与EndPaint,否则WM_PAINT会导致无效区域的背景被擦除;本函数返回HDC绘图上下文*/
		HDC hdc = BeginPaint(hwnd[1], &ps);

		/*
		* 内容绘制
		*/
		/*手动更改绘图上下文字体与字号*/
		onFontRender(hdc, 15);

		/*绘制文字*/
		TextOut(hdc, 154,  48, text_game_rating,       lstrlenW(text_game_rating));
		TextOut(hdc, 154, 123, text_game_board_length, lstrlenW(text_game_board_length));
		TextOut(hdc, 154, 180, text_game_board_height, lstrlenW(text_game_board_height));
		TextOut(hdc, 154, 240, text_game_mine_num,     lstrlenW(text_game_mine_num));

		/*结束绘图,释放绘图区*/
		EndPaint(hwnd[1], &ps);
		break;
	}

	//对用户操作控件(鼠标,键盘)等事件进行响应
	case WM_COMMAND:
	{

		switch (wParam) {
		/*响应button_game_option_confirm点击事件*/
		case 3301: {
			memset(combobox_game_rating_select_ITEM_NAME, 0, sizeof(combobox_game_rating_select_ITEM_NAME));
			GetWindowText(combobox_game_rating_select, combobox_game_rating_select_ITEM_NAME, 100);
			/*
			setlocale(LC_ALL, "");
			FILE* tFile = fopen("D:\\12333.txt", "a+");
			fprintf(tFile, "%ws", combobox_game_rating_select_ITEM_NAME);
			fprintf(tFile, "%s", "\n");
			fclose(tFile);
			*/
			break;
		}

		/*响应combobox_game_rating_select选项被选中事件*/
		/*解释为什么是68836:
		 *CreateWindow创建combobox类控件时,第9个参数为此控件窗口菜单句柄(窗口标识),用于在回调函数响应WM_COMMAND消息时使用
		 *WPARAM为无符号32位整数,combobox控件选项被选中造成内容变更时,发送消息中wParam的并非为combobox控件窗口菜单句柄值
		 *而是将变更类型消息作为高十六位,combobox控件窗口菜单句柄作为低十六位的组合所得到得无符号32位整数
		 *本处CBN_SELCHANGE宏值为1,combobox_game_rating_select件窗口菜单句柄值为3300 
		 *二进制分别为 0000 0000 0000 0001 与 0000 1100 1110 0100
		 *按照高低十六位二进制组合,结果为 0000 0000 0000 0001 0000 1100 1110 0100
		 *即68836
		*/
		case 68836:
		{

			memset(combobox_game_rating_select_ITEM_NAME, 0, sizeof(combobox_game_rating_select_ITEM_NAME));
			GetWindowText(combobox_game_rating_select, combobox_game_rating_select_ITEM_NAME, 100);
			SendMessage(inputbox_game_board_length, EM_SETREADONLY, 1, 0);
			SendMessage(inputbox_game_board_height, EM_SETREADONLY, 1, 0);
			SendMessage(inputbox_game_mine_num, EM_SETREADONLY, 1, 0);
			if (StrCmp(text_game_rating_custom, combobox_game_rating_select_ITEM_NAME) == 0) {
				SendMessage(inputbox_game_board_length, EM_SETREADONLY, 0, 0);
				SendMessage(inputbox_game_board_height, EM_SETREADONLY, 0, 0);
				SendMessage(inputbox_game_mine_num, EM_SETREADONLY, 0, 0);
				SendMessage(inputbox_game_board_length, WM_SETTEXT, 0, (LPARAM)L"");
				SendMessage(inputbox_game_board_height, WM_SETTEXT, 0, (LPARAM)L"");
				SendMessage(inputbox_game_mine_num, WM_SETTEXT, 0, (LPARAM)L"");
			}
			else if (StrCmp(text_game_rating_easyyy, combobox_game_rating_select_ITEM_NAME) == 0) {
				SendMessage(inputbox_game_board_length, WM_SETTEXT, 0, (LPARAM)L"16");
				SendMessage(inputbox_game_board_height, WM_SETTEXT, 0, (LPARAM)L"9");
				SendMessage(inputbox_game_mine_num, WM_SETTEXT, 0, (LPARAM)L"10");
			}
			else if (StrCmp(text_game_rating_medium, combobox_game_rating_select_ITEM_NAME) == 0) {
				SendMessage(inputbox_game_board_length, WM_SETTEXT, 0, (LPARAM)L"16");
				SendMessage(inputbox_game_board_height, WM_SETTEXT, 0, (LPARAM)L"16");
				SendMessage(inputbox_game_mine_num, WM_SETTEXT, 0, (LPARAM)L"40");
			}
			else if (StrCmp(text_game_rating_harddd, combobox_game_rating_select_ITEM_NAME) == 0) {
				SendMessage(inputbox_game_board_length, WM_SETTEXT, 0, (LPARAM)L"30");
				SendMessage(inputbox_game_board_height, WM_SETTEXT, 0, (LPARAM)L"16");
				SendMessage(inputbox_game_mine_num, WM_SETTEXT, 0, (LPARAM)L"99");
			}
			else {

			}
			break;
		}
		
		}

		break;
	}
		// 窗口关闭消息
	case WM_CLOSE:
		
		DestroyWindow(hwnd[1]);
		break;
		// 窗口销毁消息
	case WM_DESTROY:
		CreateWindow_GameMain(initInstance, initnCmdShow);
		//PostQuitMessage(0); // 发送离开消息给系统
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