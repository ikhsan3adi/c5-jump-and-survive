#include <stdlib.h>
#include <SDL3/SDL.h>

#include "game.h"
#include "game_state.h"
#include "menu_state.h"
#include "game_stat.h"
#include "SFX.h"
#include "ui.h"
#include "level.h"

Uint64 last_time;

int main()
{
  Game *game = NULL;
  GameState *current_state = NULL;

  Uint64 current_time = 0;
  double delta_time; // delta_time dalam satuan detik

  initialize("Jump & Survive", "1.0", "com.c5.jump-and-survive");

  create_game_instance("Jump & Survive", SCREEN_WIDTH, SCREEN_HEIGHT);

  game = get_game_instance();

  // load assets (fonts, sfx)
  init_font();
  // init_audio();

  load_levels("assets/levels/");

  change_game_state(&menu_state);

  last_time = SDL_GetPerformanceCounter();

  while (!game->is_exit)
  {
    current_state = get_current_game_state();

    /** =========================== INPUT/EVENT HANDLING ============================= */

    if (SDL_PollEvent(game->event))
    {
      if (game->event->type == SDL_EVENT_QUIT)
      {
        game->is_exit = true;
        break;
      }

      current_state->handle_input(game->event);
    }

    /** ========================= GAME LOOP & UPDATE PHYSICS ========================= */

    // mendapatkan time/counter saat ini
    current_time = SDL_GetPerformanceCounter();

    if (game->is_physics_paused)
    {
      delta_time = 0.0f;
      resume_physics();
    }
    else
    {
      // membuat delta time (waktu antara frame saat ini denga frame sebelumnya)
      delta_time = (double)((current_time - last_time) / (double)SDL_GetPerformanceFrequency());
    }

    last_time = current_time;

    current_state->update(delta_time);

    /** =============================== RENDERING =================================== */

    current_state->render(game->renderer);
    SDL_RenderPresent(game->renderer);

    SDL_Delay(16); // Delay untuk mencapai ~60 FPS
  }

  /** ========== QUIT ========== */
  SDL_Log("Exiting game...");

  current_state->cleanup();

  exit_game(EXIT_SUCCESS);

  return 0;
}
