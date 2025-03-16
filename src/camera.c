#include "camera.h"

#include "quaternion.h"
#include "helpers.h"
#include "mat4f.h"
#include "mesh.h"

static float deg_to_rad(const float radians) {
    return radians * (180.0f / PI_F);
}

static void compute_mvp(const Camera* const restrict cam, Mat4f* const restrict mvp) {
    // Compute view matrix components.
    const Vec3f subbed    = vec3f_substract(&cam->target, &cam->position);
    const Vec3f forward   = vec3f_normalize(&subbed);
    const Vec3f normalized = vec3f_cross(&cam->up, &forward);
    const Vec3f right     = vec3f_normalize(&normalized);
    const Vec3f corrected = vec3f_cross(&right, &forward);

    const Mat4f view = (Mat4f){
        .mat = {
            {right.x,    right.y,    right.z,    0.0f},
            {corrected.x,corrected.y,corrected.z,0.0f},
            {-forward.x, -forward.y, -forward.z, 0.0f},
            {0.0f,       0.0f,       0.0f,       1.0f}
        }
    };

    // Translation to move the world relative to the camera.
    const Mat4f translate = mat4f_translate(&(Vec3f){.x = -cam->position.x,
                                                 .y = -cam->position.y,
                                                 .z = -cam->position.z});
    Mat4f viewTranslate;
    mat4f_multiply(&view, &translate, &viewTranslate);

    // Perspective projection.
    const Mat4f projection = mat4f_projection(deg_to_rad(cam->fov), 16.0f / 9.0f, 0.01f, 1000.0f);

    Mat4f vp;
    mat4f_multiply(&projection, &viewTranslate, &vp);

    // If there's a world-to-mesh transform, it can be applied here.
    // For now, assume identity transformation:
    const Mat4f world_mesh_space = mat4f_translate(&(Vec3f){.x = 0.0f, .y = 0.0f, .z = 0.0f});

    mat4f_multiply(&vp, &world_mesh_space, mvp);
}

Camera init_camera(const Vec3f position, const Vec4f quaternion, const Vec3f up, const float fov) {
  Camera cam;
  cam.fov = fov;
  cam.transform.is_dirty = true;
  cam.transform.scale = (Vec3f) { 1.0f, 1.0f, 1.0f };
  cam.transform.position = position;
  cam.transform.quaternion = quaternion;
  cam.up = up;

  return cam;
}

void look_at(Camera* restrict cam, const Vec3f* restrict target) {
  const Vec4f look_at_quat = quat_look_at(&cam->transform.position, target, &cam->up);

  set_rotation(&look_at_quat, &cam->transform);
}

void render_mesh(SDL_Renderer* const restrict renderer, const Camera* const restrict cam, const Mesh* const restrict mesh) {
    Mat4f mvp;
    compute_mvp(cam, &mvp);

    SDL_FPoint points[mesh->vertices_count] = {};

    for (uint32_t i = 0; i < mesh->vertices_count; ++i) {
        Vec4f out;
        mat4f_multiply_vec4f(&(Vec4f){.x = mesh->vertices[i].x, .y = mesh->vertices[i].y, .z = mesh->vertices[i].z, .w = 1.0f}, &out, &mvp);

        constexpr float EPSILON = 1e-6f;  // Very small tolerance number
        if (fabsf(out.w) <= EPSILON)
            continue;  // Skip unsafe divide by zero

        const float inv_w = 1.0f / out.w;
        const Vec3f ndc = {out.x * inv_w, out.y * inv_w, out.z * inv_w};

        if (ndc.x < -1.0f || ndc.x > 1.0f || ndc.y < -1.0f || ndc.y > 1.0f || ndc.z < -1.0f || ndc.z > 1.0f)
            continue;

        const SDL_FPoint p = {
            .x = ((ndc.x + 1.0f) * 0.5f * 480.0f),
            .y = ((1.0f - ndc.y) * 0.5f * 270.0f)
        };

        points[i] = p;
    }

    SDL_RenderPoints(renderer, points, mesh->vertices_count);
}
