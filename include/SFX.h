#ifndef SFX_H
#define SFX_H

#include <SDL3/SDL_mixer.h>

extern Mix_Music *stage0_bgm;
extern Mix_Music *menu_bgm;
extern Mix_Music *stage1_bgm;
extern Mix_Chunk *jump_sfx;
extern Mix_Chunk *gate_sfx;
extern Mix_Chunk *coin_sfx;
extern Mix_Chunk *dead_sfx;
extern Mix_Chunk *gameover_sfx;

// Inisialisasi audio
void init_audio();

// Memuat efek suara dari file
Mix_Chunk *load_sound(const char *file);

// Memuat music dari file
Mix_Music *load_music(const char *file);

// Memainkan efek suara
void play_sound(Mix_Chunk *sound, int channel, int loops);

void play_music(Mix_Music *sound, int loops);

void stop_music();

void stop_sound(int channel);

// Membersihkan audio
void cleanup_audio(); 

#endif
