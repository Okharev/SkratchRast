#include "transform.h"

void set_position(const Vec3f* restrict new_position, Transform* restrict transform) {
    transform->is_dirty = true;
    transform->position = *new_position;
}

void set_rotation(const Vec3f* restrict new_rotation, Transform* restrict transform) {
    transform->is_dirty = true;
    transform->position = *new_rotation;
}

void set_scale(const Vec3f* restrict new_scale, Transform* restrict transform) {
    transform->is_dirty = true;
    transform->position = *new_scale;
}

const Mat4f* get_srt(Transform* restrict restrict transform) {
    if (transform->is_dirty) {
        Mat4f out;
        const Mat4f scale = mat4f_scaling(&transform->scale);
        const Mat4f rotate = mat4f_rotateX(0.0f);;
        const Mat4f translate = mat4f_translate(&transform->position);
        mat4f_multiply(&rotate, &scale, &out);
        mat4f_multiply(&translate, &out, &out);

        transform->SRT_mat = out;
    }

    return &transform->SRT_mat;
}
