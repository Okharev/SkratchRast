#ifndef OBJ_READER_H
#define OBJ_READER_H
#include "memory/arena_allocator.h"
#include "vec3f.h"

typedef struct {
  size_t total_vertices;
  Vec3f* restrict vertices;
} Mesh;

Mesh obj_read(Arena* a, const char* path);

#endif //OBJ_READER_H
