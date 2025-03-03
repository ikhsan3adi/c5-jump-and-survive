#ifndef LEVEL1_STATE_H
#define LEVEL1_STATE_H

#include "game_state.h"

extern GameState level1_state;

void level1_init();
void level1_handle_input(SDL_Event* event);
void level1_update();
void level1_render(SDL_Renderer *renderer);
void level1_cleanup();

#endif
