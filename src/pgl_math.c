#include "purgedgl.h"

static float fast_sin(float x)
{
    float x2 = x * x;
    return x * (1.0f - x2 / 6.0f + (x2 * x2) / 120.0f);
}

static float fast_cos(float x)
{
    return fast_sin(1.5707963f - x);
}

static float fast_tan(float x)
{
    return fast_sin(x) / fast_cos(x);
}

static Vector3 mat_mul_vec(Matrix4 *m, Vector3 v)
{
    Vector3 r;
    float w =
    (
        v.x * m->m[3][0] + v.y *
        m->m[3][1] + v.z * m->m[3][2] + m->m[3][3]
    );

    if (w == 0.0f) w = 1.0f;

    r.x =
    (
        v.x * m->m[0][0] + v.y *
        m->m[0][1] + v.z * m->m[0][2] +
        m->m[0][3]
    ) / w;

    r.y =
    (
        v.x * m->m[1][0] + v.y *
        m->m[1][1] + v.z * m->m[1][2] +
        m->m[1][3]
    ) / w;

    r.z =
    (
        v.x * m->m[2][0] + v.y *
        m->m[2][1] + v.z *
        m->m[2][2] + m->m[2][3]
    ) / w;
    
    return r;
}