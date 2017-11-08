#undef UNICODE
#include <Windows.h>
#include <cstdio>
//CommCtrl.h���ڿ����ؼ��Ӿ���Ч
#include <CommCtrl.h>
#include <Commdlg.h>
#include <locale.h>
//Windows 8�����ϰ汾��ʹ�ø�ͷ�ļ�
#include <ShellScalingAPI.h>
//ѡ���ļ��жԻ���ͷ�ļ�
#include<Shlobj.h>

// �����Ӧ��lib��̬���ӿ�
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Comctl32.lib")
// �����ؼ��Ӿ�Ч��
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
// ���ھ��
HWND hwnd;
// Edit�ؼ����
HWND hwndEdit;
// ����ʵ��
HINSTANCE hInstance;
// �豸������(���ڻ��ƴ���)
HDC hdc;
// Ӧ�ó���ע������
LPCSTR regClassName = "{AAA1-BBB1-CCCCC1-DDD1}";
// ���ڱ���
LPCSTR wndTitle = "�ı��༭��";
// ����λ���Լ���С��Ϣ
wndGeoAttr wga = {200, 200, 1000, 600};
//
LPSTR initlpCmdLine;
// ������Ϣ�ṹ��(������Ϣѭ��)
MSG Msg;
// �Զ���������
HFONT hFont;
// �Զ�������
LOGFONT lgf;
// ��������
TCHAR FontName[32] = { "΢���ź�" };
// �ļ�����·��
TCHAR strFilename[MAX_PATH];
// �ļ����
HANDLE hFile;
// 
//TCHAR strSaveFilename[MAX_PATH];
// �ļ����ݻ�����
TCHAR fileBuf[0x400000];
// ���򿪵��ļ���С(DWORD��Ϊ�޷�����������)
DWORD hFileSize, readSize;
int selectFile(HWND parentHwnd, LPCSTR filter, LPCSTR InitialDir = NULL) {
	//
	OPENFILENAME ofn = { 0 };
	
	ofn.lStructSize = sizeof(OPENFILENAME);//�ṹ���С  
	ofn.hwndOwner = parentHwnd;//ӵ���Ŵ��ھ����ΪNULL��ʾ�Ի����Ƿ�ģ̬�ģ�ʵ��Ӧ����һ�㶼Ҫ��������  
	ofn.lpstrFilter = filter;// TEXT("�����ļ�\0*.*\0C/C++ Flie\0*.cpp;*.c;*.h\0\0");//���ù���  
	ofn.nFilterIndex = 1;//����������  
	ofn.lpstrFile = strFilename;//���շ��ص��ļ�����ע���һ���ַ���ҪΪNULL  
	ofn.nMaxFile = sizeof(strFilename);//����������  
	ofn.lpstrInitialDir = InitialDir;
	ofn.lpstrTitle = TEXT("��ѡ��һ���ļ�");//ʹ��ϵͳĬ�ϱ������ռ���  
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;//�ļ���Ŀ¼������ڣ�����ֻ��ѡ��  
	if (GetOpenFileName(&ofn)) {
		return 0;
	}
	else {
		return -1;
	}
}
int openFile() {
	setlocale(LC_ALL, "");
	/*���ļ�*/
	hFile = CreateFile(strFilename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//�����ʧ��,����INVALID_HANDLE_VALUEֵ
	if (hFile == INVALID_HANDLE_VALUE) {
		return -1;
	}
	//��ջ���������
	memset(fileBuf, 0, sizeof(fileBuf));
	//LPDWORD hFileSize = new DWORD;
	// ��ȡ�ļ���С
	hFileSize = GetFileSize(hFile, &hFileSize);
	if (hFileSize > 0x400000) {
		MessageBox(NULL, TEXT("ѡ����ļ�����!(����4MB)"), NULL, MB_ICONERROR);
	}
	// ��ȡ�ļ�,������������д���ļ����ݻ�����
	ReadFile(hFile, fileBuf, hFileSize, &readSize,NULL);
	// �ı�Edit�ռ�����Ϊ����������
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
	TCHAR strFilename[MAX_PATH] = { 0 };//���ڽ����ļ���  
	ofn.lStructSize = sizeof(OPENFILENAME);//�ṹ���С  
	ofn.hwndOwner = parentHwnd;//ӵ���Ŵ��ھ����ΪNULL��ʾ�Ի����Ƿ�ģ̬�ģ�ʵ��Ӧ����һ�㶼Ҫ��������  
	ofn.lpstrFilter = filter;// TEXT("�����ļ�\0*.*\0C/C++ Flie\0*.cpp;*.c;*.h\0\0");//���ù���  
	ofn.nFilterIndex = 1;//����������  
	ofn.lpstrFile = strSaveFilename;//���շ��ص��ļ�����ע���һ���ַ���ҪΪNULL  
	ofn.nMaxFile = sizeof(strSaveFilename);//����������  
	ofn.lpstrInitialDir = InitialDir;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//Ŀ¼������ڣ������ļ�ǰ��������  
	ofn.lpstrTitle = TEXT("���浽");//ʹ��ϵͳĬ�ϱ������ռ���  
	ofn.lpstrDefExt = TEXT("cpp");//Ĭ��׷�ӵ���չ��  
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
// ���ڻ�ͼ����
void onDraw2() {
	HMENU menubar = CreateMenu();
	HMENU menuPop = CreatePopupMenu();
	AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_OPEN, "���ļ�");
	AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_SAVE, "�����ļ�");
	//AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_SAVEAS, "���Ϊ");
	AppendMenu(menuPop, MF_STRING, (UINT_PTR)EDITOR_EXIT, "�˳��༭��");
	AppendMenu(menubar, MF_STRING | MF_POPUP, (UINT_PTR)menuPop, "����");
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
// ���ڴ�����Ϣ����
LRESULT CALLBACK WindowProcMain(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		hwnd = phwnd;
		onDraw2();
		/*
		break������Ҫ!!!
		break������Ҫ!!!
		break������Ҫ!!!
		��Ҫ�Ļ�˵����
		*/
		break;
	}
	case WM_PAINT:
	{
		onRender();
		break;
	}
	// ���ڻ�����Ϣ
	/*ʹ��WS_EX_LAYERED��񴰿ڲ���� WM_PAINT ��Ϣ������Ӧ,��ͼ������WM_CREATE״̬�µ�UpdateLayeredWindow()��������*/
	//case WM_PAINT:
	/*
	* ����ֻ��Ҫ������������ǵ� GDI ���ƺ����Ϳ��ԣ������ط�����������
	*/
	//onDraw2();
	//	break;
	//���û������ؼ�(���,����)���¼�������Ӧ
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case EDITOR_OPEN:
		{
			selectFile(phwnd,"�ı��ļ�\0*.txt\0");
			openFile();

			break;
		}
		case EDITOR_SAVE:
		{
			saveFile();
			//selectFile(phwnd, L"�����ļ�\0*.*\0Text Flie\0*.txt\0");
			break;
		}
		/*
		case EDITOR_SAVEAS:
		{
			saveFileAs(phwnd, "�����ļ�\0*.*\0Text Flie\0*.txt\0");
			break;
		}
		*/
		case EDITOR_EXIT: {
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			break;
		}
		default:
		{
			//���������Ϣһ��Ҫ����defWindowProc����
			return DefWindowProc(phwnd, msg, wParam, lParam);
			break;
		}
		}
		break;
	}
	// ���ڹر���Ϣ
	case WM_CLOSE:
		DestroyWindow(hwnd);
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
	return 0;
}


void RegisterWindowMain(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	// 1)���ô�������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProcMain; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 2)ע��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "����ע��ʧ��!", "����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
}

HWND CreateWindowMain(HINSTANCE hInstance, int nCmdShow) {
	hwnd = CreateWindow(
		regClassName,
		wndTitle,
		WS_OVERLAPPEDWINDOW,
		wga.X, wga.Y, wga.nWidth, wga.nHeight, // �������� x,y,��� �߶� 
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "���ڴ���ʧ��!", "����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
	// ��ʾ����
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return hwnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*����WindowsDPI����,��ֹͼƬ������ģ��,�ú���������win8������ϵͳ��ʹ��*/
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
	// ��һ��,ע�ᴰ����
	RegisterWindowMain(hInstance);
	// �ڶ���:��������
	hwnd = CreateWindowMain(hInstance, nCmdShow);
	// ������:��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}