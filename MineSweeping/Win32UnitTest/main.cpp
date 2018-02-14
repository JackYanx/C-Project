#include <Windows.h>

#define IDD_DIALOG1 50011
#define IDC_COMBO1  50012
#define IDC_BUTTON1 50013
#define IDC_EDIT1   50014

#define IDD_DIALOG2 50021
#define IDC_COMBO2  50022
#define IDC_BUTTON2 50023
#define IDC_EDIT2   50024

#define IDD_DIALOG3 50031
#define IDC_COMBO3  50032
#define IDC_BUTTON3 50033
#define IDC_EDIT3   50034

#define IDD_DIALOG4 50041
#define IDC_COMBO4  50042
#define IDC_BUTTON4 50043
#define IDC_EDIT4   50044

#define IDC_BUTTON5 50053

LRESULT CALLBACK Dialog(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	// TODO: Place code here.  
	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, NULL, (DLGPROC)Dialog);
	return 0;
}

LRESULT CALLBACK Dialog(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		UINT uSender;
		uSender = LOWORD(wParam);
		HWND hWndComboBox;
		hWndComboBox = GetDlgItem(hWnd, IDC_COMBO1);
		TCHAR szBuff[200];
		ZeroMemory(szBuff, sizeof(szBuff));
		switch (uSender)
		{
			//CB_ADDSTRING��������������  
		case IDC_BUTTON1:
			GetDlgItemText(hWnd, IDC_EDIT1, szBuff, sizeof(szBuff));
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)szBuff);
			break;

			//CB_ADDSTRING����ָ��λ���������  
		case IDC_BUTTON2:
			GetDlgItemText(hWnd, IDC_EDIT1, szBuff, sizeof(szBuff));
			SendMessage(hWndComboBox, CB_INSERTSTRING, 0, (LPARAM)szBuff);
			break;

		case IDC_BUTTON3:
			SendMessage(hWndComboBox, CB_RESETCONTENT, 0, 0);
			break;

		case IDC_BUTTON4:
			UINT uCount;
			uCount = SendMessage(hWndComboBox, CB_GETCOUNT, 0, 0);
			SetDlgItemInt(hWnd, IDC_EDIT2, uCount, TRUE);
			break;

		case IDC_BUTTON5:
			UINT uSelect;
			uSelect = GetDlgItemInt(hWnd, IDC_EDIT2, NULL, TRUE);
			SendMessage(hWndComboBox, CB_GETLBTEXT, uSelect, (LPARAM)szBuff);
			MessageBox(hWnd, szBuff, L"SHOW", MB_OK | MB_ICONINFORMATION);
			break;

		case IDOK:
			EndDialog(hWnd, lParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hWnd, lParam);
		break;
	}
	return FALSE;
}

int WINAPI wWinMain(HINSTANCE hTheApp, HINSTANCE hPrevApp, LPWSTR lpCmd, int nShow)
{
	PCWSTR cn = L"My"; // ������  
	PCWSTR tt = L"Ӧ�ó���"; // ���ڱ���  
						 // ��ƴ�����  
	WNDCLASS wc = { sizeof(WNDCLASS) };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	LoadIconMetric(hTheApp, IDI_APPLICATION, LIM_SMALL, &wc.hIcon);
	wc.lpszClassName = cn;
	wc.hInstance = hTheApp;
	RegisterClass(&wc); // ע�ᴰ����  
						// ��������  
	HWND hwnd = CreateWindow(cn, tt, WS_OVERLAPPEDWINDOW,
		28, 34, 400, 330, NULL, NULL, hTheApp, NULL);
	if (!hwnd)
	{ /* ������ڴ���ʧ�ܣ�
	  �Ǽ���ִ��Ҳû������
	  ��ʹ�����ʹ�������ɡ�
	  */
		return 0;
	}
	ShowWindow(hwnd, nShow); //��ʾ����  
	UpdateWindow(hwnd); //���´���  
						// ��Ϣѭ��  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //������Ϣ��WindowProc�ص�  
	}
	return 0;
}
