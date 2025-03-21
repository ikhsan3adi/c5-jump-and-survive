#include "paused_state.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "game_state.h"
#include "stage0_state.h"
#include "ui.h"

typedef enum
{
    PAUSED_RESUME,
    PAUSED_EXIT,
    PAUSED_COUNT
} PausedOption;

static PausedOption current_selection = PAUSED_RESUME;
static SDL_FRect resume_button = {330.0f, 300.0f, 300.0f, 60.0f};
static SDL_FRect exit_button = {330.0f, 400.0f, 300.0f, 60.0f};

GameState paused_state = {
    .init = paused_init,
    .handle_input = paused_handle_input,
    .update = paused_update,
    .render = paused_render,
    .cleanup = paused_cleanup,
};

void paused_init()
{
    SDL_Log("Paused State: Initialized");
}

void paused_handle_input(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        SDL_Log("Key Pressed: %d", event->key.key);
        switch (event->key.key)
        {
        case SDLK_DOWN:
        case SDLK_S:
            current_selection = (current_selection + 1) % PAUSED_COUNT;
            break;
        case SDLK_UP:
        case SDLK_W:
            current_selection = (current_selection - 1 + PAUSED_COUNT) % PAUSED_COUNT;
            break;
        case SDLK_RETURN:
            if (current_selection == PAUSED_RESUME)
            {
                SDL_Log("Resume Game Triggered!");
                change_game_state(&stage0_state);
            }
            else if (current_selection == PAUSED_EXIT)
            {
                SDL_Log("Exit Game Triggered!");
                paused_cleanup();
                SDL_Quit();
                exit(0);
            }
            break;
        case SDLK_ESCAPE:
            SDL_Log("Escape Key Pressed! Resuming Game...");
            change_game_state(&stage0_state);
            break;
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_MOTION)
    {
        int x = event->motion.x;
        int y = event->motion.y;

        if (x >= resume_button.x && x <= resume_button.x + resume_button.w &&
            y >= resume_button.y && y <= resume_button.y + resume_button.h)
        {
            current_selection = PAUSED_RESUME;
        }
        else if (x >= exit_button.x && x <= exit_button.x + exit_button.w &&
                 y >= exit_button.y && y <= exit_button.y + exit_button.h)
        {
            current_selection = PAUSED_EXIT;
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        int x = event->button.x;
        int y = event->button.y;
        if (x >= resume_button.x && x <= resume_button.x + resume_button.w &&
            y >= resume_button.y && y <= resume_button.y + resume_button.h)
        {
            SDL_Log("Resume Game Clicked!");
            change_game_state(&stage0_state);
        }
        else if (x >= exit_button.x && x <= exit_button.x + exit_button.w &&
                 y >= exit_button.y && y <= exit_button.y + exit_button.h)
        {
            SDL_Log("Exit Game Clicked!");
            paused_cleanup();
            SDL_Quit();
            exit(0);
        }
    }
}

void paused_update(double delta_time) {}

void paused_render(SDL_Renderer *renderer)
{
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color bg_color = {50, 50, 50, 255}; // Background lebih gelap

    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);

    render_text(renderer, sixtyfourconvergence_font, "PAUSED", 70, 40, 2.7, white);
    SDL_Color resume_color = (current_selection == PAUSED_RESUME) ? yellow : white;
    SDL_Color exit_color = (current_selection == PAUSED_EXIT) ? yellow : white;

    SDL_Color brown_orange = {175, 90, 40, 255}; // Warna brown_orange
    SDL_SetRenderDrawColor(renderer, brown_orange.r, brown_orange.g, brown_orange.b, brown_orange.a);
    SDL_RenderFillRect(renderer, &resume_button);
    render_text(renderer, pixelify_font, "Resume", resume_button.x + 90, resume_button.y + 5, 1, resume_color);

    SDL_RenderFillRect(renderer, &exit_button);
    render_text(renderer, pixelify_font, "Exit", exit_button.x + 115, exit_button.y + 5, 1, exit_color);

    SDL_RenderPresent(renderer);
}

void paused_cleanup()
{
    SDL_Log("Paused State: Cleaned up");
}