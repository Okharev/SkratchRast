#include <stdint.h>

#include "helpers.h"
#include "obj_reader.h"

Mesh obj_read(Arena* restrict a, const char* const restrict path) {
  FILE* file = fopen(path, "r");
  ASSERT_MSG(file != nullptr, "file could not be opened");

  Mesh mesh;
  mesh.total_vertices = 0;

  char line[32];
  // iterate through all lines to get total vertex & face amount
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'v' && line[1] == ' ') {
      mesh.total_vertices++;
    }
  }

  ASSERT_MSG(mesh.total_vertices != 0, "obj file doesn't contain vertices");

  rewind(file);

  mesh.vertices = arena_alloc(a, mesh.total_vertices * sizeof(Vec3f));

  size_t v_index = 0;
  while (fgets(line, sizeof(line), file)) {
    if (line[0] != 'v' || line[1] != ' ')
      continue;

    Vec3f vertex;
    if (sscanf(line + 2, "%f %f %f", &vertex.x, &vertex.y, &vertex.z) == 3) {
      mesh.vertices[v_index++] = vertex;
    }
  }

  fclose(file);
  return mesh;
}
