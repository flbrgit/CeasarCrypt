#include <sys/stat.h>
#include <unistd.h>
#include "convert.h"
#include "random.h"


int main(int argc, char *argv[]) {
    int option;
    char *text = NULL;
    char *filename = NULL;
    int mode = 0;
    int key = 0;
    unsigned long long seed = 0;
    char* out = "./output";
    char* endptr;
    unsigned long tmp;

    while ((option = getopt(argc, argv, "t:f:o:edk:s:")) != -1) {
        switch (option) {
            case 't':
                text = optarg;
                mode |= MODE_TEXT;
                break;
            case 'f':
                filename = optarg;
                mode |= MODE_FILE;
                break;
            case 'o':
                out = optarg;
                break;
            case 'e':
                mode |= MODE_ENCRYPT;
                break;
            case 'd':
                mode |= MODE_DECRYPT;
                break;
            case 'k':
                errno = 0;
                long tmp1 = strtol(optarg, &endptr, 10);
                if (endptr == optarg || *endptr != '\0' || (errno == ERANGE && (tmp1 == LONG_MAX || tmp1 == LONG_MIN)) || (errno != 0 && tmp1 == 0)) {
                    fprintf(stderr, "Key to big!\n");
                    exit(EXIT_FAILURE);
                }
                key = tmp1;
                break;
            case 's':
                errno = 0;
                tmp = strtoull(optarg, &endptr, 10);
                if (endptr == optarg || *endptr != '\0' || (errno != 0 && tmp == 0)) {
                    fprintf(stderr, "Seed to big!\n");
                    exit(EXIT_FAILURE);
                }
                seed = tmp;
                break;
            case '?':
                if (optopt == 't' || optopt == 'f' || optopt == 'k' || optopt == 's') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                }
                return 1;
            default:
                abort();
        }
    }
    if (mode & MODE_DECRYPT && mode & MODE_ENCRYPT) exit(EXIT_FAILURE);
    if (mode & MODE_TEXT && mode & MODE_FILE) exit(EXIT_FAILURE);

    struct alphabet * a = create_alphabet(mode);
    shuffle_alphabet(a->alphabet, a->length, seed);

    print_list(a->alphabet, a->length);

    struct info * i = malloc(sizeof(struct info));
    i->mode = mode;

    if (mode & MODE_FILE) {
        struct stat sb;
        if (stat(filename, &sb) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        printf("Loading file...\n");

        FILE* file = fopen(filename, "rb");

        void* buf = malloc(sizeof(unsigned char) * sb.st_size);
        if (fread(buf, sizeof(unsigned char), sb.st_size, file) != sb.st_size) {
            fclose(file);
            exit(1);
        }
        i->data = buf;
        i->len = sb.st_size;
        fclose(file);
        printf("Converting...\n");
        convert(i, a, key);
        file = fopen(out, "wb");
        printf("Writing file...\n");
        fwrite(i->data, sizeof(unsigned char), sb.st_size, file);
        fclose(file);
        free(buf);
        printf("Done.\n");
    } else if (mode & MODE_TEXT) {
        i->data = (unsigned char *) text;
        i->len = strlen(i->data);
        printf("Converting...\n");
        convert(i, a, key);

        printf("Output:");
        print_list((char*)i->data, i->len);
    }


    free(a->alphabet);
    free(a);
    free(i);
    return 0;
}
