// src/allocator.c
#include <stddef.h>   // size_t
#include <stdlib.h>   // NULL
#include <string.h>   // memset, memcpy
#include <stdio.h>
#include "allocator.h"

// --- Globals for strategy & metrics ---
fit_strategy current_fit = FIRST_FIT;  // default
size_t allocations_done = 0;           // performance counter
size_t blocks_traversed = 0;           // performance counter

// --- Internal helpers (file-local) -----------------------------------------

// Return payload capacity (bytes available to user) for a header.
static inline size_t payload_capacity(const block_header *h) {
    return h->total_size - HEADER_SIZE;
}

// First-fit search for a free block with at least `need` total bytes.
static block_header* first_fit(size_t need) {
    block_header *cur = (block_header *)heap_start;
    while (cur) {
        blocks_traversed++;  // count every block visited
        if (cur->is_free && cur->total_size >= need) return cur;
        cur = cur->next;
    }
    return NULL;
}

// Best-fit search: return smallest free block >= need.
static block_header* best_fit(size_t need) {
    block_header *cur = (block_header *)heap_start;
    block_header *best = NULL;
    while (cur) {
        blocks_traversed++;  // count every block visited
        if (cur->is_free && cur->total_size >= need) {
            if (!best || cur->total_size < best->total_size) {
                best = cur;
            }
        }
        cur = cur->next;
    }
    return best;
}

// Split `blk` into [allocated part of `need`] + [remaining free part], if useful.
static void maybe_split(block_header *blk, size_t need) {
    size_t remainder = blk->total_size - need;
    if (remainder >= HEADER_SIZE + ALIGNMENT) {
        unsigned char *base = (unsigned char *)blk;
        block_header *new_free = (block_header *)(base + need);
        new_free->total_size = remainder;
        new_free->is_free    = 1;
        new_free->next       = blk->next;

        blk->total_size = need;
        blk->next       = new_free;
    }
}

// Merge `a` with its next if both free.
static void coalesce_with_next(block_header *a) {
    if (!a || !a->next) return;
    block_header *b = a->next;
    if (a->is_free && b->is_free) {
        a->total_size += b->total_size;
        a->next = b->next;
    }
}

// Try to coalesce with previous and/or next.
static void coalesce_around(block_header *h) {
    block_header *prev = NULL, *cur = (block_header *)heap_start;
    while (cur && cur != h) {
        prev = cur;
        cur = cur->next;
    }
    if (prev) {
        coalesce_with_next(prev);
        coalesce_with_next(prev);
    } else {
        coalesce_with_next(h);
    }
}

// --- Public API -------------------------------------------------------------

void *my_malloc(size_t size) {
    if (size == 0) return NULL;

    size_t payload = align_up(size, ALIGNMENT);
    size_t need    = HEADER_SIZE + payload;

    block_header *blk = NULL;
    if (current_fit == FIRST_FIT) {
        blk = first_fit(need);
    } else {
        blk = best_fit(need);
    }

    if (!blk) return NULL;  // out of memory

    maybe_split(blk, need);
    blk->is_free = 0;

    allocations_done++;  // track successful allocations

    return payload_from_hdr(blk);
}

void my_free(void *ptr) {
    if (!ptr) return;
    block_header *h = hdr_from_payload(ptr);
    h->is_free = 1;
    coalesce_around(h);
}

void *my_calloc(size_t num, size_t size) {
    if (num != 0 && size > (SIZE_MAX / num)) return NULL; // overflow check
    size_t total = num * size;
    void *p = my_malloc(total);
    if (!p) return NULL;
    memset(p, 0, total);
    return p;
}

void *my_realloc(void *ptr, size_t size) {
    if (!ptr) {
        return my_malloc(size);
    }
    if (size == 0) {
        my_free(ptr);
        return NULL;
    }

    block_header *oldh = hdr_from_payload(ptr);
    size_t old_cap = payload_capacity(oldh);
    size_t new_cap = align_up(size, ALIGNMENT);

    if (old_cap >= new_cap) return ptr;

    void *n = my_malloc(size);
    if (!n) return NULL;
    memcpy(n, ptr, old_cap);
    my_free(ptr);
    return n;
}



