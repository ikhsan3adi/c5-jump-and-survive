# Modul `game`

**Pembuat:** [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `game.c` & `game.h`

## Struktur `Game`

```c title="game.h"
typedef struct
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} Game;
```

Struktur `Game` menyimpan pointer ke window dan renderer SDL yang digunakan untuk menampilkan grafis game.

---

## Variabel dan Konstanta

### **game**

```c title="game.c"
static Game game;
```

Variabel global `game` adalah instance dari game, yang mencakup pembuatan window dan renderer SDL. Variabel ini dibuat menggunakan `static` untuk memastikan bahwa variabel hanya dapat di-_initialize_ satu kali saja.

---

## Penjelasan Setiap Fungsi

### **initialize()**

```c title="game.h"
void initialize(const char *appname, const char *appversion, const char *appidentifier);
```

Fungsi `initialize` digunakan untuk melakukan inisialisasi awal aplikasi game. Fungsi ini menerima tiga parameter string: `appname` (nama aplikasi), `appversion` (versi aplikasi), dan `appidentifier` (identifier unik aplikasi). Fungsi ini akan mengatur metadata aplikasi menggunakan `SDL_SetAppMetadata` dan menginisialisasi sistem SDL menggunakan `SDL_Init` dengan flag `SDL_INIT_VIDEO` untuk mengaktifkan subsistem video. Jika inisialisasi SDL gagal, fungsi akan mencetak pesan error ke log dan keluar dari program.

```c title="game.c"
void initialize(const char *appname, const char *appversion, const char *appidentifier)
{
  SDL_SetAppMetadata(appname, appversion, appidentifier);

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    exit(2);
  }
}
```

---

### **create_game_instance()**

```c title="game.h"
void create_game_instance(const char *title, int width, int height);
```

Fungsi `create_game_instance` bertanggung jawab untuk membuat instance dari game, yang mencakup pembuatan window dan renderer SDL. Fungsi ini menerima tiga parameter: `title` (judul window), `width` (lebar window), dan `height` (tinggi window). Window dibuat menggunakan `SDL_CreateWindow` dengan flag `SDL_WINDOW_OPENGL`, dan renderer dibuat untuk window tersebut menggunakan `SDL_CreateRenderer`. Instance `Game` disimpan dalam variabel statis global `game`.

```c title="game.c"
void create_game_instance(const char *title, int width, int height)
{
  game.window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
  game.renderer = SDL_CreateRenderer(game.window, NULL);
}
```

---

### **get_game_instance()**

```c title="game.h"
Game *get_game_instance();
```

Fungsi `get_game_instance` digunakan untuk mendapatkan pointer ke instance `Game` yang telah dibuat. Fungsi ini tidak menerima parameter dan mengembalikan pointer ke struct `Game`. Sebelum memanggil fungsi ini, `create_game_instance()` harus dipanggil terlebih dahulu. Jika `create_game_instance()` belum pernah dipanggil (yaitu, `game.window` masih NULL), fungsi akan mencetak pesan log.

```c title="game.c" hl_lines="5"
Game *get_game_instance()
{
  if (!game.window)
  {
    SDL_Log("Game instance has not been initialized!, call `create_game_instance` first.");
  }
  return &game;
}
```

## Interaksi dengan modul lain

Fungsi-fungsi yang didefinisikan dalam modul `game` ini (yaitu `initialize()`, `create_game_instance()`, dan `get_game_instance()`) dipanggil dari [`main.c` (main program)](./main.md) untuk melakukan inisialisasi SDL, membuat window dan renderer game untuk digunakan di bagian lain program, contohnya digunakan di fungsi render dari `game_state`

```c title="main.c" hl_lines="1 2 7"
  Game *game = get_game_instance();
  SDL_Renderer *renderer = game->renderer;

  GameState *current_state = get_current_game_state();

  current_state->update(delta_time);
  current_state->render(renderer);
```

---
