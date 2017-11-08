#include "LStack.h"
int main() {
    LStack mStack;
    int arr[20] = {
        1,2,2,3,4,
        4,5,9,10,10,
        11,13,16,16,20,
        21,22,22,22,26
    };
    for (int i = 0; i < 20;i++) {
        mStack.push(arr[i]);
    }
    int n;
    while (mStack.getCount() != 6) {
        mStack.pop(n);
        std::cout << n << std::endl;
    }
    return 0;
}