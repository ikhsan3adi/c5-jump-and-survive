#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "menu_state.h"
#include "level0_state.h"

// Enum untuk pilihan menu
typedef enum {
    MENU_START,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

// Variabel untuk melacak pilihan menu
static MenuOption current_selection = MENU_START;
static TTF_Font *title_font = NULL;
static TTF_Font *menu_font = NULL;
static SDL_FRect start_button = {120.0f, 150.0f, 200.0f, 50.0f};
static SDL_FRect exit_button = {120.0f, 220.0f, 200.0f, 50.0f};

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
    
    if (TTF_Init() < 0)
    {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        exit(1);
    }
    
    title_font = TTF_OpenFont("assets/SixtyfourConvergence-Regular.ttf", 48);
    menu_font = TTF_OpenFont("assets/PixelifySans-Regular.ttf", 36);
    
    if (!title_font || !menu_font)
    {
        SDL_Log("Failed to load fonts: %s", SDL_GetError());
        exit(1);
    }
}

void menu_handle_input(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
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
                    change_game_state(&level0_state); // Pindah ke level 0
                }
                else if (current_selection == MENU_EXIT)
                {
                    SDL_Log("Exit Game Triggered!");
                    SDL_Quit();
                    exit(0);
                }
                break;
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
            SDL_Quit();
            exit(0);
        }
    }
}

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, strlen(text), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FRect dest_rect = {x, y, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, NULL, &dest_rect);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void menu_update(double delta_time) {}

void menu_render(SDL_Renderer *renderer)
{
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color bg_color = {50, 50, 150, 255};

    // Atur background
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);

    // Tampilkan teks judul
    render_text(renderer, title_font, "JUMP & SURVIVE", 100, 50, white);

    // Tombol Start
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &start_button);
    SDL_Color start_color = (current_selection == MENU_START) ? yellow : white;
    render_text(renderer, menu_font, "Start Game", start_button.x + 30, start_button.y + 10, start_color);

    // Tombol Exit
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &exit_button);
    SDL_Color exit_color = (current_selection == MENU_EXIT) ? yellow : white;
    render_text(renderer, menu_font, "Exit Game", exit_button.x + 30, exit_button.y + 10, exit_color);
    
    // Tampilkan ke layar
    SDL_RenderPresent(renderer);
}

void menu_cleanup()
{
    if (title_font) TTF_CloseFont(title_font);
    if (menu_font) TTF_CloseFont(menu_font);
    TTF_Quit();
    SDL_Log("Menu State: Cleaned up");
}
