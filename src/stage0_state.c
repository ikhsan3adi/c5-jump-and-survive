#include <stdio.h>
#include <SDL3/SDL.h>

#include "stage0_state.h"
#include "stage1_state.h"
#include "game.h"
#include "game_state.h"
#include "player.h"
#include "level.h"
#include "obstacles.h"
#include "entity.h"
#include "game_stat.h"
#include "ui.h"
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

  player = create_player((Transform){120, 416, 32, 32}, 10000.0f, 1.0f, 1);
  init_game_stat(&game_stat);
  start_timer(&game_stat);

  SDL_Renderer *renderer = get_game_instance()->renderer;
  show_stage_transition(renderer, 0);

  // Memainkan musik latar belakang
  if (stage0_bgm)
  {
    play_music(stage0_bgm, INT32_MAX);
  }
  change_level(0);
}

void stage0_handle_input(SDL_Event *event)
{
  handle_player_input(player, event);

  if (event->type == SDL_EVENT_KEY_DOWN)
  {

    if (event->key.scancode == SDL_SCANCODE_ESCAPE)
    {
      stop_music();
      SDL_Renderer *renderer = get_game_instance()->renderer;
      show_pause_ui(renderer);
      play_music(stage0_bgm, INT32_MAX);
    }
  }
}

void stage0_update(double delta_time)
{
  update_entity(player, delta_time, NULL, 0);

  game_stat.elapsed_time = get_elapsed_time(&game_stat);

  if (is_exit(&player->transform))
  {
    SDL_Renderer *renderer = get_game_instance()->renderer;
    show_level_transition(renderer, 0, current_level);
    current_level++;

    change_level(current_level);

    if (current_level == 1 || current_level == 0)
    {
      initiate_player(player, 100, 300);
    }
    else if (current_level == 2)
    {
      initiate_player(player, 650, 100);
    }
    else if (current_level == 3)
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
}

void stage0_cleanup()
{
  SDL_Log("Stage 0 State: Cleaned up");
  destroy_player(player); //
}
