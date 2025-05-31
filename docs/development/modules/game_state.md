# Modul `game_state`

**Pembuat:** [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `game_state.h` & `game_state.c`

## Struktur `GameState`

```c title="game_state.h"
typedef struct GameState
{
  void (*init)();
  void (*handle_input)(SDL_Event *);
  void (*update)(double delta_time);
  void (*render)(SDL_Renderer *);
  void (*cleanup)();
} GameState;
```

Struktur `GameState` mendefinisikan blueprint untuk berbagai state dalam game. Setiap state diimplementasikan sebagai sekumpulan fungsi yang menangani inisialisasi, input, pembaruan logika, rendering, dan pembersihan.:

* `init`: Fungsi untuk melakukan inisialisasi state.
* `handle_input`: Fungsi untuk menangani input dari pengguna.
* `update`: Fungsi untuk memperbarui logika game dengan parameter `delta_time` (waktu berlalu sejak frame terakhir).
* `render`: Fungsi untuk menggambar elemen-elemen game ke layar menggunakan `SDL_Renderer`.
* `cleanup`: Fungsi untuk membersihkan resource yang digunakan oleh state sebelum state diubah.

---

## Variabel dan Konstanta

### **current_state**

```c title="game_state.h"
GameState *current_state;
```

Variabel global `current_state` adalah pointer yang menunjuk ke state game yang sedang aktif. Variabel ini diubah menggunakan fungsi `change_game_state`.

---

## Penjelasan Setiap Fungsi

### **change_game_state**

```c title="game_state.h"
void change_game_state(GameState *new_state);
```

Fungsi `change_game_state` digunakan untuk mengubah state game saat ini. Fungsi ini menerima satu parameter: `new_state`, yang merupakan pointer ke struct `GameState` yang ingin diaktifkan. Ketika state baru diubah, fungsi ini akan melakukan langkah-langkah berikut:

1. Jika ada state saat ini (`current_state` tidak NULL), fungsi `cleanup` dari state saat ini akan dipanggil untuk membersihkan sumber daya yang mungkin digunakan.
2. Pointer `current_state` akan diubah untuk menunjuk ke `new_state`.
3. Fungsi `init` dari `new_state` akan dipanggil untuk melakukan inisialisasi state yang baru.

```c title="game_state.c"
void change_game_state(GameState *new_state)
{
  if (current_state)
  {
    current_state->cleanup(); // clean up previous state
  }
  current_state = new_state;
  current_state->init(); // initialize new state
}
```

---

### **get_current_game_state**

```c title="game_state.h"
GameState *get_current_game_state();
```

Fungsi `get_current_game_state` digunakan untuk mendapatkan pointer ke state game yang sedang aktif saat ini (`current_state`). Fungsi ini tidak menerima parameter dan mengembalikan pointer ke struct `GameState`. Sebelum memanggil fungsi ini, `change_game_state()` harus dipanggil setidaknya sekali untuk menginisialisasi `current_state`. Jika `current_state` belum diinisialisasi (masih NULL), fungsi akan mencetak pesan error ke log dan keluar dari program.

```c title="game_state.c"
GameState *get_current_game_state()
{
  if (!current_state)
  {
    SDL_Log("`current_state` has not been initialized!, call `change_game_state` first.");
    exit(1);
  }

  return current_state;
}
```

## Interaksi dengan modul lain

Modul `game_state` ini memiliki interaksi dengan modul lain sebagai berikut:

* **Implementasi State**

    Struktur `GameState` diimplementasikan secara konkret dalam modul-modul state spesifik seperti `menu_state`, `stage0_state`, dan `leaderboard_state`. Setiap modul ini akan mendefinisikan fungsi `init`, `handle_input`, `update`, `render`, dan `cleanup` sesuai dengan logika state masing-masing.

* **Pemanggilan `change_game_state`**

    Fungsi `change_game_state` dipanggil di `main.c` untuk mengatur state awal game (`menu_state`). Selain itu, fungsi ini juga dipanggil di dalam implementasi setiap state (`menu_state`, `stage0_state`, `leaderboard_state`) untuk melakukan transisi antar state berdasarkan kondisi tertentu dalam game.

    ```c title="main.c"
    change_game_state(&menu_state);
    ```

* **Pemanggilan `get_current_game_state()`**

    Di dalam game loop pada `main.c`, fungsi `get_current_game_state()` dipanggil untuk mendapatkan pointer ke state game yang sedang aktif (`current_state`). Pointer ini kemudian digunakan untuk memanggil fungsi-fungsi penting dari state saat ini, yaitu `update(delta_time)` untuk memperbarui logika game, `render(renderer)` untuk menggambar frame saat ini, dan `handle_input(event)` untuk memproses input dari pengguna.

    ```c title="main.c" hl_lines="1"
    GameState *current_state = get_current_game_state();
    current_state->update(delta_time);
    current_state->render(renderer);
    ```

---
