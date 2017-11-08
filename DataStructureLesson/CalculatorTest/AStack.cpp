#include "AStack.h"
AStack::AStack() {
    initialize();
}
int AStack::initialize() {
    memset(data, INIT_VALUE, MAX_SIZE * sizeof(int));
    count = 0;
    head = data;
    rear = head;
    return 0;
}
int AStack::getCount() {
    return this->count;
}
int AStack::pop(int& des) {
    if (count == 0) {
        return -1;
    }
    count--;
    des = data[count];
    rear--;
    return 0;
}
int AStack::push(int src) {
    if (count == MAX_SIZE) {
        return -1;
    }
    data[count] = src;
    count++;
    return 0;
}
int AStack::getTop(int& des) {
    if (count == 0) return -1;
    des = data[count-1];
    return 0;
}
const int* AStack::headPointer() {
    return head;
}
const int* AStack::rearPointer() {
    return rear;
}