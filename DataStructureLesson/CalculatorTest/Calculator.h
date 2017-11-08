#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "base.h"
#include "AStack.h"

const int showProcSwitch = 1;

class Calculator {
private:
    AStack numStack;
    AStack symbolStack;
    string srcExp;
    char* exp;
    int explen;
    int expcurpos;
    int result;
    int status;
    void parseExpression();
    int calc();
    void showProcess();
    int getFirstSplitNum(char* str, int& i);
public:
    Calculator();
    void init(string& src);
    int getResult();
    int getStatus();
};

#endif