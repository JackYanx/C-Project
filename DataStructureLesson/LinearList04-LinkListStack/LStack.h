#pragma once
#include <iostream>
#include <cstdlib>
#include <memory>

typedef struct Node {
    int data;
    struct Node* prior;
    struct Node* next;
}Node;
/*基于双向链表的栈*/
class LStack {
public:
    LStack();
    int initialize();
    int getCount();
    int pop(int& des);
    int push(int& src);
    const Node* headPointer();
    const Node* rearPointer();
    ~LStack();
private:
    
    int count;
    Node* head;
    Node* rear;
    int recycleMem();
};