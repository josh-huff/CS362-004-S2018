/************************************************************
*
* cardtest3.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 5 
* -----------------
*
* Unit Test for Paige Ribera's cardEffect(remodel) in dominion.c
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

void testRemodel() {

  int k[10] = {adventurer, feast, baron, mine, great_hall, 
               remodel, smithy, village, ambassador, embargo};
            
  int players = 2;
  int beforeHandSize;
  int beforeVictory = 0;
  int afterVictory = 0;
  int beforeKingdom = 0;
  int afterKingdom = 0;
  int seed = 1000;
  struct gameState state; 

  memset(&state, 23, sizeof(struct gameState));
  initializeGame(players, k, seed, &state);

  beforeHandSize = state.handCount[0];
  
  int i;
  for (i = 0; i < 10; i++){
  
    beforeKingdom += k[i];
  }
  
  int j;
  for (j = 1; j < 4; j++){
  
    beforeVictory += state.supplyCount[j];
  }
  
  int totalBeforeSupply = beforeKingdom + beforeVictory;
  
  printf("TESTING cardEffect(remodel):\n");

  // Last card is "Remodel", second to last is target card.
  int handPos = state.handCount[0];
  int trashCard = state.handCount[0] - 1;
  int choiceCard = silver;
  // OLD TEST CALL: card_remodel(&state, 0, choiceCard, trashCard, handPos);
  // NEW TEST CALL:
  //cardEffect(remodel, choice1, choice2, choice3(dummy value, not relevant to remodel), state, handPos, bonus (dummy value));
  cardEffect(remodel, trashCard, choiceCard, 0, &state, handPos, 0);
  

// Test 1 -- Current player should receive 1 new card and discard Remodel.
  printf("Test: Current player should have exact same number of cards in hand.\n");

  asserttrue(state.handCount[0], beforeHandSize);

// Test 2 -- Card should come from supply pile.
  printf("Test: card came from supply piles.\n");

  for (i = 0; i < 10; i++){
  
    afterKingdom += k[i];
  }

  for (j = 1; j < 4; j++){
  
    afterVictory += state.supplyCount[j];
  }
  
  int totalAfterSupply = afterKingdom + afterVictory;

  asserttrue(totalBeforeSupply, totalAfterSupply);

// Test 3 -- Card should not be value greater than 4.
  printf("Test: card value 4 or less. Test Pass means attempt to get Mine failed.\n");
  choiceCard = mine;
  //asserttrue(card_remodel(&state, 0, choiceCard, trashCard, handPos), -1);
  asserttrue(cardEffect(remodel, trashCard, choiceCard, 0, &state, handPos, 0), -1);

}

int main(int argc, char *argv[]){
  
  testRemodel();
  return 0;
}
