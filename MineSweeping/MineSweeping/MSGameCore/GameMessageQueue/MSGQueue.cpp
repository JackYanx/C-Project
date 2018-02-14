#include "MSGQueue.h"

Queue::Queue() {
	front = NULL;
	rear = NULL;
	qCount = 0;
}
void Queue::initQueue() {
	front = new QNode;
	front->next = NULL;
	rear = front;
}
void Queue::insertElement(int* e) {
	QNode* p = new QNode;
	p->data = *e;
	p->next = NULL;
	rear->next = p;
	rear = p;
	qCount++;
}
void Queue::deleteElement(int* e) {
	if (qCount < 1) {
		return;
	}
	QNode* p;
	p = front->next;
	*e = p->data;
	front->next = p->next;
	if (rear == p) {
		rear = front;
	}
	delete p;
	qCount--;
}
void Queue::destroySelf() {
	QNode* p = front->next;
	while (p != rear) {
		front->next = p->next;
		delete p;
		p = front->next;
	}
	delete p;
	delete front;
	front = NULL;
	rear = NULL;
	qCount = -1;
}
bool Queue::isEmpty() {
	if (qCount < 1)
		return true;
	else
		return false;
}
int  Queue::getElementNum() {
	return qCount;
}