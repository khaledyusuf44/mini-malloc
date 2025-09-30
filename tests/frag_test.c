#include "allocator.h"
#include <stdio.h>

int main(void) {
    printf("=== Fragmentation Test ===\n");
    heap_init();

    // Step 1: alloc A, B, C
    void *A = my_malloc(200);
    void *B = my_malloc(300);
    void *C = my_malloc(400);
    printf("Allocated A=%p, B=%p, C=%p\n", A, B, C);
    print_heap();

    // Step 2: free B (creates a hole between A and C)
    my_free(B);
    printf("Freed B\n");
    print_heap();

    // Step 3: alloc D (fits inside B’s hole if splitting works)
    void *D = my_malloc(250);
    printf("Allocated D=%p (inside B’s freed space)\n", D);
    print_heap();

    // Step 4: free A and C (tests coalescing around)
    my_free(A);
    my_free(C);
    printf("Freed A and C\n");
    print_heap();

    // Step 5: invariants check
    if (check_invariants()) {
        printf("Invariants hold ✅\n");
    }

    printf("=== Fragmentation Test Finished ===\n");
    return 0;
}

