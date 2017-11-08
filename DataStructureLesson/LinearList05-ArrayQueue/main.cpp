#include "Queue.h"
using namespace std;

int main() {
	Queue q;
	q.initQueue();
	int n,m;
	cin >> n;
	while (n != -1) {
		q.insertElement(&n);
		cin >> n;
	}
	cout << "\n...\n";
	cin.get();
	while (!q.isEmpty()) {
		q.deleteElement(&m);
		cout << m << endl;
	}
	cin >> n;
	q.insertElement(&n);
	cin >> n;
	q.insertElement(&n);
	q.deleteElement(&m);
	cout << m << endl;
	cin.get();
	q.destroySelf();
	return 0;
}