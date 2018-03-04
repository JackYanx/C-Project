#include "GameController.h"
#include "../UI/Window/wnd_base.h"
#include "../MSGameCore/CoreLogic.h"
#include "../Utils/Log.h"
#include "../resource1.h"

/*bitmapres*/
//static BITMAP oBitmap_empty;
//static BITMAP oBitmap_flagabove;
//static BITMAP oBitmap_mine;
//static BITMAP oBitmap_mineexploded;
//static BITMAP oBitmap_nomine;
//static BITMAP oBitmap_nums[8];
//static BITMAP oBitmap_num1;
//static BITMAP oBitmap_num2;
//static BITMAP oBitmap_num3;
//static BITMAP oBitmap_num4;
//static BITMAP oBitmap_num5;
//static BITMAP oBitmap_num6;
//static BITMAP oBitmap_num7;
//static BITMAP oBitmap_num8;
//static BITMAP oBitmap_uncovered;
//static BITMAP oBitmap_unknown;

static HBITMAP hBitmap_empty = NULL;
static HBITMAP hBitmap_flagabove = NULL;
static HBITMAP hBitmap_mine = NULL;
static HBITMAP hBitmap_mineexploded = NULL;
static HBITMAP hBitmap_nomine = NULL;
static HBITMAP hBitmap_nums[8] = { 0 };
static HBITMAP hBitmap_num1 = NULL;
static HBITMAP hBitmap_num2 = NULL;
static HBITMAP hBitmap_num3 = NULL;
static HBITMAP hBitmap_num4 = NULL;
static HBITMAP hBitmap_num5 = NULL;
static HBITMAP hBitmap_num6 = NULL;
static HBITMAP hBitmap_num7 = NULL;
static HBITMAP hBitmap_num8 = NULL;
static HBITMAP hBitmap_uncovered = NULL;
static HBITMAP hBitmap_unknown = NULL;


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
	/*获取设备上下文*/
	HDC hdc = GetDC(hwnd);

	HDC backgroundDC = CreateCompatibleDC(hdc);
	HBITMAP backgroundBitmap = CreateCompatibleBitmap(hdc, canveWidthPix, canveHeightPix);

	ReleaseDC(hwnd, hdc);
	SelectObject(backgroundDC, backgroundBitmap);
	return true;
}
bool selectHBmpObject(HDC& drawDC,const GirdBox& gb) {
	if (!drawDC) {
		errlog(__FUNCTION__, "HDC nullptr");
		return false;
	}
	switch (gb.gStatus)
	{
	case GirdBoxStatus::EMPTY:
		SelectObject(drawDC, hBitmap_empty);
		break;
	case GirdBoxStatus::MINE:
		SelectObject(drawDC, hBitmap_mine);
		break;
	case GirdBoxStatus::MINESRD:
		SelectObject(drawDC, hBitmap_nums[gb.srdMineCt-1]);
		break;
	case GirdBoxStatus::UNTAPPED:
		SelectObject(drawDC, hBitmap_uncovered);
		break;
	case GirdBoxStatus::FLAGABOVE:
		SelectObject(drawDC, hBitmap_flagabove);
		break;
	case GirdBoxStatus::UNKNOWEN:
		SelectObject(drawDC, hBitmap_unknown);
		break;
	case GirdBoxStatus::MINEEXPLODED:
		SelectObject(drawDC, hBitmap_mineexploded);
		break;
	case GirdBoxStatus::NOMINE:
		SelectObject(drawDC, hBitmap_nomine);
		break;
	default:
		/*严重错误*/
		errlog(__FUNCTION__,"GAMEMODEL ERROR OCCURED. APPLICATION EXIT");
		MessageBox(NULL, L"error!", L"GAME ERROR", MB_ICONHAND);
		exit(-1);
		return false;
	}
	return true;
}
BOOL WINAPI GameController::draw(HDC pDC,HDC bufferDC, HDC drawDC, HBITMAP bufferBmp) {
	/*获取设备上下文*/
	//HDC bufferDC = CreateCompatibleDC(pDC);
	//HDC drawDC = CreateCompatibleDC(pDC);
	//HBITMAP bufferBmp = CreateCompatibleBitmap(pDC, canveWidthPix, canveHeightPix);
	//SelectObject(bufferDC, bufferBmp);
	
	const GirdBox** backMap = gameModel->getBackGameBoard();
	
	for (int i = 0; i < boardLength;i++) {
		for (int j = 0; j < boardHeight;j++) {
			selectHBmpObject(drawDC, backMap[i][j]);
			BitBlt(bufferDC, i * GirdImageWidthPix + boardPosiX, j * GirdImageHeightPix + boardPosiY, GirdImageWidthPix, GirdImageHeightPix, drawDC, 0, 0, SRCCOPY);
		}
	}
	
	BitBlt(pDC, 0, 0, canveWidthPix, canveHeightPix, bufferDC, 0, 0, SRCCOPY);

	//DeleteDC(drawDC);
	//DeleteDC(bufferDC);
	//DeleteObject(bufferBmp);
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
	boardPosiX = MarginLeftPix;
	boardPosiY = MarginTopPix;
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
	
	hBitmap_empty = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-empty.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_empty, sizeof(Bitmap), &oBitmap_empty);

	hBitmap_flagabove = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-flagabove.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_flagabove, sizeof(Bitmap), &oBitmap_flagabove);

	hBitmap_mine = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-mine.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_mine, sizeof(Bitmap), &oBitmap_mine);

	hBitmap_mineexploded = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-mineexploded.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_mineexploded, sizeof(Bitmap), &oBitmap_mineexploded);

	hBitmap_nomine = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-nomine.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_nomine, sizeof(Bitmap), &oBitmap_nomine);

	hBitmap_num1 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num1, sizeof(Bitmap), &oBitmap_num1);
	hBitmap_nums[0] = hBitmap_num1;

	hBitmap_num2 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num2, sizeof(Bitmap), &oBitmap_num2);
	hBitmap_nums[1] = hBitmap_num2;

	hBitmap_num3 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num3, sizeof(Bitmap), &oBitmap_num3);
	hBitmap_nums[2] = hBitmap_num3;

	hBitmap_num4 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num4, sizeof(Bitmap), &oBitmap_num4);
	hBitmap_nums[3] = hBitmap_num4;

	hBitmap_num5 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num5, sizeof(Bitmap), &oBitmap_num5);
	hBitmap_nums[4] = hBitmap_num5;

	hBitmap_num6 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num6, sizeof(Bitmap), &oBitmap_num6);
	hBitmap_nums[5] = hBitmap_num6;

	hBitmap_num7 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num7.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num7, sizeof(Bitmap), &oBitmap_num7);
	hBitmap_nums[6] = hBitmap_num7;

	hBitmap_num8 = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-num8.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_num8, sizeof(Bitmap), &oBitmap_num8);
	hBitmap_nums[7] = hBitmap_num8;

	hBitmap_uncovered = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-uncovered.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_uncovered, sizeof(Bitmap), &oBitmap_uncovered);

	hBitmap_unknown = (HBITMAP)LoadImage(cHINSTANCE, L"res\\bitmap\\msg-unknown.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//GetObject(hBitmap_unknown, sizeof(Bitmap), &oBitmap_unknown);
	inflog("Bitmap Res Loaded");
	return true;
}