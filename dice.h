/*
  Functions to handle dices and rolling of these

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#ifndef _DICE
#define _DICE

void initDice();
int rollDice();
int numDiceValue(int search, int dices[]);
void rollAllDices(int dices[]);
int selectReroll(int dices[]);

#endif
