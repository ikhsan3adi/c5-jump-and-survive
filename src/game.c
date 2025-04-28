#include <stdlib.h>

#include "game.h"

// main game instance
static Game game;

void initialize(const char *appname, const char *appversion, const char *appidentifier)
{
  SDL_SetAppMetadata(appname, appversion, appidentifier);

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
  {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    exit(2);
  }
}

void create_game_instance(const char *title, int width, int height)
{
  game.window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
  game.renderer = SDL_CreateRenderer(game.window, NULL);
  SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_BLEND);
}

Game *get_game_instance()
{
  if (!game.window)
  {
    SDL_Log("Game instance has not been initialized!, call `create_game_instance` first.");
  }
  return &game;
}

void skip_physics_frame()
{
  game.is_physics_paused = true;
}

void resume_physics()
{
  game.is_physics_paused = false;
}
