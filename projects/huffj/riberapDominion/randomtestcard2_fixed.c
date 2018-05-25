/************************************************************
*
* randomtestcard2.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 5 
* -----------------
*
* Random Test for Paige Ribera's playVillage in dominion.c
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

void randomTestVillage(struct gameState *original_state, int player, int handPos){

  struct gameState state_copy;
  memcpy(&state_copy, original_state, sizeof(struct gameState));

  
  int r;  
  r = playVillage(player, &state_copy, handPos);
  r_asserttrue(r, 0);
  
  // Simulate adding Village to played pile
  if(!r_asserttrue(original_state->playedCardCount, state_copy.playedCardCount - 1)){

    differences++;
  }    

  // Simulate having drawn a card (opponent is unchanged)     
  if(!r_asserttrue(original_state->handCount[player], state_copy.handCount[player])){

    differences++;
  }  
  
  if(!r_asserttrue(original_state->deckCount[!player], state_copy.deckCount[!player])){

    differences++;
  }  

  if(!r_asserttrue(original_state->handCount[!player], state_copy.handCount[!player])){

    differences++;
  }  
  
  if(!r_asserttrue(original_state->discardCount[!player], state_copy.discardCount[!player])){

    differences++;
  }   

  if(!r_asserttrue(original_state->numActions, state_copy.numActions - 1)){

    differences++;
  } 

}

int main(int argc, char *argv[]){

  struct gameState state;

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};

  initializeGame(2, k, 2000, &state);
  printf("RANDOM TESTING playVillage():\n");

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

    state.numActions = floor(Random() * 3 + 1);

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
  
    randomTestVillage(&state, currentPlayer, handPos);
  }
  
  printf("Differences:%d\n", differences);
  return 0;
}
