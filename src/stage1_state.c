#include <stdio.h>
#include <SDL3/SDL.h>

#include "stage1_state.h"
#include "game.h"
#include "game_state.h"
#include "player.h"


// Definisi state
GameState stage1_state = {
    .init = stage1_init,
    .handle_input = stage1_handle_input,
    .update = stage1_update,
    .render = stage1_render,
    .cleanup = stage1_cleanup,
};

void stage1_init() {}

void stage1_handle_input(SDL_Event *event) {}

void stage1_update(double delta_time) {}

void stage1_render(SDL_Renderer *renderer) {}

void stage1_cleanup() {}