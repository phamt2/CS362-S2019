#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void main(){
    
    //Initializes srand to randomize numbers based on time.
    srand(time(NULL));

    //Initializes variables to store how many error counts there are out of how many times the function villageRefactored is called.
    int drawErrorCount = 0;
    int actionErrorCount = 0;
    int removeErrorCount = 0;
    int discardErrorCount = 0;
    int timesRan = 0;

    //Loop in order to test the randomtest 5000 times per player.
    for (int b = 0; b < 5000; b++)
    {
        //Initializes the amount of players that will be in the game based on the max players which was 4.
        int randomPlayers = 2 + rand() % 2;

        //Initializes game with the randomPlayers variable so we can call the villageRefactored function later.
        int handPos = 0;
        int seed = 10;
        struct gameState nGame;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
        initializeGame(randomPlayers, k, seed, &nGame);

        //Prints how many players are in the game to keep track of how many players this initialization has.
        printf("\nNumber of players this game is: %d\n", randomPlayers);

        //Loops for the amount of players this round has.
        for (int i = 0; i < randomPlayers; i++)
        {

            //Sets random deck count from 1 - 500 and grabs a random number from that number to be estates.
            int randomDeckCount = 1 + rand() % 499;
            int randomEstateCount = rand() % randomDeckCount;
            
            //Prints out deck size for this player.
            printf("Testing deck size of %d for player %d.\n", randomDeckCount, i + 1);

            //Sets deck count to 0 first then initializes deck of current player to a deck filled with estate cards based on the variable from randomEstateCount then from there it will subtract the estate count cards from the max card count to get the amount of coppers that will be placed within the deck.
            nGame.deckCount[i] = 0;

            for (int a = 0; a < randomEstateCount; a++)
            {
                nGame.deck[i][a] = estate;
                nGame.deckCount[i]++;
            }

            for (int a = randomEstateCount; a < randomDeckCount; a++)
            {
                nGame.deck[i][a] = copper;
                nGame.deckCount[i]++;
            }

            //Sets random amount of actions to test
            int randomAction = rand() % 30;
            
            printf("Number of actions for this player is %d\n", randomAction);

            //Sets number of actions in total to the game..
            nGame.numActions = randomAction;

            //Sets number of played cards pile
            int randomPlayed = rand() % randomDeckCount;
            nGame.playedCardCount = randomPlayed;

            //Sets number of cards in current players hand
            nGame.handCount[i] = 1 + rand() % 499;
            int beforeHand = nGame.handCount[i];

            villageRefactored(i, &nGame, handPos);


            //Checks to see if a card was drawn from the deck appropriately
            if ((randomDeckCount - 1) == nGame.deckCount[i])
            {
                printf("The draw was correct\n");
            }

            else if ((randomDeckCount - 1) < nGame.deckCount[i])
            {
                printf("The draw was incorrect. Village card did not draw from the deck.\n");
                drawErrorCount++;
            }

            else
            {
                printf("The draw was incorrect. Village card drew %d cards instead", (randomDeckCount - nGame.deckCount[i]));
                drawErrorCount++;
            }

            //Checks to see if number of actions was increased by 2 appropriately.
            if ((randomAction + 2) == nGame.numActions)
            {
                printf("The number of actions was correct\n");
            }

            else
            {
                printf("The number of actions was incorrectly added\n");
                actionErrorCount++;
            }

            //Checks to see if number of cards in the played pile is appropriately discarded correctly.
            if (nGame.handCount[i] == beforeHand)
            {
                printf("Card was removed from hand appropriately\n");
            }

            else
            {
                printf("Card was not removed from hand appropriately\n");
                removeErrorCount++;
            }

            if (nGame.numActions + 1 == randomAction)
            {
                printf("Village card was discarded properly into the played pile\n");
            }

            else
            {
                printf("Village card was not discarded in the play pile\n");
                discardErrorCount++;
            }

            timesRan++;
        } 
    }

    //Prints out total of errors within each action of the function villageRefactored
    printf("\nTOTAL NUMBER OF DRAW ERRORS: %d OUT OF %d\n", drawErrorCount, timesRan);    
    printf("\nTOTAL NUMBER OF ACTION ERRORS: %d OUT OF %d\n", actionErrorCount, timesRan);    
    printf("\nTOTAL NUMBER OF HAND DISCARD ERRORS: %d OUT OF %d\n", removeErrorCount, timesRan);   
    printf("\nTOTAL NUMBER OF PLAYED PILE DISCARD ERRORS: %d OUT OF %d\n", discardErrorCount, timesRan);    

}

