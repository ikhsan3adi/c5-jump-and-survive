#include <stdlib.h>

#include "level.h"
#include "level_parser.h"
#include "entity.h"
#include "player.h"
#include "obstacles.h"
#include "game.h"
#include "SFX.h"

#include <SDL3/SDL_image.h>
#include <SDL3/SDL_mixer.h>
#include <stdlib.h>

LevelNode *level_head = NULL;
LevelNode *current_level = NULL;
Switch *current_switches = NULL;
Switch_Obstacles *current_switch_obstacles = NULL;
int current_switches_count = 0;
int current_switch_obstacles_count = 0;

short current_level_map[MAP_HEIGHT][MAP_WIDTH];

SDL_Texture *current_bg_texture = NULL;

void load_levels(const char *dir)
{
  load_json_levels(&level_head, dir);
  current_level = level_head;
  change_level();
}

void change_level()
{
  if (!current_level)
  {
    SDL_Log("No current level set, cannot change level.");
    return;
  }

  free(current_switches);
  free(current_switch_obstacles);

  current_switches = malloc(sizeof(Switch) * current_level->switches_count);
  current_switch_obstacles = malloc(sizeof(Switch_Obstacles) * current_level->switch_obstacles_count);

  if (!current_switches || !current_switch_obstacles)
  {
    SDL_Log("Memory allocation failed for switches or switch obstacles.");
    return;
  }

  // bg image
  char dir[] = "assets/images/";
  char *img_path = malloc(sizeof(char) * (strlen(current_level->bg_image) + strlen(dir) + 1));
  strcpy(img_path, dir);
  strcat(img_path, current_level->bg_image);
  current_bg_texture = IMG_LoadTexture(get_game_instance()->renderer, img_path);

  // bg music
  char audio_dir[] = "assets/SFX/";
  char *audio_path = malloc(sizeof(char) * (strlen(current_level->bg_music) + strlen(audio_dir) + 1));
  strcpy(audio_path, audio_dir);
  strcat(audio_path, current_level->bg_music);
  current_bgm = load_music(audio_path);

  memcpy(current_level_map, current_level->map, sizeof(current_level->map));
  memcpy(current_switches, current_level->switches, sizeof(Switch) * current_level->switches_count);
  memcpy(current_switch_obstacles, current_level->switch_obstacles, sizeof(Switch_Obstacles) * current_level->switch_obstacles_count);

  current_switches_count = current_level->switches_count;
  current_switch_obstacles_count = current_level->switch_obstacles_count;

  find_gate_tiles();
  hide_gate_tiles();
}

void render_level(SDL_Renderer *renderer)
{
  bool gate_found = false;

  SDL_RenderTexture(renderer, current_bg_texture, NULL, NULL);

  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      SDL_FRect tile_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

      switch (current_level_map[y][x])
      {
      case PLATFORM:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        SDL_RenderFillRect(renderer, &tile_rect);
        break;
      case SOLID_OBSTACLE:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        SDL_RenderFillRect(renderer, &tile_rect);
        break;
      case SWITCH:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        SDL_RenderFillRect(renderer, &tile_rect);
        break;
      case COINS:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        draw_coin(renderer, tile_rect, COINS);
        break;
      case EXIT_GATE:
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &tile_rect);
        // render pinggiran gate 1 kali saja
        if (!gate_found)
        {
          // render gate untuk melapisi kotak putih
          draw_gate(renderer, tile_rect);
          gate_found = true;
        }
        break;
      case BUTTON:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        SDL_RenderFillRect(renderer, &tile_rect);
        break;
      case SAWS:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        draw_rotating_saw(renderer, tile_rect, SDL_GetTicks() / 2 % 360);
        break;
      case SPIKE:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        draw_triangle(renderer, tile_rect);
        break;
      case FAKE_COINS:
        SDL_SetRenderDrawColor(renderer, current_level->foreground_color.r, current_level->foreground_color.g, current_level->foreground_color.b, current_level->foreground_color.a);
        draw_coin(renderer, tile_rect, FAKE_COINS);
        break;
      default:
        break;
      }
    }
  }
}

void build_level_list_from_array(LevelNode **head, LevelNode *levels[], int count)
{
  // Step 1: Find the head (where prev == "")
  LevelNode *head_node = NULL;
  for (int i = 0; i < count; i++)
  {
    if (strlen(levels[i]->prev_name) == 0)
    {
      head_node = levels[i];
      break;
    }
  }

  if (!head_node)
    return; // Can't find head level

  *head = head_node;
  LevelNode *current = head_node;

  // Step 2: Link based on 'next'
  while (strlen(current->next_name) > 0)
  {
    LevelNode *next = NULL;
    for (int i = 0; i < count; i++)
    {
      if (strcmp(levels[i]->name, current->next_name) == 0)
      {
        next = levels[i];
        break;
      }
    }

    if (!next)
    {
      break; // broken chain
    }

    current->next = next;
    next->prev = current;
    current = next;
  }
}

void goto_level_by_name(LevelNode *head, const char *name)
{
  LevelNode *current = head;

  while (current != NULL)
  {
    if (strcmp(current->name, name) == 0)
    {
      current_level = current;
      return;
    }
    current = current->next;
  }

  change_level();
}

void goto_next_level()
{
  if (current_level->next == NULL)
  {
    SDL_Log("Already at the last level.");
    return;
  }
  current_level = current_level->next;
  change_level();
}

void goto_prev_level()
{
  if (current_level->prev == NULL)
  {
    SDL_Log("Already at the first level.");
    return;
  }
  current_level = current_level->prev;
  change_level();
}

void clear_level()
{
  LevelNode *current = level_head;
  LevelNode *next = NULL;
  while (current != NULL)
  {
    next = current->next;
    free(current->switches);
    free(current->switch_obstacles);
    free(current->saws);
    free(current);
    current = next;
  }
  level_head = NULL;

  memset(current_level_map, 0, sizeof(current_level_map));

  free(current_switches);
  free(current_switch_obstacles);

  current_switches = NULL;
  current_switch_obstacles = NULL;
  current_switches_count = 0;
  current_switch_obstacles_count = 0;
  current_level = NULL;

  SDL_Log("All levels cleared.");
}

int count_level_coins()
{
  int count = 0;
  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      if (current_level_map[y][x] == COINS)
      {
        count++;
      }
    }
  }
  return count;
}
