/************************************************************
*
* unittest3.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for testFullDeckCount() in dominion.c
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

void testFullDeckCount() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);
  
  printf("TESTING fullDeckCount():\n");
	
	
// Test 1 -- testFullDeckCount accurately finds the number of instances of the card in the player's beginning deck
  printf("Test: fullDeckCount returns number of Village cards in each player's beginning deck. There should be none.\n");

  asserttrue(fullDeckCount(0, village, &state), 0);
  asserttrue(fullDeckCount(1, village, &state), 0);

// Test 2 -- testFullDeckCount accurately finds the number of instances of the card in the player's changed deck
  printf("Test: The first player has used three copper to buy a Village.\n");

  state.discard[0][state.discardCount[0]] = village; 
  state.discardCount[0]++; 
  asserttrue(fullDeckCount(0, village, &state), 1);

// Test 3 -- testFullDeckCount ensures the second player's deck hasn't been altered.
  printf("Test: Player two still has zero Villages.\n");

  asserttrue(fullDeckCount(1, village, &state), 0);

}

int main(int argc, char *argv[]){

  testFullDeckCount();
  return 0;
}
