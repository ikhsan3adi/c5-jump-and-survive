#include <stdio.h>
#include <SDL3/SDL.h>

#include "level0_state.h"
#include "game.h"
#include "game_state.h"

// Definisi state
GameState level0_state = {
    .init = level0_init,
    .handle_input = level0_handle_input,
    .update = level0_update,
    .render = level0_render,
    .cleanup = level0_cleanup,
};

void level0_init()
{
  SDL_Log("Level 0 State: Initialized");
}

void level0_handle_input(SDL_Event *event) {}

void level0_update() {}

void level0_render(SDL_Renderer *renderer)
{
  SDL_RenderPresent(renderer);
}

void level0_cleanup()
{
  SDL_Log("Level 0 State: Cleaned up");
}