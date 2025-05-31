# Modul `level`

**Pembuat:** [Hisyam Khaeru Umam (241511078)](https://github.com/Umeem26) & [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid)

**File:** `level.c` & `level.h`

## Struktur `LevelNode`

Struktur `LevelNode` menyimpan semua data yang diperlukan untuk mendefinisikan sebuah level dalam game.

```c title="level.h"
typedef struct LevelNode LevelNode;

struct LevelNode
{
  char name[32];
  char prev_name[32]; // name level sebelumnya
  char next_name[32]; // name level selanjutnya

  Vector player_spawn;

  SDL_Color foreground_color;
  SDL_Color background_color;

  char bg_image[32];
  char bg_music[32];

  Switch *switches;
  Switch_Obstacles *switch_obstacles;
  Saw *saws;

  int switches_count;
  int switch_obstacles_count;
  int saws_count;

  short map[MAP_HEIGHT][MAP_WIDTH];

  LevelNode *prev;
  LevelNode *next;
};
```

---

## Variabel dan Konstanta

### **TILE\_SIZE**

```c
#define TILE_SIZE 32
```

Konstanta yang mendefinisikan ukuran (lebar dan tinggi) setiap tile dalam pixel.

### **MAP\_WIDTH**

```c
#define MAP_WIDTH 30
```

Konstanta yang mendefinisikan lebar peta level dalam jumlah tile.

### **MAP\_HEIGHT**

```c
#define MAP_HEIGHT 20
```

Konstanta yang mendefinisikan tinggi peta level dalam jumlah tile.

### **level\_head**

```c
extern LevelNode *level_head;
```

Pointer ke node level paling depan (head) dari linked list level. Pointer ini tidak boleh berubah selama game berjalan.

### **current\_level**

```c
extern LevelNode *current_level;
```

Pointer ke node level yang sedang dimuat atau dimainkan saat ini. Pointer ini dapat berubah saat berpindah level.

### **current\_switches**

```c
extern Switch *current_switches;
```

Pointer ke array of `Switch` yang mewakili semua switch di level saat ini.

### **current\_switch\_obstacles**

```c
extern Switch_Obstacles *current_switch_obstacles;
```

Pointer ke array of `Switch_Obstacles` yang mewakili semua rintangan switch di level saat ini.

### **current\_switches\_count**

```c
extern int current_switches_count;
```

Jumlah switch di level saat ini.

### **current\_switch\_obstacles\_count**

```c
extern int current_switch_obstacles_count;
```

Jumlah rintangan switch di level saat ini.

### **current\_level\_map**

```c
extern short current_level_map[MAP_HEIGHT][MAP_WIDTH];
```

Array 2D yang menyimpan data peta untuk level yang sedang aktif.

-----

## Penjelasan Setiap Fungsi

### **load\_levels**

```c title="level.h"
void load_levels(const char *dir);
```

Fungsi ini memuat semua level dari file JSON di direktori yang ditentukan, membangun linked list level, dan mengatur level pertama sebagai level saat ini.

### **build\_level\_list\_from\_array**

```c title="level.h"
void build_level_list_from_array(LevelNode **head, LevelNode *levels[], int count);
```

Fungsi ini membangun linked list level dari array `LevelNode` yang diberikan.

### **goto\_level\_by\_name**

```c title="level.h"
void goto_level_by_name(LevelNode *head, const char *name);
```

Fungsi ini mengubah `current_level` ke level yang memiliki nama yang sesuai dengan `name`.

### **goto\_next\_level**

```c title="level.h"
void goto_next_level();
```

Fungsi ini mengubah `current_level` ke level berikutnya dalam linked list.

### **goto\_prev\_level**

```c title="level.h"
void goto_prev_level();
```

Fungsi ini mengubah `current_level` ke level sebelumnya dalam linked list.

### **change\_level**

```c title="level.h"
void change_level();
```

Fungsi `change_level` digunakan untuk mengganti level permainan saat ini. Fungsi ini menyalin data peta, switch, dan obstacle dari `current_level` ke variabel global yang sesuai dan melakukan inisialisasi ulang status tombol-tombol level.

### **render\_level**

```c title="level.h"
void render_level(SDL_Renderer *renderer);
```

Fungsi `render_level` bertanggung jawab untuk menggambar peta level saat ini ke layar. Fungsi ini akan melakukan iterasi melalui array `current_level_map` dan menggambar tile yang sesuai pada setiap posisi. Fungsi ini juga akan memanggil fungsi-fungsi dari modul `obstacles` untuk menggambar elemen-elemen seperti koin, gerbang keluar, tombol, dan rintangan lainnya.

### **clear\_level**

```c title="level.h"
void clear_level();
```

Fungsi ini membersihkan semua memori yang dialokasikan untuk level, termasuk node level, switch, switch obstacles, dan saws. Fungsi ini dipanggil saat game selesai atau keluar.

-----

## Interaksi dengan modul lain

Modul `level` berinteraksi dengan modul lain sebagai berikut:

  * **Modul `level_parser`**: Modul `level` menggunakan fungsi `load_json_levels` dari `level_parser` untuk memuat data level dari file JSON.
  * **Modul `entity` (terutama `player`):** Modul `level` berinteraksi dengan entity pemain untuk:
      * **Deteksi Tabrakan:** State permainan akan menggunakan data peta dari `current_level_map` untuk mendeteksi tabrakan antara pemain dan tile-tile di level (misalnya, lantai, dinding, rintangan).
      * **Interaksi dengan Elemen Level:** State permainan akan memeriksa interaksi pemain dengan elemen-elemen level seperti koin (untuk menambah skor), gerbang keluar (untuk berpindah ke level berikutnya), dan tombol (untuk memicu perubahan pada level). Informasi tentang posisi dan jenis tile di `current_level_map` digunakan untuk menentukan interaksi ini.
  * **Modul `obstacles`:** Modul `level` menggunakan fungsi-fungsi dari modul `obstacles` (seperti `draw_coin`, `draw_gate`, `draw_switch`, `draw_spike`, `draw_rotating_saw`) untuk menggambar elemen-elemen interaktif dan rintangan dalam level saat `render_level` dipanggil.
