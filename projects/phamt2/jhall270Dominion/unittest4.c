#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can unit test the function embargoRefactored
    int handPos = 0;

    int seed = 10;
    int players = 2;
    int player = 0;
    
    struct gameState nGame;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(players, k, seed, &nGame);

    //Sets choice1 to be 0;
    int choice1 = 0,
        choice2 = 0,
        choice3 = 0;

    int bonus = 0;

    printf("Unit test to see if embargoRefactored gives 2 coins.\n");

    //Stores current coins in a vriable
    int curCoins = nGame.coins;

    cardEffect(embargo, choice1, choice2, choice3, &nGame, handPos, &bonus);

    //Checks to see if appropriate amount of coins are increased after function is called.
    if (curCoins + 2 == nGame.coins)
    {
        printf("Unit test passed! Coins were appropriately added to the player.\n\n");
    }

    else if (curCoins + 1 == nGame.coins)
    {
        printf("Unit test failed! Coins were not appropriately added. Only one coin was added.\n\n");
    }

    else if (curCoins > nGame.coins)
    {
        printf("Unit test failed! Coins were somehow lost.\n\n");
    }

    else 
    {
        printf("Unit test failed! Coins did not add appropriately.\n\n");
    }

    //Sets embargo coins to 0
    nGame.embargoTokens[0] = 0;

    //Sets choice to 0
    choice1 = 0;

    //Calls embargo function again with new arguments
    cardEffect(embargo, choice1, choice2, choice3, &nGame, handPos, &bonus);

    printf("Unit test to check if embargo token is appropriately added.\n");

    //Checks if embargo tokens are increased appropriately after function call
    if (nGame.embargoTokens[0] == 1)
    {
        printf("Unit test passed! Embargo tokens was appropriately increased.\n");
    }

    else
    {
        printf("Unit test failed! Embargo tokens was not added approrpiately.\n");
    }
}

