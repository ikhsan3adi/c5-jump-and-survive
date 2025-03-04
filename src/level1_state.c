#include <stdio.h>
#include <SDL3/SDL.h>

#include "level1_state.h"
#include "game.h"
#include "game_state.h"

// Definisi state
GameState level1_state = {
    .init = level1_init,
    .handle_input = level1_handle_input,
    .update = level1_update,
    .render = level1_render,
    .cleanup = level1_cleanup,
};

void level1_init() {}

void level1_handle_input(SDL_Event *event) {}

void level1_update(double delta_time) {}

void level1_render(SDL_Renderer *renderer) {}

void level1_cleanup() {}