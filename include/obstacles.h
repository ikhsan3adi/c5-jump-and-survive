#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <SDL3/SDL.h>
#include "entity.h"

typedef struct {
    Entity entity;
    float rotation;       // Untuk rotasi Saw
    float rotationSpeed;  // Kecepatan rotasi Saw
    int type;
} Obstacle;

extern Obstacle *obstacles[];
// Membuat obstacle baru (Saw atau Spike)
Obstacle *create_obstacle(double x, double y, double w, double h, int type);

// Memperbarui obstacle (khusus Saw untuk rotasi)
void update_obstacle(Obstacle *obstacle, float delta_time);

// Menggambar obstacle di layar
void render_obstacle(SDL_Renderer *renderer, const Obstacle *obstacle);

// Menghapus obstacle
void destroy_obstacle(Obstacle *obstacle);

// Fungsi tambahan untuk menggambar Saw dan Spike
void draw_rotating_saw(SDL_Renderer *renderer, SDL_FRect rect, float angle);
void draw_triangle(SDL_Renderer *renderer, SDL_FRect rect);
void draw_coin(SDL_Renderer *renderer, SDL_FRect rect, int type);
void draw_gate(SDL_Renderer *renderer,  SDL_FRect exit_rect);

#endif
