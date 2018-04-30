/************************************************************
*
* unittest2.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for whoseTurn() in dominion.c
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

void testWhoseTurn() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);
  
  printf("TESTING whoseTurn():\n");
	
// Test 1 -- whoseTurn indicates the appropriate player found in the game state.
  printf("Test: whoseTurn returns correct player.\n");

  asserttrue(whoseTurn(&state), 0);
  
// Test 2 -- The turn has advanced. whoseTurn shows the player has been updated.
  printf("Test: The turn has advanced. whoseTurn returns correct player.\n");

  endTurn(&state);
  asserttrue(whoseTurn(&state), 1);

// Test 3 -- Multiple turns later. whoseTurn is not greater than the number of players in the game
  printf("Test: whoseTurn number is not greater than (n - 1), where n is the number of players in the game.\n");
  
  endTurn(&state);
  endTurn(&state);
  endTurn(&state);
  asserttrue(whoseTurn(&state) < players - 1, 1);

}

int main(int argc, char *argv[]){

  testWhoseTurn();
  return 0;
}
