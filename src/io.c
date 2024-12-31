//
// Created by Joshua Davis on 12/27/24.
//

#include <stdio.h>
#include <stdlib.h>

// get file bytes from stdin, return pointer to buffer containing file bytes
unsigned char* read_bmp(int* filesize) {
    // Create a buffer to store the BMP data
    unsigned char* data = malloc(10000000);  // 10MB max size

    // Read entire file into buffer
    *filesize = fread(data, 1, 10000000, stdin);

    // return pointer to buffer
    return data;
}

// write file bytes in buffer to stdout
void write_bmp(unsigned char* data, int filesize) {
    fwrite(data, 1, filesize, stdout);
}