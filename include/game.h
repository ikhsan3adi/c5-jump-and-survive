#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

typedef struct
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} Game;

// set metadata, initialize SDL
void initialize(const char *appname, const char *appversion, const char *appidentifier);

// create global Game singleton
void create_game_instance(const char *title, int width, int height);

// get `Game` singleton instance
// `create_game_instance()` must be called first at least once
Game *get_game_instance();

#endif