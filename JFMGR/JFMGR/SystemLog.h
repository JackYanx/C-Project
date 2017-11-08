
#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H
/*日志记录结构体*/
typedef struct SYSLOG {
	/*操作时间*/
	unsigned int mTime;
	/*操作类型说明如下:
	1为系统启动,2为系统退出,3导入用户数据,4导出用户数据,
	5为新建卡,6为查询卡,7为注销卡,
	8为新增计费标准,9为修改计费标准,
	10为用户上机,11为用户下机,
	12为用户充值,13为用户退费
	*/
	unsigned int operationType;
	/*操作金额*/
	unsigned int money;
	/*操作是否成功*/
	unsigned int isSuccess;
	/*用户ID*/
	char cardID[20];
}SYSLOG;

#endif
