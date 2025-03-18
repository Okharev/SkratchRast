#ifndef MESH_H
#define MESH_H

#include <stdint.h>

#include "vec3f.h"
#include "memory/arena_allocator.h"

typedef struct Mesh {
    uint32_t vertices_count;
    uint32_t edges_count;
    uint32_t *edges;
    Vec3f *vertices;
} Mesh;

Mesh *mesh_from_obj(Arena *arena, const char *restrict path);

#endif //MESH_H
