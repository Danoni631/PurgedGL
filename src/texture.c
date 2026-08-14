#include "purgedgl.h"

static float currentu = 0.0f;
static float currentv = 0.0f;

void PurgedGLBindTexture(GLContext *ctx, GLTexture *tex)
{
    ctx->current_texture = tex;
}

void PurgedGLTexCoord2f(GLContext *ctx, float u, float v)
{
    (void)ctx;
    currentu = u;
    currentv = v;
}