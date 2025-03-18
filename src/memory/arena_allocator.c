#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../helpers.h"
#include "arena_allocator.h"

static constexpr uintptr_t DEFAULT_ALIGNMENT = 2 * sizeof(void *);

static bool is_power_of_two(const uintptr_t x) {
    return (x & x - 1) == 0;
}

/// @param ptr the pointer to align
/// @param align assumes that this is  a power of two
/// @return the offsetted aligned pointer
static uintptr_t align_forward(const uintptr_t ptr, const size_t align) {
    uintptr_t p = ptr;
    // Same as (p % a) but faster as 'a' is a power of two
    const uintptr_t modulo = p & align - 1;

    if (modulo != 0) {
        // If 'p' address is not aligned, push the address to the
        // next value which is aligned
        p += align - modulo;
    }
    return p;
}

Arena arena_init(void *restrict backing_buffer, const size_t backing_buffer_length) {
    Arena a;
    memset(backing_buffer, 0, backing_buffer_length);
    a.mem_buff = (uintptr_t) backing_buffer;
    a.buff_len = backing_buffer_length;
    a.curr_offset = (uintptr_t) backing_buffer;

    return a;
}

void arena_free(Arena *restrict a, void *restrict ptr) {
}

void *arena_alloc(Arena *restrict a, const size_t size) {
    return arena_alloc_align(a, size, DEFAULT_ALIGNMENT);
}

void *arena_alloc_align(Arena *restrict a, const size_t size, const size_t align) {
    const uintptr_t aligned_offset = align_forward(a->curr_offset, align);

    // Checking that we don't exceed buffer allocation
    ASSERT_MSG(a->curr_offset + size <= a->mem_buff + a->buff_len, "exceeded arena allocation");

    a->curr_offset = aligned_offset + size;

    return (void *) aligned_offset;
}

void *arena_resize_align(Arena *restrict a, void *restrict old_memory, size_t old_size, size_t new_size, size_t align) {
}

void arena_free_all(Arena *a) {
}
