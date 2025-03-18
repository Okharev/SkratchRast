#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>

#include "vec3f.h"
#include "ppm.h"
#include "mesh.h"
#include "quaternion.h"
#include "transform.h"

// TODO Add caching mechanism for view matrix and projection matrix
typedef struct Camera {
    Transform transform;
    bool proj_dirty;
    bool view_dirty;
    Mat4f cache_proj;
    Mat4f cache_view;
    Vec3f up;
    float fov;
    float near;
    float far;
    float aspect_ratio;
} Camera;

typedef struct Entity {
    Mesh *mesh;
    Transform transform;
} Entity;

Camera init_camera(Vec3f position, Quaternion quaternion, Vec3f up, float fov, float near, float far,
                   float aspect_ratio);

Mat4f *get_view(Camera *restrict cam);

Mat4f *get_proj(Camera *restrict cam);

void move_camera(Camera *restrict cam, const Vec3f *restrict move);

void camera_look_at(Camera *restrict cam, Vec3f *restrict target);

void render_mesh(SDL_Renderer *restrict renderer, Camera *restrict cam, Entity *restrict entity);

#endif //CAMERA_H
