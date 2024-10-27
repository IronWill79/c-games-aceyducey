#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));

    printf("Acey Ducey Card Game\nOriginally by Creative Computing - Morristown, New Jersey\n\nAcey Ducey is played in the following manner.\nThe dealer (computer) deals two cards face up. You have an option to bet or not bet depending on whether or not you feel the card will have a value between the first two.\nIf you do not want to bet, input a '0'\n\n");

    int money = 100;
    int card1 = 0;
    int card2 = 0;
    int dealerCard = 0;

    printf("You now have %i dollars\n\n", money);

    bool shouldQuit = false;

    do
    {
        printf("Here are your next two cards\n");

        do
        {
            do
            {
                card1 = (rand() % 14) + 2;
            } while (card1 < 2 || card1 > 14);

            do
            {
                card2 = (rand() % 14) + 2;
            } while (card2 < 2 || card2 > 14);
        } while (card1 >= card2);

        if (card1 < 11)
        {
            printf("%i\n", card1);
        }
        else if (card1 == 11)
        {
            printf("JACK\n");
        }
        else if (card1 == 12)
        {
            printf("QUEEN\n");
        }
        else if (card1 == 13)
        {
            printf("KING\n");
        }
        else if (card1 == 14)
        {
            printf("ACE\n");
        }

        if (card2 < 11)
        {
            printf("%i\n", card2);
        }
        else if (card2 == 11)
        {
            printf("JACK\n");
        }
        else if (card2 == 12)
        {
            printf("QUEEN\n");
        }
        else if (card2 == 13)
        {
            printf("KING\n");
        }
        else if (card2 == 14)
        {
            printf("ACE\n");
        }

        bool validBet = false;
        int bet = 0;

        do
        {
            printf("What is your bet?\n");
            char rawInput[80];
            char *inputStr;

            errno = 0;
            fgets(rawInput, sizeof(rawInput) / sizeof(rawInput[0]), stdin);
            bet = (int)strtol(rawInput, &inputStr, 10);

            if (errno == ERANGE || *inputStr != '\0')
            {
                // Invalid bet entered
                printf("Invalid amount bet. Try again.\n\n");
            }
            else if (bet == 0)
            {
                printf("Chicken!!\n\n");
                validBet = true;
            }
            else if (bet > money)
            {
                printf("Sorry, my friend, but you bet too much. You only have %i dollars to bet.", money);
            }
        } while (!validBet);

        do
        {
            dealerCard = (rand() % 14) + 2;
        } while (dealerCard < 2 || dealerCard > 14);

        if (dealerCard < 11)
        {
            printf("%i\n", dealerCard);
        }
        else if (dealerCard == 11)
        {
            printf("JACK\n");
        }
        else if (dealerCard == 12)
        {
            printf("QUEEN\n");
        }
        else if (dealerCard == 13)
        {
            printf("KING\n");
        }
        else if (dealerCard == 14)
        {
            printf("ACE\n");
        }

        if (dealerCard <= card1 && dealerCard < card2)
        {
            printf("You win!!!\n");
            money += bet;
        }
        else
        {
            printf("Sorry, you lose\n");
            if (bet < money)
            {
                money -= bet;
            }
            else
            {
                printf("Sorry, friend, but you blew your wad.\nTry again (Yes or No)\n");

                char rawInput[80];
                char *input;
                fgets(rawInput, sizeof(rawInput) / sizeof(rawInput[0]), stdin);
                sscanf(rawInput, " %s", &input);
                if (input != "Yes")
                {
                    printf("Ok hope you had fun!");
                    shouldQuit = true;
                }
            }
        }
    } while (!shouldQuit);

    return EXIT_SUCCESS;
}
