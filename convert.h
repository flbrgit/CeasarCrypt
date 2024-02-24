#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


#define MODE_ENCRYPT 1
#define MODE_DECRYPT 2
#define MODE_FILE 4
#define MODE_TEXT 8


struct alphabet {
    unsigned char* alphabet;
    int length;
};


struct info {
    unsigned char mode;
    size_t len;
    unsigned char * data;
};


/**
 * Helper method to print output strings
 * @param a String to print
 * @param len Length of string
 */
void print_list(char* a, size_t len);


/**
 * Encrypts or decrypts given data with the Ceasar-Crypt algorithm
 * @param info Struct with mode, data and length of data in bytes
 * @param alphabet Struct with randomized alphabet and number of characters
 * @param key The key used to calculate
 */
void convert(struct info * info, struct alphabet * alphabet, unsigned char key);


/**
 * Creates a completely randomly shuffled alphabet in the given mode
 * @param mode Mode to generate
 * @return
 */
struct alphabet * create_alphabet(int mode);


/**
 * Shuffles a given alphabet using the provided seed
 * @param array Array to shuffle
 * @param size Size of the array
 * @param seed Seed to use
 */
void shuffle_alphabet(unsigned char *array, size_t size, unsigned int seed);