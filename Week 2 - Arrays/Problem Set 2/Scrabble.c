#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Functions
int result(char *a, char *b);

int main(void)
{
    char *player1Phrase = get_string("Player 1: "); // Prompts player 1 for their phrase
    char *player2Phrase = get_string("Player 2: "); // Prompts player 2 for their phrase

    switch (result(player1Phrase, player2Phrase))
    {
        case 0:
            printf("Player 1 wins!\n");
            break;
        case 1:
            printf("Player 2 wins!\n");
            break;
        case 2:
            printf("Tie!\n");
            break;
    }
}

// Function that will help us decide the result of the Scrabble game
int result(char *a, char *b)
{
    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Alphabet
    int values[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; // Values of each letter

    int player1Score = 0, player2Score = 0; // We store each player's score here

    // First for loop will iterate through the alphabet
    for (int i = 0, len = strlen(alphabet); i < len; i++)
    {
        // Then, for each letter of the alphabet, we will clash it against the string of each player
        for (int j = 0, lenA = strlen(a); j < lenA; j++) // Loop for player 1
        {
            if (alphabet[i] == toupper(a[j]))
            {
                player1Score += values[i];
                // If a match is found, the value is added to the player's score
            }
        }
        for (int l = 0, lenB = strlen(b); l < lenB; l++) // Loop for player 2
        {
            if (alphabet[i] == toupper(b[l]))
            {
                player2Score += values[i];
            }
        }
        // Each player has their own loop in order to minimize the amount of iterations done
    }

    if (player1Score > player2Score)
    {
        return 0; // Player 1 wins
    }
    else if (player1Score < player2Score)
    {
        return 1; // Player 2 wins
    }
    else
    {
        return 2; // Tie
    }
}
