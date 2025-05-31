#include <stdio.h>
#include <stdlib.h>
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

// Berfungsi saat pergi ke level sebelumnya
char *current_level_name = NULL;

void set_current_level_name(const char *name)
{
  free(current_level_name);
  current_level_name = malloc(sizeof(char) * (strlen(name) + 1));
  if (current_level_name == NULL)
  {
    SDL_Log("Failed to allocate memory for current_level_name");
    exit_game(EXIT_FAILURE);
  }
  strcpy(current_level_name, name);
}

void check_previous_level()
{
  if (current_level->next == NULL) // is last level
  {
    return; // no previous level to check
  }
  if (strcmp(current_level_name, current_level->next->name) == 0) // is prev
  {
    // coins previous level + coins current level
    int earned_coins = count_level_coins() + current_level_earned_coins;
    sub_score(&game_stat, earned_coins);
  }
}

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
  show_stage_transition(renderer);

  // Memainkan musik latar belakang
  play_music(current_bgm, INT32_MAX);

  init_game_stat(&game_stat);
  start_timer(&game_stat);

  setup_level_saws();
  change_level();
  set_current_level_name(current_level->name);
}

void stage0_handle_input(SDL_Event *event)
{
  handle_player_input(player, event);

  if (event->type == SDL_EVENT_KEY_DOWN)
  {

    if (event->key.scancode == SDL_SCANCODE_ESCAPE)
    {
      pause_music();
      SDL_Renderer *renderer = get_game_instance()->renderer;
      show_pause_ui(renderer);

      if (current_state == &stage0_state &&
          strcmp(current_level_name, current_level->name) != 0)
      {
        check_previous_level();
        // Jika level berubah, reset player dan saws
        set_current_level_name(current_level->name);
        cleanup_saw_manager(&saw_manager);
        reinitiate_player(player, current_level->player_spawn);
        setup_level_saws();
        play_music(current_bgm, INT32_MAX);
      }

      resume_music();
    }
    else if (event->key.scancode == SDL_SCANCODE_F1)
    {
      stop_music();
      goto_next_level();
      reinitiate_player(player, current_level->player_spawn);
      setup_level_saws();
      reset_earned_coins();
    }
  }
}

void stage0_update(double delta_time)
{
  update_entity(player, delta_time, NULL, 0);

  add_elapsed_time(&game_stat, round(delta_time * 1000)); // convert delta_time to milliseconds

  update_all_saws(&saw_manager, delta_time);

  // Check for collision with player
  for (int i = 0; i < saw_manager.count; i++)
  {
    handle_saw_collision(saw_manager.saws[i]->transform, player->transform);
  }

  if (is_exit(&player->transform))
  {
    SDL_Renderer *renderer = get_game_instance()->renderer;
    cleanup_saw_manager(&saw_manager);
    stop_music();
    if (current_level->next == NULL)
    {
      show_congratulations_ui(renderer, game_stat);
    }
    else
    {
      show_level_transition(renderer, current_level);
      goto_next_level();
    }

    if (current_state == &stage0_state) // not exited after congrats
    {
      check_previous_level();
      set_current_level_name(current_level->name);
      change_level(); // restore current_level (coins, switches, etc.)
      reinitiate_player(player, current_level->player_spawn);
      setup_level_saws();
      play_music(current_bgm, INT32_MAX);
      reset_earned_coins();
    }
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
  free(current_level_name);
  current_level_name = NULL;
}
