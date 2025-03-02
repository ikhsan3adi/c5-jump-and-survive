#include <SDL3/SDL.h>

#include "menu_state.h"
// #include "level1_state.h"

// Definisi state menu
GameState menu_state = {
    .init = menu_init,
    .handle_input = menu_handle_input,
    .update = menu_update,
    .render = menu_render,
    .cleanup = menu_cleanup,
};

void menu_init()
{
    SDL_Log("Menu State: Initialized");
}

void menu_handle_input(SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        SDL_Log("Received Quit Event. Exiting Game...");
        change_game_state(NULL);
        exit(0);
    }
    else if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.key == SDLK_RETURN)
        {
            SDL_Log("Start Game Triggered!");
            // change_state(&level1_state);  // pindah ke level1_state
        }
    }
}

void menu_update() {}

void menu_render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Menampilkan teks menu menggunakan SDL_RenderDebugText
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 235, 190, "JUMP & SURVIVE");
    SDL_RenderDebugText(renderer, 215, 210, "Press ENTER to Start");

    SDL_RenderPresent(renderer);
}

void menu_cleanup()
{
    SDL_Log("Menu State: Cleaned up");
}