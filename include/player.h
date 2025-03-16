#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

#define PLAYER_JUMP -5000.0f
#define PLAYER_MOVE_MULTIPLIER 2000.0f

void initiate_player(Entity *player, int x, int y);

void handle_player_input(Entity *player, SDL_Event *event);

void destroy_player(Entity *player);

#endif
