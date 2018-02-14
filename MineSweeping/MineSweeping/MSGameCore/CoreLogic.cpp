#include <ctime>
#include <iostream>
#include "CoreLogic.h"
#include "..\Utils\ToolUtil.h"

int defaultSetting[3][3] = {
	{16,  9, 10},
	{16, 16, 40},
	{30, 16, 99},
};

MineSweepingGame::MineSweepingGame(int cmplxy) {
	memset(this, 0, sizeof(MineSweepingGame));
	initCb(defaultSetting[cmplxy]);
	complexity = cmplxy;
}
MineSweepingGame::MineSweepingGame(int bl, int bh, int wn) {
	memset(this, 0, sizeof(MineSweepingGame));
	int custumSetting[] = {bl, bh, wn};
	if (checkRationality(custumSetting)) {
		initCb(custumSetting);
		complexity = 3;
	}
	else {
		initCb(defaultSetting[0]);
		complexity = 0;
	}
}
void MineSweepingGame::initCb(int* paramSetting) {
	boardLength = paramSetting[0];
	boardHeight = paramSetting[1];
	mineNum = paramSetting[2];
	totalNum = boardLength * boardHeight;
	uncoveredGBNum = 0;
	startTime = (unsigned int)time(0);
	mineRating = 1.0f * mineNum / (boardLength * boardHeight);
	status = GameStatus::PREPARING;
	operationTimes = 0;
	initGirdBoxes();
	generateBoardMap();

}
void MineSweepingGame::initGirdBoxes() {
	int i, j;
	foregroundBoard = new GirdBox*[boardLength];
	backgroundBoard = new GirdBox*[boardLength];
	for (i = 0; i < boardLength; i++) {
		foregroundBoard[i] = new GirdBox[boardHeight];
		backgroundBoard[i] = new GirdBox[boardHeight];
		memset(foregroundBoard[i], 0, sizeof(GirdBox) * boardHeight);
		memset(backgroundBoard[i], 0, sizeof(GirdBox) * boardHeight);
		for (j = 0; j < boardHeight; j++) {
			backgroundBoard[i][j].gStatus = GirdBoxStatus::EMPTY;
		}
	}
}
bool MineSweepingGame::checkRationality(int* paramSetting) {
	if (paramSetting[0] < 10 || paramSetting[1] < 10 || paramSetting[0] > 40 || paramSetting[1] > 40) {
		return 0;
	}
	if (paramSetting[2] < 10 || paramSetting[2] > 100) {
		return 0;
	}
	float mineRating = 1.0f * paramSetting[2] / (paramSetting[0] * paramSetting[1]);
	if (mineRating > 0.65f) {
		return 0;
	}
	return 1;
}
void MineSweepingGame::generateBoardMap() {
	int i;

	girdQueue = new int[totalNum];
	for (i = 0; i < totalNum;i++) {
		girdQueue[i] = i;
	}
	shuffle(girdQueue,totalNum);

	//mineMap = new int*[mineNum];
	int minePosiX, minePosiY;
	for (i = 0; i < mineNum;i++) {
		//mineMap[i] = new int[2];
		//mineMap[i][0] = girdQueue[i] / boardLength;
		//mineMap[i][1] = girdQueue[i] % boardLength;
		minePosiX = girdQueue[i] % boardLength;
		minePosiY = girdQueue[i] / boardLength;
		backgroundBoard[minePosiX][minePosiY].gStatus = GirdBoxStatus::MINE;
		setSrdMineNum(minePosiX, minePosiY);
	}
}
void MineSweepingGame::setSrdMineNum(int x, int y) {
	if (x != 0 && y != 0 ) {
		if (backgroundBoard[x - 1][y - 1].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x - 1][y - 1].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x - 1][y - 1].srdMineCt++;
		}
	}
	if (x != 0) {
		if (backgroundBoard[x - 1][y].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x - 1][y].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x - 1][y].srdMineCt++;
		}
	}
	if (x != 0 && y != boardHeight - 1) {
		if (backgroundBoard[x - 1][y + 1].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x - 1][y + 1].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x - 1][y + 1].srdMineCt++;
		}
	}
	if (y != 0) {
		if (backgroundBoard[x][y - 1].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x][y - 1].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x][y - 1].srdMineCt++;
		}
	}
	if (y != boardHeight - 1) {
		if (backgroundBoard[x][y + 1].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x][y + 1].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x][y + 1].srdMineCt++;
		}
	}
	if (x != boardLength - 1 && y != 0) {
		if (backgroundBoard[x + 1][y - 1].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x + 1][y - 1].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x + 1][y - 1].srdMineCt++;
		}
	}
	if (x != boardLength - 1) {
		if (backgroundBoard[x + 1][y].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x + 1][y].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x + 1][y].srdMineCt++;
		}
	}
	if (x != boardLength - 1 && y != boardHeight - 1) {
		if (backgroundBoard[x + 1][y + 1].gStatus != GirdBoxStatus::MINE) {
			backgroundBoard[x + 1][y + 1].gStatus = GirdBoxStatus::MINESRD;
			backgroundBoard[x + 1][y + 1].srdMineCt++;
		}
	}
}
void MineSweepingGame::printCb(GirdBox** boardMap) {

}
void MineSweepingGame::tapGirdBox(int x, int y) {
	if (foregroundBoard[x][y].gStatus != GirdBoxStatus::FLAGABOVE) {
		return;
	}
	if (foregroundBoard[x][y].gStatus != GirdBoxStatus::UNTAPPED) {
		return;
	}
	if (backgroundBoard[x][y].gStatus == GirdBoxStatus::EMPTY || backgroundBoard[x][y].gStatus == GirdBoxStatus::MINESRD) {
		uncoverGirdBox(x, y);
		if (uncoveredGBNum == totalNum - mineNum) {
			this->status = GameStatus::WIN;
		}
		return;
	}
	if (backgroundBoard[x][y].gStatus == GirdBoxStatus::MINE) {
		uncoverGirdBox(x, y);
		this->status = GameStatus::LOSE;
		return;
	}
}
int MineSweepingGame::getGameStatus() {
	return 0;
}
void MineSweepingGame::uncoverGirdBox(int x, int y) {
	/*判断点击的方格是否为已打开状态,插旗子状态,有问号待定状态,如果是,不进行打开递归*/
	if (foregroundBoard[x][y].gStatus != GirdBoxStatus::UNTAPPED || foregroundBoard[x][y].gStatus == GirdBoxStatus::FLAGABOVE || foregroundBoard[x][y].gStatus == GirdBoxStatus::UNKNOWEN) {
		return;
	}
	/*判断所打开的方格是否为地雷*/
	if (backgroundBoard[x][y].gStatus == GirdBoxStatus::MINE) {
		foregroundBoard[x][y].gStatus = GirdBoxStatus::MINE;
		uncoveredGBNum++;
		return;
	}
	/*判断所打开的方格是否为数字(周围有地雷)*/
	if (backgroundBoard[x][y].gStatus == GirdBoxStatus::MINESRD) {
		foregroundBoard[x][y].gStatus = GirdBoxStatus::MINESRD;
		foregroundBoard[x][y].srdMineCt = backgroundBoard[x][y].srdMineCt;
		uncoveredGBNum++;
		return;
	}
	/*默认情况按照空方块进行处理*/
	foregroundBoard[x][y].gStatus = GirdBoxStatus::EMPTY;
	uncoveredGBNum++;
	/*对当前方格上下左右进行递归打开*/
	if (x != 0) {
		uncoverGirdBox(x - 1, y);
	}
	if (y != 0) {
		uncoverGirdBox(x, y - 1);
	}
	if (x != boardLength - 1) {
		uncoverGirdBox(x + 1, y);
	}
	if (y != boardHeight - 1) {
		uncoverGirdBox(x, y + 1);
	}
}
void MineSweepingGame::setFlagOrQuesMark(int x, int y) {
	if (foregroundBoard[x][y].gStatus == GirdBoxStatus::UNTAPPED) {
		foregroundBoard[x][y].gStatus = GirdBoxStatus::FLAGABOVE;
		return;
	}
	if (foregroundBoard[x][y].gStatus == GirdBoxStatus::FLAGABOVE) {
		foregroundBoard[x][y].gStatus = GirdBoxStatus::UNKNOWEN;
		return;
	}
	if (foregroundBoard[x][y].gStatus == GirdBoxStatus::UNKNOWEN) {
		foregroundBoard[x][y].gStatus = GirdBoxStatus::UNTAPPED;
		return;
	}
}
void MineSweepingGame::onStart() {

}
void MineSweepingGame::onFinish() {

}
void MineSweepingGame::onWin() {

}
void MineSweepingGame::onLose() {

}
MineSweepingGame::~MineSweepingGame() {

}