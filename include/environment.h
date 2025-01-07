#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "player.h"

typedef struct win Window;

void drawEnv(Player* player, Window* window);
void drawWall(int x1, int x2, int b1, int b2, Window* window);

#endif
