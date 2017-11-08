#include "Calculator.h"
Calculator::Calculator() { }
void Calculator::parseExpression() {
    char c;
    showProcess();
    for (int i = 0; i < explen; i++) {
        c = exp[i];
        if (!((c > 39 && c < 58) && c != 44 || c == 37)) {
            status = -1;
            MY_DEBUG("输入有误,请检查!\n");
            return;
        }
        switch (c) {
        case '(':
        {
            symbolStack.push((int)'(');
			expcurpos = i;
            break;
        }
        case ')':
        {
            expcurpos = i;
            calc();
            break;
        }
        case '+':
        {
            expcurpos = i;
            if (exp[expcurpos - 1] == '(') {
                numStack.push(0);
            }
            symbolStack.push((int)'+');
            break;
        }
        case '-':
        {
            expcurpos = i;
            if (exp[expcurpos - 1] == '(') {
                numStack.push(0);
            }
            symbolStack.push((int)'-');
            break;
        }
        case '*':
        {
            symbolStack.push((int)'*');
            break;
        }
        case '/':
        {
            symbolStack.push((int)'/');
            break;
        }
        case '%':
        {
            symbolStack.push((int)'%');
            break;
        }
        case '.':
        {
            //TODO:小数的处理
            break;
        }
        default:
        {
            numStack.push(getFirstSplitNum(&exp[i],i));
            expcurpos = i;
            calc();
        }
        }
    }
    numStack.pop(result);
}
void Calculator::showProcess() {
    if (showProcSwitch != 1 || status < 0) return;
	if (expcurpos == 0) {
		cout << "原表达式为:\n" << exp << endl << "计算过程如下:\n";
		return;
	}
    ostringstream output;
    int n = numStack.getCount(), m = symbolStack.getCount();
    //char c;
    int* numStackHeadPtr = (int*)numStack.headPointer();
    int* symStackHeadPtr = (int*)symbolStack.headPointer();
    for (int i = 0, j = 0; j < m; i++) {
        output << (char)symStackHeadPtr[j];
        j++;
        while (symStackHeadPtr[j] == (int)'(') {
            output << '(';
            j++;
        }
        if (numStackHeadPtr[i] < 0) {
            output << '(' << numStackHeadPtr[i] << ')';
        }
        else {
            output << numStackHeadPtr[i];
        }
    }
    output << &exp[expcurpos + 1];
    string outputStr = output.str();
    char* c = (char*)outputStr.c_str();
    int outputlen = outputStr.length();
    *(c + outputlen - 1) = 0;
    *c = ' ';
    c++;
    cout << c << endl;
}
int Calculator::getFirstSplitNum(char* str,int& i) {
    int num = 0;
    int len = 0;
    int multiple = 1;
    while (*str > 47 && *str < 58) {
        len++;
        str++;
    }
    i += len - 1;
    while (len != 0) {
        str--;
        len--;
        num += multiple * ((*str) - 48);
        multiple *= 10;
    }
    return num;
}
int Calculator::calc() {
    int sym;
    int m1, m2;
    if (symbolStack.getTop(sym) != 0) {
        cout << "计算完成!\n";
        return 0;
    }
    switch (sym) {
    case (int)'*': {
        numStack.pop(m2);
        symbolStack.pop(sym);
        numStack.pop(m1);
        numStack.push(m1 * m2);
        showProcess();
        break;
    }
    case (int)'/': {
        numStack.pop(m2);
        symbolStack.pop(sym);
        numStack.pop(m1);
        if (m2 == 0) {
            status = -1;
            MY_DEBUG("Divide By Zero!");
            return -1;
        }
        numStack.push(m1 / m2);
        showProcess();
        break;
    }
    case (int)'%': {
        numStack.pop(m2);
        symbolStack.pop(sym);
        numStack.pop(m1);
        if (m2 == 0) {
            status = -1;
            MY_DEBUG("Modulo By Zero!");
            return -1;
        }
        numStack.push(m1 % m2);
        showProcess();
        break;
    }
    }
    char c = exp[expcurpos + 1];
    if (c == ')' || c == '+' || c == '-') {
        while (symbolStack.getTop(sym) == 0 && sym != (int)'(') {
            if (sym == (int)'+') {
                
                symbolStack.pop(sym);
                numStack.pop(m2);
                numStack.pop(m1);
                numStack.push(m1 + m2);
                showProcess();
            }
            else if (sym == (int)'-') {
                symbolStack.pop(sym);
                numStack.pop(m2);
                numStack.pop(m1);
                numStack.push(m1 - m2);
                showProcess();
            }
            else {
                break;
            }
        }
        if (sym == (int)'(' && c == (int)')') {
            symbolStack.pop(sym);
        }
    }
    return 0;
}
void Calculator::init(string& src) {
    srcExp = "(" + src + ")";
    exp = (char*)srcExp.c_str();
    explen = src.length() + 2;
    expcurpos = 0;
    result = 0;
    status = 0;
}
int Calculator::getResult() {
    parseExpression();
    return result;
}
int Calculator::getStatus() {
    return status;
}