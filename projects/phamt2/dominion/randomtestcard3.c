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

    int wrong = 0;
    int right = 0;
    int drawRight = 0;
    int drawWrong = 0;
    int treasureRight = 0;
    int treasureWrong = 0;

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
            //Sets random deck count from 1 - 500 and grabs a random number from that number to be estates.
            int randomDeckCount = 1 + rand() % 498;

            //Initializes random copper, silver, and gold coins from the leftover amount after the estate is initialized
            int randomEstateCount = rand() % randomDeckCount;

            int leftOver = randomDeckCount - randomEstateCount;

            if (leftOver % 2 != 0)
            {
                leftOver = leftOver + 1;
                randomDeckCount = randomDeckCount + 1;
            }


            //Sets total number of coins within a variable
            int totalCoins = leftOver;
            int randomCopperCount = rand() % leftOver;
            leftOver = leftOver - randomCopperCount;
            int randomSilverCount = rand() % leftOver;
            leftOver = leftOver - randomSilverCount;
            
            //Prints out deck size for this player.
            printf("Testing deck size of %d for player %d.\n", randomDeckCount, i + 1);

            //Sets deck count to 0 first then initializes deck of current player to a deck filled with estate cards based on the variable from randomEstateCount. Sets copper count based on randomCopperCount variabe, sets silver count based on randomSilverCount variable and sets gold count based on randomGoldCount variable.
            nGame.deckCount[i] = 0;

            int numTreasure = 0;

            for (int a = 0; a < randomEstateCount; a++)
            {
                nGame.deck[i][a] = estate;
                nGame.deckCount[i]++;
            }

            for (int a = randomEstateCount; a < (randomCopperCount + randomEstateCount); a++)
            {
                nGame.deck[i][a] = copper;
                nGame.deckCount[i]++;
            }

            for (int a = (randomEstateCount + randomCopperCount); a < (randomEstateCount + randomCopperCount + randomSilverCount); a++)
            {
                nGame.deck[i][a] = silver;
                nGame.deckCount[i]++;
            }

            for (int a = (randomEstateCount + randomCopperCount + randomSilverCount); a < randomDeckCount; a++)
            {
                nGame.deck[i][a] = gold;
                nGame.deckCount[i]++;
            }

            //Shuffles deck using source from original dominion.c file
            shuffle(i, &nGame);

            //Prints out deck count total and then the amount of estate cards within that deck and the amount of coins in that deck
            printf("DECK COUNT %d\n", nGame.deckCount[i]);
            printf("ESTATE CARDS %d\n", randomEstateCount);
            printf("COINS CARDS %d\n", totalCoins);

            //Sets hand count to 0 to be as consistent as possible
            nGame.handCount[i] = 0;
            
            //While loops till the deck count is equal to or less than the estate cards indicating that at least all the coin cards can be all drawn
            while (nGame.deckCount[i] > randomEstateCount)
            {
                int beforeHand = nGame.handCount[i];

                int drawnTreasure = 0;

                //Calls function adventurer refactored
                adventurerRefactored(drawnTreasure, &nGame, i);

                //Checks if the 2 cards are drawn each time the adventurer is called and adds a counter for each right and each wrong
                if (beforeHand + 2 == nGame.handCount[i])
                {
                    printf("2 cards were drawn properly\n");
                    drawRight++;
                }

                else
                {
                    printf("%d were drawn instead\n", (nGame.handCount[i] - beforeHand));
                    drawWrong++;
                }

                //Counts each card in hand and checks if they are a coin. If so then add a treasure counter which will be used to add up how many treasure cards are drawn per function call and total amount of treasure cards drawn as indicated by how many are in the hand at the end of the while loop that loops until the deck becomes less than or equal to the estate count
                int treasureCounter = numTreasure;

                numTreasure = 0;

                for (int b = 0; b < nGame.handCount[i]; b++)
                {
                    int cardTest = nGame.hand[i][b];

                    if (cardTest == copper || cardTest == silver || cardTest == gold)
                    {
                        numTreasure++;
                    }
                }

                treasureCounter = numTreasure - treasureCounter;

                //Counts how many times the right amount of treasure is drawn vs the wrong amount
                if (treasureCounter == 2)
                {
                    printf("Number of treasure drawn is 2\n");
                    treasureRight++;
                }

                else
                {
                    printf("Number of treasure drawn is %d\n", treasureCounter);
                    treasureWrong++;
                }
            }

            //Counts how many times the treasures drawn are within the limit of the amount of coins within the deck vs not.
            if (numTreasure <= totalCoins)
            {
                printf("TOTAL NUMBER OF TREASURES DRAWN IS %d\n", numTreasure);
                right++;
            }

            else
            {
                printf("EXTRA NUMBER OF TREASURES DRAWN %d\n", numTreasure - totalCoins);
                wrong++;
            }

        }
    }

    //Prints out counters of all tests from above to see how many were correct or wrong in total.
    printf("\nNumber of times the right number of cards were drawn %d/%d\n", drawRight, (drawRight + drawWrong));
    printf("Number of times the wrong number of cards were drawn %d/%d\n\n", drawWrong, (drawRight + drawWrong));

    printf("Number of times the right number of treasures were drawn %d/%d\n", treasureRight, (treasureRight + treasureWrong));
    printf("Number of times the wrong number of treasures were drawn %d/%d\n\n", treasureWrong, (treasureRight + treasureWrong));

    printf("Number of times the treasure drawn did not exceed the amount of treasure in the deck %d/%d\n", right, (right + wrong));
    printf("Number of times the treasure drawn exceeded the amount of treasure in the bag %d/%d\n\n", wrong, (right + wrong));

}

