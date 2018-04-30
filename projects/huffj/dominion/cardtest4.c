/************************************************************
*
* cardtest4.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for card_village in dominion.c
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

void testVillage() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int beforeHandSize, beforeDeckSize, beforeDiscardSize, beforeNumActions;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);

  beforeHandSize = state.handCount[0];
  beforeDeckSize = state.deckCount[0];
  beforeDiscardSize = state.discardCount[0];
  beforeNumActions = state.numActions;
  
  printf("TESTING card_village():\n");

  // Last card is "Village".
  int handPos = state.handCount[0];
  card_village(&state, 0, handPos);

// Test 1 -- Current player should receive 1 new card and discard Remodel.
  printf("Test: Current player should have exact same number of cards in hand (discard Village, draw card).\n");

  asserttrue(state.handCount[0], beforeHandSize);

// Test 2 -- Card should come from own deck.
  printf("Test: card came from player's deck.\n");
  
  asserttrue(state.deckCount[0] + state.handCount[0] + state.discardCount[0], beforeHandSize + beforeDeckSize + beforeDiscardSize);  

// Test 3 -- Players should have two more actions (one net)
  printf("Test: Players should net one more action.\n");

  asserttrue(state.numActions, beforeNumActions);

}

int main(int argc, char *argv[]){
  
  testVillage();
  return 0;
}
