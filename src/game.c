#include "game.h"

// main game instance
static Game game;

void initialize(const char *appname, const char *appversion, const char *appidentifier)
{
  SDL_SetAppMetadata("Jump & Survive", "1.0", "com.c5.jump-and-survive");

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    exit(2);
  }
}

void create_game_instance(const char *title, int width, int height)
{
  game.window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
  game.renderer = SDL_CreateRenderer(game.window, NULL);
}

Game *get_game_instance()
{
  if (!game.window)
  {
    SDL_Log("Game instance has not been initialized!, call `create_game_instance` first.");
  }
  return &game;
}