#include <SDL2/SDL_render.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "environment.h"
#include "window.h"

int loadSectors[] = {
  0, 4, 0, 40,
  4, 8, 0, 40,
  8, 12, 0, 40,
  12, 16, 0, 40
};

int loadWalls[] = {
  0, 0, 32, 0, 0,
  32, 0, 32, 32, 1,
  32, 32, 0, 32, 0,
  0, 32, 0, 0, 1,

  64, 0, 96, 0, 2,
  96, 0, 96, 32, 3,
  96, 32, 64, 32, 2,
  64, 32, 64, 0, 3,

  64, 64, 96, 64, 4,
  96, 64, 96, 96, 5,
  96, 96, 64, 96, 4,
  64, 96, 64, 64, 5,

  0, 64, 32, 64, 6,
  32, 64, 32, 96, 7,
  32, 96, 0, 96, 6,
  0, 96, 0, 64, 7,
};

int dist(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

void initSectors() {
  int s, w, v2 = 0;
  for (s = 0; s < numSect; s++) {
    S[s].ws = loadSectors[s * 4];
    S[s].we = loadSectors[s * 4 + 1];
    S[s].z1 = loadSectors[s * 4 + 2];
    S[s].z2 = loadSectors[s * 4 + 3] - loadSectors[s * 4 + 2];
    for (w = S[s].ws; w < S[s].we; w++) {
      W[w].x1 = loadWalls[v2];
      W[w].y1 = loadWalls[v2 + 1];
      W[w].x2 = loadWalls[v2 + 2];
      W[w].y2 = loadWalls[v2 + 3];
      W[w].c = loadWalls[v2 + 4];
      v2 += 5;
    }
  }
}

void drawEnv(Player *player, Window *window) {
  int s, w, wx[4], wy[4], wz[4]; // Wall coordinates
  
  // Sort sectors - Bubblesort
  for (s = 0; s < numSect-1; s++) {
    for (w = 0; w < numSect-s-1; w++) {
        if (S[w].d < S[w+1].d) {
          Sectors st = S[w]; S[w] = S[w+1]; S[w+1] = st;
        }
    }
  }
  // Draw sectors
  for (s = 0; s < numSect; s++) {
    S[s].d = 0;
    for (w = S[s].ws; w < S[s].we; w++) {
      float CS = cos(player->angle*M_PI/180), SN = sin(player->angle*M_PI/180); // Trigonometry values for player angle
      int x1 = W[w].x1 - player->x, y1 = W[w].y1 - player->y;
      int x2 = W[w].x2 - player->x, y2 = W[w].y2 - player->y;
      // Wall X, Y and Z positions
      wx[0] = x1*CS - y1*SN;
      wx[1] = x2*CS - y2*SN;
      wx[2] = wx[0];
      wx[3] = wx[1];

      wy[0] = x1*SN + y1*CS;
      wy[1] = x2*SN + y2*CS;
      wy[2] = wy[0];
      wy[3] = wy[1];

      wz[0] = S[s].z1-player->z+((player->look*wy[0])/32.0);
      wz[1] = S[s].z1-player->z+((player->look*wy[1])/32.0);
      wz[2] = wz[0] + S[s].z2;
      wz[3] = wz[1] + S[s].z2;
      S[s].d+= dist(0, 0, (wx[0]+wx[1])/2, (wy[0]+wy[1])/2);

      // Don't draw behind player
      if (wy[0] < 1 && wy[1] < 1) { continue; }

      // Clip walls
      if (wy[0] < 1) { 
        clipPlayer(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]);
        clipPlayer(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]);
      }
      if (wy[1] < 1) { 
        clipPlayer(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]);
        clipPlayer(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]);
      }

      // Screen positions
      wx[0] = wx[0] * 200 / wy[0] + window->width/2; wy[0] = wz[0] * 200 / wy[0] + window->height/2;
      wx[1] = wx[1] * 200 / wy[1] + window->width/2; wy[1] = wz[1] * 200 / wy[1] + window->height/2;
      wx[2] = wx[2] * 200 / wy[2] + window->width/2; wy[2] = wz[2] * 200 / wy[2] + window->height/2;
      wx[3] = wx[3] * 200 / wy[3] + window->width/2; wy[3] = wz[3] * 200 / wy[3] + window->height/2;

      // Set color and draw wall
      if (W[w].c == 0) { SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255); }
      if (W[w].c == 1) { SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, 255); }
      if (W[w].c == 2) { SDL_SetRenderDrawColor(window->renderer, 0, 255, 0, 255); }
      if (W[w].c == 3) { SDL_SetRenderDrawColor(window->renderer, 0, 0, 255, 255); }
      if (W[w].c == 4) { SDL_SetRenderDrawColor(window->renderer, 255, 255, 0, 255); }
      if (W[w].c == 5) { SDL_SetRenderDrawColor(window->renderer, 255, 0, 255, 255); }
      if (W[w].c == 6) { SDL_SetRenderDrawColor(window->renderer, 0, 255, 255, 255); }
      if (W[w].c == 7) { SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255); }
      drawWall(wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], window);

      int dx = x2-x1, dy = y2-y1;
      int d = dist(x1, y1, x2, y2);
      int a = dist(x1, y1, player->x, player->y);
      int b = dist(x2, y2, player->x, player->y);
      if (a < d && b < d) {
        S[s].d = d;
        S[s].x = (x1+x2)/2;
        S[s].y = (y1+y2)/2;
        S[s].z1 = 0;
        S[s].z2 = 0;
      }
    }
    S[s].d /= S[s].we - S[s].ws;
  }
 }

void drawWall(int x1, int x2, int b1, int b2, int t1, int t2, Window* window) {
  int x,y;
  int dyb = b2-b1;  // Y distance of bottom line
  int dyt = t2-t1;  // Y distance of top line
  int dx = x2-x1; if (dx == 0) { dx = 1; } // X distance
  int xs = x1; // X start holded
  
  // Clip X
  if (x1 < 1) { x1 = 1; }
  if (x2 < 1) { x2 = 1; }
  if (x1 > window->width-1) { x1 = window->width-1; }
  if (x2 > window->width-1) { x2 = window->width-1; }

  for (int x = x1; x < x2; x++) {
    int y1 = dyb * (x - xs + 0.5) / dx + b1; // Y bottom point
    int y2 = dyt * (x - xs + 0.5) / dx + t1; // Y top point
    
    // Clip Y
    if (y1 < 1) { y1 = 1; }
    if (y2 < 1) { y2 = 1; }
    if (y1 > window->height-1) { y1 = window->height-1; }
    if (y2 > window->height-1) { y2 = window->height-1; }

    for (y = y1; y < y2; y++) {
      SDL_RenderDrawPoint(window->renderer, x, y);
    }
  }
}

void clipPlayer(int* x1, int* y1, int* z1, int x2, int y2, int z2) {
  float da = *y1;
  float db = y2;
  float d = da-db; if (d == 0) { d = 1; }
  float s = da/(d);
  *x1 = *x1 + s*(x2-(*x1));
  *y1 = *y1 + s*(y2-(*y1)); if (*y1 == 0) { *y1 = 1; }
  *z1 = *z1 + s*(z2-(*z1));
}
