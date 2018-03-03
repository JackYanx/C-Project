typedef struct Gird {
	int gStatus;
	int srdMineCt;
}GirdBox;
/*游戏方格状态*/
enum GirdBoxStatus {
	UNTAPPED,     /*0,未打开*/
	EMPTY,        /*1,空*/
	MINESRD,      /*2,周围有地雷*/
	MINE,         /*3,地雷*/
	FLAGABOVE,    /*4,插了旗子*/
	UNKNOWEN,     /*5,打问号*/
	MINEEXPLODED, /*6,点到地雷爆炸*/
	NOMINE        /*7,标记后但是没有地雷*/
};
#pragma once
