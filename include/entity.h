#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>

#include "physics.h"
#include "transform.h"

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

Entity *create_entity(float x, float y, float w, float h, SDL_Color color);

void update_entity(Entity *entity, float delta_time, Entity *objects[], int object_count);

void apply_entity_movement(Entity *entity, float delta_time, Entity *objects[], int object_count);

void destroy_entity(Entity *entity);

#endif