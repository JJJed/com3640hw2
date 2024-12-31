//
// Created by Joshua Davis on 12/31/24.
//

#include <stdio.h>
#include <string.h>

void debug_memcpy(void* dest, void* src, size_t n) {
    printf("Debug: Copying %zu bytes from %p to %p\n", n, src, dest);
    printf("Source data: ");
    unsigned char* src_bytes = (unsigned char*)src;
    for (size_t i = 0; i < n; i++) {
        printf("%02X ", src_bytes[i]);
    }
    printf("\n");

    memcpy(dest, src, n);

    printf("Destination data after copy: ");
    unsigned char* dest_bytes = (unsigned char*)dest;
    for (size_t i = 0; i < n; i++) {
        printf("%02X ", dest_bytes[i]);
    }
    printf("\n");
}