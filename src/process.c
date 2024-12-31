//
// Created by Joshua Davis on 12/27/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// function to convert hex offsets (hex offsets are used to locate header data) to ints
int hexOffsetToInt(char* hexOffset) {
    return (int)strtol(hexOffset, NULL, 16);
}

// function to get R, G, and B values for a RGB565 pixel
void get_rgb565_from_2_byte_pixel(uint16_t pixel, uint8_t* red, uint8_t* green, uint8_t* blue, uint16_t red_mask, uint16_t green_mask, uint16_t blue_mask) {
    // Masks for RGB565
//    uint16_t red_mask = 0xF800;
//    uint16_t green_mask = 0x07E0;
//    uint16_t blue_mask = 0x001F;


    // Extract 5/6-bit values
    uint16_t red_value = (pixel & red_mask) >> 11;   // Extract red (5 bits)
    uint16_t green_value = (pixel & green_mask) >> 5; // Extract green (6 bits)
    uint16_t blue_value = (pixel & blue_mask);       // Extract blue (5 bits)

    // Scale to 8-bit values
    *red = red_value << 3;   // Scale 5 bits to 8 bits
    *green = green_value << 2; // Scale 6 bits to 8 bits
    *blue = blue_value << 3;   // Scale 5 bits to 8 bits
}

// function to get R, G, and B values for a RGB555 pixel
void get_rgb555_from_2_byte_pixel(uint16_t pixel, uint8_t* red, uint8_t* green, uint8_t* blue, uint16_t red_mask, uint16_t green_mask, uint16_t blue_mask) {
    // Masks for RGB565
//    uint16_t red_mask = 0x7C00;
//    uint16_t green_mask = 0x3E0;
//    uint16_t blue_mask = 0x1F;

    // Extract 5/6-bit values
    uint16_t red_value = (pixel & red_mask) >> 10;   // Extract red (5 bits)
    uint16_t green_value = (pixel & green_mask) >> 5; // Extract green (6 bits)
    uint16_t blue_value = (pixel & blue_mask);       // Extract blue (5 bits)

    // Scale to 8-bit values
    *red = red_value << 3;   // Scale 5 bits to 8 bits
    *green = green_value << 3; // Scale 6 bits to 8 bits
    *blue = blue_value << 3;   // Scale 5 bits to 8 bits
}


// function to create a RGB565 pixel from R, G, and B values
uint16_t create_rgb565_2_byte_pixel(uint8_t red, uint8_t green, uint8_t blue) {
    // Scale the 8-bit values to 5-bit (red and blue) and 6-bit (green)
    uint8_t red_value = red >> 3;   // Red: Scale from 8 bits to 5 bits
    uint8_t green_value = green >> 2; // Green: Scale from 8 bits to 6 bits
    uint8_t blue_value = blue >> 3;  // Blue: Scale from 8 bits to 5 bits

    // Combine the 5/6-bit values into a 16-bit pixel (RGB565 format)
    uint16_t pixel = (red_value << 11) | (green_value << 5) | blue_value;
    return pixel;
}

// function to create a RGB555 pixel from R, G, and B values
uint16_t create_rgb555_2_byte_pixel(uint8_t red, uint8_t green, uint8_t blue) {
    // Scale the 8-bit values to 5-bit (red and blue) and 6-bit (green)
    uint8_t red_value = red >> 3;   // Red: Scale from 8 bits to 5 bits
    uint8_t green_value = green >> 3; // Green: Scale from 8 bits to 5 bits
    uint8_t blue_value = blue >> 3;  // Blue: Scale from 8 bits to 5 bits

    // Combine the 5/6-bit values into a 16-bit pixel (RGB565 format)
    uint16_t pixel = (red_value << 10) | (green_value << 5) | blue_value;
    return pixel;
}

// get/set little endian functions (most attributes of BMP files are stored in little endian format)
// 16-bit functions (2 bytes)
uint16_t get_little_endian_int16(const uint8_t *data, size_t starting_index) {
    uint16_t result = 0;
    result |= ((uint16_t)data[starting_index]);
    result |= ((uint16_t)data[starting_index + 1]) << 8;
    return result;
}

void set_little_endian_int16(uint8_t *data, size_t starting_index, uint16_t value) {
    data[starting_index] = value & 0xFF;
    data[starting_index + 1] = (value >> 8) & 0xFF;
}

// 24-bit functions (3 bytes)
uint32_t get_little_endian_int24(const uint8_t *data, size_t starting_index) {
    uint32_t result = 0;
    result |= ((uint32_t)data[starting_index]);
    result |= ((uint32_t)data[starting_index + 1]) << 8;
    result |= ((uint32_t)data[starting_index + 2]) << 16;
    return result;
}

void set_little_endian_int24(uint8_t *data, size_t starting_index, uint32_t value) {
    data[starting_index] = value & 0xFF;
    data[starting_index + 1] = (value >> 8) & 0xFF;
    data[starting_index + 2] = (value >> 16) & 0xFF;
}

// 32-bit functions (4 bytes)
uint32_t get_little_endian_int32(const uint8_t *data, size_t starting_index) {
    uint32_t result = 0;
    result |= ((uint32_t)data[starting_index]);
    result |= ((uint32_t)data[starting_index + 1]) << 8;
    result |= ((uint32_t)data[starting_index + 2]) << 16;
    result |= ((uint32_t)data[starting_index + 3]) << 24;
    return result;
}

void set_little_endian_int32(uint8_t *data, size_t starting_index, uint32_t value) {
    data[starting_index] = value & 0xFF;
    data[starting_index + 1] = (value >> 8) & 0xFF;
    data[starting_index + 2] = (value >> 16) & 0xFF;
    data[starting_index + 3] = (value >> 24) & 0xFF;
}

// Get pointers to data
// Header
unsigned char* getSignatureBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0000h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getFileSizeBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0002h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getReservedBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0006h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getDataOffsetBytesPtr(unsigned char* bmp) {
    char* hexOffset = "000Ah";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}


// InfoHeader
unsigned char* getSizeBytesPtr(unsigned char* bmp) {
    char* hexOffset = "000Eh";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getWidthBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0012h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getHeightBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0016h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getPlanesBytesPtr(unsigned char* bmp) {
    char* hexOffset = "001Ah";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getBitsPerPixelBytesPtr(unsigned char* bmp) {

    char* hexOffset = "001Ch";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getCompressionBytesPtr(unsigned char* bmp) {
    char* hexOffset = "001Eh";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getImageSizeBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0022h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getXpixelsPerMBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0026h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getYpixelsPerMBytesPtr(unsigned char* bmp) {
    char* hexOffset = "002Ah";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getColorsUsedBytesPtr(unsigned char* bmp) {
    char* hexOffset = "002Eh";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

unsigned char* getImportantColorsBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0032h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

// ColorTable
unsigned char* getColorTableBytesPtr(unsigned char* bmp) {
    char* hexOffset = "0036h";
    int intOffset = hexOffsetToInt(hexOffset);
    unsigned char* ptr = bmp + intOffset;
    return ptr;
}

// Structure to contain pointers to the BMP bytes, pointers to the BMP attributes, and attributes themselves
struct BMP {
    // Pointer to memory buffer containing BMP bytes
    unsigned char* bmpBytesPtr;

    // Pointers to header bytes in memory buffer
    unsigned char* signatureBytesPtr;
    unsigned char* fileSizeBytesPtr;
    unsigned char* reservedBytesPtr;
    unsigned char* dataOffsetBytesPtr;
    unsigned char* sizeBytesPtr;
    unsigned char* widthBytesPtr;
    unsigned char* heightBytesPtr;
    unsigned char* planesBytesPtr;
    unsigned char* bitsPerPixelBytesPtr;
    unsigned char* compressionBytesPtr;
    unsigned char* imageSizeBytesPtr;
    unsigned char* XpixelsPerMBytesPtr;
    unsigned char* YpixelsPerMBytesPtr;
    unsigned char* colorsUsedBytesPtr;
    unsigned char* importantColorsBytesPtr;
    unsigned char* colorTableBytesPtr;

    // int variables to hold translated decimal attributes
    // variable sizes corresponding to number of memory blocks
    uint32_t widthDecimal;
    uint32_t heightDecimal;
    uint32_t imageSizeDecimal;
    uint16_t bitsPerPixelDecimal;
    uint16_t bytesPerPixelDecimal;
    uint32_t fileSizeDecimal;
    uint32_t colorsUsedDecimal;

    // uint64_t to avoid overflow because maximum factor is uint32_t
    uint64_t rowByteSizeUnalignedDecimal;
    uint64_t rowByteSizeAlignedDecimal;

    // pointer to memory block containing original BMP pixel data
    unsigned char* originalPixelDataPtr;
};

// create new BMP struct
struct BMP* newBMP(unsigned char* bmpBytesPtr) {
    // dynamically allocate space for the bmp struct
    struct BMP* bmpStructPtr = malloc(sizeof(struct BMP));
    // initialize the struct's pointer to the BMP bytes
    bmpStructPtr->bmpBytesPtr = bmpBytesPtr;
    // return the new struct
    return bmpStructPtr;
}

void defineBMPPointers(struct BMP* bmpStructPtr) {
    // initialize BMP struct header byte pointers
    bmpStructPtr->signatureBytesPtr = getSignatureBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->fileSizeBytesPtr = getFileSizeBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->reservedBytesPtr = getReservedBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->dataOffsetBytesPtr = getDataOffsetBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->sizeBytesPtr = getSizeBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->widthBytesPtr = getWidthBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->heightBytesPtr = getHeightBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->planesBytesPtr = getPlanesBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->bitsPerPixelBytesPtr = getBitsPerPixelBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->compressionBytesPtr = getCompressionBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->imageSizeBytesPtr = getImageSizeBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->XpixelsPerMBytesPtr = getXpixelsPerMBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->YpixelsPerMBytesPtr = getYpixelsPerMBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->colorsUsedBytesPtr = getColorsUsedBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->importantColorsBytesPtr = getImportantColorsBytesPtr(bmpStructPtr->bmpBytesPtr);
    bmpStructPtr->colorTableBytesPtr = getColorTableBytesPtr(bmpStructPtr->bmpBytesPtr);
}

void translateOriginalData(struct BMP* bmpStructPtr) {
    // translate select byte pointers into integers to be used arithmetically/directly
    bmpStructPtr->bitsPerPixelDecimal = get_little_endian_int16(bmpStructPtr->bitsPerPixelBytesPtr, 0);
    bmpStructPtr->bytesPerPixelDecimal = bmpStructPtr->bitsPerPixelDecimal / 8;
    bmpStructPtr->widthDecimal = get_little_endian_int32(bmpStructPtr->widthBytesPtr, 0);
    bmpStructPtr->rowByteSizeUnalignedDecimal = bmpStructPtr->bytesPerPixelDecimal * bmpStructPtr->widthDecimal;
    bmpStructPtr->rowByteSizeAlignedDecimal = bmpStructPtr->rowByteSizeUnalignedDecimal + (4 - (bmpStructPtr->rowByteSizeUnalignedDecimal % 4)) % 4;
    bmpStructPtr->heightDecimal = get_little_endian_int32(bmpStructPtr->heightBytesPtr, 0);
    bmpStructPtr->imageSizeDecimal = get_little_endian_int32(bmpStructPtr->imageSizeBytesPtr, 0);
    bmpStructPtr->fileSizeDecimal = get_little_endian_int32(bmpStructPtr->fileSizeBytesPtr, 0);
    bmpStructPtr->colorsUsedDecimal = get_little_endian_int32(bmpStructPtr->colorsUsedBytesPtr, 0);
}
// function to copy original image data into new memory block to be referenced for operations
void copyOriginalImageData(struct BMP* bmpStructPtr) {
    // calculate real decimal image size, sometimes the header is incorrectly set to 0
    bmpStructPtr->imageSizeDecimal = bmpStructPtr->rowByteSizeAlignedDecimal * bmpStructPtr->heightDecimal;
    // dynamically allocate memory for the original image data
    bmpStructPtr->originalPixelDataPtr = malloc(bmpStructPtr->imageSizeDecimal);
    // copy the original image data into the dynamically allocated memory
    memcpy(bmpStructPtr->originalPixelDataPtr, bmpStructPtr->bmpBytesPtr + get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0), bmpStructPtr->imageSizeDecimal);
}

// execute the actual operation
void executeOperation(struct BMP* bmpStructPtr, int operation) {
    // initialize 2 pointers for operational logic
    unsigned char* ptrA;
    unsigned char* ptrB;
    // run different code depending on the operation selected
    switch (operation) {
        // HFLIP
        case 0:
            // set pointer A to point to the bottom left pixel
            ptrA = bmpStructPtr->bmpBytesPtr + get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0);
            // set pointer B to point to the bottom right pixel
            ptrB = bmpStructPtr->originalPixelDataPtr + (bmpStructPtr->bytesPerPixelDecimal * (bmpStructPtr->widthDecimal - 1));

            // for each row
            for (int j = 0; j < bmpStructPtr->heightDecimal; j++) {
                // for each pixel in each row
                for (int i = 0; i < bmpStructPtr->widthDecimal; i++) {
                    // copy the pixel at pointer B to pointer A
                    memcpy(ptrA, ptrB, bmpStructPtr->bytesPerPixelDecimal);
                    // shift pointer A to the right 1 pixel
                    ptrA += bmpStructPtr->bytesPerPixelDecimal;
                    // shift pointer B to the left 1 pixel
                    ptrB -= bmpStructPtr->bytesPerPixelDecimal;
                }
                // shift pointer A up 1 column and all the way to the left
                ptrA += bmpStructPtr->rowByteSizeAlignedDecimal - bmpStructPtr->rowByteSizeUnalignedDecimal;
                // shift pointer B up 1 column and all the way to the right
                ptrB += bmpStructPtr->rowByteSizeAlignedDecimal + bmpStructPtr->rowByteSizeUnalignedDecimal;
            }
            break;
        // VFLIP
        case 1:
            // set pointer A to point to the bottom left pixel
            ptrA = bmpStructPtr->bmpBytesPtr + get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0);
            // set pointer B to point to the top left pixel
            ptrB = bmpStructPtr->originalPixelDataPtr + (bmpStructPtr->rowByteSizeAlignedDecimal * (bmpStructPtr->heightDecimal - 1));

            // for each column
            for (int j = 0; j < bmpStructPtr->widthDecimal; j++) {
                // for each pixel in each column
                for (int i = 0; i < bmpStructPtr->heightDecimal; i++) {
                    // copy the pixel at pointer B to pointer A
                    memcpy(ptrA, ptrB, bmpStructPtr->bytesPerPixelDecimal);
                    // shift pointer A up 1 pixel
                    ptrA += bmpStructPtr->rowByteSizeAlignedDecimal;
                    // shift pointer A down 1 pixel
                    ptrB -= bmpStructPtr->rowByteSizeAlignedDecimal;
                }
                // shift pointer A all the way down
                ptrA -= (bmpStructPtr->heightDecimal * bmpStructPtr->rowByteSizeAlignedDecimal);
                // shift pointer B all the way up
                ptrB += (bmpStructPtr->heightDecimal * bmpStructPtr->rowByteSizeAlignedDecimal);
                // shift pointer A to the right 1 pixel
                ptrA += bmpStructPtr->bytesPerPixelDecimal;
                // shift pointer B to the right 1 pixel
                ptrB += bmpStructPtr->bytesPerPixelDecimal;
            }
            break;
        // GRAYSCALE
        case 2:
            // run different code based on bit depth
            switch (bmpStructPtr->bitsPerPixelDecimal) {
                // bit depth: 8
                case 8:
                    // set pointer A to point to the color table bytes
                    ptrA = bmpStructPtr->colorTableBytesPtr;
                    // for each of the 256 colors used (bit depth 8 BMPs use a color table with 256 colors)
                    for (int i = 0; i < 256; i++) {
                        // grayscale calculations for color in color table
                        double r = (double) ptrA[0] * 0.229;
                        double g = (double) ptrA[1] * 0.587;
                        double b = (double) ptrA[2] * 0.114;
                        double gray = r + g + b;
                        // replace color in color table with grayscale color
                        ptrA[0] = (unsigned char) gray;
                        ptrA[1] = (unsigned char) gray;
                        ptrA[2] = (unsigned char) gray;
                        // shift pointer A over 4 bytes (each color in a color table takes uo 4 bytes)
                        ptrA += 4;
                    }
                    break;
                // bit depth: 16
                case 16:
                    // run different code depending on compression method
                    switch (bmpStructPtr->compressionBytesPtr[0]) {
                        // BI_RGB (no compression) - RGB5551
                        case 0:
                            ptrA = bmpStructPtr->bmpBytesPtr + get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0);
                            for (int j = 0; j < bmpStructPtr->heightDecimal; j++) {
                                for (int i = 0; i < bmpStructPtr->widthDecimal; i++) {
                                    uint16_t pixel = get_little_endian_int16(ptrA, 0);

                                    uint8_t red, green, blue;
                                    get_rgb555_from_2_byte_pixel(pixel, &red, &green, &blue, 63488, 2016, 31);

                                    uint8_t gray = (int) ((((double) red) * 0.299) + (((double) green) * 0.587) + (((double) blue) * 0.114));

                                    uint16_t grayPixel = create_rgb555_2_byte_pixel(gray, gray, gray);
                                    set_little_endian_int16(ptrA, 0, grayPixel);

                                    ptrA += bmpStructPtr->bytesPerPixelDecimal;
                                }
                                ptrA += bmpStructPtr->rowByteSizeAlignedDecimal - bmpStructPtr->rowByteSizeUnalignedDecimal;
                            }
                            break;
                        // BI_RLE8 8bit RLE encoding (unused)
                        case 1:
                            break;
                        // BI_RLE4 4bit RLE encoding (unused)
                        case 2:
                            break;
                        // BI_BITFIELDS
                        case 3:
                            // set pointer B to point to the color table bytes
                            // (in BI_BITFIELDS, the color masks are stored in 12-16 bytes where the color table would be)
                            ptrB = bmpStructPtr->colorTableBytesPtr;
                            // get the color masks
                            uint32_t red_mask3 = get_little_endian_int32(ptrB, 0);
                            uint32_t green_mask3 = get_little_endian_int32(ptrB, 4);
                            uint32_t blue_mask3 = get_little_endian_int32(ptrB, 8);

                            // set pointer A to point to the bottom left pixel
                            ptrA = bmpStructPtr->bmpBytesPtr + get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0);
                            // RGB565
                            if (red_mask3 == 63488 && green_mask3 == 2016 && blue_mask3 == 31) {
                                // for each row
                                for (int j = 0; j < bmpStructPtr->heightDecimal; j++) {
                                    // for each pixel in each row
                                    for (int i = 0; i < bmpStructPtr->widthDecimal; i++) {
                                        // convert the 16 bit RGB565 pixel at pointer A to uint16_t
                                        uint16_t pixel = get_little_endian_int16(ptrA, 0);

                                        // get red, green, and blue values for the RGB565 pixel as uint8_t
                                        uint8_t red, green, blue;
                                        get_rgb565_from_2_byte_pixel(pixel, &red, &green, &blue, red_mask3, green_mask3, blue_mask3);

                                        // calculate a uint8_t grayscale value
                                        uint8_t gray = (int) ((((double) red) * 0.299) + (((double) green) * 0.587) + (((double) blue) * 0.114));

                                        // create a 16 bit RGB565 pixel using the calculated grayscale value
                                        uint16_t grayPixel = create_rgb565_2_byte_pixel(gray, gray, gray);
                                        // replace the pixel at pointer A with the grayscale pixel
                                        set_little_endian_int16(ptrA, 0, grayPixel);

                                        // shift pointer A to the right 1 pixel
                                        ptrA += bmpStructPtr->bytesPerPixelDecimal;
                                    }
                                    // shift pointer A up 1 pixel and all the way to the left
                                    ptrA += bmpStructPtr->rowByteSizeAlignedDecimal - bmpStructPtr->rowByteSizeUnalignedDecimal;
                                }
                            // RGBA5551
                            } else if (red_mask3 == 31744 && green_mask3 == 992 && blue_mask3 == 31) {
                                // for each row
                                for (int j = 0; j < bmpStructPtr->heightDecimal; j++) {
                                    // for each pixel in each row
                                    for (int i = 0; i < bmpStructPtr->widthDecimal; i++) {
                                        // convert the 16 bit RGBA5551 pixel at pointer A to uint16_t
                                        uint16_t pixel = get_little_endian_int16(ptrA, 0);

                                        // get red, green, and blue values for the RGBA5551 pixel as uint8_t
                                        uint8_t red, green, blue;
                                        get_rgb555_from_2_byte_pixel(pixel, &red, &green, &blue, red_mask3, green_mask3, blue_mask3);

                                        // calculate a uint8_t grayscale value
                                        uint8_t gray = (int) ((((double) red) * 0.299) + (((double) green) * 0.587) + (((double) blue) * 0.114));

                                        // create a 16 bit RGBA5551 pixel using the calculated grayscale value
                                        uint16_t grayPixel = create_rgb555_2_byte_pixel(gray, gray, gray);
                                        // replace the pixel at pointer A with the grayscale pixel
                                        set_little_endian_int16(ptrA, 0, grayPixel);

                                        // shift pointer A to the right 1 pixel
                                        ptrA += bmpStructPtr->bytesPerPixelDecimal;
                                    }
                                    // shift pointer A up 1 pixel and all the way to the left
                                    ptrA += bmpStructPtr->rowByteSizeAlignedDecimal - bmpStructPtr->rowByteSizeUnalignedDecimal;
                                }
                            }
                            break;
                        // invalid compression type
                        default:
                            break;
                    }
                    break;
                // bit depth: 24
                case 24:
                    // set pointer A to point to the bottom left pixel
                    ptrA = bmpStructPtr->bmpBytesPtr + get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0);
                    // for each row
                    for (int j = 0; j < bmpStructPtr->heightDecimal; j++) {
                        // for each pixel in each row
                        for (int i = 0; i < bmpStructPtr->widthDecimal; i++) {
                            // get R, G, and B values and weigh them for the grayscale
                            double b = (double) ptrA[0] * 0.114;
                            double g = (double) ptrA[1] * 0.587;
                            double r = (double) ptrA[2] * 0.299;
                            // calculate the grayscale as a double
                            double gray = b + g + r;
                            // convert the grayscale to a unsigned char, and set the R, G, and B memory bytes to the grayscale value
                            ptrA[0] = (unsigned char) gray;
                            ptrA[1] = (unsigned char) gray;
                            ptrA[2] = (unsigned char) gray;
                            // move pointer A to the right 1
                            ptrA += bmpStructPtr->bytesPerPixelDecimal;
                        }
                        // move pointer A up 1 and all the way to the left
                        ptrA += bmpStructPtr->rowByteSizeAlignedDecimal - bmpStructPtr->rowByteSizeUnalignedDecimal;
                    }
                    break;
                // bit depth: 32
                case 32:
                    // identical to bit depth: 24
                    ptrA = bmpStructPtr->bmpBytesPtr + get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0);
                    for (int j = 0; j < bmpStructPtr->heightDecimal; j++) {
                        for (int i = 0; i < bmpStructPtr->widthDecimal; i++) {
                            double b = (double) ptrA[0] * 0.114;
                            double g = (double) ptrA[1] * 0.587;
                            double r = (double) ptrA[2] * 0.299;
                            double gray = b + g + r;
                            ptrA[0] = (unsigned char) gray;
                            ptrA[1] = (unsigned char) gray;
                            ptrA[2] = (unsigned char) gray;
                            ptrA += bmpStructPtr->bytesPerPixelDecimal;
                        }
                        ptrA += bmpStructPtr->rowByteSizeAlignedDecimal - bmpStructPtr->rowByteSizeUnalignedDecimal;
                    }
                    break;
                default:
                    break;
            }
            break;
        // INFO
        case 3:
            // print file info
            printf("\nFile Information:\n\n");
            printf("Pixel width: %i\n", bmpStructPtr->widthDecimal);
            printf("Pixel height: %i\n", bmpStructPtr->heightDecimal);
            printf("Bit depth: %i\n", bmpStructPtr->bitsPerPixelDecimal);
            printf("Row width (bytes): %llu\n", bmpStructPtr->rowByteSizeAlignedDecimal);
            printf("Bytes per pixel: %i\n", bmpStructPtr->bytesPerPixelDecimal);
            printf("Data offset: %i\n\n", get_little_endian_int32(bmpStructPtr->dataOffsetBytesPtr, 0));
            break;
        default:
            break;
    }
}

// function to free dynamically allocated memory for the BMP struct and original pixel data
void freeBMP(struct BMP* bmpStructPtr) {
    if (bmpStructPtr->originalPixelDataPtr) {
        free(bmpStructPtr->originalPixelDataPtr);
    }
    free(bmpStructPtr);
}

// function to process the BMP file
uint32_t processBMP(unsigned char* bmpBytesPtr, int operation) {
    // create a new BMP struct using the original memory buffer
    struct BMP* bmpStructPtr = newBMP(bmpBytesPtr);
    // define the BMP header pointers
    defineBMPPointers(bmpStructPtr);
    // translate select headers to integers
    translateOriginalData(bmpStructPtr);
    // if the operation modifies the BMP
    if (operation == 0 || operation == 1 || operation == 2) {
        // copy the original image data to new blocks of dynamically allocated memory
        copyOriginalImageData(bmpStructPtr);
    }
    // execute the operation
    executeOperation(bmpStructPtr, operation);
    // store the new file size to be returned (it should remain unchanged from when the file was initially read)
    uint32_t ret = bmpStructPtr->fileSizeDecimal;
    // free all dynamically allocated memory
    freeBMP(bmpStructPtr);
    // return the new file size
    // it should remain unchanged, but is still necessary for writing the buffer out, for now it will be returned
    return ret;
}