#ifndef COLLITIONS_H
#define COLLITIONS_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
    int x,y;
    bool is_collide;
} collition;

#endif