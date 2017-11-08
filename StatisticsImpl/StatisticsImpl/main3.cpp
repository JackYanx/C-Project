/*
* @author: 软工m1603严伟滔
* @time: 2017.09.27
* CPP File
* 结构图在附件中
*/

#include<cstdio>
typedef struct Node {
	int data;
	struct Node* next;
}Node;
Node* createLoopLinkList(int* arr, int n);
void checkDifferent(Node* head);
int AbsInt(int a);
void printArray(int* arr, int n);
void printLoopLinkList(Node* head);
int main() {
	int arr1[10] = {
		3,12,43,67,6,
		99,1,2,7,24
	};
	int arr2[10] = {
		1,2,3,3,1,
		0,2,1,2,3
	};
	printArray(arr1, 10);
	printArray(arr2, 10);
	Node* list1 = createLoopLinkList(arr1, 10);
	Node* list2 = createLoopLinkList(arr2, 10);
	printLoopLinkList(list1);
	checkDifferent(list1);
	printLoopLinkList(list2);
	checkDifferent(list2);
	return 0;
}
Node* createLoopLinkList(int* arr, int n) {
	Node* head = new Node;
	Node* p = head;
	int i;
	for (i = 0; i < n - 1; i++) {
		p->data = arr[i];
		p->next = new Node;
		p = p->next;
	}
	p->data = arr[i];
	p->next = head;
	return head;
}
void checkDifferent(Node* head) {
	bool differentLessThan2 = true;
	Node* p = head, *q = p->next;
	while (p->next != head) {
		if (AbsInt(p->data - q->data) > 2) {
			differentLessThan2 = false;
			break;
		}
		p = p->next;
		q = q->next;
	}
	if (AbsInt(p->data - q->data) > 2) {
		differentLessThan2 = false;
	}
	if (differentLessThan2) {
		printf("该循环链表环上任意两个相邻元素值之差的绝对值之差没有超过2.\n");
	}
	else {
		printf("该循环链表环上任意两个相邻元素值之差的绝对值之差超过2.\n");
	}
}
int AbsInt(int a) {
	int out = a >> 31;
	return ((a ^ out) - out);
}
void printArray(int* arr, int n) {
	printf("数组元素为:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void printLoopLinkList(Node* head) {
	printf("生成循环链表的元素为:\n");
	Node* p = head;
	while (p->next != head) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("%d", p->data);
	printf("\n");
}