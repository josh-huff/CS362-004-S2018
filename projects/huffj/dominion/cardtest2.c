/************************************************************
*
* cardtest2.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for card_adventurer in dominion.c
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

void testAdventurer() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int beforeHandSize, beforeDeckSize, beforeDiscardSize;
  int beforeVictory = 0;
  int afterVictory = 0;
  int beforeKingdom = 0;
  int afterKingdom = 0;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);

  beforeHandSize = state.handCount[0];
  beforeDeckSize = state.deckCount[0];
  beforeDiscardSize = state.discardCount[0];
  
  int i;
  for (i = 0; i < 10; i++){
  
    beforeKingdom += k[i];
  }
  
  int j;
  for (j = 1; j < 4; j++){
  
    beforeVictory += state.supplyCount[j];
  }
  
  printf("TESTING card_adventurer():\n");

  card_adventurer(&state, 0);

// Test 1 -- Current player should receive 2 cards.
  printf("Test: Current player should have exactly 1 more card in hand.\n");

  asserttrue(state.handCount[0], beforeHandSize + 1);

// Test 2 -- 2 cards should come from his own deck.
  printf("Test: 2 cards came from player's own deck.\n");

  asserttrue(state.deckCount[0] + state.handCount[0] + state.discardCount[0], beforeHandSize + beforeDeckSize + beforeDiscardSize);  
      
// Test 3 -- No state change should occur to the victory card piles and kingdom card piles.
  printf("Test: No state change to victory and kingdom card piles.\n");

  for (i = 0; i < 10; i++){
  
    afterKingdom += k[i];
  }

  for (j = 1; j < 4; j++){
  
    afterVictory += state.supplyCount[j];
  }

  asserttrue(beforeKingdom == afterKingdom, beforeVictory == afterVictory);

// Test 4 -- No Treasure was Discarded
  printf("Test:  No Treasure was Discarded. (possibly zero necessary tests)\n");
  
  int discarded = abs(beforeDiscardSize - state.discardCount[0]);
  int discardTop = state.discardCount[0] - 1;
  int m;

  if (discarded != 0){

    for (m = 0; m < discarded; m++){
  
      asserttrue(state.discard[0][discardTop] > 3 && state.discard[0][discardTop] < 7, 0);
      discardTop--;
    }
  }
  
  else{
  
    printf("Test Not Applicable: No discards made.\n");
  }
// Test 5 -- Only Treasure was Drawn
  printf("Test:  Only Treasure was Drawn. (two tests)\n");
  
  int n;
  int drawnLast = state.handCount[0] - 1;
  for (n = 0; n < 2; n++){
  
    asserttrue(state.hand[0][drawnLast] > 3 && state.hand[0][drawnLast] < 7, 1);
    drawnLast--;
  }

}

int main(int argc, char *argv[]){
  
  testAdventurer();
  return 0;
}
