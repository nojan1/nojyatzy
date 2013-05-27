/*
  Functions to handle reading and writing of the highscore file

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#ifndef _HIGHSCORE
#define _HIGHSCORE

#define HIGHSCOREPATH "highscore.bin"

struct highscorePost{
  char playername[51];
  int score;
};

void saveHighscore(char name[], int score);
void printHighscore();

#endif
