#ifndef GAME_STAT_H
#define GAME_STAT_H

#include <SDL3/SDL.h>
#include <stdbool.h> // Untuk tipe data bool

#define DEFAULT_LIVES 3 // Jumlah nyawa awal
#define MAX_NAME 20

typedef struct
{
    char nickname[MAX_NAME]; // Nama pemain
    int score;         // Skor pemain
    int lives;         // Jumlah nyawa pemain
    Uint32 start_time; // milliseconds
    Uint32 stop_time;
    Uint32 elapsed_time;
    Uint32 last_hit_time;
} GameStat;

extern GameStat game_stat; // Variabel global untuk status game

// Inisialisasi GameStat dengan jumlah nyawa awal dan waktu maksimal per level
void init_game_stat(GameStat *stat);

// Memulai atau mereset timer permainan
void start_timer(GameStat *stat);

/// @deprecated Sudah tidak digunakan, digantikan dengan `add_elapsed_time`
Uint32 get_elapsed_time(GameStat *stat);

void stop_timer(GameStat *stat);

// menjalankan timer
void add_elapsed_time(GameStat *stat, Uint32 time);

// Menambah skor berdasarkan nilai tertentu
void add_score(GameStat *stat);

// Mereset skor ke nol
void reset_score(GameStat *stat);

// Menambah satu nyawa (dengan batas maksimum)
void add_life(GameStat *stat);


// Mengurangi satu nyawa (return false jika nyawa abis)
bool sub_life(GameStat *stat);

#endif // GAME_STAT_H