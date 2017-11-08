/*
@author:    软工学术1603 严伟滔
@time:      2017.10.19
@feature:   多项式计算,优化了显示结果
@type:      CPP Source File
*/
#include <cstdio>
typedef struct Node {
    int coef;
    int expo;
    Node* prior;
    Node* next;
}Node;
Node* createPoly();
Node* add(Node* poly1, Node* poly2);
Node* subtract(Node* poly1, Node* poly2);
void printPoly(Node* poly);
int getMaxExpo(Node* poly);
Node* duplicatePoly(Node* poly);
Node* deletePoly(Node* poly);
int main() {
    Node* poly1, *poly2;
    printf("正在建立多项式1...\n");
    poly1 = createPoly();
    printf("正在建立多项式2...\n");
    poly2 = createPoly();
    printf("多项式1为:\n");
    printPoly(poly1);

    printf("多项式2为:\n");
    printPoly(poly2);
    printf("多项式1+多项式2为:\n");
    printPoly(add(poly1,poly2));
    printf("多项式1-多项式2为:\n");
    printPoly(subtract(poly1, poly2));
    printf("多项式2-多项式1为:\n");
    printPoly(subtract(poly2, poly1));
    deletePoly(poly1);
    deletePoly(poly2);
    return 0;
}
Node* createPoly() {
    Node* head = new Node;
    head->prior = NULL;
    Node* p = head, *q = NULL;
    int n,m;
    printf("请输入此多项式最高次数:\n");
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        q = new Node;
        printf("请输入第%d项的系数:\n", i);
        scanf("%d", &q->coef);
        q->expo = i;
        p->next = q;
        q->prior = p;
        p = p->next;
    }
    q->next = NULL;
    return head;
}
Node* add(Node* poly1, Node* poly2) {
    poly1 = duplicatePoly(poly1);
    poly2 = duplicatePoly(poly2);
    Node* base = (getMaxExpo(poly1) > getMaxExpo(poly2)) ? poly1 : poly2;
    Node* ext = (poly1 == base) ? poly2 : poly1;
    Node* p1 = base,*p2 = ext;
    while (p2->next != NULL) {
        p1->next->coef += p2->next->coef;
        p1 = p1->next;
        p2 = p2->next;
    }
    deletePoly(ext);
    return base;
}
Node* subtract(Node* poly1, Node* poly2) {
    poly1 = duplicatePoly(poly1);
    poly2 = duplicatePoly(poly2);
    Node* base = (getMaxExpo(poly1) > getMaxExpo(poly2)) ? poly1 : poly2;
    Node* ext = (poly1 == base) ? poly2 : poly1;
    Node* p1 = base, *p2 = ext;
    while (p2->next != NULL) {
        p1->next->coef -= p2->next->coef;
        p1 = p1->next;
        p2 = p2->next;
    }
    if (base != poly1) {
        Node* p = base;
        while (p->next != NULL) {
            p->next->coef = -p->next->coef;
            p = p->next;
        }
    }
    deletePoly(ext);
    return base;
}
void printPoly(Node* head) {
    if (head == NULL) return;
    Node* p = head;
    Node* q = NULL;
    int zeroFlag = 0;
    while (p->next != NULL) {
        if (p->next->coef != 0) {
            if (p->next->coef > 0 && zeroFlag != p->next->expo) {
                printf("+");
            }
            if (p->next->expo == 0) {
                printf("%d", p->next->coef);
            }
            else if (p->next->expo == 1) {
				if (p->next->coef == 1) {
					printf("X");
				}
				else if(p->next->coef == -1){
					printf("-X");
				}
				else {
					printf("%dX", p->next->coef);
				}
            }
            else {
				if (p->next->coef == 1) {
					printf("X^%d", p->next->expo);
				}
				else if(p->next->coef == -1){
					printf("-X^%d", p->next->expo);
				}
				else {
					printf("%dX^%d", p->next->coef, p->next->expo);
				}
            }
        }
        else {
            zeroFlag++;
        }
        p = p->next;
        q = p;
    }
    if (zeroFlag == p->expo + 1) {
        printf("0");
    }
    printf("\n");
}
int getMaxExpo(Node* poly) {
    if (poly == NULL) return 0;
    int maxExpo = 0;
    Node* p = poly;
    while (p->next != 0) {
        maxExpo = (maxExpo < p->next->expo && p->next->coef != 0) ? p->next->expo : maxExpo;
        p = p->next;
    }
    return maxExpo;
}
Node* duplicatePoly(Node* poly) {
    if (poly == NULL) return NULL;
    Node* head = new Node;
    head->prior = NULL;
    Node* p = poly, *q = NULL,*r = head;
    while(p->next != NULL) {
        q = new Node;
        q->coef = p->next->coef;
        q->expo = p->next->expo;
        r->next = q;
        q->prior = r;
        r = r->next;
        p = p->next;
    }
    q->next = NULL;
    return head;
}

Node* deletePoly(Node* poly) {
    if (poly == NULL) return NULL;
    Node* p = poly,*q = p->next;
    while (q != NULL) {
        delete p;
        p = q;
        q = q->next;
    }
    delete p;
}