#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "heap_allocator.h"

uint8_t* heap_init() {
  Block* data = (Block*)VirtualAlloc(NULL, 1024 * 1024 * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

  data[0] = (Block){.next = NULL, .size = (1024 * 1024 * 4) - sizeof(Block), .free = true};

  return (uint8_t*)(data + 1);
}

// uint8_t* heap_alloc(Heap *heap, const size_t size) {
// }