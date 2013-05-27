/*
  Game engine containg the main game loop, this is the file that makes it all happen

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#include <stdio.h>

#include "players.h"
#include "dice.h"
#include "ui.h"
#include "score.h"
#include "rules.h"
#include "highscore.h"

void gameLoop(struct player players[]){
  int activePlayer = 0;
  int dices[5];
  int selectedSlot, rerollCount;

  initDice();

  do{
    clearScreen();

    rollAllDices(dices);
    rerollCount=0;

    while(rerollCount < 2){
      clearScreen();
      printBoard(players[activePlayer]);

      setColor(GREEN, BLACK);
      printf("\nAntal omslag gjorda: %i\n\n", rerollCount);
      printDices(dices);

      //User wants to bail early, not using all rerolls
      if(!selectReroll(dices)) break;
      
      rerollCount++;
    }

    clearScreen();
    printDices(dices);

    //The user gets to select a possible slot for his score
    selectedSlot = selectWhereToSave(dices, players[activePlayer]);

    if(selectedSlot != -1){
      //Assign score to the selected slot
      assignScore(&players[activePlayer], dices, selectedSlot);
    }else{
      //If no slots are valid, one has to be elminated
      clearScreen();
      printDices(dices);
      eliminateSlot(&players[activePlayer]);
    }
	
    clearScreen();
    printBoard(players[activePlayer]);

    //Advance to the next player, if all players are done the loop will end
    if(!allPlayersDone(players)){
      do{
	nextPlayersTurn(players, &activePlayer);
      }while(playerDone(players[activePlayer]));

      printf("\n%s det \x84r din tur, tryck ENTER f\x94r att spela..", players[activePlayer].playername);
      getchar();
    }else{
      break;
    }

  }while(1);

}
