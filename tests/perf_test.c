#include "allocator.h"
#include <stdio.h>

int main(void) {
    printf("\n=== Performance Test ===\n");
    heap_init();

    for (int strategy = 0; strategy < 2; strategy++) {
        current_fit = (strategy == 0 ? FIRST_FIT : BEST_FIT);
        allocations_done = 0;
        blocks_traversed = 0;

        printf("\nUsing %s:\n", strategy == 0 ? "FIRST_FIT" : "BEST_FIT");

        void *ptrs[500] = {0};
        for (int i = 0; i < 500; i++) {
            ptrs[i] = my_malloc(32);
            if (!ptrs[i]) break;
            allocations_done++;
            if (i % 2 == 0) my_free(ptrs[i]);
        }

        printf("Allocations: %zu\n", allocations_done);
        printf("Blocks traversed: %zu\n", blocks_traversed);
        if (allocations_done > 0) {
            printf("Average per allocation: %.2f\n",
                   (double)blocks_traversed / allocations_done);
        }
    }

    printf("\n=== Performance Test Finished ===\n");
    return 0;
}





