/************************************************************
*
* unittest1.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 5 
* -----------------
*
* Unit Test for isGameOver() in dominion.c
*
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

void testIsGameOver() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);
  
  printf("TESTING isGameOver():\n");

// Test 1 -- Game continues (returns false) if there are Province cards and no more than two piles are exhausted.
  printf("Test: Province cards available and two supply piles exhausted.\n");

  // Card-Drawing Strategy -- a player has combo'ed off the Smithy and Village cards
  state.supplyCount[province] = 1;
  state.supplyCount[smithy] = 0;
  state.supplyCount[village] = 0;

  asserttrue(isGameOver(&state), 0);

// Test 2 -- Game halts (returns true) if there are no more Province cards.
  printf("Test: No Province cards.\n");

  state.supplyCount[province] = 0;
  
  asserttrue(isGameOver(&state), 1);
      
// Test 3 -- Game halts (returns true) if there are four or fewer players and more than two piles exhausted.
  printf("Test: Three supply piles exhausted.\n");

  // Card-Drawing Strategy -- a player has combo'ed off the Smithy and Village cards
  state.supplyCount[province] = 1;
  state.supplyCount[feast] = 0;
  state.supplyCount[smithy] = 0;
  state.supplyCount[village] = 0;  

  asserttrue(isGameOver(&state), 1);

}

int main(int argc, char *argv[]){
  
  testIsGameOver();
  return 0;
}
