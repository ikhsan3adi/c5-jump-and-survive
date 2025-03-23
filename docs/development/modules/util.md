# Modul `util`

**Pembuat:** [Hanifidin Ibrahim (241511076)](https://github.com/Hanif13579)

**File:** `util.c` & `util.h`

## Penjelasan Setiap Fungsi

### **get_time_string**

```c title="util.h"
char *get_time_string(unsigned int time);
```

Fungsi `get_time_string` menerima waktu dalam detik (unsigned integer) sebagai input dan mengembalikan string yang diformat untuk merepresentasikan waktu tersebut dalam format yang mudah dibaca (misalnya, "Xh Ym Zs", "Ym Zs", atau "Zs").

```c title="util.c"
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

char *get_time_string(unsigned int time) {
    // Alokasi memori untuk string waktu
    char *time_string = (char *)malloc(20 * sizeof(char));

    if (time_string == NULL) {
        return NULL; // Jika gagal mengalokasi memori
    }

    unsigned int hours = time / 3600;         // Menghitung jam
    unsigned int minutes = (time % 3600) / 60; // Menghitung menit
    unsigned int seconds = time % 60;       // Menghitung detik

    // Formatkan string berdasarkan waktu
    if (hours > 0) {
        sprintf(time_string, "%uh %um %us", hours, minutes, seconds);
    } else if (minutes > 0) {
        sprintf(time_string, "%um %us", minutes, seconds);
    } else {
        sprintf(time_string, "%us", seconds);
    }

    return time_string;
}
```

---

## Interaksi dengan modul lain

Modul `util` berinteraksi dengan modul `ui` untuk menampilkan informasi waktu yang telah berlalu pada layar "Game Over" dan "Congratulations". Secara spesifik:

* **Modul `ui`:** Fungsi `get_time_string` dari modul `util` dipanggil oleh fungsi-fungsi di modul `ui` (yaitu `show_game_over_ui` dan `show_congratulations_ui`) untuk memformat waktu yang telah berlalu (didapatkan dari modul `game_stat`) menjadi string yang dapat ditampilkan kepada pemain. Ini memungkinkan pemain untuk melihat berapa lama mereka bermain sebelum game berakhir atau berhasil diselesaikan.

---
