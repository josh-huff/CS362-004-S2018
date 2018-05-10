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

#define RANDOM_TEST_LOOPS 10000 
#define NORMAL_DECK_SIZE 100
#define NORMAL_HAND_SIZE 10
#define CARD_POOL 26

int differences = 0;

void randomTestSmithy(struct gameState *original_state, int player, int handPos) {

  struct gameState state_copy;
  memcpy(&state_copy, original_state, sizeof(struct gameState));

  int r;  
  r = card_smithy(&state_copy, player, handPos);
  asserttrue(r, 0);
  
  // Simulate adding Smithy to played pile
  if(!asserttrue(original_state->playedCardCount, state_copy.playedCardCount - 1)){

    differences++;
  }    

  // Simulate having drawn three cards (opponent is unchanged)     
  if(!asserttrue(original_state->handCount[player], state_copy.handCount[player] - 2)){

    differences++;
  }  
  
  if(!asserttrue(original_state->deckCount[!player], state_copy.deckCount[!player])){

    differences++;
  }  

  if(!asserttrue(original_state->handCount[!player], state_copy.handCount[!player])){

    differences++;
  }  
  
  if(!asserttrue(original_state->discardCount[!player], state_copy.discardCount[!player])){

    differences++;
  }    
  
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
  
  for(n = 0; n < RANDOM_TEST_LOOPS; n++){
    
    time_elapsed = clock() - time_started;
    
    if(((double)time_elapsed)/CLOCKS_PER_SEC > 295){
        
      return 0;
    }
  
    for(i = 0; i < sizeof(struct gameState); i++){
    
      ((char*) &state)[i] = floor(Random() * 256);
    }
    
    currentPlayer = floor(Random() * 2);
        
    // "Sane" Randomization of State Attributes
    state.numPlayers = 2;
    state.whoseTurn = currentPlayer;

    state.handCount[currentPlayer] = floor(Random() * NORMAL_HAND_SIZE);
    for(i = 0; i < state.handCount[currentPlayer]; i++){
      
      state.hand[currentPlayer][i] = floor(Random() * CARD_POOL);
    }
    
    state.deckCount[currentPlayer] = floor(Random() * NORMAL_DECK_SIZE);
    for(i = 0; i < state.deckCount[currentPlayer]; i++){
      
      state.deck[currentPlayer][i] = floor(Random() * CARD_POOL);
    }
    
    state.discardCount[currentPlayer] = floor(Random() * NORMAL_DECK_SIZE);
    for(i = 0; i < state.discardCount[currentPlayer]; i++){
      
      state.discard[currentPlayer][i] = floor(Random() * CARD_POOL);
    }

    state.playedCardCount = floor(Random() * NORMAL_HAND_SIZE);
    for(i = 0; i < state.playedCardCount; i++){
      
      state.playedCards[i] = floor(Random() * CARD_POOL);
    }  

    handPos = floor(Random() * state.handCount[currentPlayer]);

    randomTestSmithy(&state, currentPlayer, handPos);
  }
  
  printf("Differences:%d\n", differences);
  return 0;
}
