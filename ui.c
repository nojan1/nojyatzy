/*
  Functions to handle console output and general functions for the console

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

//#define _OS windows
#define _OS linux

#include <stdio.h>
#include <stdlib.h>

#include "players.h"
#include "score.h"
#include "ui.h"

#pragma warning(disable:4996)

#if _OS == windows
#include <windows.h>
#endif

void printMenu(){
  setColor(GREEN, BLACK);
  printf("|======================|\n");
  printf("|       nojYatzy       |\n");
  printf("|======================|\n");
  printf("|     Huvud meny       |\n");
  printf("|----------------------|\n");
  printf("|  1: Spela            |\n");
  printf("|  2: Visa highscore   |\n");
  printf("|  3: Avsluta spelet   |\n");
  printf("|======================|\n");
}

//if windows use the cls command, otherwise use escape codes
void clearScreen(){
#if _OS == windows
  system("cls");
#else
  printf("\033[2J");
  printf("\033[0;0f");
#endif
}

//0:Black, 1:Red, 2:Green, 3:Yellow, 4:Blue, 5:Magenta, 6:Cyan, 7:White
//Windows uses a specific function for this, if not windows use bash escape codes
void setColor(enum Colors color, enum Colors background){
#if _OS == windows
  int windowsColors[] = {0, 4, 2, 6, 1, 5, 3, 15};
  HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  
  SetConsoleTextAttribute(stdHandle, windowsColors[(int)color] + (windowsColors[(int)background] * 16));
#else
  int bashColors[] = {30,31,32,33,34,35,36,37};
  int bashBackgroundColors[] = {40,41,42,43,44,45,46,47};

  printf("\E[%i;%im", bashColors[(int)color], bashBackgroundColors[(int)background]);
#endif
}


//Flush the input buffer
void flushStdin(){
  int ch = 0;

  if(feof(stdin)) return;

  //Loop until we find the EOF or a newline character
  while((ch = getc(stdin)) != EOF && ch != '\n'){
    continue;
  }
}

//A unused or removed result will be displayed as 0
int normalizeScore(int before){
  if(before == -1)
    return 0;
  else if(before == -2)
    return -1;
  else
    return before;
}

//Secure reading to read a integer
int readInt(char prompt[]){
  int retval;
  char row[81];

  do{
    printf(prompt);
    fgets(row, 81, stdin);
  }while(sscanf(row, "%i", &retval) != 1);

  return retval;
}

//print score board
void printBoard(struct player player){
  setColor(GREEN, BLACK);
  printf("%s's po\x84ngtavla:\n", player.playername);
  printf("---------------------------------\n");
  printf("| Ettor: %3i | Tretal: %8i |\n", normalizeScore(player.score[0]), normalizeScore(player.score[8]));
  printf("| Tv\x86or: %3i | Fyrtal: %8i |\n", normalizeScore(player.score[1]), normalizeScore(player.score[9]));
  printf("| Treor: %3i | Liten Stege: %3i |\n", normalizeScore(player.score[2]), normalizeScore(player.score[10]));
  printf("| Fyror: %3i | Stor Stege: %4i |\n", normalizeScore(player.score[3]), normalizeScore(player.score[11]));
  printf("| Femor: %3i | K\x86k: %11i |\n", normalizeScore(player.score[4]), normalizeScore(player.score[12]));
  printf("| Sexor: %3i | Chans: %9i |\n", normalizeScore(player.score[5]), normalizeScore(player.score[13]));
  printf("| 1-Par: %3i | Yatzy: %9i |\n", normalizeScore(player.score[6]), normalizeScore(player.score[14]));
  printf("| 2-Par: %3i |                  |\n", normalizeScore(player.score[7]));
  printf("---------------------------------\n");
  printf("Totalt: %i\n", getTotalScore(player));
  printf("---------------------------------\n");
}


void printDices(int dices[]){
  int i,j;

  //3 dimensional array to contain the different charcter series for each dice
  char rows[3][6][8] = {
    {"       ", " *     ", "  *    ", " *   * ", " *   * ", "  * *  "}, 
    {"   *   ", "       ", "   *   ", "       ", "   *   ", "  * *  "}, 
    {"       ", "     * ", "    *  ", " *   * ", " *   * ", "  * *  "}};

  setColor(WHITE, BLACK);
  printf("/-------\\ /-------\\ /-------\\ /-------\\ /-------\\\n");

  //loop through each of the 3 rows
  for(j = 0;j < 3;j++){
    //loop through the 5 dices
    for(i = 0;i < 5;i++){
      printf("|");

      setColor(RED, BLACK);
      //print the correct character sequence from the array previously declarded
      printf(rows[j][dices[i]-1]);
      
      setColor(WHITE, BLACK);
      printf("| ");
    }

    printf("\n");
  }

  printf("\\-------/ \\-------/ \\-------/ \\-------/ \\-------/\n");
  printf("    1         2         3         4         5    \n");
  printf("\n");
}

void printWinner(struct player player){
  setColor(YELLOW, BLACK);
  printf("   .-=========-.  \n");
  printf("   \\'-=======-'/  \n");
  printf("   _|   .=.   |_  \n");
  printf("  ((|  {{1}}  |)) \n");
  printf("   \\|   /|\\   |/  \n");
  printf("    \\__ '`' __/   \n");
  printf("      _`) (`_     \n");
  printf("    _/_______\\_   \n");
  printf("   /___________\\  \n");

  setColor(GREEN, BLACK);
  printf("===================\n");

  printf("OCH VINNAREN \x84r:\n");
  printf("%s\n", player.playername);
  printf("===================\n");

}

int askHighscore(){
  printf("Vill du spara vinnarens resultat till highscore? (y/n).. ");
  return (getchar() == 'y');
}

//Function to reset windows terminal color
void cleanupUi(){
#if _OS == windows
  system("color");
#else
  return;
#endif
}
