
#include <SDL3/SDL.h>

#include "menu_state.h"
#include "level1_state.h"

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
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.key == SDLK_RETURN)
        {
            SDL_Log("Start Game Triggered!");
            change_game_state(&level1_state); // pindah ke level1_state
        }
    }
}

void menu_update(double delta_time) {}

void menu_render(SDL_Renderer *renderer)
{
    // atur background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Menampilkan teks menu menggunakan SDL_RenderDebugText

    // atur warna
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_SetRenderScale(renderer, 1.7f, 1.7f); // Perbesar text dengan set render scale
    SDL_RenderDebugText(renderer, 120, 85, "JUMP & SURVIVE");

    SDL_SetRenderScale(renderer, 1.5f, 1.5f); // Perbesar text dengan set render scale
    SDL_RenderDebugText(renderer, 120, 150, "Press ENTER to Start");

    SDL_SetRenderScale(renderer, 1.0f, 1.0f); // ubah render scale seperti semula

    // tampilkan ke layar
    SDL_RenderPresent(renderer);
}

void menu_cleanup()
{
    SDL_Log("Menu State: Cleaned up");
}
