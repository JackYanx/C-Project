#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#pragma once
#include <iostream>
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

#endif // 

