#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

#include "menu_state.h"
#include "stage0_state.h"
#include "ui.h"
#include "player.h"
#include "level.h"
#include "SFX.h"
#include "game.h"

// Enum untuk pilihan menu
typedef enum
{
    MENU_START,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

// Variabel untuk melacak pilihan menu
static MenuOption current_selection = MENU_START;
static SDL_FRect start_button = {330.0f, 300.0f, 300.0f, 60.0f};
static SDL_FRect exit_button = {330.0f, 400.0f, 300.0f, 60.0f};

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
    play_music(menu_bgm, INT32_MAX);

    player = create_player((Transform){120, 416, 32, 32}, 0, 0, 0);

    change_level();
}

void menu_handle_input(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        SDL_Log("Key Pressed: %d (%s)", event->key.key, SDL_GetKeyName(event->key.key));
        switch (event->key.key)
        {
        case SDLK_DOWN:
        case SDLK_S:
            current_selection = (current_selection + 1) % MENU_COUNT;
            break;
        case SDLK_UP:
        case SDLK_W:
            current_selection = (current_selection - 1 + MENU_COUNT) % MENU_COUNT;
            break;
        case SDLK_RETURN:
            if (current_selection == MENU_START)
            {
                SDL_Log("Start Game Triggered!");
                change_game_state(&stage0_state);
            }
            else if (current_selection == MENU_EXIT)
            {
                SDL_Log("Exit Game Triggered!");
                menu_cleanup();
                SDL_Quit();
                exit(0);
            }
            break;
        case SDLK_ESCAPE:
            SDL_Log("Escape Key Pressed! Exiting Game...");
            menu_cleanup();
            SDL_Quit();
            exit(0);
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_MOTION)
    {
        int x = event->motion.x;
        int y = event->motion.y;

        if (x >= start_button.x && x <= start_button.x + start_button.w &&
            y >= start_button.y && y <= start_button.y + start_button.h)
        {
            current_selection = MENU_START;
        }
        else if (x >= exit_button.x && x <= exit_button.x + exit_button.w &&
                 y >= exit_button.y && y <= exit_button.y + exit_button.h)
        {
            current_selection = MENU_EXIT;
        }
    }
    else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        int x = event->button.x;
        int y = event->button.y;
        if (x >= start_button.x && x <= start_button.x + start_button.w &&
            y >= start_button.y && y <= start_button.y + start_button.h)
        {
            SDL_Log("Start Game Clicked!");
            change_game_state(&stage0_state);
        }
        else if (x >= exit_button.x && x <= exit_button.x + exit_button.w &&
                 y >= exit_button.y && y <= exit_button.y + exit_button.h)
        {
            SDL_Log("Exit Game Clicked!");
            menu_cleanup();
            SDL_Quit();
            exit(0);
        }
    }
}

void menu_update(double delta_time) {}

void menu_render(SDL_Renderer *renderer)
{
    SDL_Color bg_color = {124, 162, 142, 255};
    SDL_Color title_text_color = {124, 162, 142, 255};
    SDL_Color text_color = {10, 55, 58, 255};
    SDL_Color selected_text_color = {255, 255, 255, 255};
    SDL_Color btn_color = {124, 162, 142, 255};
    SDL_Color selected_btn_color = {124, 162, 142, 255};

    // Warna tombol diperbaiki agar sesuai dengan current_selection
    SDL_Color start_button_color = (current_selection == MENU_START) ? selected_btn_color : btn_color;
    SDL_Color exit_button_color = (current_selection == MENU_EXIT) ? selected_btn_color : btn_color;

    SDL_Color start_text_color = (current_selection == MENU_START) ? selected_text_color : text_color;
    SDL_Color exit_text_color = (current_selection == MENU_EXIT) ? selected_text_color : text_color;

    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);

    // level as background
    render_level(renderer);
    render_player(renderer, player);

    // overlay
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 120);
    SDL_RenderFillRect(renderer, &(SDL_FRect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

    render_text(renderer, sixtyfourconvergence_font, "JUMP & SURVIVE", 100, 80, 1.4, title_text_color);

    // Start button
    SDL_SetRenderDrawColor(renderer, start_button_color.r, start_button_color.g, start_button_color.b, 255);
    SDL_RenderFillRect(renderer, &start_button);
    render_text(renderer, pixelify_font, "Start Game", start_button.x + 45, start_button.y + 5, 1, start_text_color);

    // Exit button
    SDL_SetRenderDrawColor(renderer, exit_button_color.r, exit_button_color.g, exit_button_color.b, 255);
    SDL_RenderFillRect(renderer, &exit_button);
    render_text(renderer, pixelify_font, "Exit Game", exit_button.x + 65, exit_button.y + 5, 1, exit_text_color);
}

void menu_cleanup()
{
    SDL_Log("Menu State: Cleaned up");
    stop_music();
}