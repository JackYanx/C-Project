typedef struct Gird {
	int gStatus;
	int srdMineCt;
}GirdBox;
/*��Ϸ����״̬*/
enum GirdBoxStatus {
	UNTAPPED,     /*0,δ��*/
	EMPTY,        /*1,��*/
	MINESRD,      /*2,��Χ�е���*/
	MINE,         /*3,����*/
	FLAGABOVE,    /*4,��������*/
	UNKNOWEN,     /*5,���ʺ�*/
	MINEEXPLODED, /*6,�㵽���ױ�ը*/
	NOMINE        /*7,��Ǻ���û�е���*/
};
#pragma once
