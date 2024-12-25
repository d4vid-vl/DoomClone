#include "window.h"
#include <math.h>
#include <stdio.h>

// Initialize window
// * param window: Window struct
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

// Destroy window
// * param window: Window struct
void windowDestroy(Window* window) {
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);
  SDL_Quit();
}

// Handle window events
// * param window: Window struct
void windowEvents(Window* window, Player* player) {
  SDL_Event event;
  int dx = sin(player->angle*M_PI/180)*10.0;
  int dy = cos(player->angle*M_PI/180)*10.0;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        window->isRunning = false;
        break;
      case SDL_KEYDOWN: 
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          window->isRunning = false;
        } else if (event.key.keysym.sym == SDLK_w) {
          player->x += dx;
          player->y += dy;
        } else if (event.key.keysym.sym == SDLK_a) {
          player->angle -= 4;
          if (player->angle < 0) {
            player->angle += 360;
          }
        } else if (event.key.keysym.sym == SDLK_s) {
          player->x -= dx;
          player->y -= dy;
        } else if (event.key.keysym.sym == SDLK_d) {
          player->angle += 4;
          if (player->angle >= 360) {
            player->angle -= 360;
          }
        } else if (event.key.keysym.sym == SDLK_UP) {
          player->z -= 4;
        } else if (event.key.keysym.sym == SDLK_DOWN) {
          player->z += 4;
        } else if (event.key.keysym.sym == SDLK_LEFT) {
          player->look -= 1;
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
          player->look += 1;
        }
        break;
    }
  }
}

// Render everything on screen
// * param window: Window struct
void renderShow(Window* window) {
    // Draw canvas
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    SDL_RenderClear(window->renderer);
    
    // Draw player
    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_Rect player = {window->width/2 - 5, window->height/2 - 5, 10, 10};
    SDL_RenderFillRect(window->renderer, &player);
    SDL_RenderPresent(window->renderer);
}
