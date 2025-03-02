#ifndef LEVEL1_STATE_H
#define LEVEL1_STATE_H

#include <SDL3/SDL.h>

// Struktur untuk menyimpan data level 1
typedef struct {
    SDL_Texture *background;
    SDL_Rect player;
    SDL_Rect platform[5];
} Level1State;

// Inisialisasi level 1
void Level1_Init(Level1State *level, SDL_Renderer *renderer);

// Update logika permainan di level 1
void Level1_Update(Level1State *level, float deltaTime);

// Render tampilan level 1
void Level1_Render(Level1State *level, SDL_Renderer *renderer);

// Membersihkan sumber daya yang digunakan di level 1
void Level1_Cleanup(Level1State *level);

#endif // LEVEL1_STATE_H
