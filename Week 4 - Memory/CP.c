#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE; // Declaring that the structure called BYTE is composed of 8 bits of a byte

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    FILE *src = fopen(argv[1], "rb"); // Binary data reading
    FILE *dst = fopen(argv[2], "wb"); // Binary data writing

    BYTE b; // BYTE is the structure we created; its not native to C

    // Now we copy the file from src to dst

    // Reads a file. We need to pass the reference of b (pass by reference), to put them one at a time. How big? well, we could indicate
    // 1 byte or just sizeof to be sure. How many to copy at a time? 1. And finally, where to read from? from src
    // The function will return how many were read. So it will succeed as long as it does not return 0. It should only return 0 once
    // it has finished reading and copying the whole file, returning then 0 and ending the while loop
    while (fread(&b, sizeof(b), 1, src) != 0) {
        fwrite(&b, sizeof(b), 1, dst);
    }
    fclose(src);
    fclose(dst);
}
