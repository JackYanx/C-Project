/*
* @author: 软工m1603严伟滔
* @time: 2017.09.26
* CPP File
*/

#include<cstdio>
#include<memory>
void printList(int* arr, int n);
void swapPartElem(int* arr, int k, int n);
int main() {
	int dat[20] = {
		0,0,0,0,0,
		2,3,1,7,6,
		4,4,9,2,5,
		6,6,6,6,8
	};
	int n, k;
	printf("请输入要开始移动元素的位置k:\n");
	scanf("%d", &k);
	n = 20;
	swapPartElem(dat, k, n);
	printList(dat, n);
	return 0;
}
void swapPartElem(int* arr, int k, int n) {
	int* temp = new int[n];
	memset(temp, 0, n);
	for (int i = k,j = 0; i < n; i++,j++) {
		temp[j] = arr[i];
	}
	for (int m = 0,p = n-k; m < k;m++,p++) {
		temp[p] = arr[m];
	}
	memcpy(arr,temp,n * sizeof(int));
}
void printList(int* arr, int n) {
	printf("数组元素为:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}
