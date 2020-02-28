/*
 * Mallard - dynamic memory allocation
 *
 * Implementation
 */

#include <stdio.h>
#include <stddef.h>
#include "mallard.h"

int set_memory(char* mem_set, size_t max_bytes) {
    if(max_bytes > MAX_BYTES) {
        return -1;
    }

    // set memory to passed chunk pointer, allocate first free block
	memory = mem_set;
	free_memory = (void *) memory;

	// actual byte size minus header data (struct block) size
	free_memory->b_size = max_bytes - sizeof(struct block);
    free_memory->b_free = 1;
    free_memory->m_next = NULL;

    printf("Total Bytes:\t%u\nHeader Size:\t%u\nMemory Bytes:\t%u\nBlock Address:\t%x\n",
           max_bytes, sizeof(struct block), free_memory->b_size, (unsigned int) memory);

    return 0;
}

