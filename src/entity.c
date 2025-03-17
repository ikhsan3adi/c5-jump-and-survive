#include <stdlib.h>
#include <stdio.h>
#include "entity.h"
#include "level.h"

int solid_tiles[] = {
    PLATFORM,
    SOLID_OBSTACLE,
    // tambahin kalo ada
};

int destruct_tiles[] = {
  SAWS,
  SPIKE,
  FAKE_COINS
  // tambahin kalo ada
};

Entity *create_entity(double x, double y, double w, double h, SDL_Color color)
{
  Entity *e = (Entity *)malloc(sizeof(Entity));

  e->transform.x = x;
  e->transform.y = y;
  e->transform.w = w;
  e->transform.h = h;

  e->render.color = color;

  e->physics.velocity_x = 0;
  e->physics.velocity_y = 0;
  e->physics.gravity = 10000.0f;
  e->physics.speed = 1.0f;
  e->physics.friction = 1;

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
  // Simpan posisi sebelum update
  double old_x = entity->transform.x;
  double old_y = entity->transform.y;

  // Perbarui posisi berdasarkan velocity
  entity->transform.x += entity->physics.velocity_x * delta_time;

  // Cek collision dari samping (kiri/kanan)
  bool solid = is_solid(&entity->transform);

  if (solid)
  {
    entity->transform.x = old_x; // Batalkan gerakan horizontal
    entity->physics.velocity_x = 0;
  }

  // Cek collision dari atas/bawah (dengan entity lainnya)
  entity->transform.y += entity->physics.velocity_y * delta_time;
  solid = is_solid(&entity->transform);

  if (solid)
  {
    entity->transform.y = old_y;
    entity->physics.velocity_y = 0;
  }

  // gesekan (mengurangi kecepatan horizontal jika tidak bergerak)
  entity->physics.velocity_x *= entity->physics.friction;

  // test coin
  bool coin = is_coin(&entity->transform);
  if (coin)
  {
    printf("Kamu Menyentuh Koin");
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
  return transform->y + transform->h > TILE_SIZE * MAP_HEIGHT;
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
          return true;
        }
      }
    }
  }
  return false;
}