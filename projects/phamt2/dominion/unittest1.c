#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can unit test the function smithyRefactored
    int handPos = 0;

    int seed = 10;
    int players = 2;
    int player = 0;
    
    struct gameState nGame;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(players, k, seed, &nGame);

    //Sets current hand prior to function call in a variable
    int curHand = nGame.handCount[0];

    //Initializes function
    smithyRefactored(player, &nGame, handPos);

    //Checks how many cards are in the hand after function is called. Should be 3 drawn cards then 1 card discarded which should equal to 2 cards drawn.
    printf("Unit test for smithy to test how many cards end up being in the hand after smithy function is called.\n");

    if (curHand + 2 == nGame.handCount[0])
    {
        printf("Unit test passed! Two cards in total is added to the hand.\n");
    }
    else
    {
        printf("Unit test failed! Two cards in total was not added to the hand.\n");
    }
        
}
