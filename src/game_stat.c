#include "game_stat.h"
#include "ui.h"
#include "game.h"
#include "SFX.h"
#include "leaderboard.h"
#include <stdio.h>
#define SCORE_PER_COIN 10

GameStat game_stat; // Deklarasi variabel global

// Inisialisasi GameStat dengan jumlah nyawa awal dan waktu maksimal per level
void init_game_stat(GameStat *stat)
{
    stat->score = 0;             // score mulai dari 0
    stat->lives = DEFAULT_LIVES; // default nyawa (3)
    stat->start_time = 0;        // Timer juga
    stat->stop_time = 0;
    stat->elapsed_time = 0;
}

// Memulai atau mereset timer permainan
void start_timer(GameStat *stat)
{
    stat->start_time = SDL_GetTicks();
}

Uint32 get_elapsed_time(GameStat *stat)
{
    return SDL_GetTicks() - stat->start_time;
}

void stop_timer(GameStat *stat)
{
    stat->stop_time = SDL_GetTicks();
}

void add_elapsed_time(GameStat *stat, Uint32 time)
{
    game_stat.elapsed_time += time;
}

// Menambah skor berdasarkan multiplier
void add_score(GameStat *stat)
{
    stat->score += SCORE_PER_COIN;
    // base score perlu g c?
}

// Mereset skor ke nol
void reset_score(GameStat *stat)
{
    stat->score = 0;
}

// Menambah satu nyawa (dengan batas maksimum)
void add_life(GameStat *stat)
{
    if (stat->lives < DEFAULT_LIVES)
    {
        stat->lives++;
    }
}

// Mengurangi satu nyawa dan mengecek game over
bool sub_life(GameStat *stat)
{
    Uint32 now = SDL_GetTicks();

    if (stat->lives > 0 && (now - stat->last_hit_time > 500))
    { // Cooldown 0,5 detik
        stat->lives--;
        stat->last_hit_time = now;

        if (stat->lives == 0)
        {
            stop_music();
            SDL_Renderer *renderer = get_game_instance()->renderer;

            if (leaderboard_head == NULL)
            {
                leaderboard_head = load_leaderboard("leaderboard.dat");
            }
            insert_leaderboard(&leaderboard_head, *stat);
            save_leaderboard("leaderboard.dat", leaderboard_head);
            show_game_over_ui(renderer, *stat);
            return false;
        }
    }

    return true;
}
