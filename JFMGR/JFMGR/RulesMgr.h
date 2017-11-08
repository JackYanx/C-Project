#ifndef RULESMGR_H
#define RULESMGR_H

#include "global.h"

int createNewRules(bool);
int queryRules();
int changeRules();

void initRule(Rule*);
Rule* getLatestRule();
int getLatestRating();
#endif