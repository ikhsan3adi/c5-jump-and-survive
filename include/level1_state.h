#ifndef LEVEL1_STATE_H
#define LEVEL1_STATE_H

#include "game_state.h"

extern GameState level1_state;

void level1_init();
void level1_handle_input(SDL_Event *);
void level1_update(double delta_time);
void level1_render(SDL_Renderer *);
void level1_cleanup();

#endif
