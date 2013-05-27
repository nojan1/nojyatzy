/*
  Functions to handle console output and general functions for the console

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#ifndef _UI
#define _UI

#include "players.h"

enum Colors{BLACK=0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

void printMenu();
void printBoard(struct player);
void flushStdin();
int normalizeScore(int before);
void clearScreen();
void printDices(int dices[]);
void printWinner(struct player player);
int askHighscore();
int readInt(char prompt[]);
void setColor(enum Colors, enum Colors);
void cleanupUi();

#endif
