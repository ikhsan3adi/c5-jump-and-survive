# Modul `game_stat`

**Pembuat:** [Hanifidin Ibrahim (241511076)](https://github.com/Hanif13579)

**File:** `game_stat.c` & `game_stat.h`

## Struktur `GameStat`

```c title="game_stat.h"
typedef struct {
    int score;   // Skor pemain
    int lives;   // Jumlah nyawa pemain
    Uint32 start_time;
    Uint32 stop_time;
    Uint32 elapsed_time;
    Uint32 last_hit_time;
} GameStat;
```

Struktur `GameStat` menyimpan informasi statistik permainan, termasuk:

* `score`: Skor pemain saat ini.
* `lives`: Jumlah nyawa pemain yang tersisa.
* `start_time`: Waktu (dalam milisekon) saat timer permainan dimulai.
* `stop_time`: Waktu (dalam milisekon) saat timer permainan dihentikan.
* `elapsed_time`: Durasi waktu permainan yang telah berlalu (dalam milisekon).
* `last_hit_time`: Waktu (dalam milisekon) saat pemain terakhir kali terkena serangan.

---

## Variabel dan Konstanta

### **DEFAULT_LIVES**

```c
#define DEFAULT_LIVES 3  // Jumlah nyawa awal
```

Konstanta yang mendefinisikan jumlah nyawa awal pemain saat permainan dimulai.

### **game_stat**

```c
extern GameStat game_stat; // Variabel global untuk status game
```

Variabel global `game_stat` adalah instance dari struktur `GameStat` yang menyimpan status permainan saat ini. Variabel ini dapat diakses dan dimodifikasi oleh modul-modul lain dalam game.

### **SCORE_PER_COIN**

```c
#define SCORE_PER_COIN 10
```

Konstanta yang mendefinisikan jumlah skor yang ditambahkan ke `game_stat.score` setiap kali pemain mengumpulkan koin.

---

## Penjelasan Setiap Fungsi

### **init_game_stat**

```c title="game_stat.h"
void init_game_stat(GameStat *stat);
```

Fungsi `init_game_stat` digunakan untuk menginisialisasi struktur `GameStat` dengan nilai-nilai awal saat permainan dimulai atau direset. Fungsi ini menerima pointer ke struktur `GameStat` sebagai input dan mengatur `score` menjadi 0, `lives` menjadi nilai `DEFAULT_LIVES`, dan mengatur nilai awal untuk variabel waktu.

```c title="game_stat.c"
// Inisialisasi GameStat dengan jumlah nyawa awal dan waktu maksimal per level
void init_game_stat(GameStat *stat)
{
    stat->score = 0;             // score mulai dari 0
    stat->lives = DEFAULT_LIVES; // default nyawa (3)
    stat->start_time = 0;        // Timer juga
    stat->stop_time = 0;
    stat->elapsed_time = 0;
}
```

---

### **start_timer**

```c title="game_stat.h"
void start_timer(GameStat *stat);
```

Fungsi `start_timer` memulai atau mereset timer permainan dengan mencatat waktu saat ini menggunakan `SDL_GetTicks()` ke dalam variabel `start_time` pada struktur `GameStat`.

```c title="game_stat.c"
// Memulai atau mereset timer permainan
void start_timer(GameStat *stat)
{
    stat->start_time = SDL_GetTicks();
}
```

---

### **get_elapsed_time**

```c title="game_stat.h"
Uint32 get_elapsed_time(GameStat *stat);
```

Fungsi `get_elapsed_time` menghitung dan mengembalikan waktu yang telah berlalu sejak timer dimulai. Fungsi ini menghitung selisih antara waktu saat ini (`SDL_GetTicks()`) dan waktu mulai (`stat->start_time`).

```c title="game_stat.c"
Uint32 get_elapsed_time(GameStat *stat)
{
    return SDL_GetTicks() - stat->start_time;
}
```

---

### **stop_timer**

```c title="game_stat.h"
void stop_timer(GameStat *stat);
```

Fungsi `stop_timer` menghentikan timer permainan dengan mencatat waktu saat ini ke dalam variabel `stop_time` dan kemudian menghitung waktu yang telah berlalu menggunakan `get_elapsed_time`.

```c title="game_stat.c"
// Pause timer
void stop_timer(GameStat *stat)
{
    stat->stop_time = SDL_GetTicks();
    stat->elapsed_time = get_elapsed_time(stat);
}
```

---

### **add_score**

```c title="game_stat.h"
void add_score(GameStat *stat);
```

Fungsi `add_score` menambahkan sejumlah poin ke skor pemain. Jumlah poin yang ditambahkan ditentukan oleh konstanta `SCORE_PER_COIN`.

```c title="game_stat.c"
// Menambah skor berdasarkan multiplier
void add_score(GameStat *stat)
{
    stat->score += SCORE_PER_COIN;
}
```

---

### **reset_score**

```c title="game_stat.h"
void reset_score(GameStat *stat);
```

Fungsi `reset_score` mengatur kembali skor pemain menjadi nol.

```c title="game_stat.c"
// Mereset skor ke nol
void reset_score(GameStat *stat)
{
    stat->score = 0;
}
```

---

### **add_life**

```c title="game_stat.h"
void add_life(GameStat *stat);
```

Fungsi `add_life` menambahkan satu nyawa ke jumlah nyawa pemain saat ini, dengan batasan maksimum yang ditentukan oleh `DEFAULT_LIVES`.

```c title="game_stat.c"
// Menambah satu nyawa (dengan batas maksimum)
void add_life(GameStat *stat)
{
    if (stat->lives < DEFAULT_LIVES)
    {
        stat->lives++;
    }
}
```

---

### **sub_life**

```c title="game_stat.h"
bool sub_life(GameStat *stat);
```

Fungsi `sub_life` mengurangi satu nyawa dari jumlah nyawa pemain. Fungsi ini juga memeriksa apakah nyawa pemain telah habis. Jika nyawa menjadi nol, fungsi ini mengembalikan `false` (menandakan game over), jika tidak, mengembalikan `true`. Fungsi ini juga mencatat waktu terakhir kali pemain kehilangan nyawa untuk keperluan cooldown atau invincibility.

```c title="game_stat.c"
// Mengurangi satu nyawa dan mengecek game over
bool sub_life(GameStat *stat)
{
    Uint32 now = SDL_GetTicks();

    if (stat->lives > 0 && (now - stat->last_hit_time) > 1000)
    {
        stat->lives--;
        stat->last_hit_time = now;
        return stat->lives > 0;
    }
    return true;
}
```

---

## Interaksi dengan modul lain

Modul `game_stat` berinteraksi dengan modul lain sebagai berikut:

* **Modul `entity` / `player`:** Modul `entity` akan berinteraksi dengan `game_stat` untuk:
    * Mengurangi nyawa pemain menggunakan fungsi `sub_life` ketika pemain berada pada kondisi tertentu (misalnya, masuk ke void).
    * Menambah skor pemain menggunakan fungsi `add_score` ketika pemain mengumpulkan item koin.
    * Mendapatkan informasi tentang jumlah nyawa pemain saat ini untuk keperluan game over.
* **Modul `ui`:** Modul `ui` menggunakan informasi dari struktur `GameStat` (melalui variabel global `game_stat`) untuk menampilkan status permainan kepada pemain. Ini termasuk:
    * Menampilkan skor pemain saat ini menggunakan `game_stat.score` dalam UI game.
    * Menampilkan jumlah nyawa pemain saat ini menggunakan `game_stat.lives` dalam UI game.
    * Menampilkan skor akhir dan statistik lainnya pada layar "Game Over" dan "Congratulations" menggunakan data dari `game_stat`.

---
