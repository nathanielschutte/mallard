/*
 * Mallard - dynamic memory allocation
 *
 * Implementation
 */

#include <stdio.h>
#include <stddef.h>
#include "mallard.h"

/**
 * Initialize mallard with free block of memory from mem_set, max size max_bytes
 * This must be done before using any other function
*/
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


/**
 * Split block for newly allocated block, place in fit_slot of with size
*/
void split(struct block *fit_slot, size_t size) {

    // to second half of split block
    struct block *b_new = (void *) ((void *) fit_slot + size + sizeof(struct block));

    // new block with remaining size
    b_new->b_size = fit_slot->b_size - size - sizeof(struct block);
    b_new->b_free = 1;
    b_new->m_next = fit_slot->m_next; // link second half block to previous next

    fit_slot->b_size = size;
    fit_slot->b_free = 0;
    fit_slot->m_next = b_new;
}

/**
 * Allocate a block of memory of size num_bytes.
 * Return NULL if whole memory block has not yet been set or if the requested block
 * is too large.
*/
void * mallard(size_t num_bytes) {
    void *result;

    // set_memory hasn't been called yet
    if(!(free_memory->b_size)) {
        printf("Memory has not been set for use by mallard");
        return NULL;
    }

    // num_bytes greater than max possible allocation
    if(num_bytes > MAX_BYTES) {
        printf("Requested bytes for allocation greater than max allowed bytes");
        return NULL;
    }

    struct block *curr;
    curr = free_memory; // begin

    // move forward while: slot too small, slot already allocated, still more slots to go
    while((curr->b_size < num_bytes || (curr->b_free == 0)) && (curr->m_next != NULL)) {
        curr = curr->m_next;

        
    }
}