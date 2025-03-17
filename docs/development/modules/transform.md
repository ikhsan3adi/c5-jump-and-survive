# Modul `transform`

**Pembuat:** [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `transform.h`

## Struktur `Transform`

```c title="transform.h"
typedef struct
{
  double x, y, w, h;
} Transform;
```

Struktur `Transform` merepresentasikan posisi dan dimensi dari suatu objek dalam game. Struktur ini memiliki anggota sebagai berikut:

* `x`: Koordinat x (horizontal) dari objek (dalam satuan pixel).
* `y`: Koordinat y (vertikal) dari objek (dalam satuan pixel).
* `w`: Lebar (width) dari objek (dalam satuan pixel).
* `h`: Tinggi (height) dari objek (dalam satuan pixel).

## Interaksi dengan modul lain

Modul `transform` ini memiliki keterikatan yang erat dengan modul lain:

* **Bagian dari `Entity`**

    Struktur `Transform` digunakan sebagai salah satu anggota (subvariabel) di dalam struktur `Entity`. Contohnya, sebuah entity player akan memiliki variabel `Transform` untuk menentukan lokasinya di layar.

    ```c title="entity.h" hl_lines="3"
    typedef struct
    {
        Transform transform;
        EntityRenderComponent render;
        Physics physics;
    } Entity;
    ```

    Modul `transform` juga berinteraksi erat dengan logika fisika entity & player di modul `entity` & `physics`. Informasi posisi (`x`, `y`) dan ukuran (`w`, `h`) dari `Transform` digunakan untuk mengimplementasikan gravitasi (memperbarui posisi `y`) dan pergerakan player (memperbarui posisi `x` dan `y` berdasarkan input dan kecepatan).

* **Pengecekan collision dengan Tile Map**

    Informasi posisi dan ukuran dari struktur `Transform` digunakan di dalam modul `entity` dan `level` untuk melakukan pengecekan terhadap tile map. Ini penting untuk deteksi tabrakan antara objek game (yang memiliki komponen `Transform`) dengan tile map. Misalnya, untuk mencegah player berjalan menembus dinding atau platform.

    ```c title="entity.c" hl_lines="1 2-5"
    bool is_solid(Transform *transform) {
      int left = transform->x / TILE_SIZE;
      int right = (transform->x + transform->w - 1) / TILE_SIZE;
      int top = transform->y / TILE_SIZE;
      int bottom = (transform->y + transform->h - 1) / TILE_SIZE;

      for (int y = top; y <= bottom; y++) {
          for (int x = left; x <= right; x++) {
              if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
                  return false;
              }
              for (size_t i = 0; i < sizeof(solid_tiles) / sizeof(solid_tiles[0]); i++) {
                  if (current_level_map[y][x] == solid_tiles[i]) {
                      return true;
                  }
              }
          }
      }
      return false;
    }
    ```

---
