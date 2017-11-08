typedef struct Gird {
	int gStatus;
	int srdMineCt;
}GirdBox;
enum GirdBoxStatus {
	UNTAPPED,     /*0,未打开*/
	EMPTY,        /*1,空*/
	MINESRD,      /*2,周围有地雷*/
	MINE,         /*3,地雷*/
	FLAGABOVE,    /*4,插了旗子的*/
	UNKNOWEN      /*5,打问号的*/
};
#pragma once
