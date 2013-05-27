/*
  Functions for calculating and handling the score

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#include "players.h"
#include "dice.h"
#include "rules.h"

int getTotalScore(struct player player){
  int i,tempScore = 0;

  for(i = 0;i < 15; i++){
    //summarize all scores that have not been removed or is unused
    if(player.score[i] != -1 && player.score[i] != -2){
      tempScore += player.score[i];
    }

    //if the score of slot 1 to 6 are greater then 62 additional points shell be given
    if(i == 5 && tempScore > 62){
      tempScore += 50;
    }
  }

  return tempScore;
}

void assignScore(struct player *player, int dices[], int whereToAssign){
  int tempScore=0,i,tmp;
  int occurrences[6] = {0,};

  countOccurrences(dices, occurrences);

  if(whereToAssign >= 0 && whereToAssign <= 5){
    //Ettor till sexor
    tempScore = numDiceValue(whereToAssign + 1, dices) * (whereToAssign + 1);
  }else if(whereToAssign == 6){
    //1 par
    for(i = 5;i >= 0;i--){
      if(occurrences[i] >= 2){
	      tempScore = 2 * (i+1);
	      break;
       }
    }
  }else if(whereToAssign == 7){
    //2 par
    for(i = 0;i < 6;i++){
	    if(occurrences[i] >= 2){
	      for(tmp = 0;tmp < 6;tmp++){
	        if(tmp != i && occurrences[tmp] >= 2){
	          tempScore = (2 * (i+1)) + (2 * (tmp+1));
	          break;
	        }
	      }
	    }
    }
  }else if(whereToAssign == 8){
    //Tretal
    for(i = 0;i < 6;i++){
      if(occurrences[i] >= 3){
	      tempScore = 3 * (i+1);
	      break;
      }
    }
  }else if(whereToAssign == 9){
    //Fyrtal
    for(i = 0;i < 6;i++){
      if(occurrences[i] >= 4){
	      tempScore = 4 * (i+1);
	      break;
      }
    }
  }else if(whereToAssign == 10){
    //Liten stege
    tempScore = 15;
  }else if(whereToAssign == 11){
    //Stor stege
    tempScore = 20;
  }else if(whereToAssign == 12){
    //Kåk
    for(i = 0;i < 6;i++){
      if(occurrences[i] == 3){
	      for(tmp = 0;tmp < 6;tmp++){
	        if(tmp != i && occurrences[tmp] == 2){
	          tempScore = (3 * (i+1)) + (2 * (tmp+1));
	        }
	      }
      }
    }
  }else if(whereToAssign == 13){
    //Chans
    tempScore = dices[0] + dices[1] + dices[2] + dices[3] + dices[4];
  }else if(whereToAssign == 14){
    //Yatzy
    tempScore = 50;
  }

  player->score[whereToAssign] = tempScore;

}
