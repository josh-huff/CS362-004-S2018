/************************************************************
*
* unittest4.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for testSupplyCount() in dominion.c
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

void testSupplyCount() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);
  
  printf("TESTING supplyCount():\n");
  	
// Test 1 -- testSupplyCount accurately finds the beginning number of cards in the pile.
  printf("Test: Game starts with 10 village cards.\n");
  asserttrue(supplyCount(village, &state), 10);

// Test 2 -- testSupplyCount updates when a card is taken from that supply.
  printf("Test: A village has been taken. Count updates.\n");
  state.supplyCount[village] -= 1;
  asserttrue(supplyCount(village, &state), 9);

}

int main(int argc, char *argv[]){

  testSupplyCount();
  return 0;
}
