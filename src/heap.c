#include "allocator.h"
#include <assert.h>
#include <stdint.h>

static unsigned char HEAP[HEAP_SIZE + ALIGNMENT];

void *heap_start;
void *heap_end;

void heap_init(void) {
    uintptr_t raw = (uintptr_t)HEAP;
    uintptr_t aligned = (raw + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);

    heap_start = (void*)aligned;
    heap_end   = (unsigned char*)heap_start + HEAP_SIZE;

    block_header *h = (block_header*)heap_start;
    h->total_size = HEAP_SIZE;
    h->is_free = 1;
    h->next = NULL;

    assert(((size_t)h % ALIGNMENT) == 0);
}


