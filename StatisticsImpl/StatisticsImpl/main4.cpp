/*
* @author: 软工m1603严伟滔
* @time: 2017.09.27
* CPP File
*/

#include<cstdio>
typedef struct Node {
	int data;
	struct Node* next;
}Node;
Node* createLinkList(int* arr,int n);
void printLinkList(Node* head);
void deleteElem(Node* head, int i);
void deleteRepetitionElem(Node* head);
int main() {
	int arr[20] = {
        1,2,2,3,4,
        4,5,9,10,10,
        11,13,16,16,20,
        21,22,22,22,26
	};

    Node* list = createLinkList(arr, 20);
    printLinkList(list);
    deleteRepetitionElem(list);
    printLinkList(list);
}
Node* createLinkList(int* arr, int n) {
    Node* head = new Node;
    Node* q = head,*p;
    for (int i = 0; i < n;i++) {
        p = new Node;
        p->next = NULL;
        p->data = arr[i];
        q->next = p;
        q = q->next;
    }
    return head;
}
void printLinkList(Node* head) {
    printf("该单链表的元素为:\n");
    Node* p = head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
void deleteElem(Node* head, int i) {
    Node* p = head->next,*q = head;
    while (p != NULL) {
        if (p->data == i) {
            break;
        }
        p = p->next;
        q = q->next;
    }
    q->next = p->next;
    delete p;
}
void deleteRepetitionElem(Node* head) {
    Node* p = head->next->next, *q = head->next;
    Node* temp = NULL;
    while (p != NULL) {
        if (p->data == q->data) {
            temp = p;
            q->next = p->next;
            p = p->next;
            delete temp;
            temp = NULL;
        }
        else {
            p = p->next;
            q = q->next;
        }
    }
}