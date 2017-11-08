#ifndef MSGQUEUE_H
#define MSGQUEUE_H
#pragma once
#include <iostream>
#include "..\GirdBox.h"
enum MSGMessageList {
	MSG_START,
	MSG_FINISH,
	MSG_WIN,
	MSG_LOSE,
	MSG_TAPGIRDBOX,
	MSG_UNCOVERGIRDBOX,
	MSG_SETFLAG,
	MSG_SETUNKNOWN
};
typedef struct tag_MSGMessage {
	int messageType;
	int girdBoxType;
	int posi_X, posi_Y;

}*MSGMessage;

typedef struct QNode {
	int data;
	QNode* next;
}QNode;

class Queue {
public:
	Queue();
	void initQueue();
	void insertElement(int* e);
	void deleteElement(int* e);
	void destroySelf();
	bool isEmpty();
	int  getElementNum();
private:
	/*队列头部指针*/
	QNode* front;
	/*队列尾部指针*/
	QNode* rear;
	/*队列成员计数*/
	int qCount;
};

#endif