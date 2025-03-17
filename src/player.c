#include <stdlib.h>
#include <SDL3/SDL.h>
#include "player.h"
#include "level.h"

Entity *player;

// array untuk menyimpan status tombol
bool key_state[SDL_SCANCODE_COUNT];

void initiate_player(Entity *player, int x, int y)
{
  player->transform.x = x;
  player->transform.y = y;
}

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

void render_player(SDL_Renderer *renderer, Entity *player)
{

  // **1. Tubuh (bulat dengan warna gelap)**
  SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Warna gelap
  SDL_FRect body = {player->transform.x, player->transform.y, TILE_SIZE, TILE_SIZE - 8};
  SDL_RenderFillRect(renderer, &body);

  // **2. Tangan (kotak kecil di samping)**
  SDL_FRect hand1 = {player->transform.x - 8, player->transform.y + 10, 10, 10};
  SDL_FRect hand2 = {player->transform.x + TILE_SIZE , player->transform.y + 10, 10, 10};
  SDL_RenderFillRect(renderer, &hand1);
  SDL_RenderFillRect(renderer, &hand2);

  // **3. Kaki (kotak kecil di bawah)**
  SDL_FRect leg1 = {player->transform.x + TILE_SIZE - 27, player->transform.y + TILE_SIZE - 8, 10, 10};
  SDL_FRect leg2 = {player->transform.x + TILE_SIZE - 12 , player->transform.y + TILE_SIZE - 8, 10, 10};
  SDL_RenderFillRect(renderer, &leg1);
  SDL_RenderFillRect(renderer, &leg2);

  // **4. Mata bercahaya merah**
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Warna merah terang
  SDL_FRect eye1 = {player->transform.x + 10, player->transform.y + 12, 6, 6};
  SDL_FRect eye2 = {player->transform.x + 24, player->transform.y + 12, 6, 6};
  SDL_RenderFillRect(renderer, &eye1);
  SDL_RenderFillRect(renderer, &eye2);

  // **5. Efek glow mata (cahaya di sekitar)**
  SDL_SetRenderDrawColor(renderer, 200, 50, 50, 180); // Merah transparan untuk efek glow
  SDL_FRect glow1 = {player->transform.x + 8, player->transform.y + 10, 10, 10};
  SDL_FRect glow2 = {player->transform.x + 22, player->transform.y + 10, 10, 10};
  SDL_RenderFillRect(renderer, &glow1);
  SDL_RenderFillRect(renderer, &glow2);
}
