#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void main(){
    
    //Initializes game so we can unit test the function villagerefactored
    int handPos = 0;

    int seed = 10;
    int players = 2;
    int player = 0;
    
    struct gameState nGame;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    initializeGame(players, k, seed, &nGame);

    //Sets current hand count prior to function call in a variable
    int curHand = nGame.handCount[0];

    //Sets current actions prior to function call into a variable
    int curActions = nGame.numActions;

    //sets current deck count prior to function call into a variable
    int decks = nGame.deckCount[0];

    //Sets current playuedpile to 0 prior to the function call.
    nGame.playedCardCount = 0;
    //Calls villageRefactored function with appropriate arguments predefined above
    villageRefactored(player, &nGame, handPos);

    //Subtracts prior call deck count to new deck count
    int nDeck = decks - nGame.deckCount[0];

    printf("Unit test for village to test if a card was drawn properly\n");

    //Checks to see how many cards in total was drawn.
    if (nGame.deckCount[0] == decks - 1)
    {
        printf("Unit test passed! 1 card was drawn.\n\n");
    }

    //If total amount of cards exceed the previous hand prior to function call then more cards were either drawn or discard call didn't work
    else if (nGame.deckCount[0] < decks - 1)
    {
        printf("Unit test failed! More than one card was drawn.\n\n");
    }

    //Checks if current hand is less than the prior hand which would mean that no card was drawn or 2 cards were discarded instead of one
    else if (nGame.deckCount[0] == decks)
    {
        printf("Unit test failed! No card was drawn .\n\n");
    }

    else
    {
        printf("Unit test failed! For some reason you lost a card.\n\n");
    }

    printf("Unit test to see if number of actions is increased by 2.\n");

    //Checks number of actions increased by the function call
    if (curActions + 2 == nGame.numActions)
    {
        printf("Unit test passed! The number of actions are increased by 2.\n\n");
    }

    else if (nGame.numActions == curActions + 1)
    {
        printf("Unit test failed! The number of actions are increased by 1.\n\n");
    }

    else if (nGame.numActions == 0)
    {
        printf("Unit test failed! The number of actions are 0.\n\n");
    }

    else
    {
        printf("Unit test failed! Everything crashed.\n\n");
    }

    printf("Unit test to see if discard card is properly discarded.\n");

    if (nDeck > -1 && nGame.handCount[0] == curHand + nDeck - 1 )
    {
        printf("Unit test passed! Card was successfully discarded from hand.\n\n");
    }

    else
    {
        printf("Unit test failed! Card was not successfully discarded from hand.\n\n");
    }

    //Checks to see if discarded card is placed in play piled instead of being trashed
    
    printf("Unit test to test if discarded card is placed into the play pile.\n");
    if (nGame.playedCardCount == 1)
    {
        printf("Unit test passed! Card was successfully placed into the played pile.\n");
    }

    else
    {
        printf("Unit test failed! Card was not successfully placed into played pile.\n");
    }


}

