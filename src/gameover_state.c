#include "gameover_state.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "stage0_state.h"
#include "ui.h"
#include "SFX.h"

typedef enum
{
    GAMEOVER_RETRY,
    GAMEOVER_EXIT,
    GAMEOVER_COUNT
} GameOverOption;

static GameOverOption current_selection = GAMEOVER_RETRY;
static SDL_FRect retry_button = {330.0f, 300.0f, 300.0f, 60.0f};
static SDL_FRect exit_button = {330.0f, 400.0f, 300.0f, 60.0f};

GameState gameover_state = {
    .init = game_over_init,
    .handle_input = game_over_handle_input,
    .update = game_over_update,
    .render = game_over_render,
    .cleanup = game_over_cleanup,
};

void game_over_init()
{
    SDL_Log("Game Over State: Initialized");
    play_sound (dead_sfx,1 ,0);
}

void game_over_handle_input(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        SDL_Log("Key Pressed: %d", event->key.key);
        switch (event->key.key)
        {
        case SDLK_DOWN:
        case SDLK_S:
            current_selection = (current_selection + 1) % GAMEOVER_COUNT;
            break;
        case SDLK_UP:
        case SDLK_W:
            current_selection = (current_selection - 1 + GAMEOVER_COUNT) % GAMEOVER_COUNT;
            break;
        case SDLK_RETURN:
            if (current_selection == GAMEOVER_RETRY)
            {
                SDL_Log("Retry Game Triggered!");
                change_game_state(&stage0_state);
            }
            else if (current_selection == GAMEOVER_EXIT)
            {
                SDL_Log("Exit Game Triggered!");
                game_over_cleanup();
                SDL_Quit();
                exit(0);
            }
            break;
        case SDLK_ESCAPE:
            SDL_Log("Escape Key Pressed! Exiting Game...");
            game_over_cleanup();
            SDL_Quit();
            exit(0);
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_MOTION)
    {
        int x = event->motion.x;
        int y = event->motion.y;

        if (x >= retry_button.x && x <= retry_button.x + retry_button.w &&
            y >= retry_button.y && y <= retry_button.y + retry_button.h)
        {
            current_selection = GAMEOVER_RETRY;
        }
        else if (x >= exit_button.x && x <= exit_button.x + exit_button.w &&
                 y >= exit_button.y && y <= exit_button.y + exit_button.h)
        {
            current_selection = GAMEOVER_EXIT;
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        int x = event->button.x;
        int y = event->button.y;
        if (x >= retry_button.x && x <= retry_button.x + retry_button.w &&
            y >= retry_button.y && y <= retry_button.y + retry_button.h)
        {
            SDL_Log("Retry Game Clicked!");
            change_game_state(&stage0_state);
        }
        else if (x >= exit_button.x && x <= exit_button.x + exit_button.w &&
                 y >= exit_button.y && y <= exit_button.y + exit_button.h)
        {
            SDL_Log("Exit Game Clicked!");
            game_over_cleanup();
            SDL_Quit();
            exit(0);
        }
    }
}

void game_over_update(double delta_time) {}

void game_over_render(SDL_Renderer *renderer)
{
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color bg_color = {100, 0, 0, 255}; // Background lebih gelap

    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);

    render_text(renderer, sixtyfourconvergence_font, "GAME OVER", 80, 60, 2, white);
    SDL_Color retry_color = (current_selection == GAMEOVER_RETRY) ? yellow : white;
    SDL_Color exit_color = (current_selection == GAMEOVER_EXIT) ? yellow : white;

    SDL_Color brown_orange = {175, 90, 40, 255}; // Warna brown_orange
    SDL_SetRenderDrawColor(renderer, brown_orange.r, brown_orange.g, brown_orange.b, brown_orange.a);
    SDL_RenderFillRect(renderer, &retry_button);
    render_text(renderer, pixelify_font, "Retry", retry_button.x + 100, retry_button.y + 5, 1, retry_color);

    SDL_RenderFillRect(renderer, &exit_button);
    render_text(renderer, pixelify_font, "Exit", exit_button.x + 115, exit_button.y + 5, 1, exit_color);

    SDL_RenderPresent(renderer);
}

void game_over_cleanup()
{
    SDL_Log("Game Over State: Cleaned up");
}
