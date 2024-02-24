#include "convert.h"


void shuffle_alphabet(unsigned char *array, size_t size, unsigned int seed) {
    srand(seed);
    if (size > 1) {
        size_t i;
        for (i = 0; i < size - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            unsigned char t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}


struct alphabet * create_alphabet(int mode) {
    unsigned char * alphabet = malloc(sizeof(unsigned char) * (mode & MODE_TEXT ? 90 : 256));
    if (alphabet == NULL) {
        exit(1);
    }
    if (mode & MODE_TEXT) {
        int j = 0;

        for (int i = 32; i < 126; i++) {
            if (i == 34 || i == 39 || i == 64 || i == 96) continue;
            alphabet[j++] = i;
        }
    } else {
        for (int i = 0; i < 256; i++) {
            alphabet[i] = i;
        }
    }
    struct alphabet * a = malloc(sizeof(struct alphabet));
    a->alphabet = alphabet;
    a->length = mode & MODE_TEXT ? 90 : 256;
    return a;
}


void print_list(char* a, size_t len) {
    for (int i = 0; i < len; i++) {
        printf("%c", a[i]);
    }
    printf("\n");
}


void convert(struct info * info, struct alphabet * alphabet, unsigned char key) {
    unsigned char* output = calloc(info->len, sizeof(unsigned char));
    int upper = 1;
    for (int i = 0; i < info->len; i++) {
        unsigned char * e = memchr(alphabet->alphabet, (int)info->data[i], alphabet->length);
        int place = (int)(e - alphabet->alphabet);
        int index = info->mode & MODE_ENCRYPT ? (place + key + i) : (place - key + alphabet->length * upper - i);
        output[i] = alphabet->alphabet[index % alphabet->length];
        if (i % alphabet->length == 0) upper++;
    }
    info->data = output;
}