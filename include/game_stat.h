#ifndef GAME_STAT_H
#define GAME_STAT_H

#include <SDL3/SDL.h>
#include <stdbool.h> // Untuk tipe data bool

#define DEFAULT_LIVES 3  // Jumlah nyawa awal

typedef struct {
    int score;   // Skor pemain
    int lives;   // Jumlah nyawa pemain
    Uint32 start_time; 
    Uint32 stop_time;
    Uint32 elapsed_time; 
} GameStat;

extern GameStat game_stat; // Variabel global untuk status game

// Inisialisasi GameStat dengan jumlah nyawa awal dan waktu maksimal per level
void init_game_stat(GameStat *stat);

// Memulai atau mereset timer permainan
void start_timer(GameStat *stat);

Uint32 get_elapsed_time(GameStat *stat);

// Pause timer
void stop_timer(GameStat *stat);

// Menambah skor berdasarkan nilai tertentu
void add_score(GameStat *stat);

// Mereset skor ke nol
void reset_score(GameStat *stat);

// Menambah satu nyawa (dengan batas maksimum)
void add_life(GameStat *stat);

// Mengurangi satu nyawa (cek jika game over)
void sub_life(GameStat *stat);

#endif // GAME_STAT_H