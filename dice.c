/*
  Functions to handle dices and rolling of these

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "ui.h"

//initialize the random number generator
void initDice(){
  srand((int)time(NULL));
}

//randomizing a number between 1 and 6
int rollDice(){
  return (rand() % 6 + 1);
}

void rollAllDices(int dices[]){
  int i;

  //loop through all 5 dices and rolling them
  for(i=0;i<5;i++){
    dices[i] = rollDice();
  }
}

//count the number of occurrences of a specific dice
int numDiceValue(int search, int dices[]){
  int i,retval = 0;
  
  for(i = 0;i < 5;i++){
    if(dices[i] == search){
      retval++;
    }
  }

  return retval;
}

//Select which dices to reroll
int selectReroll(int dices[]){
  char row[81], temp[2];
  int i, enteredInt;

  temp[1] = '\0';

  setColor(GREEN, BLACK);
  printf("Enter dices to re roll (example: 1 3 5)\nTo do no re rolls at all enter 0\nInput: ");

  //Read the users input as a character string
  fgets(row, 80, stdin);

  //loop through each character
  for(i = 0;row[i] != '\0';i++){
    //check that the input is valid
    if(row[i] >= '1' && row[i] <= '6'){
      //Convert the inputed character to a integer
      temp[0] = row[i];
      enteredInt = atoi(temp);

      //roll the speciefied dice
      dices[enteredInt-1] = rollDice();
    }else if(row[i] == '0' && i == 0){
      //User entered 0, ie doesn't want any more rerolls
      return 0;
    }
  }

  //Continue with rerolls
  return 1;
}
