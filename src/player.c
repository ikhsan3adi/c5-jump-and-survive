#include <stdlib.h>
#include <SDL3/SDL.h>
#include "player.h"

// array untuk menyimpan status tombol
bool key_state[SDL_SCANCODE_COUNT];

void handle_player_input(Entity *player, SDL_Event *event)
{
  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    key_state[event->key.scancode] = true; // tombol ditekan

    if (key_state[SDL_SCANCODE_LEFT])
    {
      player->physics.velocity_x = -player->physics.speed * PLAYER_MOVE_MULTIPLIER;
    }
    else if (key_state[SDL_SCANCODE_RIGHT])
    {
      player->physics.velocity_x = player->physics.speed * PLAYER_MOVE_MULTIPLIER;
    }
    if ((key_state[SDL_SCANCODE_UP] || key_state[SDL_SCANCODE_SPACE]) && player->physics.velocity_y == 0)
    {
      player->physics.velocity_y = PLAYER_JUMP;
    }
  }
  else if (event->type == SDL_EVENT_KEY_UP)
  {
    key_state[event->key.scancode] = false; // tombol dilepas

    // Cek apakah masih ada tombol lain (arrow kiri dan kanan) yang ditekan
    // sebelum menghentikan player
    if (!key_state[SDL_SCANCODE_LEFT] && !key_state[SDL_SCANCODE_RIGHT])
    {
      player->physics.velocity_x = 0;
    }
  }
}

void destroy_player(Entity *player)
{
  destroy_entity(player);
}
