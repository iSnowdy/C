#include <ctype.h> // isalpha
#include <math.h>  // round
#include <stdio.h>
#include <string.h> // strlen

// Functions
float colemanLiauIndex(char *text);

int main(void)
{
    char *text = get_string("Text:");
    int index = round(colemanLiauIndex(text)); // We round the index to the nearest integer

    // Criteria explained
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

float colemanLiauIndex(char *text)
{
    float L = 0.0, S = 0.0;
    int words = 1; // Since we can not check the first word, we initialize it at 1
    // L is the average number of letters per 100 words in a text
    // S is the average number of sentences per 100 words in a text

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        { // Every space is a word, basically
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        { // Endings of a sentence
            S++;
        }
        if (isalpha(text[i]))
        { // Checks if the character is in the alphabet
            L++;
        }
    }

    L = (L / words) * 100.0; // Average number of letters per 100 words
    S = (S / words) * 100.0; // Average number of sentences per 100 words

    return 0.0588 * L - 0.296 * S - 15.8; // Formula for the index
}
