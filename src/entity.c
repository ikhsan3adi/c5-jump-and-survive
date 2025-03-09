#include <stdlib.h>
#include "entity.h"
#include "level.h"

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
  Transform *collision = check_collision_all(&entity->transform, (Transform **)objects, object_count);

  if (collision)
  {
    entity->transform.x = old_x; // Batalkan gerakan horizontal
    entity->physics.velocity_x = 0;
  }

  // Cek collision dari atas/bawah (dengan entity lainnya)
  entity->transform.y += entity->physics.velocity_y * delta_time;
  collision = check_collision_all(&entity->transform, (Transform **)objects, object_count);

  if (collision)
  {
    if (entity->physics.velocity_y > 0)
    { // Jatuh ke bawah
      entity->transform.y = collision->y - entity->transform.h;
    }
    else
    { // Tabrakan dari atas
      entity->transform.y = collision->y + collision->h;
    }
    entity->physics.velocity_y = 0;
  }

  // Cek jika menginjak tile map / platform/obstacle
  bool solid = is_solid(&entity->transform);
  SDL_Log("is solid: %d", solid);
  if (solid)
  {
    entity->transform.y = old_y;
    entity->physics.velocity_y = 0;
  }

  // gesekan (mengurangi kecepatan horizontal jika tidak bergerak)
  entity->physics.velocity_x *= entity->physics.friction;
}

void destroy_entity(Entity *entity)
{
  free(entity);
}