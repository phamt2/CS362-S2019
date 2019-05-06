#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can card test for the function smithyRefactored
    int handPos = 0;

    int seed = 10;
    int players = 2;
    int player = 0;
    
    struct gameState nGame;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(players, k, seed, &nGame);

    //Puts current hand count in variable before function is called
    int curHand = nGame.handCount[0];

    //Puts current deck count in variable before function is called
    int deckCounter = nGame.deckCount[0];
    printf("Card test to test smithy if smithy appropriately draws and discards a card.\n");

    //Calls smithyRefactored function with predefined arguments
    smithyRefactored(player, &nGame, handPos);

    //Subtracts deckCounter from the new deckCounter after the function was called
    int counter = deckCounter - nGame.deckCount[0];

    //Subtracts the current hand from the previous hand before the funciton was called
    int counterHand = nGame.handCount[0] - curHand;

    //Subtracts 1 from counter which would indicate that a card was discarded from the amount of cards drawn.
    int handCheck = counter - 1;

    //Checks if the appropriate cards were drawn and the proper amount of cards remain in the hand after a card is discarded
    if (counter == 3 && counterHand == 2)
    {
        printf("Card test passed! 3 cards was drawn from the deck and 1 card was discarded from the hand.\n");
    }

    else if (counter < 3 && curHand + handCheck == nGame.handCount[0])
    {
        printf("Card test failed! %d was drawn instead and was discarded properly.\n", counter);
    }

    else if (counter == 3 && curHand + handCheck != nGame.handCount[0])
    {
       printf("Card test failed! 3 cards were drawn but was not discarded properly.\n");
    }

    else
    {
       printf("Card test failed! %d was drawn instead and was not discarded properly.\n", counter);
    } 

}
