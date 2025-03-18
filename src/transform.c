#include "transform.h"
#include "vec3f.h"

void set_position(const Vec3f *restrict new_position, Transform *restrict transform) {
    transform->is_dirty = true;
    transform->position = *new_position;
}

void set_rotation(const Quaternion *restrict new_rotation, Transform *restrict transform) {
    transform->is_dirty = true;
    transform->quaternion = *new_rotation;
}

void set_scale(const Vec3f *restrict new_scale, Transform *restrict transform) {
    transform->is_dirty = true;
    transform->scale = *new_scale;
}

const Mat4f *get_trs(Transform *restrict transform) {
    if (transform->is_dirty) {
        Mat4f out;
        const Mat4f scale = mat4f_scaling(&transform->scale);
        const Mat4f rotate = quat_to_mat4f(&transform->quaternion);
        const Mat4f translate = mat4f_translate(&transform->position);
        mat4f_multiply(&translate, &rotate, &out);
        mat4f_multiply(&out, &scale, &out);

        transform->SRT_mat = out;
        transform->is_dirty = false;
    }

    return &transform->SRT_mat;
}
