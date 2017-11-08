#undef UNICODE
#include <Windows.h>
#include <cstdio>
//CommCtrl.h用于开启控件视觉特效
#include <CommCtrl.h>
#include <Commdlg.h>
#include <locale.h>
//Windows 8及以上版本可使用该头文件
#include <ShellScalingAPI.h>
//选择文件夹对话框头文件
#include<Shlobj.h>

// 编译对应的lib静态链接库
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Comctl32.lib")
// 开启控件视觉效果
#pragma comment(linker,"\"/manifestdependency:type='win32' \  name = 'Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")
#define EDITOR_OPEN 0x0000A01
#define EDITOR_SAVE 0x0000A02
#define EDITOR_SAVEAS 0x0000A03
#define EDITOR_EXIT 0x0000A04
#define EDITOR_ABOUT 0x0000A05
#define MAX_PATH_LENGTH 300
typedef struct WindowGeometricAttributes {
	int X;
	int Y;
	int nWidth;
	int nHeight;
} wndGeoAttr, WindowGeometricAttributes;
// 窗口句柄
HWND hwnd;
// Edit控件句柄
HWND hwndEdit;
// 窗口实例
HINSTANCE hInstance;
// 设备上下文(用于绘制窗口)
HDC hdc;
// 应用程序注册类名
LPCSTR regClassName = "{AAA1-BBB1-CCCCC1-DDD1}";
// 窗口标题
LPCSTR wndTitle = "文本编辑器";
// 窗口位置以及大小信息
wndGeoAttr wga = {200, 200, 1000, 600};
//
LPSTR initlpCmdLine;
// 窗口消息结构体(用于消息循环)
MSG Msg;
// 自定义字体句柄
HFONT hFont;
// 自定义字体
LOGFONT lgf;
// 字体名称
TCHAR FontName[32] = { "微软雅黑" };
// 文件完整路径
TCHAR strFilename[MAX_PATH];
// 文件句柄
HANDLE hFile;
// 
//TCHAR strSaveFilename[MAX_PATH];
// 文件内容缓冲区
TCHAR fileBuf[0x400000];
// 所打开的文件大小(DWORD即为无符号整数类型)
DWORD hFileSize, readSize;
int selectFile(HWND parentHwnd, LPCSTR filter, LPCSTR InitialDir = NULL) {
	//
	OPENFILENAME ofn = { 0 };
	
	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小  
	ofn.hwndOwner = parentHwnd;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
	ofn.lpstrFilter = filter;// TEXT("所有文件\0*.*\0C/C++ Flie\0*.cpp;*.c;*.h\0\0");//设置过滤  
	ofn.nFilterIndex = 1;//过滤器索引  
	ofn.lpstrFile = strFilename;//接收返回的文件名，注意第一个字符需要为NULL  
	ofn.nMaxFile = sizeof(strFilename);//缓冲区长度  
	ofn.lpstrInitialDir = InitialDir;
	ofn.lpstrTitle = TEXT("请选择一个文件");//使用系统默认标题留空即可  
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;//文件、目录必须存在，隐藏只读选项  
	if (GetOpenFileName(&ofn)) {
		return 0;
	}
	else {
		return -1;
	}
}
int openFile() {
	setlocale(LC_ALL, "");
	/*打开文件*/
	hFile = CreateFile(strFilename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//如果打开失败,返回INVALID_HANDLE_VALUE值
	if (hFile == INVALID_HANDLE_VALUE) {
		return -1;
	}
	//清空缓冲区内容
	memset(fileBuf, 0, sizeof(fileBuf));
	//LPDWORD hFileSize = new DWORD;
	// 获取文件大小
	hFileSize = GetFileSize(hFile, &hFileSize);
	if (hFileSize > 0x400000) {
		MessageBox(NULL, TEXT("选择的文件过大!(大于4MB)"), NULL, MB_ICONERROR);
	}
	// 读取文件,将读到的内容写入文件内容缓冲区
	ReadFile(hFile, fileBuf, hFileSize, &readSize,NULL);
	// 改变Edit空间内容为缓冲区内容
	SetWindowText(hwndEdit, fileBuf);//fileBuf);
	
	return 0;
}
int saveFile() {
	if (hFile == INVALID_HANDLE_VALUE) return -1;
	memset(fileBuf, 0, 0x400000);
	GetWindowText(hwndEdit, fileBuf, 0x400000);
	DWORD textLen = strlen(fileBuf);
	WriteFile(hFile, fileBuf, textLen, NULL, NULL);
	return 0;
}
/*
int saveFileAs(HWND parentHwnd, LPCSTR filter, LPCSTR InitialDir = NULL) {
	OPENFILENAME ofn = { 0 };
	TCHAR strFilename[MAX_PATH] = { 0 };//用于接收文件名  
	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小  
	ofn.hwndOwner = parentHwnd;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
	ofn.lpstrFilter = filter;// TEXT("所有文件\0*.*\0C/C++ Flie\0*.cpp;*.c;*.h\0\0");//设置过滤  
	ofn.nFilterIndex = 1;//过滤器索引  
	ofn.lpstrFile = strSaveFilename;//接收返回的文件名，注意第一个字符需要为NULL  
	ofn.nMaxFile = sizeof(strSaveFilename);//缓冲区长度  
	ofn.lpstrInitialDir = InitialDir;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//目录必须存在，覆盖文件前发出警告  
	ofn.lpstrTitle = TEXT("保存到");//使用系统默认标题留空即可  
	ofn.lpstrDefExt = TEXT("cpp");//默认追加的扩展名  
	if (GetSaveFileName(&ofn)) {
		return 0;
	}
	else {
		return -1;
	}
}
*/
void changeFont(HWND hwnd,int wordSize) {
	HDC hdc = GetDC(hwnd);
	memset(&lgf, 0, sizeof(lgf));
	lgf.lfHeight = GetDeviceCaps(hdc, LOGPIXELSY) * wordSize / 72;
	strcpy(lgf.lfFaceName, FontName);
	hFont = CreateFontIndirect(&lgf);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, 1);
}
// 窗口绘图函数
void onDraw2() {
	HMENU menubar = CreateMenu();
	HMENU menuPop = CreatePopupMenu();
	AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_OPEN, "打开文件");
	AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_SAVE, "保存文件");
	//AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_SAVEAS, "另存为");
	AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_EXIT, "退出编辑器");
	AppendMenu(menubar, MF_STRING | MF_POPUP, (UINT_PTR)menuPop, "操作");
	SetMenu(hwnd, menubar);

	hwndEdit = CreateWindow("edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL |
		ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		0, 0, 1000, 600, hwnd, NULL, NULL, NULL);
	changeFont(hwndEdit,12);
}


void onRender() {
	RECT rect = { 0 };
	GetWindowRect(hwnd, &rect);
	DrawText(GetDC(hwnd), fileBuf, hFileSize, &rect, DT_CALCRECT);
}
// 窗口处理消息过程
LRESULT CALLBACK WindowProcMain(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		hwnd = phwnd;
		onDraw2();
		/*
		break语句很重要!!!
		break语句很重要!!!
		break语句很重要!!!
		重要的话说三次
		*/
		break;
	}
	case WM_PAINT:
	{
		onRender();
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
		switch (LOWORD(wParam))
		{
		case EDITOR_OPEN:
		{
			selectFile(phwnd,"文本文件\0*.txt\0");
			openFile();

			break;
		}
		case EDITOR_SAVE:
		{
			saveFile();
			//selectFile(phwnd, L"所有文件\0*.*\0Text Flie\0*.txt\0");
			break;
		}
		/*
		case EDITOR_SAVEAS:
		{
			saveFileAs(phwnd, "所有文件\0*.*\0Text Flie\0*.txt\0");
			break;
		}
		*/
		case EDITOR_EXIT: {
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			break;
		}
		default:
		{
			//不处理的消息一定要交给defWindowProc处理
			return DefWindowProc(phwnd, msg, wParam, lParam);
			break;
		}
		}
		break;
	}
	// 窗口关闭消息
	case WM_CLOSE:
		DestroyWindow(hwnd);
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


void RegisterWindowMain(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	// 1)配置窗口属性
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProcMain; // 设置第四步的窗口过程回调函数
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 2)注册
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "窗口注册失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // 进程退出
	}
}

HWND CreateWindowMain(HINSTANCE hInstance, int nCmdShow) {
	hwnd = CreateWindow(
		regClassName,
		wndTitle,
		WS_OVERLAPPEDWINDOW,
		wga.X, wga.Y, wga.nWidth, wga.nHeight, // 出现坐标 x,y,宽度 高度 
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "窗口创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // 进程退出
	}
	// 显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return hwnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*禁用WindowsDPI缩放,防止图片和文字模糊,该函数仅能在win8及以上系统中使用*/
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
	// 第一步,注册窗口类
	RegisterWindowMain(hInstance);
	// 第二步:创建窗口
	hwnd = CreateWindowMain(hInstance, nCmdShow);
	// 第三步:消息循环
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}