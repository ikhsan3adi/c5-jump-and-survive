# Modul `obstacles`

**Pembuat:** [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid) & [Hanifidin Ibrahim (241511076)](https://github.com/Hanif13579)

**File:** `obstacles.c` & `obstacles.h`

## Struktur `Switch`

```c title="obstacles.h"
typedef struct
{
    Vector button;
    Vector switches[100];

} Switch;
```

Struktur `Switch` digunakan untuk merepresentasikan sebuah tombol dalam level yang dapat mengaktifkan atau menonaktifkan elemen lain.

* `button`: Menyimpan posisi tombol sebagai `Vector`.
* `switches`: Array yang menyimpan posisi elemen-elemen (seperti platform) yang dipengaruhi oleh tombol ini.

---

## Struktur `Switch_Obstacles`

```c title="obstacles.h"
typedef struct
{
    Vector button;
    Vector switches[100];
    Vector obstacles[100];

} Switch_Obstacles;
```

Struktur `Switch_Obstacles` mirip dengan `Switch`, namun digunakan untuk tombol yang memengaruhi keberadaan rintangan.

* `button`: Menyimpan posisi tombol sebagai `Vector`.
* `switches`: Array yang menyimpan posisi elemen-elemen yang diaktifkan/dinonaktifkan.
* `obstacles`: Array yang menyimpan posisi rintangan yang muncul/hilang saat tombol ditekan.

---

## Struktur `Saw`

```c title="obstacles.h"
typedef struct {
    Transform transform;
    Physics physics;
} Saw;
```

Struktur `Saw` merepresentasikan objek gergaji sebagai rintangan bergerak.

* `transform`: Menyimpan informasi posisi (`x`, `y`), lebar (`w`), dan tinggi (`h`) gergaji menggunakan struct `Transform`.
* `physics`: Menyimpan informasi fisika gergaji seperti kecepatan horizontal dan vertikal menggunakan struct `Physics`.

---

## Struktur `SawManager`

```c title="obstacles.h"
typedef struct {
    Saw* saws[MAX_SAWS];
    int count;
} SawManager;
```

Struktur `SawManager` digunakan untuk mengelola banyak objek gergaji dalam satu level.

* `saws`: Array pointer ke struct `Saw`, menyimpan hingga `MAX_SAWS` objek gergaji.
* `count`: Menyimpan jumlah gergaji yang saat ini aktif dalam manager.

---

## Variabel dan Konstanta

### **saw_manager**

```c title="obstacles.h"
extern SawManager saw_manager;
```

Variabel global `saw_manager` bertipe `SawManager`. Variabel ini digunakan untuk menyimpan dan mengelola semua objek gergaji yang ada di level saat ini.

### **MAX_SAWS**

```c title="obstacles.h"
#define MAX_SAWS 20
```

Konstanta `MAX_SAWS` mendefinisikan jumlah maksimum gergaji yang dapat dikelola oleh `SawManager`.

### **PI**

```c title="obstacles.h"
#define PI 3.14159265
```

Konstanta `PI` mendefinisikan nilai pi yang digunakan dalam perhitungan, untuk rotasi gergaji.

---

## Penjelasan Setiap Fungsi

### **draw_rotating_saw**

```c title="obstacles.h"
void draw_rotating_saw(SDL_Renderer *renderer, SDL_FRect rect, float angle);
```

Fungsi `draw_rotating_saw` digunakan untuk menggambar objek gergaji yang berputar pada layar. Fungsi ini menerima renderer, persegi panjang posisi dan ukuran gergaji, serta sudut rotasi sebagai input.

### **draw_triangle**

```c title="obstacles.h"
void draw_triangle(SDL_Renderer *renderer, SDL_FRect rect);
```

Fungsi `draw_triangle` digunakan untuk menggambar segitiga, yang digunakan untuk merepresentasikan rintangan seperti spike (paku). Fungsi ini menerima renderer dan persegi panjang posisi dan ukuran segitiga sebagai input.

### **draw_coin**

```c title="obstacles.h"
void draw_coin(SDL_Renderer *renderer, SDL_FRect rect, int type);
```

Fungsi `draw_coin` digunakan untuk menggambar objek koin pada layar. Fungsi ini menerima renderer, persegi panjang posisi dan ukuran koin, serta tipe koin sebagai input.

### **draw_gate**

```c title="obstacles.h"
void draw_gate(SDL_Renderer *renderer, SDL_FRect exit_rect);
```

Fungsi `draw_gate` digunakan untuk menggambar gerbang keluar pada layar. Fungsi ini menerima renderer dan persegi panjang posisi dan ukuran gerbang sebagai input.

### **create_saw**

```c title="obstacles.h"
Saw *create_saw(float x, float y, float w, float h, float velocity_x, float velocity_y);
```

Fungsi `create_saw` digunakan untuk membuat objek gergaji baru. Fungsi ini menerima posisi `x` dan `y`, lebar `w`, tinggi `h`, serta kecepatan horizontal `velocity_x` dan vertikal `velocity_y` sebagai input dan mengembalikan pointer ke objek `Saw` yang baru dibuat.

### **update_saw**

```c title="obstacles.h"
void update_saw(Saw *saw, float delta_time);
```

Fungsi `update_saw` digunakan untuk memperbarui posisi objek gergaji berdasarkan kecepatannya dan waktu yang berlalu (`delta_time`). Fungsi ini menerima pointer ke objek `Saw` dan nilai `delta_time` sebagai input.

### **render_saw**

```c title="obstacles.h"
void render_saw(SDL_Renderer *renderer, Saw *saw, float angle);
```

Fungsi `render_saw` digunakan untuk merender (menggambar) objek gergaji pada layar. Fungsi ini menerima renderer, pointer ke objek `Saw`, dan sudut rotasi sebagai input.

### **init_saw_manager**

```c title="obstacles.h"
void init_saw_manager(SawManager* manager);
```

Fungsi `init_saw_manager` digunakan untuk menginisialisasi `SawManager`. Fungsi ini menerima pointer ke `SawManager` sebagai input dan mengatur nilai awal `count` menjadi 0.

### **add_saw**

```c title="obstacles.h"
void add_saw(SawManager* manager, float x, float y, float w, float h, float velocity_x, float velocity_y);
```

Fungsi `add_saw` digunakan untuk menambahkan objek gergaji baru ke dalam `SawManager`. Fungsi ini menerima pointer ke `SawManager`, posisi `x` dan `y`, lebar `w`, tinggi `h`, serta kecepatan horizontal `velocity_x` dan vertikal `velocity_y` sebagai input.

### **cleanup_saw_manager**

```c title="obstacles.h"
void cleanup_saw_manager(SawManager* manager);
```

Fungsi `cleanup_saw_manager` digunakan untuk membersihkan memori yang dialokasikan untuk objek-objek gergaji yang dikelola oleh `SawManager`. Fungsi ini menerima pointer ke `SawManager` sebagai input dan membebaskan memori yang digunakan oleh setiap `Saw` dalam array `saws`.

### **setup_level_saws**

```c title="obstacles.h"
void setup_level_saws(int level);
```

Fungsi `setup_level_saws` digunakan untuk mengatur posisi dan properti gergaji yang ada dalam level tertentu. Implementasi fungsi ini (terlihat di `obstacles.c`) menggunakan nilai `current_level` dari modul `level` untuk menentukan gergaji mana yang akan ditambahkan ke `saw_manager` untuk setiap level.

---

## Interaksi dengan modul lain

Modul `obstacles` berinteraksi dengan modul lain sebagai berikut:

* **Modul Vector:** Struktur `Switch` dan `Switch_Obstacles` menggunakan struct `Vector` dari modul `vector`.
* **Modul `stage0_state`:** Modul `obstacles` berinteraksi dengan `stage0_state` melalui fungsi `setup_level_saws`. Fungsi ini dipanggil dari `stage0_init` dan `stage0_update` untuk mengatur gergaji yang sesuai untuk level saat ini di stage 1.
* **Modul `level`:** Modul `obstacles` berinteraksi dengan `level` untuk mendapatkan informasi tentang level saat ini (`current_level`) dan ukuran tile (`TILE_SIZE`). Informasi ini digunakan dalam fungsi `setup_level_saws` untuk menentukan posisi dan konfigurasi gergaji. Selain itu, fungsi `draw_rotating_saw`, `draw_triangle`, `draw coin` dan `draw_gate` dari modul `obstacles` dipanggil oleh fungsi `render_level` dari modul `level` untuk menggambar gergaji pada level saat ini.

---
