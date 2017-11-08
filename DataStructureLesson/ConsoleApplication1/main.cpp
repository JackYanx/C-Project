#include <iostream>
using namespace std;

struct pnode {
	int expn; //ָ��
	float coef; //ϵ��
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


	cout << "�������һ������ʽ�� ";
	inputPolynomial(ha);
	outputPolynomial(ha);
	cout << "\n������ڶ�������ʽ�� ";
	inputPolynomial(hb);
	outputPolynomial(hb);
	cout << "\n��������ʽ���Ϊ�� ";
	addPolynomial(ha, hb, hc);
	outputPolynomial(hc);
	cout << "\n��������ʽ���Ϊ�� ";
	minuspolynomial(ha, hb, hd);
	outputPolynomial(hd);

	return 0;
}

void inputPolynomial(pnode *&h) {
	pnode* q = h; //ָ�������β�ڵ�

	cout << "���������ʽ�м��";
	int i;
	cin >> i;
	cout << "�������������ʽ�ĸ���Ԫ�أ���������ϵ��������ָ����\n";
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
	cout << "����ʽ��ϵ����ָ������Ϊ�� ";
	while (p != NULL) {
		cout << p->coef << " " << p->expn << "     ";
		p = p->next;
	}
}

void addPolynomial(pnode* ha, pnode* hb, pnode* &hc) {
	pnode* p = ha->next;//ָ�����ʽһ��ָ��
	pnode* q = hb->next;//ָ�����ʽ����ָ��
						//hc:������ͷָ�� rc:������βָ�� ��ʼ��������
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
	pnode* p = ha->next;//ָ�����ʽһ��ָ��
	pnode* q = hb->next;//ָ�����ʽ����ָ��
						//hd:������ͷָ�� rc:������βָ�� ��ʼ��������
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
