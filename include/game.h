#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

typedef struct
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} Game;

void create_game_instance();

Game *get_game_instance();

#endif