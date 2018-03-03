#ifndef _CORELOGIC_H
#define _CORELOGIC_H
#pragma once

#include "GirdBox.h"
enum GameComplexity {
	EASY,
	MEDIUM,
	DIFFICULT,
	CUSTUM
};
enum GameStatus {
	PREPARING,
	UNDERWAY,
	WIN,
	LOSE
};

class MineSweepingGame {
private:
	int boardLength;
	int boardHeight;
	int mineNum;
	int totalNum;
	int uncoveredGBNum;
	unsigned int startTime;
	float mineRating;
	int status;
	int complexity;
	int operationTimes;
	int* girdQueue;
	int** mineMap;
	GirdBox** foregroundBoard, **backgroundBoard;

	void initCb(int*);
	void initGirdBoxes();
	bool checkRationality(int*);
	void generateBoardMap();
	void setSrdMineNum(int, int);
	void uncoverGirdBox(int, int);
	void setFlagOrQuesMark(int, int);
	void onStart();
	void onFinish();
	void onWin();
	void onLose();
public:
	MineSweepingGame(int cmplxy = 0);
	MineSweepingGame(int bl, int bh, int wn);
	~MineSweepingGame();
	void printCb(GirdBox**);
	const GirdBox** getForeGameBoard();
	const GirdBox** getBackGameBoard();
	void tapGirdBox(int x, int y);
	int getGameStatus();
};


#endif // !_CORELOGIC_H


