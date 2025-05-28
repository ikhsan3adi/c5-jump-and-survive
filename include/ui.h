#ifndef UI_H
#define UI_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

#include "game_stat.h"
#include "leaderboard.h"

#define PIXELIFYSANS_FONT "assets/fonts/PixelifySans-Regular.ttf"
#define SIXTYFOURCONVERGENCE_FONT "assets/fonts/SixtyfourConvergence-Regular.ttf"

extern TTF_Font *sixtyfourconvergence_font;
extern TTF_Font *pixelify_font;
extern SDL_Window *window;

void init_font();

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, float scale, SDL_Color color);

void render_game_ui(SDL_Renderer *renderer, GameStat *stat);

bool show_input_player_name(SDL_Window *window,SDL_Renderer *renderer, TTF_Font *font, GameStat *stat);

void show_game_over_ui(SDL_Renderer *renderer, GameStat stat);

void show_pause_ui(SDL_Renderer *renderer);

/**
 * @param stage next level's stage
 * @param level next level
 */
void show_level_transition(SDL_Renderer *renderer, int stage, int level);

void show_stage_transition(SDL_Renderer *renderer, int stage);

void show_leaderboard_ui(SDL_Renderer *renderer, LeaderboardNode *head);

void show_congratulations_ui(SDL_Renderer *renderer, GameStat stat);

void clean_up_ui();

#endif