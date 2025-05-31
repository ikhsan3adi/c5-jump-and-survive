# Modul `entity`

**Pembuat:** [Hisyam Khaeru Umam (241511078)](https://github.com/Umeem26), [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid) & [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `entity.c` & `entity.h`

## Struktur `Entity`

### **EntityRenderComponent**

```c title="entity.h"
typedef struct
{
    SDL_Color color;
} EntityRenderComponent;
```

Struktur `EntityRenderComponent` menyimpan informasi yang berkaitan dengan rendering sebuah entity, saat ini hanya menyimpan `color` dari entity.

### **Entity**

```c title="entity.h"
typedef struct
{
    Transform transform;
    EntityRenderComponent render;
    Physics physics;
} Entity;
```

Struktur `Entity` adalah struktur utama yang merepresentasikan objek dalam game. Struktur ini terdiri dari:

* `transform`: Komponen `Transform` yang menyimpan informasi posisi (`x`, `y`) dan ukuran (`w`, `h`) entity.
* `render`: Komponen `EntityRenderComponent` yang menyimpan informasi rendering entity.
* `physics`: Komponen `Physics` yang menyimpan informasi fisika entity seperti kecepatan, gravitasi, dan gesekan.

---

## Variabel dan Konstanta

### Konstanta Tile Type

```c
#define EMPTY 0
#define PLATFORM 1
#define SOLID_OBSTACLE 2
#define SWITCH 3
#define COINS 4
#define SPIKE 5
#define LIFE 6
#define SAWS 7
#define FAKE_COINS 8
#define EXIT_GATE 9
#define BUTTON 10
```

Konstanta-konstanta ini mendefinisikan berbagai jenis tile yang dapat terdapat dalam peta level.

### **solid_tiles**

```c
extern int solid_tiles;
```

Array integer yang berisi daftar tipe-tipe tile yang dianggap solid dan akan menghalangi pergerakan entity.

### **destruct_tiles**

```c
extern int destruct_tiles;
```

Array integer yang berisi daftar tipe-tipe tile yang dianggap berbahaya atau dapat dihancurkan.

### **gate_tiles**

```c
extern Vector gate_tiles[10];
```

Array `Vector` (struct dengan anggota `x` dan `y` untuk koordinat) yang menyimpan posisi tile gerbang keluar. Ukuran array menunjukkan maksimum 10 tile gerbang.

### **num_gate_tiles**

```c
int num_gate_tiles = 0;
```

Variabel integer yang menyimpan jumlah tile gerbang keluar yang ditemukan dalam level saat ini.

### **saw_manager**

```c
extern SawManager saw_manager;
```

Variabel global yang merupakan struct atau pointer ke struct yang mengelola perilaku dan status dari semua gergaji (saws) dalam game. (Definisi `SawManager` tidak ada dalam file ini).

---

## Penjelasan Setiap Fungsi

### **create_entity**

```c title="entity.h"
Entity *create_entity(Transform transform, Physics physics, EntityRenderComponent render);
```

Fungsi `create_entity` mengalokasikan memori untuk sebuah `Entity` dan menginisialisasi komponen `transform`, `physics`, dan `render` dengan nilai yang diberikan. Fungsi ini menerima struct `Transform`, `Physics`, dan `EntityRenderComponent` sebagai input dan mengembalikan pointer ke `Entity` yang baru dibuat.

```c title="entity.c"
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

// ... (definisi array solid_tiles, destruct_tiles, gate_tiles)

Entity *create_entity(Transform transform, Physics physics, EntityRenderComponent render)
{
    Entity *e = (Entity *)malloc(sizeof(Entity));

    e->transform = transform;
    e->physics = physics;
    e->render = render;

    return e;
}
```

---

### **update_entity**

```c title="entity.h"
void update_entity(Entity *entity, float delta_time, Entity *objects, int object_count);
```

Fungsi `update_entity` memperbarui status sebuah entity setiap frame. Fungsi ini menerima pointer ke `Entity`, `delta_time` (waktu yang berlalu sejak frame terakhir), array pointer ke entity lain (`objects`), dan jumlah objek dalam array. Di dalam fungsi ini, gravitasi diterapkan pada entity dan kemudian fungsi `apply_entity_movement` dipanggil untuk menangani pergerakan dan tabrakan.

```c title="entity.c"
void update_entity(Entity *entity, float delta_time, Entity *objects, int object_count)
{
  // gravitasi
  apply_gravity(&entity->physics, delta_time);

  apply_entity_movement(entity, delta_time, objects, object_count);
}
```

---

### **apply_entity_movement**

```c title="entity.h"
void apply_entity_movement(Entity *entity, float delta_time, Entity *objects, int object_count);
```

Fungsi `apply_entity_movement` mengimplementasikan logika pergerakan entity. Fungsi ini menerima pointer ke `Entity`, `delta_time`, array pointer ke entity lain (`objects`), dan jumlah objek dalam array. Fungsi ini memperbarui posisi entity berdasarkan kecepatan horizontal dan vertikalnya, serta menangani deteksi dan respons terhadap tabrakan dengan objek lain (tile-tile solid).

---

### **destroy_entity**

```c title="entity.h"
void destroy_entity(Entity *entity);
```

Fungsi `destroy_entity` membebaskan memori yang dialokasikan untuk sebuah `Entity`. Fungsi ini menerima pointer ke `Entity` yang akan dihancurkan.

---

### **is_solid**

```c title="entity.h"
bool is_solid(Transform *transform);
```

Fungsi `is_solid` memeriksa apakah tile pada posisi yang diberikan (melalui `Transform`) termasuk dalam kategori tile solid berdasarkan array `solid_tiles`. Fungsi ini mengakses peta level (`current_level_map`) dan membandingkan tipe tile dengan daftar tile solid.

---

### **is_void**

```c title="entity.h"
bool is_void(Transform *transform);
```

Fungsi `is_void` memeriksa apakah tile pada posisi yang diberikan adalah tile kosong (`EMPTY`).

---

### **is_exit**

```c title="entity.h"
bool is_exit(Transform *transform);
```

Fungsi `is_exit` memeriksa apakah tile pada posisi yang diberikan adalah tile gerbang keluar (`EXIT_GATE`).

---

### **is_coin**

```c title="entity.h"
bool is_coin(Transform *transform);
```

Fungsi `is_coin` memeriksa apakah tile pada posisi yang diberikan adalah tile koin (`COINS`). Jika iya, fungsi ini juga akan mengganti tile tersebut menjadi kosong (`EMPTY`) pada peta level dan memainkan efek suara koin.

---

### **is_destruct**

```c title="entity.h"
bool is_destruct(Transform *transform);
```

Fungsi `is_destruct` memeriksa apakah tile pada posisi yang diberikan termasuk dalam kategori tile yang dapat dihancurkan berdasarkan array `destruct_tiles`. Jika iya, fungsi ini akan mengganti tile tersebut menjadi kosong (`EMPTY`) pada peta level.

---

### **is_button**

```c title="entity.h"
bool is_button(Transform *transform, Vector button);
```

Fungsi `is_button` memeriksa apakah tile pada posisi yang diberikan adalah tile tombol (`BUTTON`) dan sesuai dengan posisi tombol yang diberikan (`Vector button`).

---

### **interaction_buttons_switch**

```c title="entity.h"
void interaction_buttons_switch(Entity *player, Switch button);
```

Fungsi `interaction_buttons_switch` menangani interaksi antara pemain dan tombol jenis switch. Jika pemain berada di atas tombol dan tombol belum aktif (`is_on` adalah false), fungsi ini akan mengaktifkan tombol (`is_on` menjadi true) dan mengubah tile switch pada peta level menjadi kosong (`EMPTY`).

---

### **interaction_buttons_obstacles**

```c title="entity.h"
void interaction_buttons_obstacles(Entity *player, Switch_Obstacles button);
```

Fungsi `interaction_buttons_obstacles` menangani interaksi antara pemain dan tombol yang mengaktifkan/menonaktifkan rintangan. Jika pemain berada di atas tombol dan tombol belum aktif, fungsi ini akan mengaktifkan tombol dan mengubah tile rintangan pada peta level menjadi tile rintangan solid (`SOLID_OBSTACLE`).

---

### **has_coin_tiles**

```c title="entity.h"
bool has_coin_tiles();
```

Fungsi `has_coin_tiles` memeriksa apakah ada tile koin (`COINS`) yang tersisa di peta level saat ini. Fungsi ini melakukan iterasi melalui `current_level_map` dan mengembalikan `true` jika menemukan tile koin, dan `false` jika tidak

---

### **find_gate_tiles**

```c title="entity.h"
void find_gate_tiles();
```

Fungsi `find_gate_tiles` mencari semua tile gerbang keluar (`EXIT_GATE`) dalam peta level saat ini dan menyimpan posisinya dalam array `gate_tiles`. Fungsi ini juga mengupdate nilai `num_gate_tiles`.

---

## Interaksi dengan modul lain

Modul `entity` berinteraksi dengan modul lain sebagai berikut:

* **Modul `physics`:** Modul `entity` menggunakan struct `Physics` sebagai salah satu komponennya. Fungsi `update_entity` memanggil fungsi `apply_gravity` dari modul `physics`. Fungsi-fungsi deteksi tabrakan (`check_collision`) dari modul `physics` juga digunakan dalam `apply_entity_movement`.
* **Modul `transform`:** Modul `entity` menggunakan struct `Transform` sebagai komponen untuk menyimpan posisi dan ukuran entity.
* **Modul `game_stat`:** Modul `entity` berinteraksi dengan `game_stat` melalui fungsi `is_coin` yang akan menambah skor pemain (walaupun implementasinya tidak terlihat eksplisit di sini).
* **Modul `obstacles`:** Modul `entity` berinteraksi dengan `obstacles` melalui konstanta tile seperti `SAWS` dan melalui fungsi-fungsi spesifik untuk menangani interaksi dengan objek-objek level (walaupun detailnya tidak sepenuhnya terlihat).
* **Modul `player`:** Modul `entity` merepresentasikan semua objek dalam game, termasuk pemain. Fungsi-fungsi seperti `interaction_buttons_switch` dan `interaction_buttons_obstacles` secara spesifik menangani interaksi pemain dengan elemen level.
* **Modul `level`:** Modul `entity` sangat bergantung pada modul `level`. Fungsi-fungsi seperti `is_solid`, `is_void`, `is_exit`, `is_coin`, `is_destruct`, dan fungsi-fungsi interaksi tombol mengakses dan memodifikasi `current_level_map` dari modul `level`. Konstanta seperti `TILE_SIZE`, `MAP_WIDTH`, dan `MAP_HEIGHT` juga didefinisikan atau digunakan dari modul `level`.
* **Modul `vector`:** Modul `entity` menggunakan struct `Vector` untuk merepresentasikan posisi tile, terutama untuk `gate_tiles` dan dalam fungsi-fungsi interaksi tombol.
* **Modul `sfx`:** Fungsi `is_coin` memanggil `play_sound` dari modul `sfx` untuk memainkan efek suara saat koin dikumpulkan.
* **Modul `ui`:** Modul `ui` akan berinteraksi dengan modul `entity` untuk mendapatkan informasi tentang posisi dan tampilan entity (melalui komponen `transform` dan `render`) untuk keperluan rendering.

---
