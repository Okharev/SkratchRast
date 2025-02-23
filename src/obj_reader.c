#include <stdint.h>

#include "obj_reader.h"
#include "helpers.h"

Mesh obj_read(Arena* restrict a, const char* const restrict path) {
  FILE *file = fopen(path, "r");

  ASSERT_MSG(file != nullptr, "file could not be opened");

  Mesh mesh;
  mesh.total_vertices = 3644;
  mesh.vertices = arena_alloc(a, mesh.total_vertices * sizeof(Vec3f));

  char c;
  size_t vert_idx = 0;
  do {
    char line[32];
    for (uint8_t i = 0; i < 32; ++i) {
      if (c == '\n') {
        c = fgetc(file);
        break;
      }
      line[i] = c;
      c = fgetc(file);
    }

    Vec3f v;
    const char (* restrict x)[9] = &line[2];
    const char (* restrict y)[9] = &line[12];
    const char (* restrict z)[9] = &line[21];
    v.x = atof(x);
    v.y = atof(y);
    v.z = atof(z);

    mesh.vertices[vert_idx] = v;
    vert_idx++;
  } while (!feof(file));

  fclose(file);
  return mesh;
}

static size_t getline(char** restrict line, FILE* restrict file) {

}