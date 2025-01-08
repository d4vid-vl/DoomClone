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
  initSectors();
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
  const Uint8* keys = SDL_GetKeyboardState(NULL);
  int dx = sin(player->angle*M_PI/180)*10.0;
  int dy = cos(player->angle*M_PI/180)*10.0;

  window->lastFrame = SDL_GetTicks();
  if (window->lastFrame >= window->lastTime + 1000) {
    window->lastTime = window->lastFrame;
    window->fps = window->frameCount;
    window->frameCount = 0;
  }

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        window->isRunning = false;
        break;
    }
  }
  if (keys[SDL_SCANCODE_ESCAPE]) {
    window->isRunning = false;
  }  
  if (keys[SDL_SCANCODE_W]) {
    player->x += dx;
    player->y += dy;
  }
  if (keys[SDL_SCANCODE_A]) {
    player->angle -= 4;
    if (player->angle < 0) {
      player->angle += 360;
    }
  }
  if (keys[SDL_SCANCODE_S]) {
    player->x -= dx;
    player->y -= dy;
  }
  if (keys[SDL_SCANCODE_D]) {
    player->angle += 4;
    if (player->angle >= 360) {
      player->angle -= 360;
    }
  }
  if (keys[SDL_SCANCODE_J]) {
    player->x -= dy;
    player->y += dx;
  }
  if (keys[SDL_SCANCODE_L]) {
    player->x += dy;
    player->y -= dx;
  }
  if (keys[SDL_SCANCODE_UP]) {
    player->z -= 4;
  }
  if (keys[SDL_SCANCODE_DOWN]) {
    player->z += 4;
  }
  if (keys[SDL_SCANCODE_LEFT]) {
    player->look -= 1;
  }
  if (keys[SDL_SCANCODE_RIGHT]) {
    player->look += 1;
  }
}

// Render everything on screen
// * param window: Window struct
void renderShow(Window* window, Player* player) {
    // Frame rate control
    window->frameCount++;  
    int timerFPS = SDL_GetTicks() - window->lastFrame;
    if (FRAME_TARGET_TIME > timerFPS) {
        SDL_Delay(FRAME_TARGET_TIME - timerFPS);
    }
    
    // Draw canvas
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    SDL_RenderClear(window->renderer);
    
    // Draw player
    drawEnv(player, window);
    SDL_RenderPresent(window->renderer);
}
