#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
    uint8_t *start;
    size_t size;
} Heap;


typedef struct {
    size_t size;
    struct Block* prev;
    struct Block* next;
} Block;

Heap heap_init() {
    constexpr size_t size = 1024 * 1024 * 10;
    const Heap heap = {
        .start = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE),
        .size = size
    };

    return heap;
}

uint8_t* heap_alloc(Heap *heap, const size_t size) {
    auto buff = (Block*) heap->start;
    *buff = Block {
        .size = size,
        .prev = nullptr,
        .next = sizeof(Block) + size,
    };
}