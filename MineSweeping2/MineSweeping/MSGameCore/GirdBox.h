typedef struct Gird {
	int gStatus;
	int srdMineCt;
}GirdBox;
enum GirdBoxStatus {
	UNTAPPED,     /*0,δ��*/
	EMPTY,        /*1,��*/
	MINESRD,      /*2,��Χ�е���*/
	MINE,         /*3,����*/
	FLAGABOVE,    /*4,�������ӵ�*/
	UNKNOWEN      /*5,���ʺŵ�*/
};
#pragma once
