
#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H
/*��־��¼�ṹ��*/
typedef struct SYSLOG {
	/*����ʱ��*/
	unsigned int mTime;
	/*��������˵������:
	1Ϊϵͳ����,2Ϊϵͳ�˳�,3�����û�����,4�����û�����,
	5Ϊ�½���,6Ϊ��ѯ��,7Ϊע����,
	8Ϊ�����Ʒѱ�׼,9Ϊ�޸ļƷѱ�׼,
	10Ϊ�û��ϻ�,11Ϊ�û��»�,
	12Ϊ�û���ֵ,13Ϊ�û��˷�
	*/
	unsigned int operationType;
	/*�������*/
	unsigned int money;
	/*�����Ƿ�ɹ�*/
	unsigned int isSuccess;
	/*�û�ID*/
	char cardID[20];
}SYSLOG;

#endif
