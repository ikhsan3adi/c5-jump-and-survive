#ifndef LEVEL_H
#define LEVEL_H

#include <SDL3/SDL.h>

#include "transform.h"
#include "obstacles.h"

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

typedef struct LevelNode LevelNode;

struct LevelNode
{
  char name[32];
  char prev_name[32]; // name level sebelumnya
  char next_name[32]; // name level selanjutnya

  Vector player_spawn;

  SDL_Color foreground_color;
  SDL_Color background_color;

  char bg_image[32];
  char bg_music[32];

  Switch *switches;
  Switch_Obstacles *switch_obstacles;
  Saw *saws;

  int switches_count;
  int switch_obstacles_count;
  int saws_count;

  short map[MAP_HEIGHT][MAP_WIDTH];

  LevelNode *prev;
  LevelNode *next;
};

//! pointer level node paling depan, tidak boleh berubah
extern LevelNode *level_head;

//! pointer level yang sedang dimuat, boleh berubah
extern LevelNode *current_level;

// load all levels from directory
void load_levels(const char *dir);

// hapus node awal
void insert_last(LevelNode **head, LevelNode *level);

void insert_level(LevelNode **head, LevelNode *level);

// hapus node terakhir
void delete_last(LevelNode **head);

// set current_level dengan level node yang mempunyai name
void goto_level_by_name(LevelNode *head, const char *name);

// set current_level menjadi current_level->next
void goto_next_level();

// set current_level menjadi current_level->prev
void goto_prev_level();

// bersihkan semua level
void clear_level(LevelNode *head);

// extern short level0_map[MAP_HEIGHT][MAP_WIDTH];
// extern short level1_map[MAP_HEIGHT][MAP_WIDTH];
// extern short level2_map[MAP_HEIGHT][MAP_WIDTH];
// extern short level3_map[MAP_HEIGHT][MAP_WIDTH];
// extern short level4_map[MAP_HEIGHT][MAP_WIDTH];
// extern short level5_map[MAP_HEIGHT][MAP_WIDTH];

// extern int current_level;
// extern Switch buttonL1;
// extern Switch buttonL51;
// extern Switch buttonL52;
// extern Switch buttonL61;
// extern Switch buttonL62;
// extern Switch_Obstacles buttonL7;
// extern Switch_Obstacles buttonL81;
// extern Switch buttonL82;
// extern Switch_Obstacles buttonL91;
// extern Switch_Obstacles buttonL92;
// extern Switch_Obstacles buttonL101;
// extern Switch buttonL102;
// extern Switch_Obstacles buttonL103;

extern short current_level_map[MAP_HEIGHT][MAP_WIDTH];
extern Switch *current_switches;
extern Switch_Obstacles *current_switch_obstacles;
extern int current_switches_count;
extern int current_switch_obstacles_count;

void change_level();

void render_level(SDL_Renderer *renderer);

#endif
