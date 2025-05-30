#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "stage0_state.h"
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

  current_level = level_head;
  player = create_player(
      (Transform){current_level->player_spawn.x * TILE_SIZE, current_level->player_spawn.y * TILE_SIZE, 32, 32},
      TILE_SIZE * 50,   // gravity (50 TILE / s^2)
      TILE_SIZE * 5.5f, // speed = 5.5 tile per second
      1.0f);

  SDL_Renderer *renderer = get_game_instance()->renderer;
  show_stage_transition(renderer, 0);

  // Memainkan musik latar belakang
  if (stage0_bgm)
  {
    play_music(stage0_bgm, INT32_MAX);
  }
  setup_level_saws();
  init_game_stat(&game_stat);
  start_timer(&game_stat);
  change_level();
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

  add_elapsed_time(&game_stat, round(delta_time * 1000));

  update_all_saws(&saw_manager, delta_time);

  // Check for collision with player
  for (int i = 0; i < saw_manager.count; i++)
  {
    handle_saw_collision(saw_manager.saws[i]->transform, player->transform);
  }

  if (is_exit(&player->transform))
  {
    SDL_Renderer *renderer = get_game_instance()->renderer;
    if(current_level->next == NULL)
    {
      show_congratulations_ui(renderer, game_stat);
      cleanup_saw_manager(&saw_manager);
      return;
    }
    show_level_transition(renderer, 0, current_level);
    goto_next_level();
    cleanup_saw_manager(&saw_manager);
    setup_level_saws();
    reinitiate_player(player, current_level->player_spawn);
  }

}

void stage0_render(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 124, 162, 142, 255);
  SDL_RenderClear(renderer);

  // Render map
  render_level(renderer);

  // Render Saws

  render_all_saws(renderer, &saw_manager);

  // Render player
  render_player(renderer, player);

  render_game_ui(renderer, &game_stat);
}

void stage0_cleanup()
{
  SDL_Log("Stage 0 State: Cleaned up");
  destroy_player(player);
  cleanup_saw_manager(&saw_manager);
}
