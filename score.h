/*
  Functions for calculating and handling the score

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#ifndef _SCORE
#define _SCORE

#include "players.h"

int getTotalScore(struct player player);
void assignScore(struct player *player, int dices[], int wheretoassign);

#endif
