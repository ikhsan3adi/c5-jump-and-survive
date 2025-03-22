#ifndef LEVEL_H
#define LEVEL_H

#include <SDL3/SDL.h>

#include "transform.h"
#include "obstacle.h"

#define TILE_SIZE 32
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

extern short level0_map[MAP_HEIGHT][MAP_WIDTH];
extern short level1_map[MAP_HEIGHT][MAP_WIDTH];
extern short level2_map[MAP_HEIGHT][MAP_WIDTH];
extern short level3_map[MAP_HEIGHT][MAP_WIDTH];
extern short level4_map[MAP_HEIGHT][MAP_WIDTH];
extern short level5_map[MAP_HEIGHT][MAP_WIDTH];

extern int current_level;
extern Switch buttonL1;
extern Switch buttonL51;
extern Switch buttonL52;
extern Switch buttonL61;
extern Switch buttonL62;
extern Switch_Obstacles buttonL7;
extern Switch_Obstacles buttonL81;
extern Switch buttonL82;
extern Switch_Obstacles buttonL91;
extern Switch_Obstacles buttonL92;
extern Switch_Obstacles buttonL101;
extern Switch buttonL102;
extern Switch_Obstacles buttonL103;

extern short current_level_map[MAP_HEIGHT][MAP_WIDTH];

void change_level(int level);

void render_level(SDL_Renderer *renderer);

#endif
