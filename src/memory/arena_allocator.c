#include <memoryapi.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <winnt.h>

#include "../helpers.h"
#include "arena_allocator.h"

#define DEFAULT_ALIGNEMENT (sizeof(void*) * 2)

static bool is_power_of_two(const uintptr_t x) {
  return (x & x - 1) == 0;
}

void arena_init(Arena* a, void* backing_buffer, size_t backing_buffer_length) {}

void arena_free(Arena* a, void* ptr) {}

void* arena_alloc(Arena* a, size_t size) {}

void* arena_alloc_align(Arena* a, size_t size, size_t align) {}

void* arena_resize_align(Arena* a, void* old_memory, size_t old_size, size_t new_size, size_t align) {}

void arena_free_all(Arena* a) {}