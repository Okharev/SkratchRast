#include <memoryapi.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <winnt.h>

#include "../helpers.h"
#include "arena_allocator.h"

#define DEFAULT_ALIGNEMENT (sizeof(void*) * 2)

static inline bool is_power_of_two(uintptr_t num) {
  return (num & (num - 1)) == 0;
}

static uintptr_t align_forward(uintptr_t ptr, size_t align) {
  uintptr_t p, a, modulo;

  ASSERT_MSG(is_power_of_two(align), "%d is not pow of 2", align);

  p = ptr;
  a = (uintptr_t)align;
  // Same as (p % a) but faster as 'a' is a power of two
  modulo = p & (a - 1);

  if (modulo != 0) {
    // If 'p' address is not aligned, push the address to the
    // next value which is aligned
    p += a - modulo;
  }
  return p;
}

uintptr_t* arena_push(Arena* arena, const size_t size) {}

void arena_reset(Arena* arena) {
  arena->offset = 0;
}
