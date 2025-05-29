#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <SDL3/SDL.h>
#include "vector.h"
#include "physics.h"
#include "transform.h"

#define MAX_SAWS 101

#define PI 3.14159265

typedef struct
{
    Vector button;
    Vector switches[100];

} Switch;

typedef struct
{
    Vector button;
    Vector switches[100];
    Vector obstacles[100];

} Switch_Obstacles;

typedef struct
{
    Transform transform;
    Physics physics;
} Saw;

typedef struct
{
    Saw *saws[MAX_SAWS];
    int count;
} SawManager;

extern SawManager saw_manager;

// Fungsi tambahan untuk menggambar Saw dan Spike
void draw_rotating_saw(SDL_Renderer *renderer, SDL_FRect rect, float angle);
void draw_triangle(SDL_Renderer *renderer, SDL_FRect rect);
void draw_coin(SDL_Renderer *renderer, SDL_FRect rect, int type);
void draw_gate(SDL_Renderer *renderer, SDL_FRect exit_rect);

Saw *create_saw(float x, float y, float w, float h, float velocity_x, float velocity_y);

void update_saw(Saw *saw, float delta_time);

void render_saw(SDL_Renderer *renderer, Saw *saw, float angle);

void init_saw_manager(SawManager *manager);

void add_saw(SawManager *manager, float x, float y, float w, float h, float velocity_x, float velocity_y);

void update_all_saws(SawManager *manager, float delta_time);

void render_all_saws(SDL_Renderer *renderer, SawManager *manager);

void cleanup_saw_manager(SawManager *manager);

void setup_level_saws();

#endif
