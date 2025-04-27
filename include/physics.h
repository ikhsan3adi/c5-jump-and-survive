#ifndef PHYSICS_H
#define PHYSICS_H

#include "transform.h"

typedef struct
{
  double velocity_x; // Kecepatan horizontal
  double velocity_y; // Kecepatan vertikal
  float gravity;     // Gravitasi
  float speed;       // Kecepatan
  float friction;    // Gesekan
} Physics;

void apply_gravity(Physics *physics, float delta_time);

// AABB (Axis-Aligned Bounding Box) Collision Detection
int check_collision(Transform a, Transform b);

// Cek collision dengan semua objek dalam level
Transform *check_collision_all(Transform *entity, Transform *objects[], int object_count);

void handle_saw_collision(Transform saw_transform, Transform player_transform);

#endif