// --- Question #2: Steganography using 4-bit LSB algorithm --- //

// LIBRARIES TO INCLUDE
#include <stdio.h>
#include <stdlib.h>

// DEFINED CONSTANTS
#define WIDTH 512
#define HEIGHT 512

// FUNCTION PROTOTYPES
int readPGMText(const char *filename, unsigned char *pixels, int width, int height);
int writePGMText(const char *filename, unsigned char *pixels, int width, int height);
int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height);
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height);
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height);

// FUNCTION DEFINITIONS
// Function to read a PGM image in text format.
// 'pixels' stores the pixel values of the image specified by 'filename'.
int readPGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *PGM_file = fopen(filename, "r"); // opening file in read mode
    if (PGM_file == NULL) {
        printf("Error: Could not open input file.\n"); // error handling
        return 1;
    }

    // memory allocation for checking file format
    char *file_format = (char *)malloc(3 * sizeof(char));
    if (file_format == NULL) {
        printf("Error: Memory allocation failed for file format.\n"); // error handling
        fclose(PGM_file); // closing file
        return 1;
    }

    // validating file format
    fscanf(PGM_file, "%2s", file_format);
    if (file_format[0] != 'P' || file_format[1] != '2') {
        printf("Error: Invalid file format.\n"); // error handling
        free(file_format); // freeing memory
        fclose(PGM_file); // freeing memory
        return 1;
    }
    free(file_format); // freeing memory

    // reading commented line from the file to put the pointer ahead
    char *comment = (char *)malloc(3 * sizeof(char));
    if (comment == NULL) {
        printf("Error: Unable to read file\n");
        fclose(PGM_file);
        return 1;
    }
    fscanf(PGM_file,"%s",comment);
    free(comment); // freeing memory

    // reading width, height and max. grayscale vals
    int img_width, img_height, max_gray;
    fscanf(PGM_file, "%d %d %d", &img_width, &img_height, &max_gray);

    // checking if dimensions match
    if (img_width != width || img_height != height) {
        printf("Error: Image dimensions mismatch.\n"); // error handling
        fclose(PGM_file); // closing file
        return 1;
    }

    // reading pixel values into memory
    for (int i = 0; i < width * height; i++) {
        int value;
        if (fscanf(PGM_file, "%d", &value) != 1 || value < 0 || value > 255) {
            printf("Error: Failed to read pixel value.\n"); // error handling 
            fclose(PGM_file);
            return 1;
        }
        pixels[i] = (unsigned char)value; // storing pixel values
    }

    fclose(PGM_file); // closing file
    return 0;
}


// Function to write a PGM image in text format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename'.
int writePGMText(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *PGM_file = fopen(filename, "w"); // opening file in read mode
    if (PGM_file == NULL) {
        printf("Error: Could not create output file.\n"); // error handling
        return 1;
    }

    fprintf(PGM_file, "P2\n%d %d\n255\n", width, height); // write file header

    // writing pixel values line by line
    unsigned char *pointer = pixels;
    for (int i = 0; i< (width*height); i++) {
        fprintf(PGM_file, "%d\n", *pointer);
        pointer++;
    }

    fclose(PGM_file); // closing file
    return 0;
}


// Function to write a PGM image in binary format.
// The dereferenced values of 'pixels' are stored in the PGM image specified by 'filename' in binary format.

int writePGMBinary(const char *filename, unsigned char *pixels, int width, int height) {
    FILE *PGM_file = fopen(filename,"wb"); // opening file in binary write mode
    if (PGM_file == NULL) {
        printf("Error: Could not create file.\n"); // error handling
        return 1;
    }

    fprintf(PGM_file, "P5\n%d %d\n255\n",width,height); // writing file header
    fwrite(pixels,sizeof(unsigned char),(width*height),PGM_file); // writing pixel values (binary)

    fclose(PGM_file); // closing file
    return 0;
}

// Function to hide a secret image using the 4-bit LSB steganography algorithm.
// The dereferenced values of 'coverPixels' (cover image) are updated with the dereferenced values of 
// 'secretPixels' (secret image) based on the 4-bit LSB steganography algorithm

void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, int width, int height) {
    for (int i = 0; i<(width*height); i++) {
        unsigned char coverMSB = coverPixels[i] & 0xF0; // hiding upper 4 bits
        unsigned char secretMSB = (secretPixels[i] & 0xF0) >> 4; // extracting upper 4 bits and shift down
        coverPixels[i] = coverMSB | secretMSB; // combining both
    }
}

// Function to extract the secret image using 4-LSB steganography algorithm.
// The extracted pixel values, derived from the stego image referenced by 'coverPixels',
// are stored in the memory space pointed to by 'outputPixels' 
void extractLSB(unsigned char *coverPixels, unsigned char *outputPixels, int width, int height) {
    for (int i = 0; i< (width*height);i++) {
        unsigned char secret = (coverPixels[i] & 0x0F) << 4; // extracting lower 4 bits and shift up
        outputPixels[i] = secret; // storing extracted
    }
}

// MAIN FUNCTION
int main() {
    // image inputs
    char *cover_image="baboon.pgm";
    char *secret_image="farm.pgm";
    char *stego_image="stego_image_bin.pgm";
    char *extracted_secret="extracted_secret.pgm";
    

    unsigned char *coverPixels, *secretPixels, *outputPixels;
    int coverWidth=WIDTH, coverHeight=HEIGHT, secretWidth=WIDTH, secretHeight=HEIGHT;

    // Using malloc, dynamically request extact memory space,referenced by coverPixels, to store the cover image pixel values. 
	coverPixels = (unsigned char *)malloc(coverWidth*coverHeight);
    if (coverPixels == NULL) {
        printf("Error: Memory was not allocated for coverPixels.\n");
        return 1;
    }

    // Read the cover image file (text PGM) and store its pixels in 'coverPixels' referenced memory space.
    if (readPGMText(cover_image,coverPixels,coverWidth,coverHeight)!=0){
        free(coverPixels);
        return 1;
    }

    //  Using malloc, dynamically request extact memory space, referenced by 'secretPixels', to store the secret image pixel values.
    secretPixels = (unsigned char *)malloc(secretWidth*secretHeight);
    if (secretPixels == NULL) {
        printf("Error: Memory was not allocated for secretPixels.\n");
        return 1;
    }

    // Read the secret image file (text PGM) and store its pixels in 'secretPixels' referenced memory space.
    if (readPGMText(secret_image, secretPixels,secretWidth, secretHeight)!=0){
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Check if the dimensions of both images match, exit if they don't.
    if (coverWidth != secretWidth || coverHeight != secretHeight) {
        printf("Error: Cover and secret images must have the same dimensions.\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }
 
    // Call the function embedLSB to embed the secret image into the cover image.
    embedLSB(coverPixels,secretPixels,coverWidth,coverHeight);
            
    // Save the stego image into binary format to stego_image_bin.pgm
    if (writePGMBinary(stego_image,coverPixels,WIDTH,HEIGHT)!=0){
        free(coverPixels);
        free(secretPixels);
        return 1;
    }
  
    //  Using malloc, dynamically request exact memory space, referenced by 'outputPixels', to store the extracted secret image    
    outputPixels = (unsigned char *)malloc(WIDTH*HEIGHT);
    if (outputPixels == NULL) {
        printf("Error: Could not allocate memory for outputPixels.\n");
        free(coverPixels);
        free(secretPixels);
        return 1;
    }

    // Call the function extractLSB to extract the secret image from the stego image
    extractLSB(coverPixels,outputPixels,WIDTH,HEIGHT);
    
    // Save the extracted secret image in a text format to extracted_secret.pgm
    if (writePGMText(extracted_secret,outputPixels,WIDTH,HEIGHT)!=0) {
        free(coverPixels);
        free(secretPixels);
        free(outputPixels);
        return 1;
    }

    // Free allocated memory
    free(coverPixels);
    free(secretPixels);
    free(outputPixels);

    return 0;
}