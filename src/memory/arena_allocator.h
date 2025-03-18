#ifndef ARENA_ALLOC_H
#define ARENA_ALLOC_H

#include <stddef.h>  // Defines size_t

typedef struct {
    uintptr_t mem_buff;
    size_t buff_len;
    uintptr_t curr_offset;
} Arena;

Arena arena_init(void *backing_buffer, size_t backing_buffer_length);

void arena_free(Arena *a, void *ptr);

void *arena_alloc(Arena *a, size_t size);

void *arena_alloc_align(Arena *a, size_t size, size_t align);

void *arena_resize_align(Arena *a, void *old_memory, size_t old_size, size_t new_size, size_t align);

void arena_free_all(Arena *a);

#endif
