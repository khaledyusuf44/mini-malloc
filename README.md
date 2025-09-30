# Mini Memory Allocator (mini-malloc)

A custom memory allocator implemented in C that provides a simplified version of `malloc`, `calloc`, `realloc`, and `free`.  
This project was built step by step to explore low-level memory management, alignment, fragmentation handling, and allocation strategies.

---

## Project Goals

- Build a self-contained allocator that manages a 1 MB heap in user space.
- Implement core allocation primitives: `my_malloc`, `my_calloc`, `my_realloc`, `my_free`.
- Explore allocation strategies: **FIRST_FIT** and **BEST_FIT**.
- Understand and mitigate fragmentation via block splitting and coalescing.
- Add debugging utilities such as `print_heap()` and `check_invariants()`.
- Run performance and fragmentation tests to compare strategies.

---

## Key Features

- **Heap simulation**: allocations managed inside a fixed-size 1 MB buffer.
- **Block headers**: metadata per block (size, free/used, next pointer).
- **Alignment**: all returned pointers are 16-byte aligned.  
  Example: request(18) → allocated(32).
- **Allocation strategies**:
  - `FIRST_FIT`: first free block large enough.
  - `BEST_FIT`: smallest free block large enough.
- **Fragmentation handling**: splitting and coalescing of blocks.
- **Debugging tools**:
  - `print_heap()` → dumps heap state.
  - `check_invariants()` → validates consistency.
  - `check_leaks()` → reports unfreed allocations.
- **Test suite**: functional, fragmentation, and performance tests.

---

## Limitations

- No detection of double frees.
- No protection against dangling pointers.
- Fixed heap size (1 MB). Out-of-memory is signaled with `NULL`.

---

## Project Structure

```plaintext
include/allocator.h      # API definitions
src/allocator.c          # Allocation logic
src/heap.c               # Heap initialization
src/utils.c              # Helpers
tests/test_allocator.c   # API tests
tests/frag_test.c        # Fragmentation tests
tests/perf_test.c        # Performance tests
Makefile                 # Build & test automation
README.md                # Project documentation
```

---

## Example Output

### Fragmentation Test

```plaintext
=== Fragmentation Test ===
Allocated A, B
Freed B
Allocated C (inside B’s freed space)
Freed A and C
Heap invariant check: OK
```

### Performance Test

```plaintext
=== Performance Test ===

Using FIRST_FIT:
Allocations: 1000
Blocks traversed: 62750
Average per allocation: 62.75

Using BEST_FIT:
Allocations: 1000
Blocks traversed: 188000
Average per allocation: 188.00

=== Performance Test Finished ===
```

---

## What We Achieved

1. Built a functioning mini memory allocator from scratch.
2. Implemented allocation strategies and compared their efficiency.
3. Added support for block splitting and coalescing.
4. Created a test suite for correctness, fragmentation, and performance.
5. Delivered a learning tool for systems programming and memory management concepts.

---

## Next Steps

- Add error detection for double frees and invalid frees.
- Implement boundary tags for faster coalescing.
- Support variable heap sizes or dynamic growth.
- Extend performance benchmarks with larger workloads.

---

This project is both a learning exercise and a foundation for understanding how memory allocators work under the hood.
