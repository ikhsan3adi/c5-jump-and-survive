# Modul `level`

**Pembuat:** [Hisyam Khaeru Umam (241511078)](https://github.com/Umeem26) & [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid)

**File:** `level.c` & `level.h`

## Struktur `level`

Modul `level` menggunakan struktur yang didefinisikan dalam file header lain:

* **`Transform`**: Didefinisikan dalam `transform.h`, digunakan untuk merepresentasikan posisi dan ukuran tile dalam level.
* **`Switch`** dan **`Switch_Obstacles`**: Didefinisikan dalam `obstacles.h`, digunakan untuk merepresentasikan elemen interaktif dalam level seperti tombol dan objek yang dipengaruhi oleh tombol.

```c title="level.h"
#include <SDL3/SDL.h>
#include "transform.h"
#include "obstacles.h"

// ... (definisi struct Switch dan Switch_Obstacles ada di obstacles.h)
```

---

## Variabel dan Konstanta

### **TILE_SIZE**

```c
#define TILE_SIZE 32
```

Konstanta yang mendefinisikan ukuran (lebar dan tinggi) setiap tile dalam pixel.

### **MAP_WIDTH**

```c
#define MAP_WIDTH 30
```

Konstanta yang mendefinisikan lebar peta level dalam jumlah tile.

### **MAP_HEIGHT**

```c
#define MAP_HEIGHT 20
```

Konstanta yang mendefinisikan tinggi peta level dalam jumlah tile.

### **level0_map` ... `level10_map**

```c
extern short level0_map[MAP_HEIGHT][MAP_WIDTH];
extern short level1_map[MAP_HEIGHT][MAP_WIDTH];
extern short level2_map[MAP_HEIGHT][MAP_WIDTH];
extern short level3_map[MAP_HEIGHT][MAP_WIDTH];
extern short level4_map[MAP_HEIGHT][MAP_WIDTH];
...
extern short level10_map[MAP_HEIGHT][MAP_WIDTH];
```

Array 2D yang menyimpan data peta untuk masing-masing level (level 0 hingga level 10). Setiap elemen array merepresentasikan jenis tile pada posisi tertentu dalam peta.

### **current_level**

```c
extern int current_level;
```

Variabel integer yang menyimpan nomor level saat ini yang sedang dimainkan.

### **buttonL1` ... `buttonL103**

```c
extern Switch buttonL1;
extern Switch buttonL51;
extern Switch buttonL52;
extern Switch buttonL61;
extern Switch buttonL62;
extern Switch_Obstacles buttonL7;
extern Switch_Obstacles buttonL81;
extern Switch buttonL82;
extern Switch_Obstacles buttonL91;
extern Switch_Obstacles buttonL92;
extern Switch_Obstacles buttonL101;
extern Switch buttonL102;
extern Switch_Obstacles buttonL103;
```

Variabel-variabel global yang merupakan instance dari struct `Switch` dan `Switch_Obstacles`. Ini merepresentasikan status dan konfigurasi dari tombol-tombol dan objek terkait dalam berbagai level. Nama variabel menunjukkan level tempat tombol tersebut berada (misalnya, `buttonL1` untuk tombol di level 1).

### **current_level_map**

```c
extern short current_level_map[MAP_HEIGHT][MAP_WIDTH];
```

Array 2D yang menyimpan data peta untuk level yang sedang aktif. Variabel ini akan menunjuk ke salah satu array peta level (`level0_map` hingga `level5_map`) berdasarkan nilai `current_level`.

---

## Penjelasan Setiap Fungsi

### **change_level**

```c title="level.h"
void change_level(int level);
```

Fungsi `change_level` digunakan untuk mengganti level permainan saat ini. Fungsi ini menerima nomor level baru sebagai input. Berdasarkan nomor level yang diberikan, fungsi ini akan mengupdate variabel global `current_level` dan menyalin data peta dari array peta level yang sesuai (`level0_map` hingga `level5_map`) ke dalam array `current_level_map`. Fungsi ini juga melakukan inisialisasi ulang status tombol-tombol level.

---

### **render_level**

```c title="level.h"
void render_level(SDL_Renderer *renderer);
```

Fungsi `render_level` bertanggung jawab untuk menggambar peta level saat ini ke layar. Fungsi ini menerima renderer SDL sebagai input. Fungsi ini akan melakukan iterasi melalui array `current_level_map` dan menggambar tile yang sesuai pada setiap posisi berdasarkan nilai dalam array. Fungsi ini juga akan memanggil fungsi-fungsi dari modul `obstacles` untuk menggambar elemen-elemen seperti koin, gerbang keluar, tombol, dan rintangan lainnya.

---

## Interaksi dengan modul lain

Modul `level` berinteraksi dengan modul lain sebagai berikut:

* **Modul `stage0_state` dan `stage1_state`:** Modul `level` sangat erat berinteraksi dengan state permainan. Fungsi `change_level` dipanggil dari state-state ini untuk memuat level yang berbeda berdasarkan progres game. Fungsi `render_level` juga dipanggil setiap frame dari state permainan untuk menampilkan level saat ini.
* **Modul `entity` (terutama `player`):** Modul `level` berinteraksi dengan entity pemain untuk:
    * **Deteksi Tabrakan:** State permainan akan menggunakan data peta dari `current_level_map` untuk mendeteksi tabrakan antara pemain dan tile-tile di level (misalnya, lantai, dinding, rintangan).
    * **Interaksi dengan Elemen Level:** State permainan akan memeriksa interaksi pemain dengan elemen-elemen level seperti koin (untuk menambah skor), gerbang keluar (untuk berpindah ke level berikutnya), dan tombol (untuk memicu perubahan pada level). Informasi tentang posisi dan jenis tile di `current_level_map` digunakan untuk menentukan interaksi ini.
* **Modul `obstacles`:** Modul `level` menggunakan fungsi-fungsi dari modul `obstacles` (seperti `draw_coin`, `draw_gate`, `draw_switch`, `draw_spike`, `draw_rotating_saw`) untuk menggambar elemen-elemen interaktif dan rintangan dalam level saat `render_level` dipanggil.

---
