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
	/*����ͷ��ָ��*/
	QNode* front;
	/*����β��ָ��*/
	QNode* rear;
	/*���г�Ա����*/
	int qCount;
};

#endif // 

