#ifndef STAGE0_STATE_H
#define STAGE0_STATE_H

#include "game_state.h"

extern GameState stage0_state;

void stage0_init();
void stage0_handle_input(SDL_Event *);
void stage0_update(double delta_time);
void stage0_render(SDL_Renderer *);
void stage0_cleanup();

#endif
