/*
 *双向链表
 */

#include <cstdio>
typedef struct Node {
    int data;
    Node* prior;
    Node* next;
}Node;
Node* createlist(int n);
void printlist(Node* head);
int main() {
    int n;
    printf("请输入数据数量:\n");
    scanf("%d", &n);
    printf("请开始输入数据:\n");
    Node* p = createlist(n);
    printf("你输入的数据为:\n");
    printlist(p);
    return 0;
}
Node* createlist(int n) {
    Node* head = new Node;
    head->prior = NULL;
    Node* p = head, *q = NULL;
    for (int i = 0; i < n; i++) {
        q = new Node;
        scanf("%d", &q->data);
        p->next = q;
        q->prior = p;
        p = p->next;
    }
    q->next = NULL;
    return head;
}
void printlist(Node* head) {
    Node* p = head;
    Node* q = NULL;
    printf("正序输出为:\n");
    while (p->next != NULL) {
        printf("%d ", p->next->data);
        p = p->next;
        q = p;
    }
    printf("\n倒序输出为:\n");
    while (q->prior != NULL) {
        printf("%d ", q->data);
        q = q->prior;
    }
}