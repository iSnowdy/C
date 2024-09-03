#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
char *substitutionCipher(char *plaintext, char *key);

int main(int argc, char *argv[])
{
    // First of all, we check for a valid input parameter by CLA
    if (argc != 2)
    { // Only one input besides the run command should be given
        printf("Wrong input. Please try again using ./substitution KEY\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    { // Alphabet length
        printf("Provide a valid KEY parameter (length)\n");
        return 1;
    }

    int letterCount[26] = {0};
    // An array of ints of size 26. One slot for each letter of the
    // alphabet

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isalpha(argv[1][i]))
        { // Everything must be alphabet characters
            printf("Provide a valid KEY parameter (alphabet)\n");
            return 1;
        }

        int freqIndex = toupper(argv[1][i]) - 'A';
        // The index is occupied by letters of the alphabet from 0 to 25 (-A)
        letterCount[freqIndex]++; // The occurence is updated. So if there is more than
        // once occurence, the count at that index will be > 1
        if (letterCount[freqIndex] > 1)
        {
            printf("Provide a valid KEY parameter (no repeats)\n");
            return 1;
        }
    }

    char *plaintext = get_string("plaintext:  ");
    char *ciphertext = substitutionCipher(plaintext, argv[1]);

    printf("ciphertext: %s\n", ciphertext);
}

// Function that takes in as a parameter two strings. The plaintext and they key
// that we will use to substitute the plaintext to the ciphertext
char *substitutionCipher(char *plaintext, char *key)
{
    const int len = strlen(plaintext);
    char *ciphertext = malloc(len + 1); // We allocate memory to the result string

    for (int i = 0; i < len; i++)
    {
        char plaintextplaceholder;
        char cipherplaceholder = plaintext[i];

        // With the if's we make sure we are handling it case-sensitive
        if (cipherplaceholder >= 'A' && cipherplaceholder <= 'Z')
        {
            int value = (int) plaintext[i] - 65;
            plaintextplaceholder = toupper(key[value]); // To find out the index
        }
        else if (cipherplaceholder >= 'a' && cipherplaceholder <= 'z')
        {
            int value = (int) plaintext[i] - 97;
            plaintextplaceholder = tolower(key[value]);
        }
        else
        {
            plaintextplaceholder = cipherplaceholder;
        }
        ciphertext[i] = plaintextplaceholder;
    }
    ciphertext[len] = '\0';
    return ciphertext;
}
