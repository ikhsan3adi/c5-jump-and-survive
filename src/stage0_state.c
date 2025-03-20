#include <stdio.h>
#include <SDL3/SDL.h>

#include "stage0_state.h"
#include "stage1_state.h"
#include "game.h"
#include "game.h"
#include "game_state.h"
#include "player.h"
#include "level.h"
#include "entity.h"
#include "game_stat.h"
#include "ui.h"
Entity *player;
#include "SFX.h"

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

  // Inisialisasi playerL
  player = create_entity(100, 400, 32, 32, (SDL_Color){0, 0, 0, 255});
  init_game_stat(&game_stat);
  start_timer(&game_stat);

  // Memainkan musik latar belakang
  if (stage0_bgm)
  {
    play_music(stage0_bgm, INT32_MAX);
  }
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

  game_stat.elapsed_time = get_elapsed_time(&game_stat);

  if (is_exit(&player->transform)) {
    change_level(current_level + 1);
    initiate_player(player, 100, 300);
    if (current_level == 2)
    {
      initiate_player(player, 650, 100);
    }
    if (current_level == 3)
    {
      change_game_state(&stage1_state);
      initiate_player(player, 70, 170);
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
  render_player(renderer, player);

  render_game_ui(renderer, &game_stat);

  SDL_RenderPresent(renderer);
}

void stage0_cleanup()
{
  SDL_Log("Stage 0 State: Cleaned up");
  destroy_player(player);
}
