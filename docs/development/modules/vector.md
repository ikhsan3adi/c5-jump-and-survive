# Modul `vector`

**Pembuat:** [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid)

**File:** `vector.h`

## Struktur `Vector`

```c title="vector.h"
typedef struct
{
    int y, x;
} Vector;
```

Struktur `Vector` merepresentasikan sebuah vektor 2D dengan komponen integer. Struktur ini memiliki anggota sebagai berikut:

* `y`: Komponen y (vertikal) dari vektor.
* `x`: Komponen x (horizontal) dari vektor.

---

## Interaksi dengan modul lain

* **Posisi 'Button' dan 'Switch'**

    Struktur `Vector` digunakan sebagai sebuah posisi untuk menentukan posisi beberapa *Obstacle*, salah satunya *Switch* dan *Button* dalam level.

    ```c title="level.c" hl_lines="1 11-21"
    Switch buttonL1;

    ...

    void change_level(int level)
    {
      switch (level)
      {
        case 1:
        memcpy(current_level_map,level1_map,sizeof(level1_map));
        buttonL1 = (Switch){
          .button = {13,6},
          .switches = {{13,7},{13,8},
                      {14,7},{14,8},
                      {15,7},{15,8},
                      {16,7},{16,8},
                      {17,7},{17,8},
                      {18,7},{18,8},
                      {19,7},{19,8},
          }
        };
        break;

      ...

      }

      ...
    }
    ```

---
