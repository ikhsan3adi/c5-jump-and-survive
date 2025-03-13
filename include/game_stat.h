#ifndef GAME_STAT_H
#define GAME_STAT_H

#include <SDL3/SDL.h>

#define DEFAULT_LIVES 3  // Jumlah nyawa awal

typedef struct {
    int score;          // Skor pemain
    int lives;          // Jumlah nyawa pemain
    Uint32 start_time;  // Waktu mulai permainan
    Uint32 max_time;    // Waktu maksimal untuk menyelesaikan level
} GameStat;

extern GameStat game_stat; // Deklarasi variabel global untuk game_stat

// Inisialisasi GameStat
void init_game_stat(GameStat *stat, Uint32 max_time);

// Menambah skor berdasarkan waktu yang tersisa
void add_score(GameStat *stat, int base_score, float multiplier);

// Mereset skor ke nol
void reset_score(GameStat *stat);

// Memulai timer permainan
void start_timer(GameStat *stat);

// Menghentikan timer dan mengembalikan waktu yang telah berlalu dalam detik
Uint32 stop_timer(GameStat *stat);

// Menambah satu nyawa (dengan batas maksimum)
void add_life(GameStat *stat);

// Mengurangi satu nyawa (cek jika game over)
void sub_life(GameStat *stat);

#endif // GAME_STAT_H