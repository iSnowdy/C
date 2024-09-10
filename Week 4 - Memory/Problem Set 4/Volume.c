// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]); // We get the factor the increase the volume by and store it

    // TODO: Copy header from input file to output file (cp)
    uint8_t *header = malloc(HEADER_SIZE); // Dynamically allocate memory
    if (header == NULL)
    { // If there is no space, abort
        fclose(input);
        fclose(output);
        printf("Memory allocation has failed\n");
        return 1;
    }
    // The bytes of the header of a WAV file can be treated with and unsigned int of 8 bits

    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
    // No while needed because we read and copy the 'entire' chunk at once

    // TODO: Read samples from input file and write updated data to output file
    int16_t *buffer = malloc(sizeof(int16_t));
    if (buffer == NULL)
    { // Once again, handle the case where there's no memory available
        fclose(input);
        fclose(output);
        printf("Memory allocation has failed\n");
        return 1;
    }
    // To represent samples, on the other hand, an unsigned int is not enough
    // Hence why use a signed int of 16 bits
    while (fread(buffer, sizeof(int16_t), 1, input))
    {
        *buffer *= factor;
        // We modify the temporary data taken from the OG file by the factor the user wants
        fwrite(buffer, sizeof(int16_t), 1, output);
    }
    // Close files and free up memory as to prevent memory leaks
    free(header);
    free(buffer);
    fclose(input);
    fclose(output);
}
