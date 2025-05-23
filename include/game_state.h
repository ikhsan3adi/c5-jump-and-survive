#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL3/SDL.h>

typedef struct GameState
{
  void (*init)();
  void (*handle_input)(SDL_Event *);
  void (*update)(double delta_time);
  void (*render)(SDL_Renderer *);
  void (*cleanup)();
} GameState;

// pointer to current state, call `change_game_state()` to switch between states
extern GameState *current_state;

// change `current_state`'s state to `new_state`
void change_game_state(GameState *new_state);

// get current `GameState` state
GameState *get_current_game_state();

#endif