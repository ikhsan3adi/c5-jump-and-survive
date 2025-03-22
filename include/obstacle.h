#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL3/SDL.h>
#include "vector.h"
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
#endif

