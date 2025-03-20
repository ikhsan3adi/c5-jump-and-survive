#ifndef PAUSED_STATE_H
#define PAUSED_STATE_H

#include "game_state.h"

extern GameState paused_state;

void paused_init();
void paused_handle_input(SDL_Event *event);
void paused_update(double delta_time);
void paused_render(SDL_Renderer *renderer);
void paused_cleanup();

#endif