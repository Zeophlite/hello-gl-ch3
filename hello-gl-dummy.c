#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <stdio.h>
#include "sdl.h"

static int make_resources(void)
{
    return 1;
}

/*
 * GLUT callbacks:
 */
static void update_fade_factor(void)
{
}

static void render(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapBuffers();
}

extern int done;

/*
 * Entry point
 */
int main(int argc, char** argv)
{
    initSDL();

    glewInit();
    if (!glewIsSupported("GL_VERSION_2_0")) {
        fprintf(stderr, "OpenGL 2.0 not available\n");
        return 1;
    }

    if (!make_resources()) {
        fprintf(stderr, "Failed to load resources\n");
        return 1;
    }

    while (!done) {
        handleInput();
        update_fade_factor();
        render();
    }

    SDL_Quit();
    return 0;
}

