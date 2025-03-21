#include <stdio.h>
#include <SDL3/SDL.h>

#include "stage0_state.h"
#include "stage1_state.h"
#include "game.h"
#include "game_state.h"
#include "player.h"
#include "level.h"

Entity *player;

// Definisi state
GameState stage0_state = {
    .init = stage0_init,
    .handle_input = stage0_handle_input,
    .update = stage0_update,
    .render = stage0_render,
    .cleanup = stage0_cleanup,
};

void stage0_init()
{
  SDL_Log("Stage 0 State: Initialized");

  // Inisialisasi player
  player = create_entity(100, 400, 32, 32, (SDL_Color){0, 0, 0, 255});
}

void stage0_handle_input(SDL_Event *event)
{
  handle_player_input(player, event);

  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    //! CONTOH
    if (event->key.scancode == SDL_SCANCODE_N)
    {
      change_level(current_level == 0 ? 1 : 0);

      if (current_level == 2)
      {
        change_game_state(&stage1_state);
      }
    }
  }
}

void stage0_update(double delta_time)
{
  update_entity(player, delta_time, NULL, 0);
  
  if (is_exit(&player->transform)) {
    change_level(current_level + 1);
    initiate_player(player,100,300);
    if (current_level == 2)
    {
      initiate_player(player,650,100);
    }
    if (current_level == 3)
    {
      initiate_player(player,70,170);
    }
    if (current_level == 4)
    {
      initiate_player(player,570,70);
    } 
    if (current_level == 5)
    {
      initiate_player(player,80,300);
    } 
  }
    
}


void stage0_render(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 124, 162, 142, 255);
  SDL_RenderClear(renderer);

  // Render map
  render_level(renderer);

  // Render player
  SDL_SetRenderDrawColor(renderer, player->render.color.r, player->render.color.g, player->render.color.b, 255);
  SDL_FRect player_rect = {player->transform.x, player->transform.y, player->transform.w, player->transform.h};
  SDL_RenderFillRect(renderer, &player_rect);


  SDL_RenderPresent(renderer);
}

void stage0_cleanup()
{
  SDL_Log("Stage 0 State: Cleaned up");
  destroy_player(player);
}
