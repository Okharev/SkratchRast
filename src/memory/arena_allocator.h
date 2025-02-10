#ifndef ARENA_ALLOC_H
#define ARENA_ALLOC_H

#include <stdint.h>

typedef struct {
  uintptr_t* mem_buff;
  size_t capacity;
  size_t offset;
} Arena;

uintptr_t* arena_push(Arena* arena, const size_t size);
void arena_reset(Arena* arena);

#endif