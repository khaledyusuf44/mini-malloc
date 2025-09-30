Mini Memory Allocator

A custom memory allocator implemented in C that provides a simplified version of malloc, calloc, realloc, and free.
This project was built step by step to explore low-level memory management, alignment, fragmentation handling, and allocation strategies.

⸻

Project Goals
• Build a self-contained allocator that manages a 1 MB heap in user space.
• Implement core allocation primitives (my_malloc, my_calloc, my_realloc, my_free).
• Explore allocation strategies: FIRST_FIT and BEST_FIT.
• Understand and mitigate fragmentation through block splitting and coalescing.
• Add debugging utilities such as print_heap() and check_invariants().
• Run performance and fragmentation tests to compare allocation strategies.

⸻

Key Features
• Heap simulation: Allocations are managed inside a fixed-size 1 MB buffer.
• Block headers: Each block stores metadata (size, free/used state, next pointer).
• Alignment guarantee: All returned pointers are 16-byte aligned.
• Example: a request of 18 bytes results in a 32-byte aligned allocation.
• Allocation strategies:
• FIRST_FIT: Selects the first available free block large enough.
• BEST_FIT: Selects the smallest free block large enough.
• Fragmentation management:
• Splitting: Large free blocks are split when possible.
• Coalescing: Adjacent free blocks are merged during my_free.
• Debugging tools:
• print_heap() dumps block state (address, size, free/used).
• check_invariants() validates internal consistency.
• check_leaks() reports unfreed allocations.
• Test suite:
• Functional tests for correctness.
• Fragmentation tests to observe block splitting/merging.
• Performance tests comparing FIRST_FIT vs BEST_FIT.

⸻

Limitations
• No detection of double frees.
• No detection of dangling pointer usage.
• No guard against freeing memory that was not allocated by this allocator.
• Fixed heap size (1 MB). Out-of-memory is signaled by returning NULL.

⸻

Project Structure

.
├── include/
│ └── allocator.h # Public API and type definitions
├── src/
│ ├── allocator.c # Allocation logic (malloc, free, etc.)
│ ├── heap.c # Heap initialization
│ ├── utils.c # Helper utilities
├── tests/
│ ├── test_allocator.c # Basic API and correctness tests
│ ├── frag_test.c # Fragmentation behavior tests
│ ├── perf_test.c # Performance comparison (FIRST_FIT vs BEST_FIT)
├── Makefile # Build and test automation
└── README.md # Project documentation

⸻

Example Output

Fragmentation Test

=== Fragmentation Test ===
Allocated A, B
Freed B
Allocated C (inside B’s freed space)
Freed A and C
Heap invariant check: OK

Performance Test

=== Performance Test ===

Using FIRST_FIT:
Allocations: 1000
Blocks traversed: 62750
Average per allocation: 62.75

Using BEST_FIT:
Allocations: 1000
Blocks traversed: 188000
Average per allocation: 188.00

⸻

What We Achieved 1. Built a functioning mini memory allocator from scratch. 2. Implemented allocation strategies and compared their efficiency. 3. Added support for block splitting and coalescing. 4. Created a test suite for correctness, fragmentation, and performance. 5. Delivered a learning tool for systems programming and memory management concepts.

⸻

Next Steps
• Add error detection for double frees and invalid frees.
• Implement boundary tags for faster coalescing.
• Support variable heap sizes or dynamic growth.
• Extend performance benchmarks with larger workloads.

⸻

This project is both a learning exercise and a foundation for understanding how memory allocators work under the hood.
It demonstrates how higher-level abstractions like malloc can be implemented using simple but careful memory management logic.
