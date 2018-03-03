#pragma once
#include <Windows.h>
#include "../MSGameCore/CoreLogic.h"
typedef struct _GameInfo {
	MineSweepingGame* gameModel;
	int boardLength;
	int boardHeight;
	int mineNum;
	TCHAR* playerName;
}_GameInfo, GameInfo;
/*
typedef struct _DCInfo {
	HWND cHWND;
	HDC* pDC_ptr;
	HDC* memDC_ptr;
	int* displayAreaWidth_ptr;
	int* displayAreaHeight_ptr;
}_DCInfo, DCInfo;
*/
enum ActionType
{
	MOUSE_CLICK,
	
};
typedef struct _ActionInfo {
	ActionType actionType;
	void* param1;
	void* param2;
}_ActionInfo, ActionInfo;

class GameController final {
public:
	GameController();
	~GameController();
	BOOL WINAPI initialize(_GameInfo*, HWND, HINSTANCE, int*, int*);
	/*Draw on Physical Device Context*/
	BOOL WINAPI draw(HWND);
	BOOL WINAPI draw(HDC,HDC,HDC,HBITMAP);
	BOOL WINAPI actionProc(_ActionInfo*);
	BOOL WINAPI actionProc(ActionType,void*,void*);
	//HDC drawOnPDC();
	//BOOL CALLBACK gameModelProc();
private:
	MineSweepingGame* gameModel;
	//Game Board Size
	int boardLength;
	int boardHeight;
	int mineNum;
	//
	static const int MarginTopPix = 40;
	static const int MarginBottomPix = 70;
	static const int MarginLeftPix = 30;
	static const int MarginRightPix = 30;
	static const int GirdImageWidthPix = 16;
	static const int GirdImageHeightPix = 16;
	//HDC Pixel Size
	int canveWidthPix;
	int canveHeightPix;
	int boardPosiX, boardPosiY;
	HWND cHWND;
	HINSTANCE cHINSTANCE;
	TCHAR playerName[20];
	BOOL initCanve();
	BOOL calculateCanveSize();
	BOOL loadRes();
};