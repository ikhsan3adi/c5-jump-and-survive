#include "game_stat.h"
#include <stdio.h>

GameStat game_stat; // Deklarasi variabel global

// Inisialisasi GameStat dengan jumlah nyawa awal dan waktu maksimal per level
void init_game_stat(GameStat *stat) {
    stat->score = 0;
    stat->lives = DEFAULT_LIVES;
    stat->timer = 0; // Konversi dari milidetik ke detik
    stat->is_paused = false;
}

// Memulai atau mereset timer permainan
void start_timer(GameStat *stat) {
    stat->timer = 0; // Konversi dari ms ke detik
    stat->is_paused = false;
}

// Pause timer
void pause_timer(GameStat *stat) {
    stat->is_paused = true;
}

// Resume timer
void resume_timer(GameStat *stat) {
    stat->is_paused = false;
}

// Update timer setiap detik jika game tidak di-pause
void update_timer(GameStat *stat) {
    if (!stat->is_paused && stat->timer >= 0) {
        stat->timer++;
    }
}

// Menambah skor berdasarkan multiplier
void add_score(GameStat *stat, int base_score, float multiplier) {
    stat->score += base_score + (stat->timer * multiplier);
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