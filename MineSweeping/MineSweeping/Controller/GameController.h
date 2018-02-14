#pragma once
#include <Windows.h>
#include "../MSGameCore/CoreLogic.h"
typedef struct _GameInfo {
	MineSweepingGame* gameModel;
	int boardLength;
	int boardHeight;
	int mineNum;
	TCHAR playerName[20];
}_GameInfo, GameInfo;
typedef struct _DCInfo {
	HWND cHWND;
	HDC pDC;
	HDC memDC;
	int displayAreaWidth;
	int displayAreaHeight;
}_DCInfo, DCInfo;
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
	BOOL WINAPI initialize(_GameInfo*, _DCInfo*);
	HDC WINAPI drawOnMemDC(HDC);
	BOOL WINAPI actionProc(_ActionInfo*);
	BOOL WINAPI actionProc(ActionType,void*,void*);
	//HDC drawOnPDC();
	//BOOL CALLBACK gameModelProc();
private:
	MineSweepingGame* gameModel;
	HWND cHWND;
	HDC pDC;
	HDC memDC;
	TCHAR playerName[20];
};