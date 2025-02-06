#ifndef ARENA_ALLOC_H
#define ARENA_ALLOC_H

#include <stdint.h>

typedef struct {
  uint8_t* mem_buff;
  size_t capacity;
  size_t offset;
} Arena;

Arena arena_init(const size_t capacity);
void* arena_push(Arena* arena, const size_t size);
void arena_reset(Arena* arena);
void arena_free(Arena* arena);

#endif