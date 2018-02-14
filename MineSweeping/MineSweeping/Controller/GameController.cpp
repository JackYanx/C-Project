#include "GameController.h"
#include "../MSGameCore/CoreLogic.h"
#include "../Utils/Log.h"
GameController::GameController() {

}
GameController::~GameController() {

}
BOOL WINAPI GameController::initialize(_GameInfo* gi, _DCInfo* di) {
	if (!gi || !di) {
		errlog(__FILE__,__FUNCTION__,__LINE__,"gi or di is NULL");
	}

	return true;
}
HDC WINAPI GameController::drawOnMemDC(HDC) {
	return NULL;
}
BOOL WINAPI GameController::actionProc(_ActionInfo* ai) {
	return this->actionProc(ai->actionType, ai->param1, ai->param2);
}
BOOL WINAPI GameController::actionProc(ActionType, void*, void*) {
	return true;
}