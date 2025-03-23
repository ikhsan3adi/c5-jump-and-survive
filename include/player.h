#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

#define PLAYER_JUMP -5000.0f
#define PLAYER_MOVE_MULTIPLIER 2000.0f

extern Entity *player;

extern bool key_state[SDL_SCANCODE_COUNT];

Entity *create_player(Transform transform, double gravity, double speed, double friction);

void initiate_player(Entity *player, int x, int y);

void reinitiate_player(Entity *player, int level);

void handle_player_input(Entity *player, SDL_Event *event);

void destroy_player(Entity *player);

void render_player(SDL_Renderer *renderer, Entity *player);

#endif
