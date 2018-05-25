/************************************************************
*
* cardtest1.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 5 
* -----------------
*
* Unit Test for Paige Ribera's playSmithy in dominion.c
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
  int beforeHandSize, beforeDeckSize, beforeDiscardSize, beforeOppHand, beforeOppDeck, beforeOppDiscard;
  int beforeVictory = 0;
  int afterVictory = 0;
  int beforeKingdom = 0;
  int afterKingdom = 0;
  int seed = 1000;

  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);
  
  int currentPlayer = whoseTurn(&state);

  beforeHandSize = state.handCount[currentPlayer];
  beforeDeckSize = state.deckCount[currentPlayer];
  beforeDiscardSize = state.discardCount[currentPlayer];
  
  // NEW TEST Criteria -- ensure opponent's hand and deck are unchanged
  beforeOppHand = state.handCount[!currentPlayer];
  beforeOppDeck = state.deckCount[!currentPlayer];  
  
  int i;
  for (i = 0; i < 10; i++){
  
    beforeKingdom += k[i];
  }
  
  int j;
  for (j = 1; j < 4; j++){
  
    beforeVictory += state.supplyCount[j];
  }

  printf("\n-----TESTING playSmithy():\n");
  // Force one of the opening cards to be "Smithy."
  state.hand[currentPlayer][beforeHandSize - 1] = 13;
  printf("Hand contents before playing Smithy:\n");
  printHand(currentPlayer, &state);

  playSmithy(currentPlayer, &state, beforeHandSize - 1);

// Test 1 -- Current player should receive exact 3 cards.
  printf("Test: Current player should receive exact 3 cards.\n");
  if(!asserttrue(state.handCount[currentPlayer], beforeHandSize + 2)){
    
    printf("Hand size before drawing: %d\n", beforeHandSize);
    printf("Hand size after drawing: %d\n", state.handCount[currentPlayer]);
    printHand(currentPlayer, &state);
  }

// Test 2 -- Drawn cards should come from his own deck.
  printf("Test: Three cards came from the sum of player's deck and discard piles.\n");
  if(!asserttrue(state.deckCount[currentPlayer] + state.discardCount[currentPlayer], beforeDeckSize + beforeDiscardSize - 3)){
  
    printf("Deck + discard size before playing Smithy: %d\n", beforeDeckSize + beforeDiscardSize);
    printf("Deck + discard size after playing Smithy: %d\n", state.deckCount[currentPlayer] + state.discardCount[currentPlayer]);
  }

// NEW TEST, 2a
  printf("Test: No cards came from opponent's deck, discard, or hand.\n");

  if(!asserttrue(state.deckCount[!currentPlayer] + state.handCount[!currentPlayer] + state.discardCount[!currentPlayer], 
                 beforeOppHand + beforeOppDeck + beforeOppDiscard)){
    
    printf("Opponent Hand + deck + discard size before drawing: %d\n", beforeOppHand + beforeOppDeck + beforeOppDiscard);
    printf("Opponent Hand + deck + discard size after drawing: %d\n", state.deckCount[!currentPlayer] + state.handCount[!currentPlayer] + state.discardCount[!currentPlayer]);
  }
      
// Test 3 -- No state change should occur to the victory card piles and kingdom card piles.
  printf("Test: No state change to victory and kingdom card piles.\n");

  for (i = 0; i < 10; i++){
  
    afterKingdom += k[i];
  }

  for (j = 1; j < 4; j++){
  
    afterVictory += state.supplyCount[j];
  }

  if(!asserttrue(beforeKingdom + beforeVictory, afterKingdom + afterVictory)){
  
    printf("Kingdom size before drawing: %d\n", beforeKingdom);
    printf("Kingdom size after drawing: %d\n", afterKingdom);
    printf("Victory size before drawing: %d\n", beforeVictory);
    printf("Victory size after drawing: %d\n", afterVictory);    
  }

}

int main(int argc, char *argv[]){
  
  testSmithy();
  return 0;
}
