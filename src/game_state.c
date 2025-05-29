#include <stdlib.h>

#include "game_state.h"

GameState *current_state;

void change_game_state(GameState *new_state)
{
  if (current_state)
  {
    current_state->cleanup(); // clean up previous state
  }
  current_state = new_state;
  current_state->init(); // initialize new state
}

GameState *get_current_game_state()
{
  if (!current_state)
  {
    SDL_Log("`current_state` has not been initialized!, call `change_game_state` first.");
    exit(1);
  }

  return current_state;
}
