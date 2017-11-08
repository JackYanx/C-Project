#pragma once

#ifndef TOOLUTILS_H
#define TOOLUTILS_H

#include <iostream>
#include <string>

void initIntArray(int *keyInt, int target, int length);
void initCharArray(char *keyChar, char target, int length);
char* getLastCharOfString(std::string&);
char* getLastCharOfString(const char*);
std::string getPassword();
#endif

