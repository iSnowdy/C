#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *filename = argv[1];

    FILE *file = fopen(filename, "r"); // Open the file only read mode
    if (file == NULL) {
        return 1;
    }
    uint8_t buffer[4]; // Our Buffer to read the file is 4 bytes long
    // It is 4 bytes instead of 1 because PDF files have a 4 bytes signature int at the beginning
    // We can't really use an int type of data because it is 4 bytes long, not 1 byte long. So the data
    // read would not be accurate

    fread(buffer, 1, 4, file); // read to - how big the chunks to read - how many chunks read at once - from where

    for (int i = 0; i < 4; i++) {
        printf("%i\n", buffer[i]); // Should read: 37 80 68 70 ---> PDF signature 4 bytes
    }
    fclose(file);
    return 0;
}
