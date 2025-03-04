#ifndef LEVEL0_STATE_H
#define LEVEL0_STATE_H

#include "game_state.h"

extern GameState level0_state;

void level0_init();
void level0_handle_input(SDL_Event *);
void level0_update(double delta_time);
void level0_render(SDL_Renderer *);
void level0_cleanup();

#endif
