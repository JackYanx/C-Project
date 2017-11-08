#include <iostream>
using namespace std;

struct pnode {
	int expn; //指数
	float coef; //系数
	struct pnode *next;
};

void inputPolynomial(pnode *&h);
void outputPolynomial(pnode *h);
void addPolynomial(pnode* ha, pnode* hb, pnode* &hc);
void minuspolynomial(pnode *ha, pnode*hb, pnode* &hd);


int main() {
	pnode *ha;
	pnode *hb;
	pnode *hc;
	pnode *hd;

	/*init(ha);
	init(hb);
	init(hc);*/

	ha = new pnode;
	ha->next = NULL;

	hb = new pnode;
	hb->next = NULL;

	hc = new pnode;
	hc->next = NULL;

	hd = new pnode;
	hd->next = NULL;


	cout << "请输入第一个多项式： ";
	inputPolynomial(ha);
	outputPolynomial(ha);
	cout << "\n请输入第二个多项式： ";
	inputPolynomial(hb);
	outputPolynomial(hb);
	cout << "\n两个多项式相加为： ";
	addPolynomial(ha, hb, hc);
	outputPolynomial(hc);
	cout << "\n两个多项式相减为： ";
	minuspolynomial(ha, hb, hd);
	outputPolynomial(hd);

	return 0;
}

void inputPolynomial(pnode *&h) {
	pnode* q = h; //指向链表的尾节点

	cout << "请输入多项式有几项：";
	int i;
	cin >> i;
	cout << "请依次输入多项式的各个元素（即先输入系数后输入指数）\n";
	for (int k = 0; k < i; k++) {
		pnode* p = new pnode;
		p->next = NULL;
		float c; cin >> c;
		int e; cin >> e;
		p->expn = e;
		p->coef = c;

		if (h->next == NULL) {
			h->next = p;
			q = p;
		}
		else {
			q->next = p;
			q = p;
		}
		q->next = NULL;
	}


}

void outputPolynomial(pnode *h) {
	pnode *p = h->next;
	cout << "多项式的系数和指数依次为： ";
	while (p != NULL) {
		cout << p->coef << " " << p->expn << "     ";
		p = p->next;
	}
}

void addPolynomial(pnode* ha, pnode* hb, pnode* &hc) {
	pnode* p = ha->next;//指向多项式一的指针
	pnode* q = hb->next;//指向多项式二的指针
						//hc:新链的头指针 rc:新链的尾指针 初始化新链表
	hc = ha;
	// pnode* m = hc;
	pnode* rc = hc;
	while (p&&q) {
		if (p->expn < q->expn) {
			rc->next = p;
			rc = p;
			p = p->next;

		}
		else if (p->expn == q->expn) {
			float x = p->coef + q->coef;
			if (x != 0) {
				p->coef = x;
				rc->next = p;
				rc = p;
				p = p->next;

			}
			else {
				pnode* u = p;
				p = p->next;
				delete u;

			}
			pnode* u = q;
			q = q->next;
			delete u;
		}
		else if (p->expn > q->expn) {
			rc->next = q;
			rc = q;
			q = q->next;

		}
	}
	if (p) rc->next = p;
	else rc->next = q;
}

void minuspolynomial(pnode *ha, pnode*hb, pnode* &hd) {
	pnode* p = ha->next;//指向多项式一的指针
	pnode* q = hb->next;//指向多项式二的指针
						//hd:新链的头指针 rc:新链的尾指针 初始化新链表
	hd = ha;
	// pnode* m = hc;
	pnode* rc = hd;
	while (p&&q) {
		if (p->expn < q->expn) {
			rc->next = p;
			rc = p;
			p = p->next;

		}
		else if (p->expn == q->expn) {
			float x = p->coef - q->coef;
			if (x != 0) {
				p->coef = x;
				rc->next = p;
				rc = p;
				p = p->next;

			}
			else {
				pnode *u = p;
				p = p->next;
				delete u;

			}
			pnode* f = q;
			q = q->next;
			delete f;
		}
		else if (p->expn > q->expn) {
			q->coef = -(q->coef);
			rc->next = q;
			rc = q;
			q = q->next;

		}
	}
	if (p) rc->next = p;
	else rc->next = q;
}
