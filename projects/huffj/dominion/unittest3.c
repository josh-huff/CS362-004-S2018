/************************************************************
*
* unittest3.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS362 -- Spring 2018
* Assignment 3 
* -----------------
*
* Unit Test for testFullDeckCount() in dominion.c
*
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void testFullDeckCount() {

/*
int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
*/
	
  // Test 1 -- testFullDeckCount accurately finds the number of instances of the card in the player's deck
  // Test 2 -- testFullDeckCount accurately finds the number of instances of the card in the player's hand
  // Test 3 -- testFullDeckCount accurately finds the number of instances of the card in the player's discard

}

int main(int argc, char *argv[]){

  testFullDeckCount();
  return 0;
}
