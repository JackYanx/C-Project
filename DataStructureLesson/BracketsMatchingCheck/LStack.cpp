#include "LStack.h"
LStack::LStack() {
    initialize();
}
int LStack::initialize() {
    head = new Node;
    head->prior = NULL;
    head->next = NULL;
    rear = head;
    count = 0;
    return 0;
}
int LStack::getCount() {
    return count;
}
int LStack::pop(int& des) {
    if (count < 1) {
        return -1;
    }
    des = rear->data;
    Node* q = rear;
    q->prior->next = NULL;
    rear = rear->prior;
    count--;
    delete q;
}
int LStack::push(int& src) {
    Node* p = new Node;
    p->data = src;
    p->next = NULL;
    p->prior = rear;
    rear->next = p;
    rear = rear->next;
    count++;
    return 0;
}
Node* LStack::headPointer() {
    return head;
}
Node* LStack::rearPointer() {
    return rear;
}
LStack::~LStack() {
    recycleMem();
}
int LStack::recycleMem() {
    int temp;
    while (count != 0) {
        pop(temp);
    }
    delete head;
    head = NULL;
    rear = NULL;
    return 0;
}