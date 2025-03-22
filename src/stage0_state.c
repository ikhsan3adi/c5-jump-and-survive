#include <stdio.h>
#include <SDL3/SDL.h>

#include "stage0_state.h"
#include "stage1_state.h"
#include "game.h"
#include "game.h"
#include "game_state.h"
#include "player.h"
#include "level.h"
#include "obstacles.h"

#define MAX_OBSTACLES 10

Obstacle *obstacle[MAX_OBSTACLES];
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

  //inisialisasi obstacle
  obstacle[0] = create_obstacle(400, 442, 30, 10, SAWS);
  obstacle[1] = create_obstacle(210, 437, 30, 10, SPIKE);
  obstacle[2] = create_obstacle(637, 435, 30, 10, FAKE_COINS);
  obstacle[3] = create_obstacle(230, 437, 30, 10, SPIKE);

  //inisialisasi coin
  obstacle[4] = create_obstacle(600, 400, 30, 10, COINS);
  obstacle[5] = create_obstacle(300, 400, 30, 10, COINS);

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
   
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    if (obstacle[i]) {
        update_obstacle(obstacle[i], delta_time);
    } 
  }


  if (is_exit(&player->transform)) {
    change_level(current_level + 1);

    for (int i = 0; i < MAX_OBSTACLES; i++) {
        if (obstacle[i]) {
            destroy_obstacle(obstacle[i]);  
            obstacle[i] = NULL;
        }
    }

    if (current_level == 1) {
        obstacle[0] = create_obstacle(300, 375, 30, 10, SAWS);
        obstacle[1] = create_obstacle(350, 400, 30, 10, COINS);
        obstacle[2] = create_obstacle(450, 385, 30, 10, SPIKE);
        obstacle[3] = create_obstacle(470, 400, 30, 10, COINS);
    } 
    else if (current_level == 2) {
        obstacle[0] = create_obstacle(200, 390, 30, 10, FAKE_COINS);
        obstacle[1] = create_obstacle(500, 129, 30, 10, SPIKE);
        obstacle[2] = create_obstacle(470, 390, 30, 10, COINS);
        obstacle[3] = create_obstacle(350, 420, 30, 10, COINS);

    } 
    else if (current_level == 3) {
        obstacle[0] = create_obstacle(400, 390, 30, 10, COINS);
        obstacle[1] = create_obstacle(470, 390, 30, 10, COINS);
        obstacle[2] = create_obstacle(300, 375, 30, 10, SAWS);
        obstacle[2] = create_obstacle(370, 375, 30, 10, SAWS); 
    } 
    else if  {
        obstacle[0] = create_obstacle(400, 442, 30, 10, SAWS);
    }

    initiate_player(player, 100, 300);
    if (current_level == 2) { initiate_player(player, 650, 100); }
    if (current_level == 3) { initiate_player(player, 70, 170); }
    if (current_level == 4) { initiate_player(player, 570, 70); }
    if (current_level == 5) { initiate_player(player, 50, 300); }
    if (current_level == 6) { initiate_player(player, 80, 300); }
    if (current_level == 7) { initiate_player(player, 650, 50); }
    if (current_level == 8) { initiate_player(player, 100, 70); }
    if (current_level == 9) { initiate_player(player, 75, 500); }
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

  for (int i = 0; i < MAX_OBSTACLES; i++) {
    if (obstacle[i]) {
        render_obstacle(renderer, obstacle[i]);  // ✅ Kirim pointer ke obstacle
    }
  }



  SDL_RenderPresent(renderer);
}

void stage0_cleanup()
{
  SDL_Log("Stage 0 State: Cleaned up");
  destroy_player(player);//
}
