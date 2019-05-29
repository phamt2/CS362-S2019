#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can card test one of the switch calls of the card effect function of great_hall card.
    int handPos = 0;

    int seed = 10;
    int players = 2;

    int choice1 = 0,
        choice2 = 0,
        choice3 = 0,
        bonus = 0;
    
    struct gameState nGame;


    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(players, k, seed, &nGame);

    //Sets number of actions to zero
    nGame.numActions = 0;

    //Puts deckcount prior to function call into variable
    int deckCounter = nGame.deckCount[0];

    //Puts current hand count prior to function call into variable.
    int currentHand = nGame.handCount[0];

    //Calls on the cardEffect function to activate switch of great_hall
    cardEffect(great_hall, choice1, choice2, choice3, &nGame, handPos, &bonus);

    printf("Card test to see if great_hall adds a card, an action, and discards a card.\n");

    //Subtracts deck counter prior to the call and after the call to find the amount of cards drawn in total.
    int decks = deckCounter - nGame.deckCount[0];

    //Checks to see how many cards were drawn from the deck
    if (decks == 1)
    {
        printf("Card test passed! 1 card was drawn from the deck.\n");
    }

    else
    {
        printf("Card test failed! Inappropriate amount of cards were drawn from the deck.\n");
    }

    //Checks to see how many actions was added after the function was called
    if (nGame.numActions == 1)
    {
        printf("Card test passed! 1 action was added.\n");
    }

    else
    {
        printf("Card test failed! 1 action was not added.\n");
    }

    //Checks to see if the discard part of the call worked.
    if ((currentHand + decks) - 1 == nGame.handCount[0])
    {
        printf("Card test passed! 1 card was discarded.\n");
    }

    else
    {
        printf("Card test failed! 1 card was not discarded.\n");
    }
}

