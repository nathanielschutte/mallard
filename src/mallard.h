/*
 * Mallard - dynamic memory allocation
 *
 * Header
 *
 * */

#include <stdio.h>
#include <stddef.h>

#define MAX_BYTES 10000

char *memory;

struct block {
	size_t b_size;
	int b_free;
	struct block *m_next;
};

struct block *free_memory;

int set_memory(char* mem_set, size_t max_bytes);
void split(struct block *fit_slot, size_t size);
void *mallard(size_t byte_num);
void merge();
void free(void *ptr);
