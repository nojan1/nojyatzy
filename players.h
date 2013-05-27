/*
  Functions to handle players and whose turn it is

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#ifndef _PLAYERS
#define _PLAYERS

struct player{
  char playername[51];
  int inUse;
  int score[15];
};

void createPlayers(struct player players[]);
struct player getLeadingPlayer(struct player players[]);
int playerDone(struct player);
int allPlayersDone(struct player players[]);
void nextPlayersTurn(struct player players[], int *activePlayer);
int numPlayers(struct player players[]);

#endif
