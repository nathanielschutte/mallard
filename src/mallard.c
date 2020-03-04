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
int mal_setmemory(char* mem_set, size_t max_bytes) {
    if(max_bytes > MAX_BYTES) {
        return -1;
    }

    // set memory to passed chunk pointer, allocate first free block
	memory = mem_set;
    total_bytes = max_bytes;
    free_memory = (void *) memory;

	// actual byte size minus header data (struct block) size
	free_memory->b_size = max_bytes - sizeof(struct block);
    free_memory->b_free = 1;
    free_memory->m_next = NULL;

    printf("Total Bytes:\t%u\nHeader Size:\t%u\nMemory Bytes:\t%u\nBlock Address:\t0x%x\n",
           total_bytes, sizeof(struct block), free_memory->b_size, (unsigned int) free_memory);

    return 0;
}


/**
 * Split block for newly allocated block, place in fit_slot of with size
*/
void mal_split(struct block *fit_slot, size_t size) {

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
        printf("Memory has not been set for use by mallard\n");
        return NULL;
    }

    // num_bytes greater than max possible allocation
    if(num_bytes > MAX_BYTES) {
        printf("Requested block larger than max allowed bytes\n");
        return NULL;
    }
    
    switch(use_alloc) {
        case(FIRST_FIT):
            return mFirstFit(num_bytes);
        break;
        default:
        result = NULL;
    }
    return result;
}


/**
 * First fit algorithm for memory allocation
*/
void * mFirstFit(size_t num_bytes) {
    void *result;
    struct block *curr;
    curr = free_memory; // begin

    while((curr->b_size < num_bytes || (curr->b_free == 0)) && (curr->m_next != NULL)) {
        curr = curr->m_next;
    }

    // exact fit
    if(curr->b_size == num_bytes) {
        curr->b_free = 0;
        result = (void *) (++curr); // move past metadata header
    }

    // else... also need an extra header on split
    else if(curr->b_size > (num_bytes + sizeof(struct block))) {
        mal_split(curr, num_bytes);
        result = (void *) (++curr);
        return result;
    }
    else {
        result = NULL;
        printf("Insufficient memory to allocate requested block\n");
    }
    return result;
}


/**
 * Merge consecutive free blocks
 * Can assume that memory is initialized as this is called from free
*/
void mal_merge() {
    struct block *curr;
    curr = free_memory;
    while(curr->m_next != NULL) {

        // this block and the next are both free, merge
        if(curr->b_free && curr->m_next->b_free) {
            curr->b_size += curr->m_next->b_size + sizeof(struct block);
            curr->m_next = curr->m_next->m_next;
        }

        // only move on once all consecutive blocks are merged
        else {
            curr = curr->m_next;
        }
    }
}


/**
 * Free memory at pointer
*/
void mal_free(void *ptr) {
    if(ptr < (void *) memory || ptr > (void *) (memory + total_bytes)) {
        printf("Pointer not within range of mallard\'s memory\n");
        return;
    }

    struct block *curr = ptr;
    curr--; // retreat to start of metadata
    curr->b_free = 1;
    mal_merge();
}


/**
 * Print all blocks to console
 * 0x00 [FREE/ALOC] bytes
*/
void printAllBlocks() {
    struct block *curr = free_memory;
    if(!(free_memory->b_size)) {
        printf("Memory not set\n");
        return;
    }

    while(curr != NULL) {
        if(curr->b_free)
            printf("0x%x  [FREE] %u\n", (unsigned int) curr, curr->b_size);
        else
            printf("0x%x [ALLOC] %u\n", (unsigned int) curr, curr->b_size);

        curr = curr->m_next;
    }
}