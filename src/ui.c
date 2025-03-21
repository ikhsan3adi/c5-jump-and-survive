#include <stdio.h>
#include <stdlib.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "ui.h"
#include "menu_state.h"
#include "game.h"

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
    sprintf(timer_text, "Time: %d", stat->elapsed_time / 1000);
    render_text(renderer, pixelify_font, timer_text, 800, 10, 1, light_brown);
}

void render_menu_ui(SDL_Renderer *renderer)
{
    SDL_Color cyan = {0, 255, 255, 255};
    render_text(renderer, pixelify_font, "Main Menu", 200, 100, 1, cyan);
    render_text(renderer, pixelify_font, "Start Game", 220, 200, 1, cyan);
    render_text(renderer, pixelify_font, "Exit Game", 220, 250, 1, cyan);
}

void show_level_transition(SDL_Renderer *renderer, int stage, int level)
{
    Uint64 start = SDL_GetTicks();
    Uint64 max_time = 1500; // ms
    SDL_Color text_color;

    char title_text[32];
    char subtitle_text[32];
    char body_text[32];

    // buat string
    snprintf(title_text, sizeof(title_text), "Level %d Completed!", level);
    snprintf(subtitle_text, sizeof(subtitle_text), "Next Level: %d", level + 1);
    snprintf(body_text, sizeof(body_text), "Stage %d", stage);

    int rect_width = 0;

    skip_physics_frame();

    switch (stage)
    {
    case 0:
        text_color = (SDL_Color){255, 255, 255, 255};
        SDL_SetRenderDrawColor(renderer, 10, 55, 58, 255);
        break;
    case 1:
        text_color = (SDL_Color){255, 255, 255, 255};
        SDL_SetRenderDrawColor(renderer, 52, 54, 77, 255);
        break;
    }

    while (SDL_GetTicks() - start < max_time)
    {
        Uint64 elapsed = SDL_GetTicks() - start;

        // Update lebar rect (efek swipe)
        rect_width = (elapsed * SCREEN_WIDTH) / max_time;

        // Draw swipe effect (rectangle)
        SDL_FRect swipe_rect = {0, 0, rect_width, SCREEN_HEIGHT};
        SDL_RenderFillRect(renderer, &swipe_rect);

        // Render text
        render_text(renderer, sixtyfourconvergence_font, title_text,
                    SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 - 150,
                    1.2,
                    text_color);
        render_text(renderer, pixelify_font, subtitle_text,
                    SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 - 40,
                    1,
                    text_color);
        render_text(renderer, pixelify_font, body_text,
                    SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 80,
                    1, text_color);

        // render
        SDL_RenderPresent(renderer);

        // Delay untuk smooth animation
        SDL_Delay(16);
    }
}

void show_stage_transition(SDL_Renderer *renderer, int stage)
{
    Uint64 start = SDL_GetTicks();
    Uint64 max_time = 1500; // ms
    Uint64 elapsed = 0;
    SDL_FRect swipe_rect;
    SDL_Color text_color;
    int rect_width = 0;
    char title_text[32];

    skip_physics_frame();

    snprintf(title_text, sizeof(title_text), "Stage %d", stage);

    while (elapsed < max_time)
    {
        elapsed = SDL_GetTicks() - start;

        switch (stage)
        {
        case 0:
            text_color = (SDL_Color){245, 255, 245, 255};

            // stage 0 bg color
            SDL_SetRenderDrawColor(renderer, 10, 55, 58, 255);
            break;
        case 1:
            text_color = (SDL_Color){255, 255, 220, 255};

            // stage 0 bg color
            SDL_SetRenderDrawColor(renderer, 10, 55, 58, 255);
            SDL_RenderClear(renderer);

            // stage 1 bg color
            SDL_SetRenderDrawColor(renderer, 52, 54, 77, 255);
            break;
        }

        // Update lebar rect (efek swipe)
        rect_width = (elapsed * SCREEN_WIDTH) / max_time;

        // Draw swipe effect (rectangle)
        swipe_rect = (SDL_FRect){0, 0, rect_width, SCREEN_HEIGHT};
        SDL_RenderFillRect(renderer, &swipe_rect);

        // Render text
        render_text(renderer, sixtyfourconvergence_font, title_text,
                    SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 150,
                    1.2,
                    text_color);

        // render
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
}

void clean_up_ui()
{
    if (sixtyfourconvergence_font)
        TTF_CloseFont(sixtyfourconvergence_font);
    if (pixelify_font)
        TTF_CloseFont(pixelify_font);
    TTF_Quit();
}