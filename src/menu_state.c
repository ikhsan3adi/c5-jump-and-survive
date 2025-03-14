#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "menu_state.h"
#include "level0_state.h"
#include "ui.h"

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

void drawFilledCircle(SDL_Renderer *renderer, int cx, int cy, int radius)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                SDL_RenderPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

void drawCapsuleButton(SDL_Renderer *renderer, SDL_FRect *rect, SDL_Color color)
{
    int radius = rect->h / 2;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Menggambar bagian tengah tombol (persegi panjang)
    SDL_FRect middle_rect = {rect->x + radius, rect->y, rect->w - (2 * radius), rect->h};
    SDL_RenderFillRect(renderer, &middle_rect);

    // Menggambar lingkaran kiri & kanan dengan fungsi terpisah
    drawFilledCircle(renderer, rect->x + radius, rect->y + radius, radius);
    drawFilledCircle(renderer, rect->x + rect->w - radius, rect->y + radius, radius);
}

void menu_init()
{
    SDL_Log("Menu State: Initialized");
}

void menu_handle_input(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        SDL_Log("Key Pressed: %d", event->key.key); // Debug log
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
                change_game_state(&level0_state);
            }
            else if (current_selection == MENU_EXIT)
            {
                SDL_Log("Exit Game Triggered!");
                menu_cleanup();
                SDL_Quit();
                exit(0);
            }
            break;
        case SDLK_ESCAPE: // Tombol ESC untuk keluar
            SDL_Log("Escape Key Pressed! Exiting Game...");
            menu_cleanup();
            SDL_Quit();
            exit(0);
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
            change_game_state(&level0_state);
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
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color bg_color = {50, 50, 150, 255};

    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);

    render_text(renderer, sixtyfourconvergence_font, "JUMP & SURVIVE", 90, 80, 1.4, white);
    SDL_Color start_color = (current_selection == MENU_START) ? yellow : white;
    SDL_Color exit_color = (current_selection == MENU_EXIT) ? yellow : white;

    SDL_Color green = {0, 128, 0, 255};
    drawCapsuleButton(renderer, &start_button, green);
    render_text(renderer, pixelify_font, "Start Game", start_button.x + 45, start_button.y + 5, 1, start_color);

    SDL_Color red = {200, 0, 0, 255};
    drawCapsuleButton(renderer, &exit_button, red);
    render_text(renderer, pixelify_font, "Exit Game", exit_button.x + 65, exit_button.y + 5, 1, exit_color);
    SDL_RenderPresent(renderer);
}

void menu_cleanup()
{
    SDL_Log("Menu State: Cleaned up");
}