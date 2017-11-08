/*
* @author: 计算机学院 软工m1603严伟滔
* @time: 2017.10.15
* CPP File
*/
#include<cstdio>
typedef struct Node {
    int data;
    struct Node* next;
}Node;
Node* createLinkList(int* arr, int n);
void printLinkList(Node* head);
int main() {
    int arr[20] = {
        7,2,5,3,4,
        4,5,9,10,1,
        11,13,16,6,20,
        21,562,27,223,11 };
    Node* list = createLinkList(arr, 20);
    printLinkList(list);
}
Node* createLinkList(int* arr, int n) {
    Node* head = new Node;
    Node* q = head, *p;
    for (int i = 0; i < n; i++) {
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