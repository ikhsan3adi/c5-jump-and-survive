#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "vector.h"
#include "physics.h"
#include "transform.h"

#define MAX_SAWS 20


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

typedef struct {
    Transform transform;
    Physics physics;
} Saw;

typedef struct {
    Saw* saws[MAX_SAWS];
    int count;
} SawManager;

extern SawManager saw_manager;

Saw *create_saw(float x, float y, float w, float h, float velocity_x, float velocity_y);

void update_saw(Saw *saw, float delta_time);

void render_saw(SDL_Renderer *renderer, Saw *saw);

void init_saw_manager(SawManager* manager);

void add_saw(SawManager* manager, float x, float y, float w, float h, float velocity_x, float velocity_y);

void update_all_saws(SawManager* manager, float delta_time);

void render_all_saws(SDL_Renderer* renderer, SawManager* manager);

void cleanup_saw_manager(SawManager* manager);

void setup_level_saws(int level_number);

int is_wall_at(int level, int tile_x, int tile_y);
#endif

