#include "XFonts.h"

// 设备上下文
HDC fhdc;
// 自定义字体句柄
HFONT hFont;
// 自定义字体
LOGFONT lgf;
// 字体名称
int fWordSize;
TCHAR FontName[32] = {L"微软雅黑"};
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