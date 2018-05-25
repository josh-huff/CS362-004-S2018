/************************************************************
*
* cardtest2.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 5 
* -----------------
*
* Unit Test for Paige Ribera's playAdventurer in dominion.c
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
  int beforeHandSize, beforeDeckSize, beforeDiscardSize, beforeOppHand, beforeOppDeck, beforeOppDiscard;
  int beforeVictory = 0;
  int afterVictory = 0;
  int beforeKingdom = 0;
  int afterKingdom = 0;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);

  beforeHandSize = state.handCount[currentPlayer];
  beforeDeckSize = state.deckCount[currentPlayer];
  beforeDiscardSize = state.discardCount[currentPlayer];
  
  int i;
  for (i = 0; i < 10; i++){
  
    beforeKingdom += k[i];
  }
  
  int j;
  for (j = 1; j < 4; j++){
  
    beforeVictory += state.supplyCount[j];
  }
  
  int drawntreasure = 0;
  int cardDrawn = 0;
  int temphand[MAX_HAND];
  int currentPlayer = whoseTurn(&state);
  
  // NEW TEST Criteria -- ensure opponent's hand and deck are unchanged
  beforeOppHand = state.handCount[!currentPlayer];
  beforeOppDeck = state.deckCount[!currentPlayer];
  beforeOppDiscard = state.discardCount[!currentPlayer];
    
  printf("\n-----TESTING playAdventurer():\n");
  // Force one of the opening cards to be "Adventurer."
  state.hand[currentPlayer][beforeHandSize - 1] = 7;
  printf("Hand contents before playing Adventurer:\n");
  printHand(currentPlayer, &state);  

  playAdventurer(drawntreasure, &state, currentPlayer, cardDrawn, temphand);

// Test 1 -- Current player should receive 2 cards.
  printf("Test: Current player should have exactly 1 more card in hand.\n");

  if(!asserttrue(state.handCount[currentPlayer], beforeHandSize + 1)){
  
    printf("Hand size before drawing: %d\n", beforeHandSize);
    printf("Hand size after drawing: %d\n", state.handCount[currentPlayer]);    
    printHand(currentPlayer, &state);
  }

// Test 2 -- 2 cards should come from his own deck.
  if(!asserttrue(state.deckCount[currentPlayer] + state.discardCount[currentPlayer], beforeDeckSize + beforeDiscardSize - 2)){
  
    printf("Deck + discard size before drawing: %d\n", beforeDeckSize + beforeDiscardSize);
    printf("Deck + discard size after drawing: %d\n", state.deckCount[currentPlayer] + state.discardCount[currentPlayer]);
  }

// NEW TEST, 2a
  printf("Test: No cards came from opponent's deck.\n");

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

  if(!asserttrue(beforeKingdom, afterKingdom) || !asserttrue(beforeVictory, afterVictory)){
  
    printf("Kingdom size before drawing: %d\n", beforeKingdom);
    printf("Kingdom size after drawing: %d\n", afterKingdom);
    printf("Victory size before drawing: %d\n", beforeVictory);
    printf("Victory size after drawing: %d\n", afterVictory);    
  }


// Test 4 -- No Treasure was Discarded
  printf("Test:  No Treasure was Discarded. (possibly zero necessary tests)\n");
  
  int discarded = abs(beforeDiscardSize - state.discardCount[currentPlayer]);
  int discardTop = state.discardCount[currentPlayer] - 1;
  int m;

  if (discarded != 0){

    for (m = 0; m < discarded; m++){
  
      if(!asserttrue(state.discard[currentPlayer][discardTop] > 3 && state.discard[currentPlayer][discardTop] < 7, 0)){
      
        //printf("Card in discard pile is %d\n", state.discard[currentPlayer][discardTop]);
        printDiscard(currentPlayer, &state);
      }
      discardTop--;
    }
  }
  
  else{
  
    printf("Test Not Applicable: No discards made.\n");
  }
  
  
// Test 5 -- Only Treasure was Drawn
  printf("Test:  Only Treasure was Drawn. (two tests)\n");
  
  int n;
  int drawnLast = state.handCount[currentPlayer] - 1;
  for (n = 0; n < 2; n++){
  
    if(!asserttrue(state.hand[currentPlayer][drawnLast] > 3 && state.hand[currentPlayer][drawnLast] < 7, 1)){
      
      //printf("Last drawn card is %d\n", state.hand[currentPlayer][drawnLast]);
      printHand(currentPlayer, &state);
    }
    drawnLast--;
  }

}

int main(int argc, char *argv[]){
  
  testAdventurer();
  return 0;
}
