#include <ctime>
#include <cstdlib>
#include "ToolUtil.h"

void shuffle(int* arr) {

}
void shuffle(int* arr, int sz) {
	if (sz < 2 || arr == NULL) {
		return;
	}
	int i = sz;
	int j = 0;
	int temp = 0;
	srand(time(NULL));
	while (--i) {
		j = rand() % (i + 1);
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}