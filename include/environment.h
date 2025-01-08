#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#define numSect 4
#define numWall 16

#include "player.h"

typedef struct win Window;

typedef struct wall {
  int x1, y1;     // Bottom line
  int x2, y2;     // Top line
  int c;          // Color
} Walls; Walls W[30];

typedef struct sec {
  int ws, we;     // Wall start and end
  int z1, z2;     // Height start and end
  int x, y;       // Center of position
  int d;          // Distance
} Sectors; Sectors S[30];

extern int loadSectors[];
extern int loadWalls[];

void drawEnv(Player* player, Window* window);
void drawWall(int x1, int x2, int b1, int b2, int t1, int t2, Window* window);
void clipPlayer(int* x1, int* y1, int* z1, int x2, int y2, int z2);
void initSectors();
int dist(int x1, int y1, int x2, int y2);

#endif
