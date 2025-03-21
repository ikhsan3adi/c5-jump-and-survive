#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "game.h"
#include "game_state.h"
#include "menu_state.h"
#include "game_stat.h"
#include "SFX.h"
#include "ui.h"

Uint64 last_time;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  initialize("Jump & Survive", "1.0", "com.c5.jump-and-survive");

  create_game_instance("Jump & Survive", SCREEN_WIDTH, SCREEN_HEIGHT);

  init_audio();

  last_time = SDL_GetTicks();

  change_game_state(&menu_state);

  return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  if (event->type == SDL_EVENT_QUIT)
  {
    return SDL_APP_SUCCESS;
  }

  GameState *current_state = get_current_game_state();

  current_state->handle_input(event);

  return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
  Game *game = get_game_instance();

  // membuat delta time (waktu antara frame saat ini denga frame sebelumnya)
  Uint64 current_time = SDL_GetTicks();
  double delta_time;

  if (game->is_physics_paused)
  {
    delta_time = 0.0f;
    resume_physics();
  }
  else
  {
    delta_time = ((current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency());
  }

  last_time = current_time;

  SDL_Renderer *renderer = game->renderer;

  GameState *current_state = get_current_game_state();

  current_state->update(delta_time);
  current_state->render(renderer);
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  clean_up_ui();
  /* SDL will clean up the window/renderer for us. */
}