# Modul `player`

**Pembuat:** [Hisyam Khaeru Umam (241511078)](https://github.com/Umeem26), [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid) & [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `player.c` & `player.h`

## Struktur `player` (menggunakan struktur `Entity` dari modul `entity`)

```c title="player.h"
#include "entity.h"

extern Entity *player;
```

Modul `player` tidak mendefinisikan struktur baru, melainkan menggunakan struktur `Entity` yang didefinisikan di modul `entity`. Variabel global `player` adalah pointer ke instance `Entity` yang merepresentasikan pemain dalam game. Struktur `Entity` kemungkinan memiliki komponen seperti `Transform` untuk posisi dan ukuran, serta `Physics` untuk menangani pergerakan dan fisika.

---

## Variabel dan Konstanta

### **player**

```c
extern Entity *player;
```

Variabel global `player` adalah pointer ke instance `Entity` yang merepresentasikan pemain dalam game.

### **is_facing_right**

```c
extern bool is_facing_right;
```

Variabel global boolean yang menunjukkan arah hadap pemain (true jika menghadap kanan, false jika menghadap kiri).

### **key_state**

```c
extern bool key_state[SDL_SCANCODE_COUNT];
```

Array boolean yang menyimpan status tombol keyboard saat ini. Ini digunakan untuk menangani input pemain.

### **PLAYER_JUMP**

```c
#define PLAYER_JUMP -5000.0f
```

Konstanta yang mendefinisikan nilai gaya vertikal yang diterapkan saat pemain melompat. Nilai negatif menunjukkan arah ke atas.

### **PLAYER_MOVE_MULTIPLIER**

```c
#define PLAYER_MOVE_MULTIPLIER 2000.0f
```

Konstanta yang mendefinisikan faktor pengali untuk kecepatan pergerakan horizontal pemain.

---

## Penjelasan Setiap Fungsi

### **create_player**

```c title="player.h"
Entity *create_player(Transform transform, double gravity, double speed, double friction);
```

Fungsi `create_player` membuat dan menginisialisasi entity pemain. Fungsi ini menerima parameter `transform` (posisi dan ukuran awal), `gravity`, `speed`, dan `friction` untuk komponen fisika pemain. Fungsi ini mengalokasikan memori untuk entity pemain dan mengembalikan pointer ke entity yang baru dibuat.

```c title="player.c"
#include <stdlib.h>
#include <SDL3/SDL.h>
#include "player.h"
#include "level.h"
#include "SFX.h"
#include "entity.h"

Entity *player;

bool is_facing_right = true;

// array untuk menyimpan status tombol
bool key_state[SDL_SCANCODE_COUNT];

Entity *create_player(Transform transform, double gravity, double speed, double friction)
{
  Physics player_physics = {
      .velocity_x = 0,
      .velocity_y = 0,
      .gravity = gravity,
      .speed = speed,
      .friction = friction,
  };

  Entity *player = create_entity(transform, player_physics, (EntityRenderComponent){});

  return player;
}
```

---

### **initiate_player**

```c title="player.h"
void initiate_player(Entity *player, int x, int y);
```

Fungsi `initiate_player` digunakan untuk mengatur posisi awal pemain. Fungsi ini menerima pointer ke entity pemain dan koordinat x dan y sebagai input, lalu mengatur posisi `transform` dari entity pemain ke nilai yang diberikan.

```c title="player.c"
void initiate_player(Entity *player, int x, int y)
{
  player->transform.x = x;
  player->transform.y = y;
}
```

---

### **reinitiate_player**

```c title="player.h"
void reinitiate_player(Entity *player, int level);
```

Fungsi `reinitiate_player` digunakan untuk mengatur ulang posisi pemain berdasarkan level yang diberikan. Fungsi ini menerima pointer ke entity pemain dan nomor level sebagai input, lalu memanggil `initiate_player` dengan posisi awal yang berbeda-beda tergantung pada levelnya.

---

### **handle_player_input**

```c title="player.h"
void handle_player_input(Entity *player, SDL_Event *event);
```

Fungsi `handle_player_input` menangani input dari pemain. Fungsi ini menerima pointer ke entity pemain dan event SDL sebagai input. Berdasarkan event (tekanan tombol keyboard), fungsi ini akan memperbarui status `key_state` dan memicu aksi pemain seperti bergerak atau melompat.

---

### **destroy_player**

```c title="player.h"
void destroy_player(Entity *player);
```

Fungsi `destroy_player` bertanggung jawab untuk membersihkan dan membebaskan sumber daya yang terkait dengan entity pemain jika diperlukan.

---

### **render_player**

```c title="player.h"
void render_player(SDL_Renderer *renderer, Entity *player);
```

Fungsi `render_player` digunakan untuk menggambar representasi visual pemain ke layar. Fungsi ini menerima renderer SDL dan pointer ke entity pemain sebagai input. Fungsi ini akan menggunakan informasi posisi dan ukuran dari `player->transform` untuk menggambar sprite atau bentuk pemain.

---

## Interaksi dengan modul lain

Modul `player` berinteraksi dengan modul lain sebagai berikut:

* **Modul `entity`:** Modul `player` menggunakan struktur `Entity` yang didefinisikan dalam modul `entity` untuk merepresentasikan pemain. Ini termasuk penggunaan komponen `Transform` untuk posisi dan ukuran, serta `Physics` untuk pergerakan.
* **Modul `stage0_state`:** Modul player berinteraksi erat dengan state permainan (`stage0_state`). Input pemain yang ditangani oleh `handle_player_input` akan mempengaruhi pergerakan dan aksi pemain dalam game loop yang berjalan di state-state ini.
* **Modul `ui`:** Modul `ui` menggunakan fungsi `render_player` untuk menampilkan visual pemain di berbagai layar UI dan layar congratulations. Tampilan player juga digunakan di menu state sebagai elemen visual latar belakang.
* **Modul `level`:** Modul `level` berinteraksi dengan posisi pemain (`player->transform`) untuk deteksi tabrakan dengan tile map dan elemen-elemen level lainnya.
* **Modul `SFX`:** Modul `SFX` digunakan untuk memutar efek suara yang terkait dengan aksi pemain, seperti melompat (dipanggil dari dalam `handle_player_input` atau logika update pemain).

---
