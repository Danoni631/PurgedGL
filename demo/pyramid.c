#include "../src/purgedgl.h"
// You can switch "../src/purgedgl.h" to <purgedgl.h>

#define WIDTH 320
#define HEIGHT 200

static DWORD Zbuff[WIDTH * HEIGHT];

void RenderFrame(DWORD fb)
{
    GLContext gl;
    PurgedGLInit(&gl, &fb, Zbuff, WIDTH, HEIGHT);
    PurgedGLClear(&gl, 0xFF101010);

    PurgedGLModePerspective
    (
        &gl, 60.0f,
        (float)WIDTH / HEIGHT,
        0.1f, 100.0f
    );

    PurgedGLSetLightDir(&gl, 0.5f, -1.0f, -0.5f);

    PurgedGLBegin(&gl, PGL_TRIANGLES);
    PurgedGLColor3f(&gl, 1.0f, 0.0f, 0.0f);
    PurgedGLVertex(&gl,  0.0f,  0.8f, -2.5f);
    PurgedGLVertex(&gl, -0.5f, -0.5f, -2.0f);
    PurgedGLVertex(&gl,  0.5f, -0.5f, -2.0f);

    PurgedGLColor3f(&gl, 0.0f, 1.0f, 0.0f);
    PurgedGLVertex(&gl,  0.0f,  0.8f, -2.5f);
    PurgedGLVertex(&gl,  0.5f, -0.5f, -2.0f);
    PurgedGLVertex(&gl,  0.0f, -0.5f, -3.0f);
    PurgedGLEnd(&gl);
}