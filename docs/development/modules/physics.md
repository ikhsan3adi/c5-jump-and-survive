# Modul `physics`

**Pembuat:** [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid)

**File:** `physics.c` & `physics.h`

## Struktur `Physics`

```c title="physics.h"
typedef struct
{
  double velocity_x; // Kecepatan horizontal
  double velocity_y; // Kecepatan vertikal
  float gravity;     // Skala gravitasi
  float speed;       // Kecepatan dasar
  float friction;    // Faktor gesekan
} Physics;
```

Struktur `Physics` menyimpan informasi yang berkaitan dengan fisika sebuah entity, termasuk:

* `velocity_x`: Kecepatan entity pada sumbu horizontal.
* `velocity_y`: Kecepatan entity pada sumbu vertikal.
* `gravity`: Skala faktor gravitasi yang diterapkan pada entity.
* `speed`: Kecepatan dasar pergerakan entity.
* `friction`: Faktor yang mempengaruhi pengurangan kecepatan entity akibat gesekan.

---

## Variabel dan Konstanta

### **GRAVITY**

```c
#define GRAVITY 15.9f
```

Konstanta yang mendefinisikan nilai dasar gravitasi yang akan diterapkan pada entity. Nilai ini kemudian dapat diskalakan oleh komponen `gravity` pada struktur `Physics`.

---

## Penjelasan Setiap Fungsi

### **apply_gravity**

```c title="physics.h"
void apply_gravity(Physics *physics, float delta_time);
```

Fungsi `apply_gravity` menerapkan gaya gravitasi pada komponen fisika sebuah entity. Fungsi ini menerima pointer ke struktur `Physics` dan `delta_time` (waktu yang berlalu sejak frame terakhir) sebagai input. Fungsi ini memperbarui `velocity_y` berdasarkan nilai `GRAVITY`, `physics->gravity`, dan `delta_time`.

```c title="physics.c"
#include "physics.h"
#include "game_stat.h"
#include "sfx.h"
#include "player.h"
#include "level.h"
#include <stdlib.h>

#define GRAVITY 15.9f

void apply_gravity(Physics *physics, float delta_time)
{
  physics->velocity_y += GRAVITY * physics->gravity * delta_time;
}
```

---

### **check_collision**

```c title="physics.h"
int check_collision(Transform a, Transform b);
```

Fungsi `check_collision` melakukan deteksi tabrakan antara dua bounding box yang sejajar dengan sumbu (Axis-Aligned Bounding Box atau AABB). Fungsi ini menerima dua struktur `Transform` (yang memiliki anggota `x`, `y`, `w`, dan `h` untuk posisi dan dimensi) sebagai input. Fungsi ini mengembalikan nilai bukan nol (true) jika kedua bounding box bertabrakan, dan nol (false) jika tidak.

```c title="physics.c"
int check_collision(Transform a, Transform b)
{
  return (a.x < b.x + b.w &&
          a.x + a.w > b.x &&
          a.y < b.y + b.h &&
          a.y + a.h > b.y);
}
```

---

### **check_collision_all**

```c title="physics.h"
Transform *check_collision_all(Transform *entity, Transform *objects, int object_count);
```

Fungsi `check_collision_all` memeriksa apakah sebuah entity (direpresentasikan oleh `Transform`) bertabrakan dengan salah satu objek dalam array `objects`. Fungsi ini menerima pointer ke `Transform` entity, array pointer ke `Transform` objek-objek lain, dan jumlah objek dalam array. Fungsi ini mengembalikan pointer ke `Transform` objek pertama yang bertabrakan dengan entity, atau `NULL` jika tidak ada tabrakan.

```c title="physics.c"
Transform *check_collision_all(Transform *entity, Transform *objects, int object_count)
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
```

---

### **handle_saw_collision**

```c title="physics.h"
void handle_saw_collision(Transform saw_transform, Transform player_transform);
```

Fungsi `handle_saw_collision` secara spesifik menangani tabrakan antara gergaji (saw) dan pemain. Fungsi ini menerima `Transform` dari gergaji dan `Transform` dari pemain sebagai input. Jika terjadi tabrakan (menggunakan fungsi `check_collision`), fungsi ini akan memutar efek suara kematian (`dead_sfx`), mengurangi nyawa pemain menggunakan fungsi `sub_life` dari modul `game_stat`, dan mengatur ulang posisi pemain ke posisi awal level saat ini menggunakan fungsi `reinitiate_player` dari modul `player`.

```c title="physics.c"
void handle_saw_collision(Transform saw_transform, Transform player_transform)
{
  if (check_collision(saw_transform, player_transform))
  {
    play_sound(dead_sfx, 4, 0);
    sub_life(&game_stat);
    reinitiate_player(player, current_level);
  }
}
```

---

## Interaksi dengan modul lain

Modul `physics` berinteraksi dengan modul lain sebagai berikut:

* **Modul `entity`:** Modul `physics` bekerja dengan komponen `Physics` dan `Transform` yang merupakan bagian dari struktur `Entity` (meskipun definisi eksplisit `Entity` tidak diberikan dalam file ini). Fungsi `apply_gravity` menerima pointer ke `Physics` component, dan fungsi-fungsi deteksi tabrakan (`check_collision` dan `check_collision_all`) menerima dan mengembalikan pointer ke `Transform` components.
* **Modul `game_stat`:** Fungsi `handle_saw_collision` memanggil fungsi `sub_life` dari modul `game_stat` untuk mengurangi jumlah nyawa pemain ketika pemain bertabrakan dengan gergaji.
* **Modul `sfx`:** Fungsi `handle_saw_collision` memanggil fungsi `play_sound` dari modul `sfx` untuk memainkan efek suara kematian ketika pemain bertabrakan dengan gergaji.
* **Modul `player`:** Fungsi `handle_saw_collision` memanggil fungsi `reinitiate_player` dari modul `player` untuk mengatur ulang posisi pemain setelah bertabrakan dengan gergaji.
* **Modul `level`:** Fungsi `handle_saw_collision` mengakses variabel global `current_level` dari modul `level` untuk menentukan posisi awal pemain saat di-reinisialisasi. Modul `physics` juga berinteraksi dengan modul `level` untuk mendapatkan informasi tentang objek-objek level yang perlu diperiksa tabrakan dengan pemain (misalnya, melalui fungsi `check_collision_all`).

---
