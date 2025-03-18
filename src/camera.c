#include "camera.h"
#include "helpers.h"
#include "mat4f.h"
#include "mesh.h"

static float deg_to_rad(const float radians) {
    return radians * (180.0f / PI_F);
}

Camera init_camera(
    const Vec3f position,
    const Quaternion quaternion,
    const Vec3f up,
    const float fov,
    const float near,
    const float far,
    const float aspect_ratio
) {
    const Mat4f def = mat4f_identity();
    Camera cam;
    cam.transform = (Transform){
        .SRT_mat = def,
        .quaternion = quaternion,
        .scale = (Vec3f){.x = 1.0f, .y = 1.0f, .z = 1.0f},
        .position = position,
        .is_dirty = true
    };
    cam.proj_dirty = true;
    cam.view_dirty = true;
    cam.up = up;
    cam.cache_proj = mat4f_projection(deg_to_rad(fov), aspect_ratio, near, far);
    cam.cache_view = mat4f_look_at(
        &cam.transform.position,
        &(Vec3f){0.0f, 0.0f, 0.0f},
        &cam.up
    );
    cam.fov = fov;
    cam.far = far;
    cam.near = near;
    cam.aspect_ratio = aspect_ratio;

    return cam;
}

Mat4f *get_view(Camera *restrict cam) {
    if (cam->view_dirty || cam->transform.is_dirty) {
        cam->cache_view = mat4f_look_at(
            &cam->transform.position,
            &(Vec3f){0.0f, 0.0f, 0.0f},
            &cam->up
        );
        cam->view_dirty = false;
    }

    return &cam->cache_view;
}

Mat4f *get_proj(Camera *restrict cam) {
    if (cam->proj_dirty) {
        cam->cache_proj = mat4f_projection(deg_to_rad(cam->fov), cam->aspect_ratio, cam->near, cam->far);
        cam->proj_dirty = false;
    }

    return &cam->cache_proj;
}

void move_camera(Camera *restrict cam, const Vec3f *restrict move) {
    cam->view_dirty = true;
    set_position(move, &cam->transform);
}

void camera_look_at(Camera *cam, Vec3f *target) {
    if (true) {
    }
}

void render_mesh(SDL_Renderer *const restrict renderer, Camera *restrict cam, Entity* restrict entity) {
    const Mesh *restrict const mesh = entity->mesh;
    Mat4f mvp;
    const Mat4f *entity_trs = get_trs(&entity->transform);
    const Mat4f *view = get_view(cam);
    const Mat4f *project_mat = get_proj(cam);
    mat4f_multiply(project_mat, view, &mvp);
    mat4f_multiply(&mvp, entity_trs, &mvp);

    SDL_Rect dim;
    SDL_GetRenderViewport(renderer, &dim);
    SDL_FPoint screen_points[mesh->vertices_count] = {};
    for (uint32_t i = 0; i < mesh->vertices_count; ++i) {
        Vec4f out;
        mat4f_multiply_vec4f(&(Vec4f){
                                 .x = mesh->vertices[i].x, .y = mesh->vertices[i].y, .z = mesh->vertices[i].z, .w = 1.0f
                             }, &out, &mvp);

        constexpr float EPSILON = 1e-6f; // Very small tolerance number
        if (fabsf(out.w) <= EPSILON)
            continue; // Skip unsafe divide by zero

        const float inv_w = 1.0f / out.w;
        const Vec3f ndc = {out.x * inv_w, out.y * inv_w, out.z * inv_w};

        if (ndc.x < -1.0f || ndc.x > 1.0f || ndc.y < -1.0f || ndc.y > 1.0f || ndc.z < -1.0f || ndc.z > 1.0f)
            continue;

        screen_points[i] = (SDL_FPoint){
            .x = ((ndc.x + 1.0f) * 0.5f * (float)dim.w),
            .y = ((1.0f - ndc.y) * 0.5f * (float)dim.h)
        };
    }

    SDL_RenderPoints(renderer, screen_points, mesh->vertices_count);
}
