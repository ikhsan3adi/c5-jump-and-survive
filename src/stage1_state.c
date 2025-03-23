#include <stdio.h>
#include <SDL3/SDL.h>

#include "stage1_state.h"
#include "game.h"
#include "game_state.h"
#include "player.h"
#include "level.h"
#include "SFX.h"
#include "ui.h"

// Definisi state
GameState stage1_state = {
    .init = stage1_init,
    .handle_input = stage1_handle_input,
    .update = stage1_update,
    .render = stage1_render,
    .cleanup = stage1_cleanup,
};

void stage1_init()
{
  SDL_Log("Stage 1 State: Initialized");

  // Inisialisasi player
  player = create_entity(100, 400, 32, 32, (SDL_Color){0, 0, 0, 255});
  init_game_stat(&game_stat);
  start_timer(&game_stat);

  SDL_Renderer *renderer = get_game_instance()->renderer;
  show_stage_transition(renderer, 1);

  if (stage1_bgm)
  {
    play_music(stage1_bgm, INT32_MAX);
  }

  change_level(current_level);
  initiate_player(player, 570, 330);
}

void stage1_handle_input(SDL_Event *event)
{
  handle_player_input(player, event);

  if (event->type == SDL_EVENT_KEY_DOWN)
  {

    if (event->key.scancode == SDL_SCANCODE_ESCAPE)
    {
      stop_music();
      SDL_Renderer *renderer = get_game_instance()->renderer;
      show_pause_ui(renderer);
      play_music(stage1_bgm, INT32_MAX);
    }
  }
}

void stage1_update(double delta_time)
{
  update_entity(player, delta_time, NULL, 0);

  game_stat.elapsed_time = get_elapsed_time(&game_stat);

  if (is_exit(&player->transform))
  {
    SDL_Renderer *renderer = get_game_instance()->renderer;

    if (current_level == 10)
    {
      show_congratulations_ui(renderer, game_stat);
      initiate_player(player, 50, 50);
      return;
    }

    show_level_transition(renderer, 1, current_level);
    current_level++;
    change_level(current_level);

    if (current_level == 4)
    {
      initiate_player(player, 570, 70);
    }
    else if (current_level == 5)
    {
      initiate_player(player, 65, 300);
    }
    else if (current_level == 6)
    {
      initiate_player(player, 80, 300);
    }
    else if (current_level == 7)
    {
      initiate_player(player, 650, 50);
    }
    else if (current_level == 8)
    {
      initiate_player(player, 100, 70);
    }
    else if (current_level == 9)
    {
      initiate_player(player, 75, 500);
    }
    else if (current_level == 10)
    {
      initiate_player(player, 50, 50);
    }
  }
}

void stage1_render(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 93, 94, 114, 255);
  SDL_RenderClear(renderer);

  // Render map
  render_level(renderer);

  // Render player
  render_player(renderer, player);

  render_game_ui(renderer, &game_stat);
}

void stage1_cleanup()
{
  SDL_Log("Stage 1 State: Cleaned up");
  destroy_player(player);
}
