#include "SDL/SDL.h"


SDL_Surface *surface;
int done = 0;

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        exit(1);
    }

    const SDL_VideoInfo *videoInfo;
    videoInfo = SDL_GetVideoInfo();

    if (!videoInfo) {
        fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
        exit(1);
    }

    int videoFlags;
    videoFlags = SDL_OPENGL;
    videoFlags |= SDL_GL_DOUBLEBUFFER;
    videoFlags |= SDL_HWPALETTE;
    videoFlags |= SDL_RESIZABLE;
    //    videoFlags |= SDL_FULLSCREEN;

    if (videoInfo->hw_available) {
        videoFlags |= SDL_HWSURFACE;
    } else {
        videoFlags |= SDL_SWSURFACE;
    }

    if (videoInfo->blit_hw) {
        videoFlags |= SDL_HWACCEL;
    }

    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    surface = SDL_SetVideoMode(400, 300, 32, videoFlags);

    if (!surface) {
        fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
        exit(1);
    }
}

void handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                    case SDLK_F1:
                        SDL_WM_ToggleFullScreen(surface);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                done = 1;
                break;
            default:
                break;
        }
    }
}

