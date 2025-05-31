#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <SDL3/SDL_image.h>

#include "menu_state.h"
#include "stage0_state.h"
#include "leaderboard.h"
#include "leaderboard_state.h"
#include "ui.h"
#include "player.h"
#include "level.h"
#include "SFX.h"
#include "game.h"

// Enum untuk pilihan menu
typedef enum
{
    MENU_START,
    MENU_LEADERBOARD,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

// Variabel untuk melacak pilihan menu
static MenuOption current_selection = MENU_START;
static SDL_FRect start_button = {(SCREEN_WIDTH / 2), 320, 300, 60};
static SDL_FRect leaderboard_button = {(SCREEN_WIDTH / 2), 390, 300, 60};
static SDL_FRect exit_button = {(SCREEN_WIDTH / 2), 460, 300, 60};

// Definisi state menu
GameState menu_state = {
    .init = menu_init,
    .handle_input = menu_handle_input,
    .update = menu_update,
    .render = menu_render,
    .cleanup = menu_cleanup,
};

SDL_Texture *bg_texture = NULL;

void menu_init()
{
    SDL_Log("Menu State: Initialized");
    play_music(menu_bgm, INT32_MAX);

    player = create_player((Transform){0, 0, TILE_SIZE, TILE_SIZE}, 0, 0, 0);

    SDL_Renderer *renderer = get_game_instance()->renderer;
    bg_texture = IMG_LoadTexture(renderer, "assets/images/bgmenu.png");

    change_level();
    reinitiate_player(player, current_level->player_spawn);
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
            else if (current_selection == MENU_LEADERBOARD)
            {
                SDL_Log("Leaderboard Opened!");
                change_game_state(&leaderboard_state);
            }
            else if (current_selection == MENU_EXIT)
            {
                SDL_Log("Exit Game Triggered!");
                menu_cleanup();
                exit_game(EXIT_SUCCESS);
            }
            break;
        case SDLK_ESCAPE:
            SDL_Log("Escape Key Pressed! Exiting Game...");
            menu_cleanup();
            exit_game(EXIT_SUCCESS);
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
        else if (x >= leaderboard_button.x && x <= leaderboard_button.x + leaderboard_button.w &&
                 y >= leaderboard_button.y && y <= leaderboard_button.y + leaderboard_button.h)
        {
            current_selection = MENU_LEADERBOARD;
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
        else if (x >= leaderboard_button.x && x <= leaderboard_button.x + leaderboard_button.w &&
                 y >= leaderboard_button.y && y <= leaderboard_button.y + leaderboard_button.h)
        {
            SDL_Log("Leaderboard Clicked!");
            change_game_state(&leaderboard_state);
        }
        else if (x >= exit_button.x && x <= exit_button.x + exit_button.w &&
                 y >= exit_button.y && y <= exit_button.y + exit_button.h)
        {
            SDL_Log("Exit Game Clicked!");
            menu_cleanup();
            exit_game(EXIT_SUCCESS);
        }
    }
}

void menu_update(double delta_time) {}

void menu_render(SDL_Renderer *renderer)
{
    SDL_Color text_color = {10, 55, 58, 255};
    SDL_Color selected_text_color = {255, 255, 255, 255};
    SDL_Color btn_color = {140, 104, 26, 255};
    SDL_Color selected_btn_color = {180, 130, 40, 255};

    // Warna tombol diperbaiki agar sesuai dengan current_selection
    SDL_Color start_button_color = (current_selection == MENU_START) ? selected_btn_color : btn_color;
    SDL_Color leaderboard_button_color = (current_selection == MENU_LEADERBOARD) ? selected_btn_color : btn_color;
    SDL_Color exit_button_color = (current_selection == MENU_EXIT) ? selected_btn_color : btn_color;

    SDL_Color start_text_color = (current_selection == MENU_START) ? selected_text_color : text_color;
    SDL_Color leaderboard_text_color = (current_selection == MENU_LEADERBOARD) ? selected_text_color : text_color;
    SDL_Color exit_text_color = (current_selection == MENU_EXIT) ? selected_text_color : text_color;

    SDL_RenderClear(renderer);

    //  background
    SDL_RenderTexture(renderer, bg_texture, NULL, NULL);

    // Start button
    SDL_SetRenderDrawColor(renderer, start_button_color.r, start_button_color.g, start_button_color.b, 255);
    SDL_RenderFillRect(renderer, &start_button);
    render_text(renderer, pixelify_font, "Start Game",
                start_button.x + start_button.w / 2 - 105,
                start_button.y + start_button.h / 2 - 20,
                1, start_text_color);

    // leaderborad button
    SDL_SetRenderDrawColor(renderer, leaderboard_button_color.r, leaderboard_button_color.g, leaderboard_button_color.b, 255);
    SDL_RenderFillRect(renderer, &leaderboard_button);
    render_text(renderer, pixelify_font, "Leaderboard",
                leaderboard_button.x + leaderboard_button.w / 2 - 115,
                leaderboard_button.y + leaderboard_button.h / 2 - 20,
                1, leaderboard_text_color);

    // Exit button
    SDL_SetRenderDrawColor(renderer, exit_button_color.r, exit_button_color.g, exit_button_color.b, 255);
    SDL_RenderFillRect(renderer, &exit_button);
    render_text(renderer, pixelify_font, "Exit Game",
                exit_button.x + exit_button.w / 2 - 80,
                exit_button.y + exit_button.h / 2 - 20,
                1, exit_text_color);
}

void menu_cleanup()
{
    SDL_Log("Menu State: Cleaned up");
    stop_music();
}