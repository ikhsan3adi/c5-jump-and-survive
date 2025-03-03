#include "physics.h"
#include <stdlib.h>

void apply_gravity(Physics *physics, float delta_time)
{
  physics->velocity_y += 9.8f * physics->gravity * delta_time;
}

int check_collision(Transform a, Transform b)
{
  return (a.x < b.x + b.w &&
          a.x + a.w > b.x &&
          a.y < b.y + b.h &&
          a.y + a.h > b.y);
}

Transform *check_collision_all(Transform *entity, Transform *objects[], int object_count)
{
  for (int i = 0; i < object_count; i++)
  {
    if (check_collision(*entity, *objects[i]))
    {
      return objects[i]; // Return objek pertama yang bertabrakan
    }
  }
  return NULL; // Tidak ada tabrakan
}
