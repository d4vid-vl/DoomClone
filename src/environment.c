#include <SDL2/SDL_render.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "environment.h"
#include "window.h"

void drawEnv(Player *player, Window *window) {
  int wx[4], wy[4], wz[4]; // Wall coordinates
  float CS = cos(player->angle*M_PI/180), SN = sin(player->angle*M_PI/180); // Trigonometry values for player angle
  int x1 = 40-player->x, y1 = 10-player->y;
  int x2 = 40-player->x, y2 = 290-player->y;
  // Wall X, Y and Z positions
  wx[0] = x1*CS - y1*SN;
  wx[1] = x2*CS - y2*SN;

  wy[0] = x1*SN + y1*CS;
  wy[1] = x2*SN + y2*CS;
  
  wz[0] = 0-player->z+((player->look*wy[0])/32.0);
  wz[1] = 0-player->z+((player->look*wy[1])/32.0);
  
  // Screen positions
  wx[0] = wx[0] * 200 / wy[0] + window->width/2; wy[0] = wz[0] * 200 / wy[0] + window->height/2;
  wx[1] = wx[1] * 200 / wy[1] + window->width/2; wy[1] = wz[1] * 200 / wy[1] + window->height/2;
  
  // Draw points
  /*if (wx[0] > 0 && wx[0] < window->width && wy[0] > 0 && wy[0] < window->height) { // Check if point is in screen
    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_Rect rect = {wx[0], wy[0], 5, 5};  
    SDL_RenderDrawRect(window->renderer, &rect);
    SDL_RenderFillRect(window->renderer, &rect);
  } 
  if (wx[1] > 0 && wx[1] < window->width && wy[1] > 0 && wy[1] < window->height) { // Check if point is in screen
    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_Rect rect = {wx[1], wy[1], 5, 5};
    SDL_RenderDrawRect(window->renderer, &rect);
    SDL_RenderFillRect(window->renderer, &rect);
  }*/ 

  drawWall(wx[0], wx[1], wy[0], wy[1], window);
}

void drawWall(int x1, int x2, int b1, int b2, Window* window) {
  int dyb = b2-b1;
  int dx = x2-x1; if (dx == 0) { dx = 1; }
  int xs = x1;

  for (int x = x1; x < x2; x++) {
    int y = dyb * (x - xs + 0.5) / dx + b1;
    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_Rect rect = {x, y, 5, 5};
    SDL_RenderDrawRect(window->renderer, &rect);
    SDL_RenderFillRect(window->renderer, &rect);
  }
}
