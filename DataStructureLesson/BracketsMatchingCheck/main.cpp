#include <string>
#include<memory>
#include "LStack.h"
using namespace std;
int isMatched(string& s, LStack& stack);
int findLongestSeries(LStack& stack, int len);
int main() {
    string s;
    const string s1 = "-1";
    LStack mStack;
    do {
        cout << "���������Ŵ�����:(����-1ֹͣ)\n";
        cin >> s;
        cout << "�ƥ������ ����Ϊ:\n";
        isMatched(s,mStack);
        if (mStack.getCount() == 0) {
            cout << s.length();
        }
        else if (mStack.getCount() == s.length()) {
            cout << 0;
        }
        else {
            cout << findLongestSeries(mStack, s.length());
        }
    } while (s != s1);
    return 0;
}
int isMatched(string& s, LStack& stack) {
    int len = s.length();
    int tem;
    if (len < 2) {
        cout << "��ƥ��!\n";
        return -1;
    }
    char* str = new char[len];
    memcpy(str,s.c_str(),len);
    tem = (int)str[0];
    stack.push(tem);
    stack.rearPointer()->num = 1;
    for (int i = 1; i < len;i++) {
        tem = (int)str[i];
        if ((stack.rearPointer()->data == (int)'(') && (tem == (int)')')) {
            stack.pop(tem);
        }
        else {
            stack.push(tem);
            stack.rearPointer()->num = i + 1;
        }
    }
    if (stack.getCount()) {
        cout << "��ƥ��!\n";
    }
    else {
        cout << "��ȫƥ��!\n";
    }         
    delete str;
    return 0;
}
int findLongestSeries(LStack& stack, int len) {
    if (stack.getCount() < 1) {
        return 0;
    }
    int n = stack.getCount(),temp,diff;
    int maxMatchingSeries = len - stack.rearPointer()->num,a,b;
    while (stack.getCount() != 1) {
        a = stack.rearPointer()->num;
        stack.pop(temp);
        b = stack.rearPointer()->num;
        diff = a - b - 1;
        maxMatchingSeries = (diff > maxMatchingSeries) ? diff : maxMatchingSeries;
    }
    return maxMatchingSeries;
}
