/*
  Functions to handle reading and writing of the highscore file

  Author: Niklas Hedlund
  Date: 2010-10-31

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "highscore.h"
#include "ui.h"

#pragma warning(disable:4996)

void saveHighscore(char name[], int score){
  int numPosts,i;
  struct highscorePost post;
  FILE *outputfile = fopen(HIGHSCOREPATH, "rb+");

  //Assign the player info to a new struct post
  for(i = 0;i < 51; i++){
    post.playername[i] = name[i];
  }
  post.score = score;

  if(outputfile == NULL){
    printf("CRITICAL ERROR!!!! HIGHSSCORE FILE COULD NOT BE WRITTEN TO!!!\a\n");
    flushStdin();
    getchar();
  }else{
    //Go to the beginning of the file
    fseek(outputfile, 0, SEEK_SET);

    //Read the amount of posts in the file, set to 1 if the file is empty, otherwise increment
    if(fread(&numPosts, sizeof(int), 1, outputfile) != (size_t)1){
      numPosts = 1;
    }else{
      numPosts++;
    }

    //Go to the beginning of and write the new number of posts
    fseek(outputfile, 0, SEEK_SET);
    fwrite(&numPosts, sizeof(int), 1, outputfile);

    //Go to the end of the file and write the new post
    fseek(outputfile, 0, SEEK_END);
    fwrite(&post, sizeof(struct highscorePost), 1, outputfile);

    fclose(outputfile);
  }
}

//Function regarding sorting by score, using the qsort function
int sortScore(const void *pekareA, const void *pekareB)
{
    struct highscorePost *postA = (struct highscorePost*)pekareA;
    struct highscorePost *postB = (struct highscorePost*)pekareB;
    
    if (postA->score > postB->score)
       return -1;
    else if (postA->score < postB->score)
       return 1;
    else
       return 0;
}

//Function regarding sorting by name, using the qsort function
int sortName(const void *pekareA, const void *pekareB)
{
    struct highscorePost *postA = (struct highscorePost*)pekareA;
    struct highscorePost *postB = (struct highscorePost*)pekareB;
    
    return strcmp(postA->playername, postB->playername);
}

void printHighscore(){
  int numPosts,i;
  char whatToDo = 's';
  struct highscorePost *posts;
  FILE *inputfile = fopen(HIGHSCOREPATH, "rb");
  
  if(inputfile == NULL){
    printf("Couldn't read the highscore file... Is there any highscore to read?\n");
    getchar(); 
  }else{
    //Read the number of posts, located first in the file
    if(fread(&numPosts, sizeof(int), 1, inputfile) != (size_t)1){
      printf("The highscore file is empty, or the read operation failed\n");
      getchar();
      return;
    }
    
    //Allocate memory for all the posts
    posts = (struct highscorePost*) malloc( sizeof(struct highscorePost) * numPosts );

    //Read posts from file
    for(i = 0; i < numPosts; i++){
      fread(&posts[i], sizeof(struct highscorePost), 1, inputfile);	
    }

    fclose(inputfile);

    //Print the highscore list
    do{
      clearScreen();
      printf("Highscore lista, sorterad p\x86 ");

      if(whatToDo == 'n'){
	      //Sort by name
	      qsort(posts, numPosts, sizeof(struct highscorePost), sortName);
	      printf("namn\n");
      }else{
	      //Sort by score
	      qsort(posts, numPosts, sizeof(struct highscorePost), sortScore);
	      printf("po\x84ng\n");
      }

      printf("\nNamn\tPo\x84ng\n");
      printf("----\t-----\n");
      
      //Print the sorted posts
      for(i = 0; i < numPosts; i++){
	      printf("%s\t%i\n", posts[i].playername, posts[i].score);		  
      }

      printf("\nEnter q to return to menu, s to sort on score and n to sort on name: ");
      scanf(" %c", &whatToDo);
    }while(whatToDo != 'q');

    //Free memory
    free(posts);
  }
}
