#include <memoryapi.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <winnt.h>

#include "../helpers.h"
#include "arena_allocator.h"

static constexpr uintptr_t DEFAULT_ALIGNMENT = (2 * sizeof(void *));

static bool is_power_of_two(const uintptr_t x) {
  return (x & x - 1) == 0;
}

/// @param ptr the pointer to align
/// @param align assumes that this is  a power of two
/// @return the offstd aligned pointer
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


Arena arena_init(void* backing_buffer, const size_t backing_buffer_length) {
  Arena a;
  a.mem_buff = (uintptr_t) backing_buffer;
  a.buff_len = backing_buffer_length;
  a.curr_offset = (uintptr_t) backing_buffer;
  a.prev_offset = 0;

  return a;
}

void arena_free(Arena* a, void* ptr) {}

void* arena_alloc(Arena* a, const size_t size) {
  return arena_alloc_align(a, size, DEFAULT_ALIGNMENT);
}

void* arena_alloc_align(Arena* a, const size_t size, const size_t align) {
  const uintptr_t aligned_offset = align_forward(a->curr_offset, align);

  // TODO Check if allocation exceeds arena buffer

  a->curr_offset = aligned_offset + size;

  return (void*) a->curr_offset;
}

void* arena_resize_align(Arena* a, void* old_memory, size_t old_size, size_t new_size, size_t align) {}

void arena_free_all(Arena* a) {}