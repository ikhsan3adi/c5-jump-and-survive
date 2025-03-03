#include <stdio.h>
#include <SDL3/SDL.h>

#include "level0_state.h"
#include "game.h"
#include "game_state.h"
#include "player.h"

Entity *player;
Entity *platform;

// Definisi state
GameState level0_state = {
    .init = level0_init,
    .handle_input = level0_handle_input,
    .update = level0_update,
    .render = level0_render,
    .cleanup = level0_cleanup,
};

void level0_init()
{
  SDL_Log("Level 0 State: Initialized");

  // Inisialisasi player
  player = create_entity(100, 400, 40, 40, (SDL_Color){255, 0, 0, 255});

  // Inisialisasi platform (tanah)
  platform = create_entity(0, 440, 600, 40, (SDL_Color){0, 255, 0, 255});
}

void level0_handle_input(SDL_Event *event)
{
  handle_player_input(player, event);
}

void level0_update(double delta_time)
{
  Entity *objects[] = {platform};
  update_entity(player, delta_time, objects, 1);
}

void level0_render(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Render player
  SDL_SetRenderDrawColor(renderer, player->render.color.r, player->render.color.g, player->render.color.b, 255);
  SDL_FRect player_rect = {player->transform.x, player->transform.y, player->transform.w, player->transform.h};
  SDL_RenderFillRect(renderer, &player_rect);

  // Render platform
  SDL_SetRenderDrawColor(renderer, platform->render.color.r, platform->render.color.g, platform->render.color.b, 255);
  SDL_FRect platform_rect = {platform->transform.x, platform->transform.y, platform->transform.w, platform->transform.h};
  SDL_RenderFillRect(renderer, &platform_rect);

  SDL_RenderPresent(renderer);
}

void level0_cleanup()
{
  SDL_Log("Level 0 State: Cleaned up");
  destroy_player(player);
  destroy_entity(platform);
}
