#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640
#define TILE_SIZE 32

typedef struct
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool is_physics_paused; // untuk memberhentikan update physics (set delta_time ke 0)
} Game;

// set metadata, initialize SDL
void initialize(const char *appname, const char *appversion, const char *appidentifier);

// create global Game singleton
void create_game_instance(const char *title, int width, int height);

// get `Game` singleton instance
// `create_game_instance()` must be called first at least once
Game *get_game_instance();

// bekukan physics untuk 1 frame
// digunakan untuk transisi level agar delta_time tidak membengkak
// yang dapat menyebabkan gravitasi player menjadi terlalu besar
void skip_physics_frame();

// resume physics updates
void resume_physics();

#endif