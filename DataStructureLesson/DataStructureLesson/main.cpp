/*
Author: m1603 严伟滔 0121610870126
CPP File
分析在最后
*/
#include <cstdio>
int bubblesort(char** strarray, int size);
int strcomp(char* str1, char* str2);
int charcmp(char a, char b);
int main() {
    char* strarr[8] = {
        "PAB",
        "5C",
        "PABC",
        "CXY",
        "CRSI",
        "7",
        "B899",
        "B9"
    };
    bubblesort(strarr, 8);
    printf("排序后的结果为:\n");
    for (int i = 0; i < 8; i++) {
        printf("%s\n", strarr[i]);
    }

    return 0;
}
/*冒泡排序算法*/
int bubblesort(char** strarray, int size) {
    int i, j, cmpresult;
    char* temp = NULL;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - i - 1; j++) {
            cmpresult = strcomp(strarray[j], strarray[j + 1]);
            if (cmpresult > 0) {
                temp = strarray[j];
                strarray[j] = strarray[j + 1];
                strarray[j + 1] = temp;
            }
        }
    }
    return 0;
}
/*字符串比较函数*/
int strcomp(char* str1, char* str2) {
    char* p = str1, *q = str2;
    int result;
    while (p != NULL && q != NULL) {
        result = charcmp(*p, *q);
        if (result != 0) {
            return result;
        }
        p++;
        q++;
    }
    return charcmp(*p, *q);
}
/*字符比较函数*/
int charcmp(char a, char b) {
    if (a == b) {
        return 0;
    }
    if ((a > 47 && a < 58) && (b > 64 && b < 91)) {
        return 1;
    }
    else if ((b > 47 && b < 58) && (a > 64 && a < 91)) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return -1;
}
/*
分析:
可以使用字符指针数组来存储各字符串首地址，进而达到存储字符串的目的
*/