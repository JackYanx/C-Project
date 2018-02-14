#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

template <class T>
void showArrayElement(T* arr,int num) {
	for (int i = 0; i < num;i++) {
		cout << arr[i] << "  ";
	}
	cout << endl;
}

int main() {
	int intarr[5] = {5,6,9,8,7};
	float floatarr[4] = {0.0, -1.2f, 6.2f, 3.1415926535f};
	char chararr[13] = {"Hello World!"};
	//使用同一个函数就可以直接输出各种类型的数组
	showArrayElement(intarr, 5);
	showArrayElement(floatarr, 4);
	showArrayElement(chararr, 13);
	return 0;
}