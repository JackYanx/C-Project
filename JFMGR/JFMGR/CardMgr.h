#ifndef CARDMGR_H
#define CARDMGR_H

#include "global.h"

int addNewCard();
int queryCard();
int logoutCard();

void initCard(Card*);
void displayCardInfo(Card*);
#endif