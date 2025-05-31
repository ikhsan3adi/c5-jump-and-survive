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

extern Switch *current_switches;
extern Switch_Obstacles *current_switch_obstacles;
extern int current_switches_count;
extern int current_switch_obstacles_count;
extern short current_level_map[MAP_HEIGHT][MAP_WIDTH];

// load all levels from directory
void load_levels(const char *dir);

/**
 * Build linked list dari array level
 * @param head pointer ke pointer LevelNode untuk menyimpan head dari linked list
 * @param level array of 'pointer LevelNode' yang akan diubah menjadi linked list
 * @param count jumlah elemen dalam array `levels`
 */
void build_level_list_from_array(LevelNode **head, LevelNode *levels[], int count);

// set current_level dengan level node yang mempunyai name
void goto_level_by_name(LevelNode *head, const char *name);

// set current_level menjadi current_level->next
void goto_next_level();

// set current_level menjadi current_level->prev
void goto_prev_level();

void change_level();

void render_level(SDL_Renderer *renderer);

// bersihkan semua level, dipanggil saat game selesai/exit
void clear_level();

#endif
