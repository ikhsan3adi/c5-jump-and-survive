#include <stdio.h>
#include "level1_state.h"
#include "entity.h"

void Level1_Init(Level1State *level, SDL_Renderer *renderer) {
    // Load background texture
    SDL_Surface *bgSurface = IMG_Load("assets/background.png");
    if (!bgSurface) {
        printf("Failed to load background: %s\n", SDL_GetError());
        return;
    }
    level->background = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_DestroySurface(bgSurface);

    // Inisialisasi posisi pemain
    level->player.x = 100;
    level->player.y = 300;
    level->player.w = 50;
    level->player.h = 50;

    // Inisialisasi platform
    for (int i = 0; i < 5; i++) {
        level->platform[i].x = 100 + i * 120;
        level->platform[i].y = 400 - (i % 2) * 50;
        level->platform[i].w = 100;
        level->platform[i].h = 20;
    }

    printf("Level 1 initialized.\n");
}

void Level1_Update(Level1State *level, float deltaTime) {
    // Logika game sederhana (bisa ditambahkan gravitasi, collision, dll.)
    level->player.y += 1; // Efek gravitasi sederhana
}

void Level1_Render(Level1State *level, SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    
    // Render background
    if (level->background) {
        SDL_RenderTexture(renderer, level->background, NULL, NULL);
    }

    // Render player
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &level->player);

    // Render platform
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < 5; i++) {
        SDL_RenderFillRect(renderer, &level->platform[i]);
    }

    SDL_RenderPresent(renderer);
}

void Level1_Cleanup(Level1State *level) {
    if (level->background) {
        SDL_DestroyTexture(level->background);
    }
    printf("Cleaning up Level 1.\n");
}