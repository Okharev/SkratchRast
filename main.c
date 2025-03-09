#include <stdint.h>
#include <stdlib.h>

#include "src/mat4f.h"
#include "src/memory/arena_allocator.h"
#include "src/obj_reader.h"

typedef struct {
    Vec3f position;
    Vec3f rotation; // Could represent Euler angles.
    Vec3f scale;
} Transform;

typedef struct {
    Vec3f position;
    Vec3f up;
    Vec3f target;
    float fov;
} Camera;

typedef struct {
    Mesh *mesh;
    Mat4f transform;
} Entity;

typedef struct {
    uint16_t x;
    uint16_t y;
} ScreenPos;

void apply_camera_transform(const Camera *restrict const camera, const Mat4f *restrict vertex,
                            Mat4f *restrict const output) {
    const Mat4f cam_relative_translation = mat4f_translate(&(Vec3f){
        .x = -camera->position.x, .y = -camera->position.y, .z = -camera->position.z
    });
    mat4f_multiply(vertex, &cam_relative_translation, output);
}

void apply_projection_transform(const Mat4f *restrict projection, const Mat4f *restrict vertex, Mat4f *restrict output) {
    mat4f_multiply(vertex, projection, output);
}

Mat4f get_cam_projection(const Camera* restrict const cam) {
    return mat4f_projection(cam->fov, 16.0f / 9.0f, 0.001f, 10000.0f);
}


int main(void) {
    constexpr size_t size = 1024 * 1024 * 8; // 8MB
    uint8_t *restrict mem_buff = malloc(size);
    Arena level_arena = arena_init(mem_buff, size);

    // mesh with vertex in local space
    Camera cam = (Camera){
        .position = (Vec3f){.x = -5.0f, .y = -5.0f, .z = -5.0f},
        .up = {.x = 0.0f, .y = 1.0f, .z = 0.0f},
        .target = {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        .fov = 75.0f
    };
    const Mesh mesh = obj_read(&level_arena, "../assets/teapot.obj");

    Mat4f final_mat = mat4f_identity();

    // Apply the WorldSpace transform to get the vertex's position in the world
    const Vec3f worldPos = (Vec3f){-5.0f, -5.0f, -5.0f};
    const Mat4f vertexPos = mat4f_translate(&worldPos);
    mat4f_multiply(&final_mat, &vertexPos, &final_mat);

    // Apply the View Space transform to get the vertex position relative from the camera
    apply_camera_transform(&cam, &final_mat, &final_mat);

    // Apply clip space here with projection matrix to apply perspective to vertexes
    const Mat4f projection = get_cam_projection(&cam);
    apply_projection_transform(&projection, &final_mat, &final_mat);

    // Perspective divide to get NDC coordinates which maps vertexes position between 1 and -1

    // Take ndc coordinates and transform them to actual pixel coordinates

    for (size_t i = 0; i < mesh.total_vertices; ++i) {
    }

    return 0;
}
