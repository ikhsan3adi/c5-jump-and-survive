#include "menu_state.h"
#include "game.h"
#include <SDL3/SDL.h>

// Definisi state menu
GameState menu_state = {
    .init = menu_init,
    .handle_input = menu_handle_input,
    .update = menu_update,
    .render = menu_render,
    .cleanup = menu_cleanup
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
    }
    else if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.keysym.sym == SDLK_RETURN)
        {
            SDL_Log("Start Game Triggered!");
            // change_state(&stage1_state); // Jika ada stage1_state
        }
    }
}

void menu_update()
{
    // Hapus logging yang terlalu sering
}

void menu_render()
{
    Game *game = get_game_instance();
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    SDL_FRect play_button = {200.0f, 150.0f, 200.0f, 50.0f};
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(game->renderer, &play_button);

    // Menampilkan teks menu menggunakan SDL_RenderDebugText
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(game->renderer, 250, 170, "JUMP & SURVIVE");
    SDL_RenderDebugText(game->renderer, 260, 190, "Press ENTER to Start");

    SDL_RenderPresent(game->renderer);
}

void menu_cleanup()
{
    SDL_Log("Menu State: Cleaned up");
}