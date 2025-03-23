# Modul `menu_state`

**Pembuat:** [Helga Athifa Hidayat (241511077)](https://github.com/helga1406)

**File:** `menu_state.c` & `menu_state.h`

## Variabel dan Konstanta

### **menu_state**

```c title="menu_state.h"
// Deklarasi menu_state agar bisa diakses di tempat lain
extern GameState menu_state;
```

`menu_state` mengimplementasikan sebuah `GameState`. Tidak ada struktur khusus yang didefinisikan di header file ini selain deklarasi dari `menu_state` itu sendiri. Implementasi detail dari struktur `GameState` dapat dilihat pada definisi `menu_state` di file `menu_state.c`.

```c title="menu_state.c"
// Definisi state menu
GameState menu_state = {
    .init = menu_init,
    .handle_input = menu_handle_input,
    .update = menu_update,
    .render = menu_render,
    .cleanup = menu_cleanup,
};
```

---

## Penjelasan Setiap Fungsi

### **menu_init**

```c title="menu_state.h"
void menu_init();
```

Fungsi `menu_init` dipanggil ketika game memasuki state menu. Fungsi ini bertanggung jawab untuk melakukan inisialisasi yang diperlukan untuk menu, seperti:

* Mencetak pesan log yang menandakan inisialisasi state menu.
* Memulai pemutaran musik latar belakang menu menggunakan fungsi `play_music` dari modul `SFX`.
* Membuat entitas player pada posisi awal di layar menu.
* Mengubah level yang ditampilkan menjadi level 0.

```c title="menu_state.c"
void menu_init()
{
    SDL_Log("Menu State: Initialized");
    play_music(menu_bgm, INT32_MAX);

    player = create_entity(120, 416, 32, 32, (SDL_Color){0, 0, 0, 255});

    change_level(0);
}
```

---

### **menu_handle_input**

```c title="menu_state.h"
void menu_handle_input(SDL_Event *);
```

Fungsi `menu_handle_input` dipanggil ketika ada input dari pengguna (misalnya, keyboard atau mouse) saat game berada di state menu. Fungsi ini menerima pointer ke event SDL sebagai input. Fungsi ini akan menangani input untuk navigasi menu (atas/bawah untuk memilih opsi, enter untuk konfirmasi) dan aksi yang sesuai (misalnya, memulai game atau keluar dari aplikasi).

---

### **menu_update**

```c title="menu_state.h"
void menu_update(double delta_time);
```

Fungsi `menu_update` dipanggil setiap frame untuk memperbarui logika yang terkait dengan state menu. Saat ini, implementasi fungsi ini kosong, yang berarti tidak ada pembaruan logika khusus yang terjadi di menu.

---

### **menu_render**

```c title="menu_state.h"
void menu_render(SDL_Renderer *renderer);
```

Fungsi `menu_render` dipanggil setiap frame untuk menggambar elemen-elemen UI dari menu ke layar. Fungsi ini menerima pointer ke renderer SDL sebagai input. Fungsi ini akan menggambar latar belakang, judul game, tombol menu (Start Game, Exit), dan indikator pilihan menu saat ini.

```c title="menu_state.c"
void menu_render(SDL_Renderer *renderer)
{
    ...
    // level as background
    render_level(renderer);
    render_player(renderer, player);

    // overlay
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 120);
    SDL_RenderFillRect(renderer, &(SDL_FRect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

    render_text(renderer, sixtyfourconvergence_font, "JUMP & SURVIVE", 100, 80, 1.4, title_text_color);

    // Start button
    SDL_SetRenderDrawColor(renderer, start_button_color.r, start_button_color.g, start_button_color.b, 255);
    SDL_RenderFillRect(renderer, &start_button);
    render_text(renderer, pixelify_font, "Start Game", start_button.x + 45, start_button.y + 5, 1, start_text_color);

    // Exit button
    SDL_SetRenderDrawColor(renderer, exit_button_color.r, exit_button_color.g, exit_button_color.b, 255);
    SDL_RenderFillRect(renderer, &exit_button);
    render_text(renderer, pixelify_font, "Exit", exit_button.x + 120, exit_button.y + 5, 1, exit_text_color);

    SDL_RenderPresent(renderer);
}
```

---

### **menu_cleanup**

```c title="menu_state.h"
void menu_cleanup();
```

Fungsi `menu_cleanup` dipanggil ketika game keluar dari state menu. Fungsi ini bertanggung jawab untuk membersihkan sumber daya yang digunakan oleh menu, seperti menghentikan musik latar belakang menu.

```c title="menu_state.c"
void menu_cleanup()
{
    SDL_Log("Menu State: Cleanup");
    stop_music();
}
```

---

## Interaksi dengan modul lain

Modul `menu_state` memiliki interaksi dengan modul lain sebagai berikut:

* **`stage0_state`:** Ketika pemain memilih "Start Game" dari menu, fungsi `change_game_state` dipanggil untuk mengubah state game menjadi `stage0_state`.
* **`ui`:** Modul `ui` digunakan untuk merender teks dan elemen-elemen antarmuka pengguna di menu menggunakan fungsi seperti `render_text`.
* **`player`:** Modul `player` digunakan untuk membuat dan menampilkan entitas player di latar belakang menu.
* **`level`:** Modul `level` digunakan untuk mengubah level yang ditampilkan menjadi level 0 sebagai latar belakang.
* **`SFX`:** Modul `SFX` digunakan untuk memutar musik latar belakang menu menggunakan fungsi `play_music` dan menghentikannya menggunakan `stop_music` saat state menu diakhiri.

---
