#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can card test adventurer refactored
    int seed = 10;
    int players = 2;
    int player = 0;
    int drawnTreasure = 0;
    
    struct gameState nGame;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(players, k, seed, &nGame);

    //Saves currenthand count in a variable before function is called
    int curHand = nGame.handCount[0];

    printf("Card test to see adventurer function works properly by adding 2 treasures to the hand.\n");

    //Calls adventurer function with the arguments we predefined earlier
    adventurerRefactored(drawnTreasure, &nGame, player);

    //Checks to see overall amount of cards in hand after function call if there is 2 more than initially then the function call was correctly done and 2 treasures were added to the hand correctly.
    if (curHand + 2 == nGame.handCount[0])
    {
        printf("Card test passed! 2 treasures were appropriately drawn.\n\n");
    }

    else
    {
        printf("Card test failed! 2 treasures were not drawn appropriately.\n\n");
    }

    //Checks to see if there is any leftover discardCount in the players hand if not that means that the cards were discarded appropriately.
    printf("Card test to see if adventurer function discards all cards properly.\n");
    
    if (nGame.discardCount[0] == 0)
    {
        printf("Card test passed! Cards were properly discarded.\n");
    }

    else
    {
        printf("Card test failed! Cards were not properly discarded.\n");
    }
}

