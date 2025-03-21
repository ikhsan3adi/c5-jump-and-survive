#ifndef STAGE1_STATE_H
#define STAGE1_STATE_H

#include "game_state.h"

extern GameState stage1_state;

void stage1_init();
void stage1_handle_input(SDL_Event *);
void stage1_update(double delta_time);
void stage1_render(SDL_Renderer *);
void stage1_cleanup();

#endif
