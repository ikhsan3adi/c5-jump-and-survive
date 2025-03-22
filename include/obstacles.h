#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <SDL3/SDL.h>
#include "entity.h"

// Fungsi tambahan untuk menggambar Saw dan Spike
void draw_rotating_saw(SDL_Renderer *renderer, SDL_FRect rect, float angle);
void draw_triangle(SDL_Renderer *renderer, SDL_FRect rect);
void draw_coin(SDL_Renderer *renderer, SDL_FRect rect, int type);
void draw_gate(SDL_Renderer *renderer, SDL_FRect exit_rect);

#endif
