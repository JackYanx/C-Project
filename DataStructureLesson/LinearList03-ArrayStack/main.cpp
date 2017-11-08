#pragma once
#include <iostream>
#include <cstdlib>
#include <memory>

const int MAX_SIZE = 100;
const int INIT_VALUE = -1;

/*基于数组的栈*/
class AStack {
public:
	AStack();
	int initialize();
	int getCount();
	int pop(int& des);
	int push(int& src);
	const int* headPointer();
	const int* rearPointer();

private:
	int data[MAX_SIZE];
	int count;
	int* head;
	int* rear;
};

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
int AStack::push(int& src) {
	if (count == MAX_SIZE) {
		return -1;
	}
	data[count] = src;
	count++;
	return 0;
}
const int* AStack::headPointer() {
	return head;
}
const int* AStack::rearPointer() {
	return rear;
}
int main(){
    int arr[20] = {
        1,2,2,3,4,
        4,5,9,10,10,
        11,13,16,16,20,
        21,22,22,22,26
    };
    AStack mStack;
    for (int i = 0; i < 20;i++) {
        mStack.push(arr[i]);
    }
    std::cout << "入栈完成!\n栈中所有元素为:\n";
    int elem = 0;
    while (mStack.getCount() != 0) {
        mStack.pop(elem);
        std::cout << elem << "\n";
    }
    return 0;
}