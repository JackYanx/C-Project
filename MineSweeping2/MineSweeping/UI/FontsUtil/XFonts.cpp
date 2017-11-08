#include "XFonts.h"

// �豸������
HDC fhdc;
// �Զ���������
HFONT hFont;
// �Զ�������
LOGFONT lgf;
// ��������
int fWordSize;
TCHAR FontName[32] = {L"΢���ź�"};
int onLoadFontFromFile(std::wstring& fontPath) {
	return 0;
}

int onFontRender(HDC hdc, int wordSize) {
	fhdc = hdc;
	fWordSize = wordSize;
	setFont();
	SelectObject(hdc, hFont);
	return 0;
}

int onFontRender(HWND hwnd, int wordSize) {
	fhdc = GetDC(hwnd);
	fWordSize = wordSize;
	setFont();
	SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, 1);
	return 0;
}

int setFont() {
	memset(&lgf, 0, sizeof(lgf));
	lgf.lfHeight = GetDeviceCaps(fhdc, LOGPIXELSY) * fWordSize / 72;
	wcscpy(lgf.lfFaceName, FontName);
	hFont = CreateFontIndirect(&lgf);
	return 0;
}