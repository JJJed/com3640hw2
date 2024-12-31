//
// Created by Joshua Davis on 12/27/24.
//

#include <stdlib.h>
#include <stdio.h>

int main() {
    char *hexstring = "001Ah";
    int location = (int)strtol(hexstring, NULL, 16);
    printf("%i\n", location);
}