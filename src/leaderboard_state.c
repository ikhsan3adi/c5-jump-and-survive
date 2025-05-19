#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <stdio.h>
#include "leaderboard_state.h"
#include "menu_state.h"
#include "ui.h"
#include "leaderboard.h"


const char *LEADERBOARD_FILE = "leaderboard.dat";

GameState leaderboard_state = {
    .init = leaderboard_init,
    .handle_input = leaderboard_handle_input,
    .update = leaderboard_update,
    .render = leaderboard_render,
    .cleanup = leaderboard_cleanup};

void leaderboard_init()
{
    SDL_Log("Leaderboard State: Initialized");
    if (leaderboard_head)
        free_leaderboard(leaderboard_head); // Hindari memory leak
    leaderboard_head = load_leaderboard(LEADERBOARD_FILE);
}

void leaderboard_handle_input(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN &&
        (event->key.key == SDLK_ESCAPE || event->key.key == SDLK_RETURN))
    {
        SDL_Log("Returning to Menu...");
        change_game_state(&menu_state);
    }
}

void leaderboard_update(double delta_time) {}

void leaderboard_render(SDL_Renderer *renderer)
{
    show_leaderboard_ui(renderer, leaderboard_head);
}
void leaderboard_cleanup()
{
    SDL_Log("Leaderboard State: Cleaned up");
    save_leaderboard(LEADERBOARD_FILE, leaderboard_head);
    free_leaderboard(leaderboard_head);
    leaderboard_head = NULL;
}