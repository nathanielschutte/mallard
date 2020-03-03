/*
 * Mallard - dynamic memory allocation
 *
 * Header
 *
 * */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define MAX_BYTES 10000

enum Algorithm {FIRST_FIT};

char *memory;

struct block {
	size_t b_size;
	int b_free;
	struct block *m_next;
};

struct block *free_memory;


// for use

int setMemory(char* mem_set, size_t max_bytes);

void split(struct block *fit_slot, size_t size);

void * mallard(size_t num_bytes);

void merge();

void free(void *ptr);


// for testing and proof

void printAllBlocks(); // print blocks to console

size_t getFreeBytes(); // count up all free bytes (exlude metadata)

size_t getAllocatedBytes(); // count up all allocated bytes (exlude metadata)

void visualize(size_t len); // attempt to visualize blocks over 'len' characters in console
