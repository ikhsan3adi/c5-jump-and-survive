#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef struct GameState
{
  void (*init)();
  void (*handle_input)();
  void (*update)();
  void (*render)();
  void (*cleanup)();
} GameState;

// pointer to current state, call `change_state()` to switch between states
extern GameState *current_state;

// change `current_state`'s state to `new_state`
void change_state(GameState *new_state);

#endif