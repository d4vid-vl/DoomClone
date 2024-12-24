#pragma once

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768
#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct win {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int height;
    int width;
    bool isRunning;
} Window;

void windowInit(Window *window);
void windowDestroy(Window *window);
void windowEvents(Window *window);
