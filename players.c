/*
  Functions to handle players and whose turn it is

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "score.h"
#include "players.h"
#include "ui.h"

#pragma warning(disable:4996)

void createPlayers(struct player players[]){
  int i,n,numplayers = 0;

  //loop until a correct number of players have been entered
  do{
    numplayers = readInt("Enter the number of players (2-6): ");
  }while(numplayers < 2 || numplayers > 6);

  for(i = 0;i < 6;i++){
    if(i < numplayers){
      printf("Enter name for player %i: ", i+1);
      fgets(players[i].playername, 50, stdin);

      //strip newline character left behind by fgets
      players[i].playername[(int)strlen(players[i].playername) - 1] = '\0';
      players[i].inUse = 1;

      //set the players score board to -1 = nothing used
      for(n=0;n<15;n++)
	      players[i].score[n] = -1;

    }else{
      //this player is not is use
      players[i].inUse = 0;
    }
  }
}

//check if a player has filled his scoreboard
int playerDone(struct player player){
  int i, res=1;

  for(i = 0;i < 15;i++){
    if(player.score[i] == -1){
      res = 0;
      break;
    }
  }

  return res;
}

//check if all players in use have filled there score boards
int allPlayersDone(struct player players[]){
  int i;

  for(i=0;i<8;i++){
    if(players[i].inUse){
      if(!playerDone(players[i])){
	return 0;
      }
    }else{
      break;
    }
  }

  return 1;
}

//get the number of players in use
int numPlayers(struct player players[]){
  int i = 0;

  while(players[i].inUse){
    i++;
  }

  return i;
}

void nextPlayersTurn(struct player players[], int *activePlayer){
  //increment the active player (index)
  (*activePlayer)++;

  //if we have gone outside the player array, reset the active player to first player
  if(*activePlayer > numPlayers(players) - 1){
    *activePlayer = 0;
  }
}

int sortPlayers(const void *pekareA, const void *pekareB)
{
    struct player *postA = (struct player*)pekareA;
    struct player *postB = (struct player*)pekareB;
    
    if (getTotalScore(*postA) > getTotalScore(*postB))
       return -1;
    else if (getTotalScore(*postA) < getTotalScore(*postB))
       return 1;
    else
       return 0;
}

//sort all players and return the first on in the array
struct player getLeadingPlayer(struct player players[]){
  qsort(players, numPlayers(players), sizeof(struct player), sortPlayers);

  return players[0];
}
