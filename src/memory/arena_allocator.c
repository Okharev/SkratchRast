#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "arena_allocator.h"

Arena arena_init(const size_t capacity) {
  const Arena arena = {
      .mem_buff = malloc(sizeof(uint8_t) * capacity),
      .capacity = capacity,
      .offset = 0,
  };

  return arena;
}

void* arena_push(Arena* arena, const size_t size) {
  uint8_t* buff = &arena->mem_buff[arena->offset];
  arena->offset += size;

  return buff;
}

void arena_reset(Arena* arena) {
  arena->offset = 0;
}

void arena_free(Arena* arena) {
  free(arena->mem_buff);
  arena->capacity = 0;
  arena->offset = 0;
}
