#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SDL3/SDL.h>
#include "game_state.h"

// Deklarasi menu_state agar bisa diakses di tempat lain
extern GameState menu_state;

// Deklarasi fungsi untuk lifecycle menu state
void menu_init();
void menu_handle_input(SDL_Event *);
void menu_update();
void menu_render(SDL_Renderer *);
void menu_cleanup();

#endif