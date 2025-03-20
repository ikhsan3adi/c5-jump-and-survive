#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "game_state.h"

extern GameState gameover_state;

void game_over_init();
void game_over_handle_input(SDL_Event *event);
void game_over_update(double delta_time);
void game_over_render(SDL_Renderer *renderer);
void game_over_cleanup();

#endif