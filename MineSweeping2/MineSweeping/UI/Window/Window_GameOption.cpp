#include "Window_GameOption.h" 

#include <locale.h>

WCHAR game_rating_drop_down_list_SELECTED_ITEM_NAME[100] = { 0 };
HWND game_rating_drop_down_list;
HWND game_option_confirm_button;
/*
// �������ھ��
HWND hwnd;
// 
HINSTANCE hInstance;
// �豸������
HDC hdc;
// �����ڻ�ͼ��Ϣ�ṹ
PAINTSTRUCT ps;
// ����ע��Ĵ�������
LPCWSTR regClassName = L"WindowClass_GameOption";
// �����ڱ���
LPCWSTR wndTitle = L"��������";
// �����ڻ���λ����Ϣ,X,Y,���,�߶�
wndGeoAttr wga = { 300,150,1010,635 };
*/
void onDraw2();
void onDraw2() {
	game_rating_drop_down_list = CreateWindow(L"combobox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		190, 20, 80, 100, hwnd[1], (HMENU)3300, hInstance[1], NULL);
	onFontRender(game_rating_drop_down_list,14);
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"����");
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"�м�");
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"�߼�");
	SendMessage(game_rating_drop_down_list, CB_ADDSTRING, 0, (LPARAM)L"�Զ���");
	
	game_option_confirm_button = CreateWindow(L"button", L"Confirm", BS_PUSHBUTTON | BS_TEXT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 20, 20, 20,20, hwnd[1],(HMENU)3301, hInstance[1], NULL);


	/*
	GetWindowText(game_rating_drop_down_list, game_rating_drop_down_list_SELECTED_ITEM_NAME, 20);
	FILE* tFile = fopen("D:\\12333.txt", "a+");
	fwprintf(tFile, L"%s", game_rating_drop_down_list_SELECTED_ITEM_NAME);
	fwprintf(tFile, L"%s", L"\n");
	fclose(tFile);
	*/
	/*
	CreateWindow(L"Button", L"���������",
		BS_PUSHBUTTON | BS_TEXT | BS_DEFPUSHBUTTON | BS_USERBUTTON | BS_AUTORADIOBUTTON | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		10, 10, 150, 28,
		hwnd[1], (HMENU)50001,
		(HINSTANCE)GetWindowLongPtr(hwnd[1], GWLP_HINSTANCE),
		NULL);
		*/
		//BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE

}
// ���ڴ�����Ϣ����
LRESULT CALLBACK WindowProc_GameOption(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		hwnd[1] = phwnd;
		onDraw2();
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
	//case WM_PAINT:
		/*
		* ����ֻ��Ҫ������������ǵ� GDI ���ƺ����Ϳ��ԣ������ط�����������
		*/
		//onDraw2();
	//	break;
	//���û������ؼ�(���,����)���¼�������Ӧ
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
		// ���ڹر���Ϣ
	case WM_CLOSE:
		DestroyWindow(hwnd[1]);
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

void RegisterWindow_GameOption(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	// 1)���ô�������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc_GameOption; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName[1];
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 2)ע��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"����ע��ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
}
HWND CreateWindow_GameOption(HINSTANCE hInstance, int nCmdShow) {
	hwnd[1] = CreateWindow(
		regClassName[1],
		wndTitle[1],
		WS_OVERLAPPEDWINDOW,
		wga[1].X, wga[1].Y, wga[1].nWidth, wga[1].nHeight, // �������� x,y,��� �߶� 
		NULL, NULL, hInstance, NULL);
	if (hwnd[1] == NULL)
	{
		MessageBox(NULL, L"���ڴ���ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
	// ��ʾ����
	ShowWindow(hwnd[1], SW_SHOW);
	UpdateWindow(hwnd[1]);
	return hwnd[1];
}