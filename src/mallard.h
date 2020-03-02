/*
 * Mallard - dynamic memory allocation
 *
 * Header
 *
 * */

#include <stdio.h>
#include <stddef.h>

#define MAX_BYTES 10000

enum Algorithm {FIRST_FIT};

char *memory;

struct block {
	size_t b_size;
	int b_free;
	struct block *m_next;
};

struct block *free_memory;

int set_memory(char* mem_set, size_t max_bytes);

void split(struct block *fit_slot, size_t size);

void * mallard(size_t num_bytes);

void merge();

void free(void *ptr);
