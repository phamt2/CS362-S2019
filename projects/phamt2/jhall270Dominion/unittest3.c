#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can unit test the function stewardrefactored
    int handPos = 0;

    int seed = 10;
    int players = 2;
    int player = 0;

    //Adding more arguments
    int bonus = 0;
    
    struct gameState nGame;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(players, k, seed, &nGame);

    printf("Unit test for steward to check to see if choice 1 works properly.\n");
    int choice1 = 1,
        choice2 = 2,
        choice3 = 3;

    //Puts current hand count in variable
    int curHand = nGame.handCount[0];

    //Puts current deck count in variable
    int curDeck = nGame.deckCount[0];

    //Calls steward function
    cardEffect(steward, choice1, choice2, choice3, &nGame, handPos, &bonus);

    //Checks to see how many cards are drawn from the deck
    if (curDeck - 2 == nGame.deckCount[0])
    {
        printf("Unit test passed! Player drew two cards!\n\n");
    }

    else if (curDeck - 1 == nGame.deckCount[0])
    {
        printf("Unit test failed! Player drew one card instead of two.\n\n");
    }

    else
    {
        printf("Unit test failed!\n\n");
    }

    printf("Unit test to test if choice 2 works properly\n");

    //Sets up arguments and calls steward function to test for choice 2
    choice1 = 2,
    choice2 = 2,
    choice3 = 3;
    int curCoins = nGame.coins;
    cardEffect(steward, choice1, choice2, choice3, &nGame, handPos, &bonus);

    //Checks if coins were added to check if choice2 works properly
    if (curCoins == nGame.coins)
    {
        printf("Unit test failed! No coins were added.\n\n");
    }

    else if (curCoins + 1 == nGame.coins)
    {
        printf("Unit test failed! Only one coin was added.\n\n");
    }

    else if (curCoins + 2 == nGame.coins)
    {
        printf("Unit test passed! Two coins was added.\n\n");
    }

    else
    {
        printf("Unit test failed! Choice failed all together and nothing happened.\n\n");
    }

    //Initializes and calls steward function again to test for choice 3
    choice1 = 3,
    choice2 = 2,
    choice3 = 3;
    
    int curHand3 = nGame.handCount[0];
    cardEffect(steward, choice1, choice2, choice3, &nGame, handPos, &bonus);

    printf("Unit test to check if player can choose to trash 2 cards in hand\n");

    //Tests if cards were appropriately trashed at the end to test for choice 3
    if (curHand3 - 3 == nGame.handCount[0])
    {
        printf("Unit test passed! 2 cards were trashed appropriately.\n");
    }

    else if (curHand3 - 2 == nGame.handCount[0])
    {
        printf("Unit test failed! Only 1 card was trashed appropriately.\n");
    }

    else
    {
        printf("Unit test failed! Nothing worked properly choice was not selected properly.\n");
    }

}

