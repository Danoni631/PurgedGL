#include "purgedgl.h"

void PurgedGLClear(GLContext *ctx, DWORD color)
{
    UINT size = ctx->width * ctx->height;
    
    for (DWORD i = 0; i < size; i++)
    {
        ctx->color_buffer[i] = color;
        ctx->z_buffer[i] = 1.0f;
    }
}

void PurgedGLColor3f
(
    GLContext *ctx,
    float r,
    float g,
    float b
)
{
    BYTE ir = (BYTE)(r * 255.0f);
    BYTE ig = (BYTE)(g * 255.0f);
    BYTE ib = (BYTE)(b * 255.0f);
    ctx->current_color = 0xFF000000 | (ir << 16) | (ig << 8) | ib;
}

void PurgedGLBegin(GLContext *ctx, int mode)
{
    (void)mode;
    ctx->vertex_count = 0;
}

void PurgedGLEnd(GLContext *ctx)
{
    ctx->vertex_count = 0;
}