#include <stdio.h>

#include "ui.h"
#include "menu_state.h"

TTF_Font *sixtyfourconvergence_font;
TTF_Font *pixelify_font;

SDL_Surface *text_surface = NULL;
SDL_Texture *text_texture = NULL;

void load_font()
{
    if (!TTF_Init())
    {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        exit(1);
    }
    sixtyfourconvergence_font = TTF_OpenFont(SIXTYFOURCONVERGENCE_FONT, 36);
    if (!sixtyfourconvergence_font)
    {
        SDL_Log("Failed to load title font: %s", SDL_GetError());
        exit(1);
    }

    pixelify_font = TTF_OpenFont(PIXELIFYSANS_FONT, 36);
    if (!pixelify_font)
    {
        SDL_Log("Failed to load menu font: %s", SDL_GetError());
        exit(1);
    }
}

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, float scale, SDL_Color color)
{
    text_surface = TTF_RenderText_Solid(font, text, strlen(text), color);
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_FRect dest_rect = {x, y, (float)text_surface->w, (float)text_surface->h};
    SDL_SetRenderScale(renderer, scale, scale);
    SDL_RenderTexture(renderer, text_texture, NULL, &dest_rect);
    SDL_SetRenderScale(renderer, 1, 1);

    if (text_surface)
        SDL_DestroySurface(text_surface);
    if (text_texture)
        SDL_DestroyTexture(text_texture);
}

// Gunakan GameStat untuk menampilkan UI game
void render_game_ui(SDL_Renderer *renderer, GameStat *stat)
{
    SDL_Color light_brown = {181, 101, 29, 255};

    int heart_x = 30;
    int heart_y = 20;
    int heart_spacing = 60;

    for (int i = 0; i < stat->lives; i++)
    {
        render_text(renderer, sixtyfourconvergence_font, "\u2665", heart_x + (i * heart_spacing), heart_y, 1, light_brown);
    }

    char score_text[50];
    sprintf(score_text, "Score: %d", stat->score);
    render_text(renderer, pixelify_font, score_text, 425, 10, 1, light_brown);

    char timer_text[50];
    sprintf(timer_text, "Time: %d", stat->start_time);
    render_text(renderer, pixelify_font, timer_text, 800, 10, 1, light_brown);
}

void render_game_over_ui(SDL_Renderer *renderer)
{
    SDL_Color red = {255, 0, 0, 255};
    SDL_FRect overlay = {0, 0, 960, 640};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, &overlay);
    render_text(renderer, pixelify_font, "Game Over", 360, 250, 1, red);
}

void render_pause_ui(SDL_Renderer *renderer)
{
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_FRect overlay = {0, 0, 960, 640};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, &overlay);
    render_text(renderer, pixelify_font, "Paused", 400, 250, 1, yellow);
}

void render_menu_ui(SDL_Renderer *renderer)
{
    SDL_Color cyan = {0, 255, 255, 255};
    render_text(renderer, pixelify_font, "Main Menu", 200, 100, 1, cyan);
    render_text(renderer, pixelify_font, "Start Game", 220, 200, 1, cyan);
    render_text(renderer, pixelify_font, "Exit Game", 220, 250, 1, cyan);
}

void clean_up_ui()
{
    if (sixtyfourconvergence_font)
        TTF_CloseFont(sixtyfourconvergence_font);
    if (pixelify_font)
        TTF_CloseFont(pixelify_font);
    TTF_Quit();
}