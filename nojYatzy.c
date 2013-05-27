/*

  Game for yatzy, supports 2 - 6 players and featuring digital dices

  For compilation on windows the preprocessor definition of _OS in ui.c needs to be set 
  to windows

  Author: Niklas Hedlund
  Date: 2010-10-31

 */

#include <stdlib.h>
#include <stdio.h>

#include "players.h"
#include "gameEngine.h"
#include "ui.h"
#include "highscore.h"
#include "score.h"

#pragma warning(disable:4996)

int main(){
  struct player players[6];
  struct player winner;
  int selection;

  do{
    clearScreen();
    printMenu();
    selection = readInt("Ange tal: ");

    switch(selection){
    case 1:
      createPlayers(players);
      gameLoop(players);

      clearScreen();
      winner = getLeadingPlayer(players);
      printWinner(winner);

      //Ask if to save to highscore
      if(askHighscore()){
	saveHighscore(winner.playername, getTotalScore(winner));
      }

      break;
    case 2:
      printHighscore();
      flushStdin();
      break;
    }
  }while(selection != 3);

  //reset console, used by windows which doesn't get its terminal colors automaticly reset
  cleanupUi();
	
  return EXIT_SUCCESS;
}
