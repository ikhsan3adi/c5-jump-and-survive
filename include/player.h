#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
typedef struct {
    int x, y;
} Transform;

typedef struct {
    SDL_Color color;
} RenderComponent;

typedef struct {
    Transform transform;
    RenderComponent render;
} Entity;


#endif