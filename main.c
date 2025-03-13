#include <stdint.h>
#include <stdlib.h>

#include "src/mesh.h"
#include "src/memory/arena_allocator.h"
#include "src/camera.h"
#include "src/ppm.h"

int main(void) {
    constexpr size_t size = 1024 * 1024 * 1; // 1MB
    uint8_t *restrict mem_buff = malloc(size);
    Arena level_arena = arena_init(mem_buff, size);

    const PPMFile* file = init_file(&level_arena, P3, 480, 270);
    clear_pixel_buff(file, (Color){0, 0, 0});

    const Mesh *mesh = mesh_from_obj(&level_arena, "../assets/karanbit.obj");
    Camera cam = init_camera((Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.3f }, (Vec3f) { .x = 0.0f, .y = 1.0f, .z = 0.0f }, (Vec3f) { .x = 0.0f, .y = 0.0f, .z = 0.0f }, 40.0f);

    // TODO Refactor this to handle window buffers
    uint16_t i = 0;
    char line[32];
    while (i != 10) {
        sprintf(line, "../image-%u.ppm", i);

        render_mesh(&cam, mesh, file);
        write_file(file, line);
        clear_pixel_buff(file, (Color) { 0, 0, 0 });

        cam.position.z += 1.0f;
        i++;
    }

    arena_free_all(&level_arena);
    free(mem_buff);

    return 0;
}
