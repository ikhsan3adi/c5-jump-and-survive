# Modul `stage1_state`

**Pembuat:** [Hisyam Khaeru Umam (241511078)](https://github.com/Umeem26) & [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid)

**File:** `stage1_state.c` & `stage1_state.h`

## Variabel dan Konstanta

### **stage1_state**

```c
GameState stage1_state = {
    .init = stage1_init,
    .handle_input = stage1_handle_input,
    .update = stage1_update,
    .render = stage1_render,
    .cleanup = stage1_cleanup,
};
```

Variabel global `stage1_state` bertipe `GameState`. Struktur ini mendefinisikan kumpulan fungsi (pointer fungsi) yang akan dipanggil pada saat state game ini aktif.

---

## Penjelasan Setiap Fungsi

### **stage1_init**

```c title="stage1_state.h"
void stage1_init();
```

Fungsi `stage1_init` dipanggil ketika game memasuki state `stage1_state`. Fungsi ini bertanggung jawab untuk inisialisasi stage 1, termasuk membuat player, memulai atau melanjutkan timer game, menambahkan nyawa pemain, menampilkan transisi stage, memainkan musik latar belakang stage 1, dan mengatur gergaji untuk level saat ini.

```c title="stage1_state.c"
void stage1_init()
{
  SDL_Log("Stage 1 State: Initialized");

  // Inisialisasi player
  player = create_player((Transform){100, 400, 32, 32}, 10000.0f, 1.0f, 1);

  if (game_stat.start_time == 0)
  {
    start_timer(&game_stat);
  }

  // tambah nyawa jika berhasil melewati stage 0
  add_life(&game_stat);

  SDL_Renderer *renderer = get_game_instance()->renderer;
  show_stage_transition(renderer, 1);

  if (stage1_bgm)
  {
    play_music(stage1_bgm, INT32_MAX);
  }

  ...
}
```

---

### **stage1_handle_input**

```c title="stage1_state.h"
void stage1_handle_input(SDL_Event *event);
```

Fungsi `stage1_handle_input` dipanggil setiap kali ada event input dari pengguna saat state `stage1_state` aktif. Fungsi ini menangani input pemain dan memungkinkan pemain untuk melakukan pause game dengan menekan tombol ESC.

```c title="stage1_state.c"
void stage1_handle_input(SDL_Event *event)
{
  handle_player_input(player, event);

  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    if (event->key.scancode == SDL_SCANCODE_ESCAPE)
    {
      stop_music();
      SDL_Renderer *renderer = get_game_instance()->renderer;
      show_pause_ui(renderer);
      play_music(stage1_bgm, INT32_MAX);
    }
  }
}
```

---

### **stage1_update**

```c title="stage1_state.h"
void stage1_update(double delta_time);
```

Fungsi `stage1_update` dipanggil setiap frame untuk memperbarui logika game dalam state `stage1_state`. Fungsi ini memperbarui posisi dan status player, waktu game, menangani transisi level, dan memeriksa kondisi game over.

```c title="stage1_state.c"
void stage1_update(double delta_time)
{
  update_entity(player, delta_time, NULL, 0);

  game_stat.elapsed_time = get_elapsed_time(&game_stat);

  if (is_exit(&player->transform))
  {
    SDL_Renderer *renderer = get_game_instance()->renderer;

    if (current_level == 10)
    {
      show_congratulations_ui(renderer, game_stat);
      initiate_player(player, 50, 50);
      return;
    }

    show_level_transition(renderer, 1, current_level);
    current_level++;
    change_level(current_level);
    cleanup_saw_manager(&saw_manager);
    setup_level_saws(current_level);

    // ... (kode implementasi untuk mengatur posisi awal player di berbagai level)
  }
}
```

---

### **stage1_render**

```c title="stage1_state.h"
void stage1_render(SDL_Renderer *renderer);
```

Fungsi `stage1_render` dipanggil setiap frame untuk merender tampilan game dalam state `stage1_state`. Fungsi ini membersihkan layar, merender level, merender player, dan menampilkan UI game.

```c title="stage1_state.c"
void stage1_render(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_level(renderer);
  render_player(renderer, player);
  render_game_ui(renderer, &game_stat);

  SDL_RenderPresent(renderer);
}
```

---

### **stage1_cleanup**

```c title="stage1_state.h"
void stage1_cleanup();
```

Fungsi `stage1_cleanup` dipanggil ketika state `stage1_state` akan diakhiri. Fungsi ini bertanggung jawab untuk membersihkan sumber daya yang digunakan oleh state ini, termasuk membersihkan saw manager.

```c title="stage1_state.c"
void stage1_cleanup()
{
  SDL_Log("Stage 1 State: Cleaned Up");
  cleanup_saw_manager(&saw_manager);
}
```

---

## Interaksi dengan modul lain

Modul `stage1_state` berinteraksi dengan modul lain sebagai berikut:

* **Modul `game`:** Menggunakan `get_game_instance()` untuk mendapatkan renderer.
* **Modul `game_stat`:** Menggunakan fungsi `start_timer`, `get_elapsed_time`, dan `add_life` untuk mengelola waktu dan nyawa pemain.
* **Modul `player`:** Menggunakan fungsi `create_player`, `handle_player_input`, `update_entity`, `render_player`, dan `initiate_player` untuk mengelola pemain.
* **Modul `level`:** Menggunakan fungsi `change_level` dan `render_level` untuk mengelola dan merender level.
* **Modul `SFX`:** Menggunakan fungsi `play_music` dan `stop_music` untuk mengelola musik latar belakang.
* **Modul `ui`:** Menggunakan fungsi `show_stage_transition`, `show_level_transition`, `show_pause_ui`, `render_game_ui`, dan `show_congratulations_ui` untuk menampilkan antarmuka pengguna.
* **Modul `obstacles`:** Menggunakan fungsi `cleanup_saw_manager` dan `setup_level_saws` untuk mengelola objek rintangan gergaji.

---
