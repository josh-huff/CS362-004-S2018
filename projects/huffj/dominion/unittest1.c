/************************************************************
*
* unittest1.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for isGameOver() in dominion.c
*
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void testIsGameOver() {


	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0){

    return 1;
  }

  //if three supply pile are at 0, the game ends
  int i;
  int j = 0;
  for (i = 0; i < 25; i++){
  
    if (state->supplyCount[i] == 0){
	
	  j++;
    }
  }

  if ( j >= 3){

    return 1;
  }

  return 0;

  // Test 1 -- Game continues (returns false) if there are Province cards.
  // Test 2 -- Game halts (returns true) if there are no more Province cards.
  // Test 3 -- Game continues (returns false) if there are no more than two piles exhausted.
  // Test 4 -- Game halts (returns true) if there are four or fewer players and no more than two piles exhausted.
  // Test 5 -- Game continues (returns false) if there are more than four players and no more than three piles exhausted.

}

int main(int argc, char *argv[]){

  testIsGameOver();
  return 0;
}
