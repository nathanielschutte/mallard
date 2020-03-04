/*
 * Test out Mallard
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mallard.h"

#define BYTES 4000
#define TEST_HEADER 26

char test_memory[BYTES];
size_t block_bytes = BYTES;

int testAll();
void printHeader(const char *test);

int main(int argc, char** argv) {
    int exit_code = 0;

    if(argc > 1) {
        if(argc == 3) {
            if(strcmp(argv[1], "-a") == 0) {
                switch(atoi(argv[2])) {
                    case(0) : use_alloc = FIRST_FIT;
                    break;
                    default : use_alloc = FIRST_FIT;
                }
            }
            else {
                printf("Invalid use\nUsage: mallard -a [algorithm index]\n -> 0 = first fit\n");
            return -1;
            }
        }
        else {
            printf("Invalid use\nUsage: mallard -a [algorithm index]\n -> 0 = first fit\n");
            return -1;
        }
    }

    exit_code = testAll();

    return exit_code; // some errors may allow code to continue to end
}


int testAll() {

    printf("\n***** MALLARD TEST *****\n\n");
    if(mal_setmemory(test_memory, block_bytes) < 0) {
        return -1;
    }

    printHeader("Initial block");
    printAllBlocks();

    mallard(sizeof(int) * 8);
    printHeader("8 Int Block");
    printAllBlocks();

    long long *test_p = mallard(sizeof(long long) * 64);
    int * test_p2 = mallard(2000);
    mallard(1000);
    printHeader("Many Allocations");
    printAllBlocks();

    printHeader("Over-Allocate");
    mallard(800);

    mal_free(test_p);
    printHeader("Free Inner Block");
    printAllBlocks();

    mal_free(test_p2);
    printHeader("Free + Force Merge");
    printAllBlocks();



    return 0;
}


void printHeader(const char *test) {
    if(strlen(test) >= TEST_HEADER - 1) {
        printf("\n");
        printf(test);
        printf("\n");
    }
    char header[TEST_HEADER + 1] = "";
    int diff = TEST_HEADER - strlen(test);
    for(int i = 0; i < diff - 2; i++) {
        header[i] = '=';
    }
    header[diff - 2] = ' ';
    for(int i = diff - 1; i < TEST_HEADER - 1; i++) {
        header[i] = test[i - diff + 1];
    }
    header[TEST_HEADER - 1] = ':';
    header[TEST_HEADER] = '\0';
    printf("\n");
    printf(header);
    printf("\n");
}