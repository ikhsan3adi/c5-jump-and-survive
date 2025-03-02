#include "game_state.h"

GameState *current_state;

void change_state(GameState *new_state)
{
  if (current_state)
  {
    current_state->cleanup(); // clean up previous state
  }
  current_state = new_state;
  current_state->init(); // initialize new state
}
