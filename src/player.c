#include <stdlib.h>
#include <SDL3/SDL.h>
#include "player.h"

void handle_player_input(Entity *player, SDL_Event *event)
{
  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    if (event->key.key == SDLK_LEFT)
      player->physics.velocity_x = -player->physics.speed;
    if (event->key.key == SDLK_RIGHT)
      player->physics.velocity_x = player->physics.speed;
    if (event->key.key == SDLK_SPACE && player->physics.velocity_y == 0)
      player->physics.velocity_y = -5000; // Jump
  } 
  else {
    player->physics.velocity_x = 0;
  }
}


void destroy_player(Entity *player)
{
  destroy_entity(player);
}
