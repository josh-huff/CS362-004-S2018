/************************************************************
*
* randomtestcard1.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 4 
* -----------------
*
* Random Test for card_smithy in dominion.c
*
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

int passed = 0;
int failed = 0;

void randomTestSmithy(struct gameState *original_state, int player, int handPos) {

  struct gameState state_copy;
  memcpy(&state_copy, original_state, sizeof(struct gameState));
  int r;  
  
  r = card_smithy(&state_copy, player, handPos);

// Test 1 -- Current player should receive exact 3 cards.
// Test 2 -- 3 cards should come from his own pile.
// Test 3 -- No state change should occur to the victory card piles and kingdom card piles.

  // Simulate drawing three cards
  int k;
  for(k = 0; k < 3; k++){
  
    if (original_state->deckCount[player] > 0){
    
      original_state->handCount[player]++;
      original_state->hand[player][original_state->handCount[player] - 1] = original_state->deck[player][original_state->handCount[player] - 1];
      original_state->deckCount[player]--;
    }
    
    else if (original_state->discardCount[player] > 0){
    
      memcpy(original_state->deck[player], state_copy.deck[player], sizeof(int) * original_state->discardCount[player]);
      memcpy(original_state->discard[player], state_copy.discard[player], sizeof(int) * original_state->discardCount[player]);
      original_state->hand[player][state_copy.handCount[player] - 1] = state_copy.hand[player][state_copy.handCount[player] - 1];
      original_state->handCount[player]++;
      original_state->deckCount[player] = original_state->discardCount[player] - 1;
      original_state->discardCount[player] = 0;
    }
  }
  
  // Simulate adding Smithy to played pile (pulled directly from dominion.c implementation of discardCard()
  original_state->playedCards[original_state->playedCardCount] = original_state->hand[player][handPos];
  original_state->playedCardCount++;  

  original_state->hand[player][handPos] = -1;
  
  if ( handPos == (original_state->handCount[player] - 1) ){

    original_state->handCount[player]--;
  }
  
  else if ( original_state->handCount[player] == 1 ){
  
    original_state->handCount[player]--;
  }
  
  else{
  
    original_state->hand[player][handPos] = original_state->hand[player][(original_state->handCount[player] - 1)];
    original_state->hand[player][original_state->handCount[player] - 1] = -1;
    original_state->handCount[player]--;
  } 

  asserttrue(r, 0);
  //asserttrue(memcmp(&state_copy, original_state, sizeof(struct gameState)), 0);
  //if(memcmp(&state_copy, original_state, sizeof(struct gameState)) == 0){passed++;} else{failed++;} 
}

int main(int argc, char *argv[]){
  

  struct gameState state;

  int k[10] = {adventurer, gardens, embargo, village, minion, 
               mine, cutpurse, sea_hag, tribute, smithy};

  initializeGame(2, k, 2000, &state);
  printf("RANDOM TESTING card_smithy():\n");
  
  int i, n, currentPlayer, handPos; 
  clock_t time_started, time_elapsed;
  time_started = clock();
  
  //TODO RESTORE TO 2000
  for(n = 0; n < 2000; n++){
    
    time_elapsed = clock() - time_started;
    
    if(((double)time_elapsed)/CLOCKS_PER_SEC > 295){
        
      return 0;
    }
  
    for(i = 0; i < sizeof(struct gameState); i++){
    
      ((char*) &state)[i] = floor(Random() * 256);
    }
    
    currentPlayer = floor(Random() * 2);
    state.numActions = floor(Random() * 5);
    state.coins = floor(Random() * 10);
    state.numBuys = floor(Random() * 3);
    state.whoseTurn = currentPlayer;
    state.phase = floor(Random() * 2);   
    state.deckCount[currentPlayer] = floor(Random() * 97) + 3;
    state.discardCount[currentPlayer] = floor(Random() * 100);
    state.handCount[currentPlayer] = floor(Random() * 25);
    state.playedCardCount = floor(Random() * 25);
    handPos = floor(Random() * state.handCount[currentPlayer]);
    randomTestSmithy(&state, currentPlayer, handPos);
    //printf("RUN %d\n", n);
  }

  
  printf("Passed: %d\n", passed);  
  printf("Failed: %d\n", failed);
  return 0;
}
