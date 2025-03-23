#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>

#include "physics.h"
#include "transform.h"
#include "game_stat.h"
#include "obstacles.h"

// Tile Type
#define EMPTY 0
#define PLATFORM 1
#define SOLID_OBSTACLE 2
#define SWITCH 3
#define COINS 4
#define SPIKE 5
#define LIFE 6
#define SAWS 7
#define FAKE_COINS 8
#define EXIT_GATE 9
#define BUTTON 10

extern int solid_tiles[];

extern int destruct_tiles[];

extern SawManager saw_manager;
typedef struct
{
    SDL_Color color;
} EntityRenderComponent;

typedef struct
{
    Transform transform;
    EntityRenderComponent render;
    Physics physics;
} Entity;

Entity *create_entity(double x, double y, double w, double h, SDL_Color color);

void update_entity(Entity *entity, float delta_time, Entity *objects[], int object_count);

void apply_entity_movement(Entity *entity, float delta_time, Entity *objects[], int object_count);

void destroy_entity(Entity *entity);

bool is_solid(Transform *transform);

bool is_void(Transform *transform);

bool is_exit(Transform *transform);

bool is_coin(Transform *transform);

bool is_destruct(Transform *transform);

bool is_button(Transform *transform,Vector button);

void interaction_buttons_switch(Entity *player,Switch button);

void interaction_buttons_obstacles_switch(Entity *player,Switch_Obstacles button);
#endif