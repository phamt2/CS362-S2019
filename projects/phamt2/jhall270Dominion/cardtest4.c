#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can card test the outpost card
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

    //Set ouptpost played prior to function call to 0
    nGame.outpostPlayed = 0;

    //Puts currenthand prior to the call in a variable to keep track of what the hand looked like before the call.
    int currentHand = nGame.handCount[0];

    //Function call to cardEffect with the switch case of the outpost card
    cardEffect(outpost, choice1, choice2, choice3, &nGame, handPos, &bonus);

    printf("Card test to see if outpost flag was added and card was discarded.\n");

    //Checks to see if the outpost switch added one outpost
    if (nGame.outpostPlayed == 1)
    {
        printf("Card test passed! Outpost flag was added.\n");
    }

    else
    {
        printf("Card test failed! Outpost flag was not added properly.\n");
    }

    //Checked to see if 1 card was discarded from the hand appropriately.
    if (currentHand == nGame.handCount[0] + 1)
    {
        printf("Card test passed! 1 card was discarded from the hand.\n");
    }

    else
    {
        printf("card test failed! 1 card was not discarded from the hand.\n");
    }
}

