/*
Created by YWT
2017.2.27 15:00
*/

#ifndef RULESINFO_H
#define RULESINFO_H

/*���������,���н���¼��λ��Ϊ��(�����)*/

/*ִ�еļƷѹ���ṹ��*/
typedef struct Rule{
	/*�Ʒѹ���ʼִ��ʱ��*/
	unsigned int startTime;
	/*�Ʒѹ������ִ��ʱ��*/
	unsigned int endTime;
	/*�ù���״̬��0Ϊ��Ч��1Ϊ����ʹ��*/
	int rStatus;
	/*�Ʒѷ��ʣ���λ Ԫ/Сʱ */
	int rating;
	/*ָ����һ���Ʒѹ����ָ��*/
	Rule* next;
}Rule;

#endif