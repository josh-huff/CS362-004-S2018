/************************************************************
*
* cardtest1.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for card_smithy in dominion.c
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

void testSmithy() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int beforeHandSize, beforeDeckSize;
  int beforeVictory = 0;
  int afterVictory = 0;
  int beforeKingdom = 0;
  int afterKingdom = 0;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);
  
  printf("TESTING card_smithy():\n");

// Test 1 -- Current player should receive exact 3 cards.
  printf("Test: Current player should receive exact 3 cards.\n");

  beforeHandSize = state.handCount[0];
  beforeDeckSize = state.deckCount[0];
  
  int i;
  for (i = 0; i < 10; i++){
  
    beforeKingdom += k[i];
  }
  
  int j;
  for (j = 1; j < 4; j++){
  
    beforeVictory += state.supplyCount[j];
  }
  
  card_smithy(&state, 0, 0);
  asserttrue(state.handCount[0], beforeHandSize + 2);

// Test 2 -- 3 cards should come from his own pile.
  printf("Test: 3 cards came from player's own pile.\n");

  asserttrue(state.deckCount[0], beforeDeckSize - 3);  
      
// Test 3 -- No state change should occur to the victory card piles and kingdom card piles.
  printf("Test: No state change to victory and kingdom card piles.\n");

  for (i = 0; i < 10; i++){
  
    afterKingdom += k[i];
  }

  for (j = 1; j < 4; j++){
  
    afterVictory += state.supplyCount[j];
  }

  asserttrue(beforeKingdom, afterKingdom);
  asserttrue(beforeVictory, afterVictory);

}

int main(int argc, char *argv[]){
  
  testSmithy();
  return 0;
}
