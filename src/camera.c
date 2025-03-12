#include "camera.h"

#include "helpers.h"
#include "mat4f.h"
#include "mesh.h"

static float deg_to_rad(const float radians) {
    return radians * (180.0f / PI_F);
}

///
/// @param position The camera location in world space
/// @param up where is the camera "up" vector (usually Y)
/// @param target where the camera is looking at (Pitch and Yaw)
/// @param fov The field of view in degrees
/// @return the final camera
Camera init_camera(const Vec3f position, const Vec3f up, const Vec3f target, const float fov) {
    Camera cam;
    cam.fov = fov;
    cam.position = position;
    cam.target = target;
    cam.up = up;

    return cam;
}

/// TODO rafcator into smaller function for clarity
/// TODO document this
/// TODO Add Edges drawing
/// TODO Add Faces drawing
/// TODO Add simple shading
/// @param cam
/// @param mesh
/// @param buffer
void render_mesh(const Camera *restrict cam, const Mesh *restrict mesh, const PPMFile* restrict const buffer) {
    const Vec3f subbed = vec3f_substract(&cam->target, &cam->position);
    const Vec3f forward = vec3f_normalize(&subbed);
    const Vec3f normalized = vec3f_cross(&cam->up, &forward);
    const Vec3f right = vec3f_normalize(&normalized);
    const Vec3f corrected = vec3f_cross(&right, &forward);

    const Mat4f view = (Mat4f){
        .mat = {
            {right.x, right.y, right.z, 0.0f},
            {corrected.x, corrected.y, corrected.z, 0.0f},
            {-forward.x, -forward.y, -forward.z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    const Mat4f translate = mat4f_translate(&(Vec3f) { .x = -cam->position.x, .y = -cam->position.y, .z = -cam->position.z });
    Mat4f result;
    mat4f_multiply(&view, &translate, &result);

    const Mat4f projection = mat4f_projection(deg_to_rad(cam->fov), 16.0f / 9.0f, 0.01f, 10000.0f);
    const Mat4f world_mesh_space = mat4f_translate(&(Vec3f) { .x = 0.0f, .y = 0.0f, .z = 0.0f });

    Mat4f vp, mvp;  // View-projection
    mat4f_multiply(&projection, &result, &vp);
    mat4f_multiply(&vp, &world_mesh_space, &mvp);

    for (int i = 0; i < mesh->vertices_count; ++i) {
        Vec4f out;
        mat4f_multiply_vec4f(&(Vec4f){.x = mesh->vertices[i].x, .y = mesh->vertices[i].y, .z = mesh->vertices[i].z, .w = 1.0f}, &out, &mvp);

        constexpr float EPSILON = 1e-6f;  // Very small tolerance number
        if (fabsf(out.w) <= EPSILON)
            continue;  // Skip unsafe divide by zero

        const float inv_w = 1.0f / out.w;
        const Vec3f ndc = {out.x * inv_w, out.y * inv_w, out.z * inv_w};

        // Clipping check: NDC must be between -1 and 1
        if (ndc.x < -1.0f || ndc.x > 1.0f || ndc.y < -1.0f || ndc.y > 1.0f || ndc.z < -1.0f || ndc.z > 1.0f)
            continue;

        const uint16_t screenX = (uint16_t)((ndc.x + 1.0f) * 0.5f * (float) buffer->width);
        const uint16_t screenY = (uint16_t)((1.0f - ndc.y) * 0.5f * (float) buffer->height);

        // Screen bounds check
        if (screenX >= buffer->width || screenY >= buffer->height)
            continue;

        set_pixel(buffer, screenX, screenY, (Color){255, 255, 255});
    }
}
