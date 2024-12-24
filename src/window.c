#include "window.h"

void windowInit(Window* window) {
  window->height = WIN_HEIGHT;
  window->width = WIN_WIDTH;
  window->isRunning = true;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    exit(1);
  }
  window->window = SDL_CreateWindow("Doom Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->width, window->height, 0);
  if (!window->window) {
    fprintf(stderr, "Error creating SDL window.\n");
    exit(1);
  }
  window->renderer = SDL_CreateRenderer(window->window, -1, 0);
  if (!window->renderer) {
    fprintf(stderr, "Error creating SDL renderer.\n");
    exit(1);
  }
}

void windowDestroy(Window* window) {
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);
  SDL_Quit();
}

void windowEvents(Window* window) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        window->isRunning = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          window->isRunning = false;
        }
        break;
    }
  }
}
