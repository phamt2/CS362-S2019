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

    //Loop in order to test the randomtest 5000 times per player.
    for (int b = 0; b < 5000; b++)
    {
        //Initializes the amount of players that will be in the game based on the max players which was 4.
        int randomPlayers = 2 + rand() % 2;

        //Initializes game with the randomPlayers variable so we can call the cardEffect function to call the outpost card later.
        int seed = 10;
        struct gameState nGame;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
        initializeGame(randomPlayers, k, seed, &nGame);

        //Prints how many players are in the game to keep track of how many players this initialization has.
        printf("\nNumber of players this game is: %d\n", randomPlayers);

        //Loops for the amount of players this round has.
        for (int i = 0; i < randomPlayers; i++)
        {
            int choice1 = 0;
            int handPos = 0;
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

            //Initializes random coin count and random cards played to check to see if the discard works and if the coins are added correctly.
            int randomCoinCount = rand() % 10000;
            nGame.coins = randomCoinCount;

            int randomPlayed = rand() % 500;
            nGame.playedCardCount = randomPlayed;

            int randomHand = rand() % 500;
            nGame.handCount[i] = randomHand;

            //Calls embargoRefactored function
            embargoRefactored(&nGame, choice1, handPos, i);

            //Using assert to check instead of if statements to attempt to get 100 percent 
            //Checks for coins if function adds 2 coins
            assert(randomCoinCount + 2 == nGame.coins);
            printf("Coins increased by 2 appropriately.\n");

            //Checks to see if the hand count is decreased properly when discarding the card
            assert(randomHand - 1 == nGame.handCount[i]);
            printf("Hand count after card is played is decreased by 1 appropriately.\n");

            //Checks to see if the card is not in the played pile and is trashed instead
            assert(nGame.playedCardCount == randomPlayed);
            printf("Card is properly trashed.\n");
        }
    }
}


