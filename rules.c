/*
  Functions for handling of rules and checking off dices

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#include <stdio.h>

#include "dice.h"
#include "players.h"
#include "ui.h"

#pragma warning(disable:4996)

int getMax(int numbers[], int currentIndex, int length){
  int nextValue;

  //if we are at the end of the list, return last value
  if(currentIndex > length-1) return numbers[currentIndex-1];

  //get the next value. This will trigger the recursive behavior
  nextValue = getMax(numbers, currentIndex+1,length);

  //return the highest number
  if(numbers[currentIndex] > nextValue){
    return numbers[currentIndex];
  }else{
	return nextValue;
  }

}

//Function to count the occurences of a specific dice in the list of 5 dices used
void countOccurrences(int dices[], int returnVal[]){
  int i;
	
  for(i = 0;i < 5;i++){
    returnVal[dices[i]-1]++;
  }
}

int inArray(int search, int arr[], int arrLength){
  int i;
	
  for(i = 0;i < arrLength; i++){
    //if the search value is found in array return true
    if(arr[i] == search){
      return 1;
    }
  }

  return 0;
}

int isValidSlot(int slot, int dices[]){
  int i, tmp=0;
  int occurrences[6] = {0,};

  countOccurrences(dices, occurrences);

  if(slot >= 0 && slot <= 5){
    //Ettor till sexor
    return (numDiceValue(slot + 1, dices) >= 1);
  }else if(slot == 6){
    //1 par
    return (getMax(occurrences, 0, 6) >= 2);
  }else if(slot == 7){
    //2 par
    for(i = 0;i < 6;i++){
      if(occurrences[i] >= 2){
	      tmp++;
      }
    }
    return (tmp >= 2);
  }else if(slot == 8){
    //Tretal
    for(i = 1; i < 7; i++){
      if(numDiceValue(i, dices) == 3){
	      return 1;
      }
    }
    return 0;
  }else if(slot == 9){
    //Fyrtal
    for(i = 1; i < 7; i++){
      if(numDiceValue(i, dices) == 4){
	      return 1;
      }
    }
    return 0;
  }else if(slot == 10){
    //Liten stege
    return (inArray(1, dices, 5) && 
	    inArray(2, dices, 5) && 
	    inArray(3, dices, 5) && 
	    inArray(4, dices, 5) && 
	    inArray(5, dices, 5));
  }else if(slot == 11){
    //Stor stege
    return (inArray(2, dices, 5) && 
	    inArray(3, dices, 5) && 
	    inArray(4, dices, 5) && 
	    inArray(5, dices, 5) && 
	    inArray(6, dices, 5));
  }else if(slot == 12){
    //Kåk
    for(i = 0;i < 6;i++){
      if(occurrences[i] >= 3){
	      for(tmp = 0;tmp < 6;tmp++){
	        if(tmp != i && occurrences[tmp] >= 2){
	          return 1;
	        }
	      }
      }
    }
    return 0;
  }else if(slot == 13){
    //Chans
    return 1;
  }else if(slot == 14){
    //Yatzy
    for(i = 1; i < 7; i++){
      if(numDiceValue(i, dices) == 5){
	      return 1;
      }
    }
    return 0;
  }
  return 0;
}

int selectWhereToSave(int dices[], struct player player){
  int slot, selectedSlot, validCounter=0;
  int validSlots[15];
  char labels[][15] = {"One's","Two's","Three's","Four's","Five's","Sixes","1-Pair","2-Pair","Three of a kind","Four of a kind","Low Strait", "High Strait", "Full house", "Chance", "Yatzy"};

  setColor(GREEN, BLACK);
  printf("Select where to save the result, the possible locations are listed below\n");

  for(slot = 0; slot < 15;slot++){
    if(player.score[slot] == -1 && isValidSlot(slot, dices)){
      validSlots[validCounter++] = slot;
      printf("%i: %s\n", slot + 1, labels[slot]);
    }else{
      validSlots[slot] = -1;
    }
  }

  //Bail if no slots where found!
  if(validSlots[0] == -1){
    return -1;
  }

  do{
    selectedSlot = readInt("\nSelect an alternative: ");
  }while(selectedSlot <= 0 || !inArray(selectedSlot-1, validSlots, 15));

  return selectedSlot-1;
}

void eliminateSlot(struct player *player){
  int i, selection, validCounter=0, validSlots[15] = {-1};
  char labels[][15] = {"One's","Two's","Three's","Four's","Five's","Sixes","1-Pair","2-Pair","Three of a kind","Four of a kind","Low Strait", "High Strait", "Full house", "Chance", "Yatzy"};

  setColor(RED, BLACK);
  printf("Your result can no be saved anywhere, select a alternative to skip:\n");

  for(i = 0;i < 15; i++){
    if(player->score[i] == -1){
      validSlots[validCounter++] = i;
      printf("%i: %s\n", i + 1, labels[i]);
    }
  }
  
  do{
    selection = readInt("\nSelect an alternative: ");
  }while(selection <= 0 || !inArray(selection-1, validSlots, 15));

  player->score[selection-1] = -2;
}
