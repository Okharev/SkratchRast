#include <stdio.h>

#include "helpers.h"
#include "mesh.h"

static bool check_file_extension(const char* restrict path, const char* restrict extension) {
    const uint16_t path_len = strlen(path);
    const uint16_t extension_len = strlen(extension);

    if (extension_len > path_len) {
        return false;
    }

    return strcmp(path + (path_len - extension_len), extension) == 0;
}

Mesh* mesh_from_obj(Arena* arena, const char* restrict path) {
    ASSERT_MSG(check_file_extension(path, "obj"), "given path is not a valid obj file");

    FILE* file = fopen(path, "r");

    ASSERT_MSG(file != nullptr, "file could not be opened");

    Mesh* mesh = arena_alloc(arena, sizeof(Mesh));

    char line[64];
    // iterate through all lines to get total vertex & face amount
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            mesh->vertices_count++;
        }
    }

    rewind(file);

    mesh->vertices = arena_alloc(arena, mesh->vertices_count * sizeof(Vec3f));

    size_t v_index = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != 'v' || line[1] != ' ')
            continue;

        char* ptr = line + 2;
        mesh->vertices[v_index].x = strtof(ptr, &ptr);
        mesh->vertices[v_index].y = strtof(ptr, &ptr);
        mesh->vertices[v_index].z = strtof(ptr, nullptr);
        v_index++;
    }
    fclose(file);

    return mesh;
}
