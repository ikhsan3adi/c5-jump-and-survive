#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL_ttf.h>

#include "ui.h"
#include "menu_state.h"
#include "game.h"
#include "level.h"
#include "player.h"
#include "SFX.h"
#include "util.h"
#include "leaderboard.h"
#include "leaderboard_state.h"

TTF_Font *sixtyfourconvergence_font;
TTF_Font *pixelify_font;
SDL_Window *window;
SDL_Renderer *renderer = NULL;

SDL_Surface *text_surface = NULL;
SDL_Texture *text_texture = NULL;

void init_font()
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
    render_text(renderer, pixelify_font, timer_text, 775, 10, 1, light_brown);
}

// Fungsi untuk menangkap input nama pemain dan menyimpannya ke GameStat
// Mengembalikan true jika input berhasil, false jika gagal (misalnya, window ditutup)
bool show_input_player_name(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, GameStat *stat) {
    if (!renderer || !font || !stat) {
        SDL_Log("Parameter input_player_name tidak valid");
        return false;
    }

    char input_text[MAX_NAME] = ""; // Buffer untuk input nama
    bool done = false; // Status input selesai
    SDL_Color text_color = {255, 255, 255, 255}; // Warna teks putih
    SDL_Color bg_color = {30, 30, 60, 255}; // Warna latar seperti leaderboard
    SDL_FRect swipe_rect = {0, 0, SCREEN_WIDTH, 0}; // Untuk efek swipe
    Uint64 start = SDL_GetTicks();
    Uint64 max_time = 1000; // 1 detik untuk animasi swipe
    float rect_height = 0;

    // Aktifkan input teks
    SDL_StartTextInput(window); // Window diatur oleh SDL secara default

    while (!done) {
        // Animasi swipe
        Uint64 elapsed = SDL_GetTicks() - start;
        rect_height = (elapsed * SCREEN_HEIGHT) / max_time;
        if (rect_height > SCREEN_HEIGHT) rect_height = SCREEN_HEIGHT;

        // Proses event
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    SDL_StopTextInput(window);
                    return false; // Gagal jika window ditutup
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.scancode == SDL_SCANCODE_RETURN && strlen(input_text) > 0) {
                        // Simpan nama ke GameStat
                        strncpy(stat->nickname, input_text, MAX_NAME - 1);
                        stat->nickname[MAX_NAME - 1] = '\0'; // Pastikan null-terminated
                        done = true;
                    } else if (event.key.scancode == SDL_SCANCODE_BACKSPACE && strlen(input_text) > 0) {
                        // Hapus karakter terakhir
                        input_text[strlen(input_text) - 1] = '\0';
                    }
                    break;
                case SDL_EVENT_TEXT_INPUT:
                    // Tambahkan teks jika tidak melebihi batas
                    if (strlen(input_text) + strlen(event.text.text) < MAX_NAME - 1) {
                        strcat(input_text, event.text.text);
                    }
                    break;
            }
        }

        // Bersihkan layar
        SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
        SDL_RenderClear(renderer);

        // Render efek swipe
        swipe_rect.h = rect_height;
        SDL_SetRenderDrawColor(renderer, 255, 18, 53, 255); // Warna merah seperti game over
        SDL_RenderFillRect(renderer, &swipe_rect);

        // Render teks petunjuk dan input
        render_text(renderer, sixtyfourconvergence_font, "MASUKKAN NAMA", 
                    SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 150, 1.2, text_color);
        render_text(renderer, pixelify_font, input_text[0] ? input_text : " ", 
                    SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 1.0, text_color);
        render_text(renderer, pixelify_font, "Tekan ENTER untuk lanjut", 
                    SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 + 50, 1.0, text_color);

        // Gambar kotak input
        SDL_FRect input_rect = {SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT / 2 - 60, 320, 50};
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Warna border emas
        SDL_RenderRect(renderer, &input_rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Smooth animation
    }

    SDL_StopTextInput(window);
    return true; // Input berhasil
}


void show_game_over_ui(SDL_Renderer *renderer, GameStat stat)
{
    if (!show_input_player_name(window, renderer, pixelify_font, &stat)) {
        // Jika input gagal, gunakan nama default
        strncpy(stat.nickname, "Anonymous", MAX_NAME - 1);
        stat.nickname[MAX_NAME - 1] = '\0';
    }

    if(leaderboard_head == NULL){
        leaderboard_head = load_leaderboard("leaderboard.dat");
    }
    insert_leaderboard(&leaderboard_head, stat);
    save_leaderboard("leaderboard.dat", leaderboard_head);

    bool is_exit = false;
    SDL_Event event;
    Uint64 start = SDL_GetTicks();
    Uint64 max_time = 1000; // ms (for rectacngle swipe)
    SDL_Color text_color = {10, 10, 10, 255};

    char *title_text = "GAME OVER";
    char *body_text = "Press ESC to exit to menu";
    char score_text[32];
    char timer_text[32];
    char name_text[32];

    sprintf(name_text, "name; %s", stat.nickname);
    sprintf(score_text, "Score: %d", stat.score);
    sprintf(timer_text, "Time: %s", get_time_string(game_stat.elapsed_time / 1000));

    int rect_height = 0;

    play_sound(gameover_sfx, 6, 0);

    skip_physics_frame();

    while (!is_exit)
    {
        Uint64 elapsed = SDL_GetTicks() - start;

        // Update lebar rect (efek swipe)
        rect_height = (elapsed * SCREEN_HEIGHT) / max_time;

        // Draw swipe effect (rectangle)
        SDL_SetRenderDrawColor(renderer, 255, 18, 53, 255);
        SDL_FRect swipe_rect = {0, 0, SCREEN_WIDTH, rect_height};
        SDL_RenderFillRect(renderer, &swipe_rect);

        // Render text
        render_text(renderer, sixtyfourconvergence_font, title_text,
                    SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 250,
                    1.2,
                    text_color);
        render_text(renderer, pixelify_font, score_text,
                    SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 100,
                    1, text_color);
        render_text(renderer, pixelify_font, timer_text,
                    SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50,
                    1, text_color);
        render_text(renderer, pixelify_font, body_text,
                    SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 + 80,
                    1, text_color);

        // render
        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);

        if (event.type == SDL_EVENT_QUIT)
            exit(0);

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                is_exit = true;
            }
        }

        // Delay untuk smooth animation
        SDL_Delay(16);
    }

    change_game_state(&menu_state);
}

void show_pause_ui(SDL_Renderer *renderer)
{
    bool is_exit = false;
    SDL_Event event;
    SDL_Color text_color = {255, 255, 0, 255};
    SDL_FRect overlay_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    skip_physics_frame();

    while (!is_exit)
    {
        // render tampilan saat ini dibelakangnya agar menciptakan efek overlay
        current_state->render(renderer);

        // render overlay
        SDL_SetRenderDrawColor(renderer, 30, 15, 20, 180);
        SDL_RenderFillRect(renderer, &overlay_rect);

        // Render text
        render_text(renderer, sixtyfourconvergence_font, "PAUSED",
                    SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 200,
                    1.2,
                    text_color);

        render_text(renderer, pixelify_font, "Press ENTER to resume",
                    SCREEN_WIDTH / 2 - 195, SCREEN_HEIGHT / 2 + 20,
                    1, text_color);

        render_text(renderer, pixelify_font, "Press ESC to exit to menu",
                    SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 + 100,
                    1, text_color);

        // render
        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                exit(0);

            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.scancode == SDL_SCANCODE_RETURN)
                {
                    is_exit = true;
                }
                if (event.key.scancode == SDL_SCANCODE_ESCAPE)
                {
                    is_exit = true;
                    change_game_state(&menu_state);
                }
            }
            else if (event.type == SDL_EVENT_KEY_UP)
            {
                key_state[event.key.scancode] = false;
            }
        }
    }
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

    play_sound(gate_sfx, 5, 0);

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
    stop_sound(5);
}

void show_leaderboard_ui(SDL_Renderer *renderer, LeaderboardNode *head)
{
    // Set background color (soft dark blue for better contrast)
    SDL_SetRenderDrawColor(renderer, 30, 30, 60, 255);
    SDL_RenderClear(renderer);

    // Define colors
    SDL_Color title_color = {255, 215, 0, 255};         // Gold for title
    SDL_Color text_color = {255, 255, 255, 255};        // White for entries
    SDL_Color header_color = {100, 200, 255, 255};      // Light blue for headers
    SDL_Color instruction_color = {200, 200, 200, 255}; // Light gray for instructions

    // Draw semi-transparent background rectangle for leaderboard table
    SDL_SetRenderDrawColor(renderer, 50, 50, 80, 200); // Darker blue, semi-transparent
    SDL_FRect table_bg = {75, 100, 810, 450};          // Scaled table size
    SDL_RenderFillRect(renderer, &table_bg);

    // Draw table border
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Gold border
    SDL_RenderRect(renderer, &table_bg);

    // Render title (centered, adjusted scale)
    render_text(renderer, sixtyfourconvergence_font, "LEADERBOARD", 300, 40, 1.0, title_color);

    render_text(renderer, pixelify_font, "RANK", 130, 130, 1.0, header_color);
    render_text(renderer, pixelify_font, "NAME", 230, 130, 1.0, header_color);
    render_text(renderer, pixelify_font, "SCORE", 375, 130, 1.0, header_color);
    render_text(renderer, pixelify_font, "TIME (s)", 675, 130, 1.0, header_color);

    // Render leaderboard entries with adjusted spacing
    LeaderboardNode *current = head;
    int i = 0;
    while (current != NULL && i < MAX_LEADERBOARD)
    {
        char buffer[64];
        // Format: Rank, Score, Time
        snprintf(buffer, sizeof(buffer), "%2d", i + 1); // Rank
        render_text(renderer, pixelify_font, buffer, 175, 190 + i * 45, 0.9, text_color);

        snprintf(buffer, sizeof(buffer), "%s", current->stat.nickname[0] ? current->stat.nickname : "Anonymous");
        render_text(renderer, pixelify_font, buffer, 200, 190 + i * 45, 0.9, text_color);

        snprintf(buffer, sizeof(buffer), "%d", current->stat.score); // Score
        render_text(renderer, pixelify_font, buffer, 450, 190 + i * 45, 0.9, text_color);

        snprintf(buffer, sizeof(buffer), "%u", current->stat.elapsed_time / 1000); // Time in seconds
        render_text(renderer, pixelify_font, buffer, 800, 190 + i * 45, 0.9, text_color);

        current = current->next;
        i++;
    }

    // Render instruction text at the bottom (adjusted position)
    render_text(renderer, pixelify_font, "Press ESC or ENTER to return", 350, 570, 1, instruction_color);
}

void show_congratulations_ui(SDL_Renderer *renderer, GameStat stat)
{

    if (leaderboard_head == NULL)
    {
        leaderboard_head = load_leaderboard("leaderboard.dat");
    }
    insert_leaderboard(&leaderboard_head, stat);
    save_leaderboard("leaderboard.dat", leaderboard_head);
    bool is_exit = false;
    SDL_Event event;
    Uint64 start = SDL_GetTicks();
    Uint64 max_time = 2000; // ms (for rectacngle swipe)
    SDL_Color text_color = {39, 39, 39, 255};
    char score_text[32];
    char timer_text[32];

    sprintf(score_text, "Score: %d", stat.score);
    sprintf(timer_text, "Time: %s", get_time_string(game_stat.elapsed_time / 1000));

    int rect_height = 0;

    play_music(win_bgm, 1);

    skip_physics_frame();

    while (!is_exit)
    {
        Uint64 elapsed = SDL_GetTicks() - start;

        // Update lebar rect (efek swipe)
        rect_height = (elapsed * SCREEN_HEIGHT) / max_time;

        // Draw swipe effect (rectangle)
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
        SDL_FRect swipe_rect = {0, 0, SCREEN_WIDTH, rect_height};
        SDL_RenderFillRect(renderer, &swipe_rect);

        // render player
        render_player(renderer, player);

        // Render text
        render_text(renderer, sixtyfourconvergence_font, "CONGRATULATIONS",
                    SCREEN_WIDTH / 2 - 330, SCREEN_HEIGHT / 2 - 250,
                    1.2,
                    text_color);
        render_text(renderer, pixelify_font, score_text,
                    SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 100,
                    1, text_color);
        render_text(renderer, pixelify_font, timer_text,
                    SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50,
                    1, text_color);
        render_text(renderer, pixelify_font, "Press ENTER to restart",
                    SCREEN_WIDTH / 2 - 205, SCREEN_HEIGHT / 2 + 40,
                    1, text_color);
        render_text(renderer, pixelify_font, "Press ESC to exit to menu",
                    SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 + 100,
                    1, text_color);

        // render
        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);

        if (event.type == SDL_EVENT_QUIT)
            exit(0);

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                is_exit = true;
                change_game_state(&menu_state);
            }
            else if (event.key.scancode == SDL_SCANCODE_RETURN)
            {
                is_exit = true;
            }
        }

        // Delay untuk smooth animation
        SDL_Delay(16);
    }
    stop_music();
}

void clean_up_ui()
{
    if (sixtyfourconvergence_font)
        TTF_CloseFont(sixtyfourconvergence_font);
    if (pixelify_font)
        TTF_CloseFont(pixelify_font);
    TTF_Quit();
}