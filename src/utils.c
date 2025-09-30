#include "allocator.h"
#include <stdio.h>
#include <assert.h>

size_t align_up(size_t size, size_t align) {
    return (size + (align - 1)) & ~(align - 1);
}

block_header* hdr_from_payload(void *payload) {
    if (!payload) return NULL;
    return (block_header*)((unsigned char*)payload - HEADER_SIZE);
}

void* payload_from_hdr(block_header *hdr) {
    if (!hdr) return NULL;
    return (void*)((unsigned char*)hdr + HEADER_SIZE);
}

void print_heap(void) {
    block_header *cur = (block_header*)heap_start;
    printf("=== Heap dump ===\n");
    while (cur) {
        printf("Block @ %p | size %zu | %s\n",
               (void*)cur, cur->total_size,
               cur->is_free ? "FREE" : "USED");
        cur = cur->next;
    }
}

int check_invariants(void) {
    block_header *cur = (block_header*)heap_start;
    size_t total = 0;

    while (cur) {
        assert(((size_t)cur % ALIGNMENT) == 0);
        assert(((size_t)payload_from_hdr(cur) % ALIGNMENT) == 0);

        assert(cur->total_size >= HEADER_SIZE);
        assert(cur->total_size % ALIGNMENT == 0);
        assert(cur->is_free == 0 || cur->is_free == 1);

        total += cur->total_size;
        if (cur->next) {
            assert((unsigned char*)cur->next ==
                   (unsigned char*)cur + cur->total_size);
        }

        cur = cur->next;
    }

    assert(total <= HEAP_SIZE);
    return 1;
}




