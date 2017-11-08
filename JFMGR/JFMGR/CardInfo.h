/*
Created by YWT
2017.2.27 15:00
*/

#pragma once

#ifndef CARDINFO_H
#define CARDINFO_H

/*���������,���н���¼��λ��Ϊ��(�����)*/

/*һ�ſ������Ѽ�¼*/
typedef struct CardConsume{
	/*�ô����Ѽ�¼ʱ��*/
	unsigned int mTime;
	/*�ô��ϻ�ʱ��*/
	unsigned int tLength;
	/*�ô����ѽ��*/
	unsigned int consumeMoney;
	/*�ôβ����Ƿ�ɹ�,0Ϊʧ��,1Ϊ�ɹ�*/
	bool isSuccess;
	/*�Ƿ�Ϊ�����Ѽ�¼,0Ϊ����,1Ϊ��ֵ,2Ϊ�˷�*/
	int consumeType;
	/*ָ����һ�μ�¼��ָ��*/
	CardConsume* next;
}CardConsume;

/*��������Ϣ*/
typedef struct Card{
	///*�û�Ψһ��ʶ*///
	//char UID[20];
	/*����*/
	char cardID[20];
	/*����*/
	char cardPassword[20];
	/*������ʱ��*/
	unsigned int createTime;
	/*�����һ��ʹ��ʱ��*/
	unsigned int lastUsageTime;
	/*��ע��ʱ��*/
	unsigned int logOutTime;
	/*�����ܳ�ֵ���*/
	unsigned int totalChargeMoney;
	/*���������ѽ��*/
	unsigned int totalConsumeMoney;
	/*����ǰ�ܽ��*/
	unsigned int remainingMoney;
	/*����ʹ�ô���*/
	unsigned int totalUsageTimes;
	/*����ǰ״̬��0Ϊδ��ʹ�ã�1Ϊ����ʹ�ã�2Ϊ��ע����3Ϊ�쳣ʧЧ,4Ϊϵͳ�˳�ʱ�������ֵ*/
	int cStatus;
	/*���Ѽ�¼��Ŀ*/
	int CCRcount;
	/*��ָ��ָ��ÿ�������Ϣͷ�ṹ��*/
	CardConsume* headCCR;
	/*��ָ��ָ��ÿ�������Ϣ��ǰ�ṹ��*/
	CardConsume* currentCCR;
	/*��ָ��ָ����һ�ſ��ṹ��*/
	Card* next;
}Card;


/*�����û��б�ṹ��*/
typedef struct OnlineUser {
	/*��ʼ�ϻ�ʱ��*/
	unsigned int sTime;
	/*ָ���Ӧ��Ƭ��ָ��*/
	Card* card;
	/*ָ����һ�������û��ṹ���ָ��*/
	OnlineUser* next;
} OnlineUser;

#endif