/*
  Functions to handle reading and writing of the highscore file

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#ifndef _HIGHSCORE
#define _HIGHSCORE

#ifndef HIGHSCOREPATH
  #define HIGHSCOREPATH "highscore.bin"
#endif

struct highscorePost{
  char playername[51];
  int score;
};

void saveHighscore(char name[], int score);
void printHighscore();

#endif
