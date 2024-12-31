#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "process.h"


// imageprocessor main function
int main(int argc, char** argv) {
    // check for correct number of arguments
    if (argc != 2) {
        // print error message to stderr
        fprintf(stderr, "Error: Incorrect number of arguments.\nFormat: imageprocessor <OPERATION>\nRun 'imageprocessor HELP' for help.\n");
        // return 1 for error
        return 1;
    }
    // create int to store file size
    int size;
    // create pointer to reference file bytes
    unsigned char* bmp;

    // HFLIP
    if (strcmp(argv[1], "HFLIP") == 0) {
        fprintf(stderr, "Reading input BMP file...\n");
        // read input BMP file from stdin
        bmp = read_bmp(&size);
        fprintf(stderr, "Processing input BMP file...\n");
        // process BMP bytes
        processBMP(bmp, 0);
        fprintf(stderr, "Writing output BMP file...\n");
        // write output BMP file to stdout
        write_bmp(bmp, size);
    // VFLIP
    } else if (strcmp(argv[1], "VFLIP") == 0) {
        fprintf(stderr, "Reading input BMP file...\n");
        // read input BMP file from stdin
        bmp = read_bmp(&size);
        fprintf(stderr, "Processing input BMP file...\n");
        // process BMP bytes
        processBMP(bmp, 1);
        fprintf(stderr, "Writing output BMP file...\n");
        // write output BMP file to stdout
        write_bmp(bmp, size);
    // GRAYSCALE
    } else if (strcmp(argv[1], "GRAYSCALE") == 0) {
        fprintf(stderr, "Reading input BMP file...\n");
        // read input BMP file from stdin
        bmp = read_bmp(&size);
        fprintf(stderr, "Processing input BMP file...\n");
        // process BMP bytes
        processBMP(bmp, 2);
        fprintf(stderr, "Writing output BMP file...\n");
        // write output BMP file to stdout
        write_bmp(bmp, size);
    // INFO
    } else if (strcmp(argv[1], "INFO") == 0) {
        fprintf(stderr, "Reading input BMP file...\n");
        // read input BMP file from stdin
        bmp = read_bmp(&size);
        fprintf(stderr, "Processing input BMP file...\n");
        // process BMP bytes and print info to stdout
        processBMP(bmp, 3);
    // HELP
    } else if (strcmp(argv[1], "HELP") == 0) {
        // set bmp to 0x0 to signal that the pointer was never used
        bmp = 0x0;
        // print usage instructions to stdout
        printf("\nGeneral Operations:\n");
        printf("cat INPUT.bmp | imageprocessor <OPERATION> > OUTPUT.bmp\n");
        printf("Valid General Operations: HFLIP, VFLIP, GRAYSCALE\n\n");
        printf("Other Operations:\n");
        printf("cat INPUT.bmp | imageprocessor <OPERATION>\n");
        printf("Valid General Operations: INFO\n\n");
    // invalid operation
    } else {
        // print error message to stderr
        fprintf(stderr, "Error: Invalid operation.\nValid Operations: HFLIP, VFLIP, GRAYSCALE\nRun 'imageprocessor HELP' for help.\n");
        // return 1 for error
        return 1;
    }
    // if bmp isn't 0x0 (if bmp pointer was used)
    if (bmp != 0x0) {
        // free dynamically allocated memory for buffer
        free(bmp);
    }
    // return 0 for success
    return 0;
}
