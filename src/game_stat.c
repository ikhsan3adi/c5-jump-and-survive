#include "game_stat.h"
#include <stdio.h>
#define SCORE_PER_COIN 10

GameStat game_stat; // Deklarasi variabel global

// Inisialisasi GameStat dengan jumlah nyawa awal dan waktu maksimal per level
void init_game_stat(GameStat *stat) {
    stat->score = 0; //score mulai dari 0
    stat->lives = DEFAULT_LIVES; // default nyawa (3)
    stat->start_time = 0; // Timer juga
    stat->stop_time = 0;
    stat->elapsed_time = 0;
}

// Memulai atau mereset timer permainan
void start_timer(GameStat *stat) {
    stat->start_time = SDL_GetTicks(); 
}

Uint32 get_elapsed_time(GameStat *stat){
    return SDL_GetTicks() - stat->start_time; 
    stat->elapsed_time = stat->stop_time - stat->start_time;
}

// Pause timer
void stop_timer(GameStat *stat) {
    stat->stop_time = SDL_GetTicks();
    stat->elapsed_time = get_elapsed_time(stat);
}

// Menambah skor berdasarkan multiplier
void add_score(GameStat *stat) {
    stat->score += SCORE_PER_COIN;
    //base score perlu g c?
}

// Mereset skor ke nol
void reset_score(GameStat *stat) {
    stat->score = 0;
}

// Menambah satu nyawa (dengan batas maksimum)
void add_life(GameStat *stat) {
    if (stat->lives < DEFAULT_LIVES) {
        stat->lives++;
        printf("Lives increased! Current Lives: %d\n", stat->lives);
    }
}

// Mengurangi satu nyawa dan mengecek game over
void sub_life(GameStat *stat) {
    if (stat->lives > 0) {
        stat->lives--;
        printf("Lives left: %d\n", stat->lives);
        
        if (stat->lives == 0) {
            printf("Game Over!\n");
            // Tambahkan logika untuk menangani game over di sini
        }
    }
}