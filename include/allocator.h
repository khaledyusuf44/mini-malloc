#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>  // size_t

// Heap constants
#define HEAP_SIZE   1048576   // 1 MB heap
#define ALIGNMENT   16
#define HEADER_SIZE ((sizeof(block_header) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

// Fit strategies
typedef enum { FIRST_FIT, BEST_FIT } fit_strategy;
extern fit_strategy current_fit;

// Public API declarations
void *my_malloc(size_t size);
void *my_calloc(size_t num, size_t size);
void *my_realloc(void *ptr, size_t size);
void  my_free(void *ptr);
void  print_heap(void);

// Leak checker
void check_leaks(void);

// Heap globals
extern void *heap_start;
extern void *heap_end;
void heap_init(void);
size_t align_up(size_t size, size_t align);

// Block header definition
typedef struct block_header {
    size_t total_size;
    int is_free;
    struct block_header *next;
} block_header;

// Pointer conversion helpers
block_header* hdr_from_payload(void *payload);
void* payload_from_hdr(block_header *hdr);

// Invariants
int check_invariants(void);

// Performance counters (visible to tests)
extern size_t allocations_done;
extern size_t blocks_traversed;

#endif // ALLOCATOR_H


