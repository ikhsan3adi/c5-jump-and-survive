#include "game.h"

// main game instance
static Game game;

void create_game_instance()
{
  game.window = SDL_CreateWindow("Game C5 Proyek 2", 600, 480, SDL_WINDOW_OPENGL);
  game.renderer = SDL_CreateRenderer(game.window, NULL);
}

Game *get_game_instance()
{
  if (!game.window)
  {
    create_game_instance();
  }
  return &game;
}