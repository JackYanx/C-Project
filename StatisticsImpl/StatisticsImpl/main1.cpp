/*
* @author: ��m1603��ΰ��
* @time: 2017.09.26
* CPP File
*/

#include<cstdio>
void delZeroElement(int*, int);
void printList(int*, int);
int main() {
	int dat[20] = {
		0,0,0,0,0,
		2,3,1,7,6,
		4,4,9,2,5,
		6,6,6,6,8
	};
	printf("ɾ��ǰ:\n");
	printList(dat, 20);
	delZeroElement(dat, 20);
	printf("\nɾ����:\n");
	printList(dat, 15);
	return 0;
}
void delZeroElement(int* arr, int n) {
	int i = 0, j = 0, *p = arr;
	while (*p == 0 && i < n) {
		i++;
		p++;
	}

	while (i < n) {
		arr[j] = *p;
		j++;
		i++;
		p++;
	}
}
void printList(int* arr, int n) {
	printf("����Ԫ��Ϊ:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}
