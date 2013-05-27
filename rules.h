/*
  Functions for handling of rules and checking off dices

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#ifndef _RULES
#define _RULES

#include "players.h"

int selectWhereToSave(int dices[], struct player player);
int isValidSlot(int slot, int dices[]);
void countOccurrences(int dices[], int returnVal[]);
void eliminateSlot(struct player *player);

#endif
