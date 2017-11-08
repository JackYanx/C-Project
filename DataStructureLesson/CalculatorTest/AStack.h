#pragma once
#include "base.h"
const int MAX_SIZE = 100;
const int INIT_VALUE = 0;

/*基于数组的栈*/
class AStack {
public:
    AStack();
    int initialize();
    int getCount();
    int pop(int& des);
    int push(int src);
    int getTop(int& des);
    const int* headPointer();
    const int* rearPointer();

private:
    int data[MAX_SIZE];
    int count;
    int* head;
    int* rear;
};