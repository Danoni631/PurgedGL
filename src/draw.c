#include "purgedgl.h"

static void draw_triangle_zbuff
(
    GLContext *ctx,
    Vector3 v0,
    Vector3 v1,
    Vector3 v2
)
{
    float hw = ctx->width * 0.5f;
    float hh = ctx->height * 0.5f;

    v0.x = (v0.x + 1.0f) * hw; v0.y = (1.0f - v0.y) * hh;
    v1.x = (v1.x + 1.0f) * hw; v1.y = (1.0f - v1.y) * hh;
    v2.x = (v2.x + 1.0f) * hw; v2.y = (1.0f - v2.y) * hh;

    int min_x = (int)(v0.x < v1.x ? (v0.x < v2.x ? v0.x : v2.x) : (v1.x < v2.x ? v1.x : v2.x));
    int max_x = (int)(v0.x > v1.x ? (v0.x > v2.x ? v0.x : v2.x) : (v1.x > v2.x ? v1.x : v2.x));
    int min_y = (int)(v0.y < v1.y ? (v0.y < v2.y ? v0.y : v2.y) : (v1.y < v2.y ? v1.y : v2.y));
    int max_y = (int)(v0.y > v1.y ? (v0.y > v2.y ? v0.y : v2.y) : (v1.y > v2.y ? v1.y : v2.y));

    if (min_x < 0) min_x = 0;
    if (min_y < 0) min_y = 0;
    if (max_x >= (int)ctx->width) max_x = ctx->width - 1;
    if (max_y >= (int)ctx->height) max_y = ctx->height - 1;

    for (int y = min_y; y <= max_y; y++)
    {
        for (int x = min_x; x <= max_x; x++)
        {
            float w0 =
            (v1.x - v0.x) * (y - v0.y) -
            (v1.y - v0.y) * (x - v0.x);
            
            float w1 =
            (v2.x - v1.x) * (y - v1.y) -
            (v2.y - v1.y) * (x - v1.x);

            float w2 = (v0.x - v2.x) * (y - v2.y) -
            (v0.y - v2.y) * (x - v0.x);

            if
            (
                (w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                (w0 <= 0 && w1 <= 0 && w2 <= 0)
            )
            {

                float area =
                (v1.x - v0.x) * (v2.y - v0.y) -
                (v1.y - v0.y) * (v2.x - v0.x);

                if (area == 0) continue;
                
                float l0 = w1 / area;
                float l1 = w2 / area;
                float l2 = w0 / area;
                float z = l0 * v0.z + l1 * v1.z + l2 * v2.z;

                int idx = y * ctx->width + x;

                if (z < ctx->z_buffer[idx])
                {
                    ctx->z_buffer[idx] = z;
                    ctx->color_buffer[idx] = ctx->current_color;
                }
            }
        }
    }
}

static void draw_textured_triangle
(
    GLContext *ctx, Vertex v0,
    Vertex v1, Vertex v2
) 
{
    float hw = ctx->width * 0.5f;
    float hh = ctx->height * 0.5f;

    v0.x = (v0.x + 1.0f) * hw; v0.y = (1.0f - v0.y) * hh;
    v1.x = (v1.x + 1.0f) * hw; v1.y = (1.0f - v1.y) * hh;
    v2.x = (v2.x + 1.0f) * hw; v2.y = (1.0f - v2.y) * hh;

    int min_x =
    (int)(v0.x < v1.x ? (v0.x < v2.x ? v0.x : v2.x) :
    (v1.x < v2.x ? v1.x : v2.x));
    int max_x =
    (int)(v0.x > v1.x ? (v0.x > v2.x ? v0.x : v2.x) :
    (v1.x > v2.x ? v1.x : v2.x));
    int min_y =
    (int)(v0.y < v1.y ? (v0.y < v2.y ? v0.y : v2.y) :
    (v1.y < v2.y ? v1.y : v2.y));
    int max_y =
    (int)(v0.y > v1.y ? (v0.y > v2.y ? v0.y : v2.y) :
    (v1.y > v2.y ? v1.y : v2.y));

    if (min_x < 0) min_x = 0;
    if (min_y < 0) min_y = 0;
    if (max_x >= (int)ctx->width) max_x = ctx->width - 1;
    if (max_y >= (int)ctx->height) max_y = ctx->height - 1;

    float area = (v1.x - v0.x) * (v2.y - v0.y) - (v1.y - v0.y) * (v2.x - v0.x);
    if (area == 0.0f) return;

    for (int y = min_y; y <= max_y; y++)
    {
        for (int x = min_x; x <= max_x; x++)
        {
            float w0 = (v1.x - v0.x) * (y - v0.y) -
            (v1.y - v0.y) * (x - v0.x);
            float w1 = (v2.x - v1.x) * (y - v1.y) -
            (v2.y - v1.y) * (x - v1.x);
            float w2 = (v0.x - v2.x) * (y - v2.y) -
            (v0.y - v2.y) * (x - v0.x);

            if
            (
                (w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                (w0 <= 0 && w1 <= 0 && w2 <= 0)
            )
            {
                float l0 = w1 / area;
                float l1 = w2 / area;
                float l2 = w0 / area;

                float z = l0 * v0.z + l1 * v1.z + l2 * v2.z;
                int idx = y * ctx->width + x;

                if (z < ctx->z_buffer[idx])
                {
                    float u = l0 * v0.u + l1 * v1.u + l2 * v2.u;
                    float v = l0 * v0.v + l1 * v1.v + l2 * v2.v;

                    DWORD texel_color =
                    0xFFFFFFFF;

                    ctx->z_buffer[idx] = z;
                    ctx->color_buffer[idx] = texel_color;
                }
            }
        }
    }
}