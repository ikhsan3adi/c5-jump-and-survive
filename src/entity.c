#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "entity.h"
#include "player.h"
#include "level.h"
#include "vector.h"
#include "obstacles.h"
#include "SFX.h"
#include "ui.h"
#include "game.h"

int solid_tiles[] = {
    PLATFORM,
    SOLID_OBSTACLE,
    BUTTON,
    SWITCH};

int destruct_tiles[] = {
    SAWS,
    SPIKE,
    FAKE_COINS};

Vector gate_tiles[10];
int num_gate_tiles = 0;

Entity *create_entity(Transform transform, Physics physics, EntityRenderComponent render)
{
  Entity *e = (Entity *)malloc(sizeof(Entity));

  e->transform = transform;
  e->physics = physics;
  e->render = render;

  return e;
}

void update_entity(Entity *entity, float delta_time, Entity *objects[], int object_count)
{
  // gravitasi
  apply_gravity(&entity->physics, delta_time);

  apply_entity_movement(entity, delta_time, objects, object_count);
}

void apply_entity_movement(Entity *entity, float delta_time, Entity *objects[], int object_count)
{
  // Simpan Posisi Sebelum Update Entity
  double old_x = entity->transform.x;
  double old_y = entity->transform.y;

  // Update posisi berdasarkan veloxity x
  entity->transform.x += entity->physics.velocity_x * delta_time;

  // Cek tabrakan dengan object solid
  bool solid = is_solid(&entity->transform);
  if (solid)
  {
    // Menangani tabrakan horizontal
    entity->transform.x = old_x;
    entity->physics.velocity_x = 0;
  }

  // Update posisi berdasarkan veloxity y
  entity->transform.y += entity->physics.velocity_y * delta_time;
  solid = is_solid(&entity->transform);
  if (solid)
  {
    // Menangani tabrakan vertikal
    entity->transform.y = old_y;
    entity->physics.velocity_y = 0;
  }

  // Implementasi button di setiap level;
  int switch_size = current_switches_count;
  int obstacle_size = current_switch_obstacles_count;
  for (int i = 0; i < switch_size; i++)
  {
    interaction_buttons_switch(entity, current_switches[i]);
  }
  for (int i = 0; i < obstacle_size; i++)
  {
    interaction_buttons_obstacles_switch(entity, current_switch_obstacles[i]);
  }

  bool coin_status = has_coin_tiles();
  if (!coin_status)
  {
    restore_gate_tiles();
  }

  // Menerapkan gesekan
  entity->physics.velocity_x *= entity->physics.friction;

  // Cek sentuhan antara player dengan koin
  bool coin = is_coin(&entity->transform);
  if (coin)
  {
    add_score(&game_stat);
  }
  bool destruct = is_destruct(&entity->transform);
  if (destruct)
  {
    sub_life(&game_stat);
    reinitiate_player(entity, current_level->player_spawn);
  }
  bool hole = is_void(&entity->transform);
  if (hole)
  {
    play_sound(dead_sfx, 4, 0);
    sub_life(&game_stat);
    reinitiate_player(entity, current_level->player_spawn);
  }
}

void destroy_entity(Entity *entity)
{
  free(entity);
}

bool is_solid(Transform *transform)
{
  int left = transform->x / TILE_SIZE;
  int right = (transform->x + transform->w - 1) / TILE_SIZE;
  int top = transform->y / TILE_SIZE;
  int bottom = (transform->y + transform->h - 1) / TILE_SIZE;

  for (int y = top; y <= bottom; y++)
  {
    for (int x = left; x <= right; x++)
    {
      if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
      {
        return false;
      }
      for (size_t i = 0; i < sizeof(solid_tiles) / sizeof(solid_tiles[0]); i++)
      {
        if (current_level_map[y][x] == solid_tiles[i])
        {
          return true;
        }
      }
    }
  }
  return false;
}

bool is_void(Transform *transform)
{
  return transform->y + transform->h > TILE_SIZE * MAP_HEIGHT + TILE_SIZE;
}

bool is_exit(Transform *transform)
{
  int left = transform->x / TILE_SIZE;
  int right = (transform->x + transform->w - 1) / TILE_SIZE;
  int top = transform->y / TILE_SIZE;
  int bottom = (transform->y + transform->h - 1) / TILE_SIZE;

  for (int y = top; y <= bottom; y++)
  {
    for (int x = left; x <= right; x++)
    {
      if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
      {
        return false;
      }
      if (current_level_map[y][x] == EXIT_GATE)
      {
        return true;
      }
    }
  }
  return false;
}

bool is_coin(Transform *transform)
{
  int left = transform->x / TILE_SIZE;
  int right = (transform->x + transform->w - 1) / TILE_SIZE;
  int top = transform->y / TILE_SIZE;
  int bottom = (transform->y + transform->h - 1) / TILE_SIZE;

  for (int y = top; y <= bottom; y++)
  {
    for (int x = left; x <= right; x++)
    {
      if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
      {
        return false;
      }
      if (current_level_map[y][x] == COINS)
      {
        current_level_map[y][x] = EMPTY;
        play_sound(coin_sfx, 2, 0);
        return true;
      }
    }
  }
  return false;
}

bool is_destruct(Transform *transform)
{
  int left = transform->x / TILE_SIZE;
  int right = (transform->x + transform->w - 1) / TILE_SIZE;
  int top = transform->y / TILE_SIZE;
  int bottom = (transform->y + transform->h - 1) / TILE_SIZE;

  for (int y = top; y <= bottom; y++)
  {
    for (int x = left; x <= right; x++)
    {
      if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
      {
        return false;
      }
      for (size_t i = 0; i < sizeof(destruct_tiles) / sizeof(destruct_tiles[0]); i++)
      {
        if (current_level_map[y][x] == destruct_tiles[i])
        {
          if (destruct_tiles[i] == FAKE_COINS)
          {
            current_level_map[y][x] = EMPTY;
          }
          play_sound(dead_sfx, 4, 0);
          return true;
        }
      }
    }
  }
  return false;
}

bool is_button(Transform *transform, Vector buttons)
{
  int left = transform->x / TILE_SIZE;
  int right = (transform->x + transform->w - 1) / TILE_SIZE;
  int top = transform->y / TILE_SIZE;
  int bottom = (transform->y + transform->h - 1) / TILE_SIZE;

  for (int y = top; y <= bottom; y++)
  {
    for (int x = left; x <= right; x++)
    {
      if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
      {
        continue;
      }

      if (y + 1 == buttons.y && x == buttons.x)
      {
        return true;
      }
    }
  }

  return false;
}

void interaction_buttons_switch(Entity *player, Switch button)
{
  bool on_button = is_button(&player->transform, button.button);
  if (on_button)
  {
    for (int i = 0; i < sizeof(button.switches) / sizeof(Vector); i++)
    {
      if (button.switches[i].x > 0 && button.switches[i].x < MAP_WIDTH &&
          button.switches[i].y > 0 && button.switches[i].y < MAP_HEIGHT)
      {
        current_level_map[button.switches[i].y][button.switches[i].x] = EMPTY;
      }
    }
  }
}

void interaction_buttons_obstacles_switch(Entity *player, Switch_Obstacles button)
{
  bool on_button = is_button(&player->transform, button.button);
  if (on_button)
  {
    for (int i = 0; i < sizeof(button.switches) / sizeof(Vector); i++)
    {
      if (button.switches[i].x > 0 && button.switches[i].x < MAP_WIDTH &&
          button.switches[i].y > 0 && button.switches[i].y < MAP_HEIGHT)
      {
        current_level_map[button.switches[i].y][button.switches[i].x] = EMPTY;
      }
    }
    for (int i = 0; i < sizeof(button.obstacles) / sizeof(Vector); i++)
    {
      if (button.obstacles[i].x > 0 && button.obstacles[i].x < MAP_WIDTH &&
          button.obstacles[i].y > 0 && button.obstacles[i].y < MAP_HEIGHT)
      {
        current_level_map[button.obstacles[i].y][button.obstacles[i].x] = SOLID_OBSTACLE;
      }
    }
  }
}

bool has_coin_tiles()
{
  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      if (current_level_map[y][x] == 4)
      {
        return true;
      }
    }
  }
  return false;
}

void find_gate_tiles()
{
  num_gate_tiles = 0;
  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      if (current_level_map[y][x] == 9)
      {
        if (num_gate_tiles < 10)
        {
          gate_tiles[num_gate_tiles].y = y;
          gate_tiles[num_gate_tiles].x = x;
          num_gate_tiles++;
        }
      }
    }
  }
}

void hide_gate_tiles()
{
  bool status = has_coin_tiles();
  if (status)
  {
    for (int i = 0; i < num_gate_tiles; i++)
    {
      int y = gate_tiles[i].y;
      int x = gate_tiles[i].x;
      current_level_map[y][x] = 0;
    }
  }
}

void restore_gate_tiles()
{
  for (int i = 0; i < num_gate_tiles; i++)
  {
    int y = gate_tiles[i].y;
    int x = gate_tiles[i].x;
    current_level_map[y][x] = 9;
  }
}