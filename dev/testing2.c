//
// Created by Joshua Davis on 12/30/24.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "io.h"
#include "process.h"

int main() {
    int filesize;
    unsigned char* bmpData = read_bmp(&filesize);

    processBMP(bmpData, 0);

    write_bmp(bmpData, filesize);
}