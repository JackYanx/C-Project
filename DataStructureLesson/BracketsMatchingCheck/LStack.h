#pragma once
#include <iostream>
#include <cstdlib>
#include <memory>

typedef struct Node {
    int data;
    int num;
    struct Node* prior;
    struct Node* next;
}Node;
/*����˫�������ջ*/
class LStack {
public:
    LStack();
    int initialize();
    int getCount();
    int pop(int& des);
    int push(int& src);
    Node* headPointer();
    Node* rearPointer();
    ~LStack();
private:
    
    int count;
    Node* head;
    Node* rear;
    int recycleMem();
};