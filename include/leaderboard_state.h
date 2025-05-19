#ifndef LEADERBOARD_STATE_H
#define LEADERBOARD_STATE_H

#include "game_state.h"

extern GameState leaderboard_state;

// Deklarasi fungsi untuk lifecycle menu state
void leaderboard_init();
void leaderboard_handle_input(SDL_Event *);
void leaderboard_update(double);
void leaderboard_render(SDL_Renderer *);
void leaderboard_cleanup();

#endif