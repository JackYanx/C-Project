#include <cstdio>
#include "Calculator.h"
int main() {
    Calculator calculator;

    string s1 = "(12)*2+3*(9-8*(9-8*2))-2*32+6/(5-6/2)";
    calculator.init(s1);
    cout << "第1次计算结果:\n" << calculator.getResult() << "\n\n";
    
    string s2 = "(6-2*1)+3+(1*12+3)%(7-6/2)";
    calculator.init(s2);
    cout << "第2次计算结果:\n" << calculator.getResult() << "\n\n";

    string s3 = "(14+2*2/2+2)%(23+6/4-2*8)-(2-2+1%100)*((10%7/2+4)*2+9-1)+(2-2)%2";
    calculator.init(s3);
    cout << "第3次计算结果:\n" << calculator.getResult() << "\n\n";

    string s4 = "+5/2+(-(-6/2)*6)+2";
    calculator.init(s4);
    cout << "第4次计算结果:\n" << calculator.getResult() << "\n\n";

    string s5 = "+(-((-90/(-0))))";
    calculator.init(s5);
    cout << "第5次计算结果:\n" << calculator.getResult() << "\n\n";
    return 0;
}