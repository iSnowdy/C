#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
char *caesarCipher(char *plaintext, int key);

int main(int argc, char *argv[])
{
    if (argc != 2)
    { // We only accept one parameter by CLA
        printf("Invalid inputt.\nPlease use./caesar key\n");
        return 1;
    }
    // We iterate through the input parameter by the user and make
    // sure it is composed of only digits
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            return 1;
        }
    }
    const int key = atoi(argv[1]); // We make the key passed by the user a constant

    char *plaintext = get_string("plaintext:  ");
    char *ciphertext = caesarCipher(plaintext, key);

    printf("plaintext:  %s\n", plaintext);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

// Function that takes the plaintext and the key as parameters and returns
// an array of characters, also called string, which is the ciphertext
char *caesarCipher(char *plaintext, int key)
{
    const int len = strlen(plaintext);
    char *ciphertext = malloc(len + 1);

    // With this algorithm we iterate through the plaintext, store temporarily
    // each character to be converted in a char and check if it is in
    // upper case or lower case, which is relevant due to wrapping
    for (int i = 0; i < len; i++)
    {
        char encriptedChar;
        char placeholder = plaintext[i];
        if (placeholder >= 'A' && placeholder <= 'Z')
        {
            encriptedChar = ((placeholder - 'A' + key) % 26) + 'A';
        }
        else if (placeholder >= 'a' && placeholder <= 'z')
        {
            encriptedChar = ((placeholder - 'a' + key) % 26) + 'a';
        }
        else
        {
            encriptedChar = placeholder;
        }
        ciphertext[i] = encriptedChar;
    }
    ciphertext[len] = '\0'; // We finish the array
    return ciphertext;
}
