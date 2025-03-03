#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

void handle_player_input(Entity *player, SDL_Event *event);

void destroy_player(Entity *player);

#endif
