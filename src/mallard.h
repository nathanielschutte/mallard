/*
 * Mallard - dynamic memory allocation
 *
 * Header info
 * */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define MAX_BYTES 10000

enum Algorithm {FIRST_FIT} use_alloc;

struct block {
	size_t b_size;
	int b_free;
	struct block *m_next;
};

char *memory; // points to first byte of total memory block
size_t total_bytes; // total number of bytes to work with
struct block *free_memory; // points to first block


// for use
int mal_setmemory(char* mem_set, size_t max_bytes);

void mal_split(struct block *fit_slot, size_t size);

void mal_merge();

void * mallard(size_t num_bytes); // user call

void mal_free(void *ptr); // user call


// allocation algorithms
void * mFirstFit(size_t num_bytes);


// for testing and proof
void printAllBlocks(); // print blocks to console

size_t getFreeBytes(); // count up all free bytes (exlude metadata)

size_t getAllocatedBytes(); // count up all allocated bytes (exlude metadata)

void visualize(size_t len); // attempt to visualize blocks over 'len' characters in console
