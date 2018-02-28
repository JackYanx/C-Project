#include "GameController.h"
#include "../UI/Window/wnd_base.h"
#include "../MSGameCore/CoreLogic.h"
#include "../Utils/Log.h"
#include "../resource1.h"

/*bitmapres*/
static HBITMAP bitmap_empty = NULL;
static HBITMAP bitmap_flagabove = NULL;
static HBITMAP bitmap_mine = NULL;
static HBITMAP bitmap_mineexploded = NULL;
static HBITMAP bitmap_nomine = NULL;
static HBITMAP bitmap_num1 = NULL;
static HBITMAP bitmap_num2 = NULL;
static HBITMAP bitmap_num3 = NULL;
static HBITMAP bitmap_num4 = NULL;
static HBITMAP bitmap_num5 = NULL;
static HBITMAP bitmap_num6 = NULL;
static HBITMAP bitmap_num7 = NULL;
static HBITMAP bitmap_num8 = NULL;
static HBITMAP bitmap_uncovered = NULL;
static HBITMAP bitmap_unknown = NULL;


GameController::GameController() {

}
GameController::~GameController() {

}

BOOL WINAPI GameController::initialize(_GameInfo* gi, HWND hwnd, HINSTANCE hinstance,int* cx_ptr, int* cy_ptr) {
	if (!gi || !hwnd) {
		errlog(__FILE__,__FUNCTION__,__LINE__,"nullptr: gi or hwnd");
		return NULL;
	}
	gameModel = gi->gameModel;
	memcpy(playerName, gi->playerName, sizeof(TCHAR) * 20);
	boardLength = gi->boardLength;
	boardHeight = gi->boardHeight;
	mineNum = gi->mineNum;
	cHWND = hwnd;
	cHINSTANCE = hinstance;
	initCanve();
	*cx_ptr = canveWidthPix;
	*cy_ptr = canveHeightPix;
	loadRes();
	return true;
}

BOOL WINAPI GameController::draw(HWND hwnd) {

	return true;
}
BOOL WINAPI GameController::actionProc(_ActionInfo* ai) {
	return this->actionProc(ai->actionType, ai->param1, ai->param2);
}
BOOL WINAPI GameController::actionProc(ActionType, void*, void*) {
	return true;
}
BOOL GameController::initCanve() {
	calculateCanveSize();
	set_window_size(cHWND, canveWidthPix, canveHeightPix);
	/*
	HDC hdc = GetDC(cHWND);
	HDC backgroundDC = CreateCompatibleDC(hdc);
	HBITMAP backgroundBitmap = CreateCompatibleBitmap(hdc, canveWidthPix, canveHeightPix);
	ReleaseDC(cHWND, hdc);
	SelectObject(backgroundDC, backgroundBitmap);
	*/
	return true;
}
BOOL GameController::calculateCanveSize() {
	canveWidthPix = MarginLeftPix + MarginRightPix + boardLength * GirdImageWidthPix;
	canveHeightPix = MarginTopPix + MarginBottomPix + boardHeight * GirdImageHeightPix;
	return true;
}
BOOL GameController::loadRes() {
	bitmap_empty = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-empty.bmp");
	bitmap_flagabove = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-flagabove.bmp");
	bitmap_mine = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-mine.bmp");
	bitmap_mineexploded = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-mineexploded.bmp");
	bitmap_nomine = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-nomine.bmp");
	bitmap_num1 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num1.bmp");
	bitmap_num2 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num2.bmp");
	bitmap_num3 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num3.bmp");
	bitmap_num4 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num4.bmp");
	bitmap_num5 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num5.bmp");
	bitmap_num6 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num6.bmp");
	bitmap_num7 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num7.bmp");
	bitmap_num8 = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-num8.bmp");
	bitmap_uncovered = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-uncovered.bmp");
	bitmap_unknown = LoadBitmap(cHINSTANCE, L"res\\bitmap\\msg-unknown.bmp");
	inflog("Bitmap Res Loaded");
	return true;
}