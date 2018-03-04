#include "Window_GameOption.h" 
#include "Window_GameMain.h"

#include <locale.h>

TCHAR combobox_game_rating_select_ITEM_NAME[100] = { 0 };
TCHAR text_game_rating[] = L"�Ѷȵȼ�";
TCHAR text_game_rating_easyyy[] = L"����";
TCHAR text_game_rating_medium[] = L"�м�";
TCHAR text_game_rating_harddd[] = L"�߼�";
TCHAR text_game_rating_custom[] = L"�Զ���";
TCHAR text_game_board_length[] = L"BoardLength";
TCHAR text_game_board_height[] = L"BoardHeight";
TCHAR text_game_mine_num[] = L"MineNum";
TCHAR text_button_game_option_confirm[] = L"ȷ��";

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

	/*������Ϸ�Ѷ�����ѡ��*/
	combobox_game_rating_select = CreateWindow(
		L"ComboBox",
		NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		336, 46, 80, 100,
		hwnd[1],
		(HMENU)3300,
		hInstance[1],
		NULL);
	/*��Ⱦ����Ϊ΢���ź�,�ֺ�14*/
	onFontRender(combobox_game_rating_select,14);

	/*Ϊ����ѡ������ĸ�ѡ��*/
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_easyyy);
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_medium);
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_harddd);
	SendMessage(combobox_game_rating_select, CB_ADDSTRING, 0, (LPARAM)text_game_rating_custom);
	/*����Ĭ���Ѷ�ѡ��Ϊ��0��,����*/
	SendMessage(combobox_game_rating_select, CB_SETCURSEL, 0, 0);


	/*������Ϸ��峤��ֵ�����*/
	inputbox_game_board_length = CreateWindow(
		L"Edit",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NOHIDESEL,
		336, 121, 194, 30,
		hwnd[1],
		(HMENU)3330,
		hInstance[1],
		NULL);
	/*��Ⱦ����Ϊ΢���ź�,�ֺ�15*/
	onFontRender(inputbox_game_board_length, 15);



	/*������Ϸ���߶�ֵ�����*/
	inputbox_game_board_height = CreateWindow(
		L"Edit",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NOHIDESEL,
		336, 181, 194, 30,
		hwnd[1],
		(HMENU)3331,
		hInstance[1],
		NULL);
	/*��Ⱦ����Ϊ΢���ź�, �ֺ�15*/
	onFontRender(inputbox_game_board_height, 15);



	/*������Ϸ�����������*/
	inputbox_game_mine_num = CreateWindow(
		L"Edit",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NOHIDESEL,
		336, 241, 194, 30,
		hwnd[1],
		(HMENU)3332,
		hInstance[1],
		NULL);
	/*��Ⱦ����Ϊ΢���ź�, �ֺ�15*/
	onFontRender(inputbox_game_mine_num, 15);

	/*�������������Ĭ��Ϊ���ɸ���״̬*/
	SendMessage(inputbox_game_board_length, EM_SETREADONLY, 1, 0);
	SendMessage(inputbox_game_board_height, EM_SETREADONLY, 1, 0);
	SendMessage(inputbox_game_mine_num, EM_SETREADONLY, 1, 0);
	SendMessage(inputbox_game_board_length, WM_SETTEXT, 0, (LPARAM)L"16");
	SendMessage(inputbox_game_board_height, WM_SETTEXT, 0, (LPARAM)L"9");
	SendMessage(inputbox_game_mine_num, WM_SETTEXT, 0, (LPARAM)L"10");

	/*������Ϸѡ��ȷ�ϰ�ť*/
	button_game_option_confirm = CreateWindow(
		L"Button",
		L"Confirm",
		BS_PUSHBUTTON | BS_TEXT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		202, 293, 169, 40,
		hwnd[1],
		(HMENU)3301,
		hInstance[1],
		NULL);
	/*��Ⱦ����Ϊ΢���ź�, �ֺ�15*/
	onFontRender(button_game_option_confirm, 15);

}

// ���ڴ�����Ϣ����(�ص�����)
LRESULT CALLBACK WindowProc_GameOption(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	/*
	WM_CREATE �ڴ�������(����CreateWindow����)ʱ������ֻ����һ�Ρ�
	WM_PAINT����Ҫ�ػ�(����UpdateWindow����)ʱ���ã�����δ�����
	WM_CREATE����WM_PAINT 
	*/
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
	case WM_PAINT: {
		PAINTSTRUCT ps;
		/*��ӦWM_PAINTʱ���������������BeginPaint��EndPaint,����WM_PAINT�ᵼ����Ч����ı���������;����������HDC��ͼ������*/
		HDC hdc = BeginPaint(hwnd[1], &ps);

		/*
		* ���ݻ���
		*/
		/*�ֶ����Ļ�ͼ�������������ֺ�*/
		onFontRender(hdc, 15);

		/*��������*/
		TextOut(hdc, 154,  48, text_game_rating,       lstrlenW(text_game_rating));
		TextOut(hdc, 154, 123, text_game_board_length, lstrlenW(text_game_board_length));
		TextOut(hdc, 154, 180, text_game_board_height, lstrlenW(text_game_board_height));
		TextOut(hdc, 154, 240, text_game_mine_num,     lstrlenW(text_game_mine_num));

		/*������ͼ,�ͷŻ�ͼ��*/
		EndPaint(hwnd[1], &ps);
		break;
	}

	//���û������ؼ�(���,����)���¼�������Ӧ
	case WM_COMMAND:
	{

		switch (wParam) {
		/*��Ӧbutton_game_option_confirm����¼�*/
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

		/*��Ӧcombobox_game_rating_selectѡ�ѡ���¼�*/
		/*����Ϊʲô��68836:
		 *CreateWindow����combobox��ؼ�ʱ,��9������Ϊ�˿ؼ����ڲ˵����(���ڱ�ʶ),�����ڻص�������ӦWM_COMMAND��Ϣʱʹ��
		 *WPARAMΪ�޷���32λ����,combobox�ؼ�ѡ�ѡ��������ݱ��ʱ,������Ϣ��wParam�Ĳ���Ϊcombobox�ؼ����ڲ˵����ֵ
		 *���ǽ����������Ϣ��Ϊ��ʮ��λ,combobox�ؼ����ڲ˵������Ϊ��ʮ��λ��������õ����޷���32λ����
		 *����CBN_SELCHANGE��ֵΪ1,combobox_game_rating_select�����ڲ˵����ֵΪ3300 
		 *�����Ʒֱ�Ϊ 0000 0000 0000 0001 �� 0000 1100 1110 0100
		 *���ոߵ�ʮ��λ���������,���Ϊ 0000 0000 0000 0001 0000 1100 1110 0100
		 *��68836
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
		// ���ڹر���Ϣ
	case WM_CLOSE:
		
		DestroyWindow(hwnd[1]);
		break;
		// ����������Ϣ
	case WM_DESTROY:
		CreateWindow_GameMain(initInstance, initnCmdShow);
		//PostQuitMessage(0); // �����뿪��Ϣ��ϵͳ
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