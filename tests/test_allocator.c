#include "allocator.h"
#include <stdio.h>

int main(void) {
    printf("=== Running allocator test (Step 3.6) ===\n");

    heap_init();

    // --- Basic API calls ---
    void *p1 = my_malloc(16);
    printf("p1 = %p (malloc 16)\n", p1);

    void *p2 = my_calloc(4, 8);
    printf("p2 = %p (calloc 4×8)\n", p2);

    void *p3 = my_realloc(p1, 32);
    printf("p3 = %p (realloc p1 → 32)\n", p3);

    my_free(p2);
    printf("Freed p2\n");

    // --- Alignment test ---
    size_t values[] = {1, 15, 16, 30, 31, 32, 33, 45, 64};
    for (int i = 0; i < 9; i++) {
        size_t aligned = align_up(values[i], ALIGNMENT);
        printf("Request %zu → aligned %zu\n", values[i], aligned);
    }

    // --- Heap info ---
    printf("Heap size = %zu bytes\n", HEAP_SIZE);
    printf("Heap start: %p, Heap end: %p\n", heap_start, heap_end);

    // --- Fake header round-trip test ---
    block_header fake;
    fake.total_size = HEADER_SIZE + 32;
    fake.is_free = 0;
    fake.next = NULL;

    void *payload = payload_from_hdr(&fake);
    block_header *back = hdr_from_payload(payload);
    printf("header @ %p -> payload @ %p -> back @ %p\n",
           (void*)&fake, payload, (void*)back);

    // --- Invariant check ---
    if (check_invariants()) {
        printf("All invariants hold ✅\n");
    }

    // --- 3.6 new tests ---
    printf("\n=== Testing malloc hardening ===\n");

    // Exact-fit test
    void *ex1 = my_malloc(128);
    my_free(ex1);
    printf("Exact-fit block allocated and freed.\n");

    // Switch to BEST_FIT
    current_fit = BEST_FIT;
    printf("Switched to BEST_FIT strategy\n");
    void *bf1 = my_malloc(64);
    if (bf1) printf("BEST_FIT allocated block for 64\n");
    my_free(bf1);

    // Out-of-memory test
    int i;
    for (i = 0; i < 200000; i++) {
        void *p = my_malloc(1024);
        if (!p) {
            printf("Out of memory reached at iteration %d\n", i);
            break;
        }
    }

    printf("=== Allocator test finished ===\n");
    return 0;
}





