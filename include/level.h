#ifndef LEVEL_H
#define LEVEL_H

#include <SDL3/SDL.h>

#include "transform.h"

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

extern short (*current_level_map)[MAP_WIDTH];

void change_level(int level);

void render_level(SDL_Renderer *renderer);

#endif
