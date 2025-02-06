#ifndef HEAP_ALLOC_H
#define HEAP_ALLOC_H

#include <stdint.h>

typedef struct {
  size_t size;
  struct Block* next;
  bool free;
} Block;

uint8_t* heap_init();

#endif