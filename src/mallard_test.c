/*
 * Test out Mallard
 *
 * */

#include <stdio.h>
#include <stddef.h>
#include "mallard.h"

#define BYTES 8000

char test_memory[BYTES];
size_t block_bytes = BYTES;

int main(int argc, char** argv) {
    int exit_code = 0; // for multiple test uses

    printf("MALLARD dynamic memory allocation test...\n");
    if(setMemory(test_memory, block_bytes) < 0) {
        return -1;
    }

    printf("\nInitial:\n");
    printAllBlocks();

    return exit_code; // some errors may allow code to continue to end
}
