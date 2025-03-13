#include "game_stat.h"
#include <stdio.h>

// Inisialisasi GameStat dengan jumlah nyawa awal dan waktu maksimal per level
void init_game_stat(GameStat *stat, Uint32 max_time) {
    stat->score = 0;
    stat->lives = DEFAULT_LIVES;
    stat->start_time = 0;
    
    // Pastikan max_time tidak bernilai nol agar timer berfungsi dengan benar
    stat->max_time = (max_time > 0) ? max_time : 60000; // Default 60 detik jika tidak diberikan
}

// Menambah skor berdasarkan waktu yang tersisa
void add_score(GameStat *stat, int base_score, float multiplier) {
    if (stat->start_time == 0) return; // Pastikan timer sudah berjalan

    Uint32 elapsed_time = SDL_GetTicks() - stat->start_time;
    Uint32 remaining_time = (stat->max_time > elapsed_time) ? (stat->max_time - elapsed_time) / 1000 : 0;

    stat->score += base_score + (remaining_time * multiplier);
}

// Mereset skor ke nol
void reset_score(GameStat *stat) {
    stat->score = 0;
}

// Memulai timer permainan
void start_timer(GameStat *stat) {
    stat->start_time = SDL_GetTicks();
}

// Menghentikan timer dan mengembalikan waktu yang telah berlalu dalam detik
Uint32 stop_timer(GameStat *stat) {
    if (stat->start_time == 0) {
        return 0; // Timer belum dimulai
    }
    Uint32 elapsed_time = SDL_GetTicks() - stat->start_time;
    return elapsed_time / 1000; // Konversi ms ke detik
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