#ifndef LEVEL_H
#define LEVEL_H

#include <SDL3/SDL.h>

#include "transform.h"

#define TILE_SIZE 32
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

// Tile Type
#define EMPTY 0
#define PLATFORM 1
#define OBSTACLE_1 2
#define OBSTACLE_2 3
#define SWITCH 4
#define COINS 5
#define TRAP 6
#define DESTRUCT 7
#define EXIT_GATE 9

extern int solid_tiles[];

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

bool is_solid(Transform *transform);

bool is_void(Transform *transform);

bool is_exit(Transform *transform);
#endif
