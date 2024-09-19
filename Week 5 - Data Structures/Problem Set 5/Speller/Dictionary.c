// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

void print_buckets(void);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;
int wordCounter = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Obtain the hash value
    unsigned int index = hash(word);
    node *ptr = table[index];
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function that takes into account the first 2 chars of every word
    char firstChar = tolower(word[0]);
    char secondChar = (word[1] != '\0' ? tolower(word[1]) : 'a');

    unsigned int firstIndex = firstChar - 'a';
    unsigned int secondIndex = secondChar - 'a';

    unsigned int returnValue = firstIndex * 26 + secondIndex;
    // If the hash value is bigger than the size of the table, return error
    return (returnValue > 676) ? (printf("Hashing error\n"), -1) : returnValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) // dictionary = file name to read from
{
    // Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    // Check if it has been properly opened
    if (dict == NULL)
    {
        printf("Could not open the dictionary (%s)", dictionary);
        return false;
    }
    // Read each word in the file and then add each word to the hash table
    // Allocate just enough space for the max length of words (and the null terminator)
    char *tempWord = malloc((LENGTH + 1) * sizeof(char));
    if (tempWord == NULL)
    {
        printf("Memory allocation for new words has failed\n");
        return false;
    }
    // First, read Strings from the given file
    while (fscanf(dict, "%s", tempWord) != EOF)
    {
        node *n = malloc(sizeof(node)); // Allocate a quantity of node mem in n address
        if (n == NULL)
        {
            printf("Memory allocation for nodes has failed\n");
            free(tempWord);
            return false;
        }

        // Copy the words into the node
        strcpy(n->word, tempWord); // tempWord for every word in the dict
        n->next = NULL;            // Temporarily set to NULL

        // Hash the word to get the index so we can store the node in the array
        unsigned int hashCode = hash(tempWord);
        // Move pointer to the next node
        n->next = table[hashCode];
        table[hashCode] = n;
        wordCounter++; // Increase the word counter
        // Free dynamically allocated memory
        free(tempWord);
        // Allocate for a new word
        tempWord = malloc((LENGTH + 1) * sizeof(char));
        if (tempWord == NULL)
        {
            printf("Memory allocation for new words has failed\n");
            free(n);
            return false;
        }
    }
    // Close the dictionary and free space
    free(tempWord);
    fclose(dict);

    print_buckets();
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // We need to free each one of the nodes created
    // First, iterate through the Hash Table
    for (int i = 0; i < N; i++)
    {
        // We use two pointers so we can properly free up the memory
        node *ptr = table[i];
        // We need two to not lose track of the header of the list
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}

void print_buckets(void)
{
    unsigned long sum_sq = 0;
    int num_words = (int)size();

    // use dynamic memory allocation instead of the stack for these arrays,
    // in order to prevent a possible stack overflow
    int *collisionCount = calloc(num_words, sizeof *collisionCount);
    int *bucketCounter  = calloc(N, sizeof *bucketCounter);
    if (bucketCounter == NULL || collisionCount == NULL)
    {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    // fill bucketCounter array
    for (int i = 0; i < N; i++)
    {
        for (node *p = table[i]; p != NULL; p = p->next)
        {
            bucketCounter[i]++;
        }
    }

    // fill collisionCount array
    for (int i = 0; i < N; i++)
    {
        collisionCount[bucketCounter[i]]++;
    }

    // print content of collisionCount array and update sum_sq
    for (int i = 0; i < num_words; i++)
    {
        if (collisionCount[i])
        {
            sum_sq += (long) i * i * collisionCount[i];
            printf("Buckets with %i nodes: %i\n", i, collisionCount[i]);
        }
    }

    // print final information
    printf("\n");
    printf("Sum  of squares: %lu\n",  sum_sq);
    printf("Mean of squares: %.3f\n", (double)sum_sq / num_words);

    // Exit the program prematurely, so that you can see the diagnostic output
    // instead of the misspelled words. Exiting prematurely will cause memory leaks,
    // so don't run this function with valgrind.
    exit(EXIT_SUCCESS);
}
