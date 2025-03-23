# Modul `UI`

**Pembuat:** [Helga Athifa Hidayat (241511077)](https://github.com/helga1406) & [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `ui.c` & `ui.h`

## Variabel dan Konstanta

### **PIXELIFYSANS_FONT**

```c
#define PIXELIFYSANS_FONT "assets/fonts/PixelifySans-Regular.ttf"
```

Konstanta string yang mendefinisikan path file font yang digunakan untuk teks piksel.

### **SIXTYFOURCONVERGENCE_FONT**

```c
#define SIXTYFOURCONVERGENCE_FONT "assets/fonts/SixtyfourConvergence-Regular.ttf"
```

Konstanta string yang mendefinisikan path file font yang digunakan untuk judul atau teks yang lebih besar.

### **sixtyfourconvergence_font**

```c
extern TTF_Font *sixtyfourconvergence_font;
```

Variabel global yang menyimpan pointer ke font yang dimuat dari file `SIXTYFOURCONVERGENCE_FONT`.

### **pixelify_font**

```c
extern TTF_Font *pixelify_font;
```

Variabel global yang menyimpan pointer ke font yang dimuat dari file `PIXELIFYSANS_FONT`.

---

## Penjelasan Setiap Fungsi

### **init_font**

```c title="ui.h"
void init_font();
```

Fungsi `init_font` menginisialisasi library SDL_ttf yang digunakan untuk rendering font. Kemudian, fungsi ini memuat dua file font yang ditentukan oleh konstanta `SIXTYFOURCONVERGENCE_FONT` dan `PIXELIFYSANS_FONT` dan menyimpan pointer ke font-font tersebut dalam variabel global `sixtyfourconvergence_font` dan `pixelify_font`. Jika inisialisasi SDL_ttf atau pemuatan font gagal, fungsi akan mencetak pesan error dan keluar dari program.

```c title="ui.c"
#include <SDL3/SDL_ttf.h>
#include "ui.h"

TTF_Font *sixtyfourconvergence_font;
TTF_Font *pixelify_font;

...

void init_font()
{
    if (!TTF_Init())
    {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        exit(1);
    }
    sixtyfourconvergence_font = TTF_OpenFont(SIXTYFOURCONVERGENCE_FONT, 36);
    ...
    pixelify_font = TTF_OpenFont(PIXELIFYSANS_FONT, 36);
    ...
}
```

---

### **render_text**

```c title="ui.h"
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, float scale, SDL_Color color);
```

Fungsi `render_text` menerima renderer SDL, font yang akan digunakan, teks yang akan dirender, posisi (x, y), skala, dan warna sebagai input. Fungsi ini membuat surface dari teks menggunakan font dan warna yang diberikan, kemudian membuat texture dari surface tersebut. Texture teks kemudian dirender ke layar pada posisi yang ditentukan dengan skala yang diberikan.

```c title="ui.c"
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, float scale, SDL_Color color)
{
    text_surface = TTF_RenderText_Solid(font, text, strlen(text), color);
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_FRect dest_rect = {x, y, (float)text_surface->w, (float)text_surface->h};
    SDL_SetRenderScale(renderer, scale, scale);
    SDL_RenderTexture(renderer, text_texture, NULL, &dest_rect);
    SDL_SetRenderScale(renderer, 1, 1);
    ...
}
```

---

### **render_game_ui**

```c title="ui.h"
void render_game_ui(SDL_Renderer *renderer, GameStat *stat);
```

Fungsi `render_game_ui` bertanggung jawab untuk menampilkan elemen-elemen antarmuka pengguna selama permainan berlangsung. Fungsi ini menerima renderer SDL dan pointer ke struktur `GameStat` sebagai input. Berdasarkan isi dari `GameStat`, fungsi ini akan menampilkan informasi seperti skor, level, atau health player di layar.

---

### **show_game_over_ui**

```c title="ui.h"
void show_game_over_ui(SDL_Renderer *renderer, GameStat stat);
```

Fungsi `show_game_over_ui` menampilkan layar "Game Over" kepada pemain. Fungsi ini menerima renderer SDL dan struktur `GameStat` sebagai input. Fungsi ini akan menampilkan teks "Game Over" dan juga skor akhir pemain, serta opsi untuk kembali ke menu utama.

---

### **show_pause_ui**

```c title="ui.h"
void show_pause_ui(SDL_Renderer *renderer);
```

Fungsi `show_pause_ui` menampilkan layar "Pause" ketika pemain menjeda permainan. Fungsi ini menerima renderer SDL sebagai input. Fungsi ini akan menampilkan teks "Paused" dan opsi untuk melanjutkan permainan atau kembali ke menu utama.

---

### **show_level_transition**

```c title="ui.h"
void show_level_transition(SDL_Renderer *renderer, int stage, int level);
```

Fungsi `show_level_transition` menampilkan layar transisi antar level. Fungsi ini menerima renderer SDL, nomor stage, dan nomor level berikutnya sebagai input. Fungsi ini akan menampilkan informasi tentang stage dan level yang akan datang.

---

### **show_stage_transition**

```c title="ui.h"
void show_stage_transition(SDL_Renderer *renderer, int stage);
```

Fungsi `show_stage_transition` menampilkan layar transisi antar stage. Fungsi ini menerima renderer SDL dan nomor stage berikutnya sebagai input. Fungsi ini akan menampilkan informasi tentang stage yang akan datang.

---

### **show_congratulations_ui**

```c title="ui.h"
void show_congratulations_ui(SDL_Renderer *renderer, GameStat stat);
```

Fungsi `show_congratulations_ui` menampilkan layar ucapan selamat ketika pemain telah menyelesaikan permainan. Fungsi ini menerima renderer SDL dan struktur `GameStat` sebagai input. Fungsi ini akan menampilkan teks "Congratulations" dan juga statistik akhir pemain.

---

### **clean_up_ui**

```c title="ui.h"
void clean_up_ui();
```

Fungsi `clean_up_ui` bertugas untuk membersihkan semua sumber daya yang telah dialokasikan oleh modul UI. Ini termasuk menutup font yang telah dimuat dan menghentikan library SDL_ttf.

```c title="ui.c"
void clean_up_ui()
{
    TTF_CloseFont(sixtyfourconvergence_font);
    TTF_CloseFont(pixelify_font);
    TTF_Quit();
}
```

---

## Interaksi dengan modul lain

Modul `ui` berinteraksi dengan beberapa modul lain dalam game:

* **Membuat Tampilan Menu dan Membuat Teks**
  
    Fungsi `render_text` digunakan untuk menampilkan teks pada tampilan game. Selain itu, `render_text` juga digunakan untuk menampilkan teks pada UI menu.

* **Stage state**

    Memanggil fungsi `show_stage_transition` dan `show_level_transition` untuk menampilkan UI transisi antar stage dan level. Selain itu,  fungsi `render_game_ui` juga digunakan untuk menampilkan UI game.

* **Modul game_stat**
  
    Digunakan untuk mendapatkan informasi statistik game yang akan ditampilkan oleh UI (misalnya, skor).

* **Modul level**
  
    Digunakan untuk mendapatkan informasi tentang level atau stage saat ini yang akan ditampilkan pada UI transisi.

* **Modul SFX**
  
    Digunakan untuk memutar musik kemenangan pada tampilan pause, game over dan congratulations.

* **Main program `main.c`**
  
    Digunakan untuk memuat dan memuat font yang digunakan dalam UI dan juga membersihkan resource yang digunakan oleh UI saat program berakhir.

---
