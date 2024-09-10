#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCKSIZE = 512;
const int filenameChars = 8; // ### (3), .jpg (4), null terminator (1)

int main(int argc, char *argv[])
{
    // Only 1 CLA accepted
    if (argc != 2)
    {
        printf("Usage: Usage: ./recover FILE\n");
        return 1;
    }
    // We open the file in read mode
    FILE *card = fopen(argv[1], "r");
    // We make sure we can open it
    if (card == NULL)
    {
        printf("Could not open the card\n");
        return 1;
    }
    uint8_t *buffer = malloc(BLOCKSIZE); // Dynamically allocate memory
    if (buffer == NULL)
    {
        printf("Memory allocation has failed\n");
        fclose(card);
        return 2;
    }

    FILE *img = NULL; // We initialize the img file to NULL
    int counter = 0;
    char *filename = malloc(filenameChars);
    // As long as we have blocks of size 512 (1 at a time) to read ...
    while (fread(buffer, 1, BLOCKSIZE, card) == BLOCKSIZE)
    { // fread(data, size, number, inptr)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Bitmasking technique with buffer[3]
            if (img != NULL)
            {
                fclose(
                    img); // Meaning if a JPEG is already open, close it before starting a new one
            }
            counter++;
            sprintf(filename, "%03i.jpg", counter - 1);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("File %s could not be created\n", filename);
                free(buffer);
                free(filename);
                fclose(card);
                return 3;
            }
            fwrite(buffer, 1, BLOCKSIZE, img); // Write for the first time
        }
        else
        {
            if (img != NULL)
            { // Continue writing
                fwrite(buffer, BLOCKSIZE, 1, img);
            }
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    printf("Terminating recover process...\n");
    free(buffer);
    free(filename);
    fclose(card);
    return 0;
}
