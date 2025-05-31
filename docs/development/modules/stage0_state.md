# Modul `stage0_state`

**Pembuat:** [Hisyam Khaeru Umam (241511078)](https://github.com/Umeem26), [Muhamad Syahid (241511081)](https://github.com/muhamadSyahid), [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi) & [Helga Athifa Hidayat (241511077)](https://github.com/helga1406)

**File:** `stage0_state.c` & `stage0_state.h`

## Variabel dan Konstanta

### **stage0_state**

```c
GameState stage0_state = {
    .init = stage0_init,
    .handle_input = stage0_handle_input,
    .update = stage0_update,
    .render = stage0_render,
    .cleanup = stage0_cleanup,
};
```

Variabel global `stage0_state` bertipe `GameState`. Struktur ini mendefinisikan kumpulan fungsi (pointer fungsi) yang akan dipanggil pada saat state game ini aktif. Fungsi-fungsi tersebut adalah `stage0_init` (inisialisasi state), `stage0_handle_input` (menangani input pengguna), `stage0_update` (memperbarui logika game), `stage0_render` (merender tampilan game), dan `stage0_cleanup` (membersihkan sumber daya yang digunakan oleh state).

---

## Penjelasan Setiap Fungsi

### **stage0_init**

```c title="stage0_state.h"
void stage0_init();
```

Fungsi `stage0_init` dipanggil ketika game memasuki state `stage0_state`. Fungsi ini bertanggung jawab untuk melakukan inisialisasi yang diperlukan untuk stage 0, termasuk:

* Mencetak log ke konsol bahwa state telah diinisialisasi.
* Membuat instance player menggunakan fungsi `create_player`.
* Memulai timer game menggunakan fungsi `start_timer` dari modul `game_stat`.
* Mendapatkan renderer dari instance game dan menampilkan UI transisi stage menggunakan fungsi `show_stage_transition`.
* Memainkan musik latar belakang untuk stage 0 menggunakan fungsi `play_music` dari modul `sfx`.
* Mengubah level game menjadi level 0 menggunakan fungsi `change_level` dari modul `level`.

```c title="stage0_state.c"
void stage0_init();
```

---

### **stage0_handle_input**

```c title="stage0_state.h"
void stage0_handle_input(SDL_Event *event);
```

Fungsi `stage0_handle_input` dipanggil setiap kali ada event input dari pengguna saat state `stage0_state` aktif. Fungsi ini bertanggung jawab untuk:

* Meneruskan event ke fungsi `handle_player_input` dari modul `player` untuk menangani input yang berkaitan dengan pemain.
* Memeriksa apakah tombol ESC ditekan. Jika ya, fungsi ini akan menghentikan musik, mendapatkan renderer, menampilkan UI pause menggunakan fungsi `show_pause_ui` dari modul `ui`, dan kemudian melanjutkan kembali musik latar belakang.

---

### **stage0_update**

```c title="stage0_state.h"
void stage0_update(double delta_time);
```

Fungsi `stage0_update` dipanggil setiap frame untuk memperbarui logika game dalam state `stage0_state`. Fungsi ini melakukan:

* Memperbarui posisi dan status player menggunakan fungsi `update_entity` dari modul `entity`.
* Memperbarui waktu yang telah berlalu dalam game menggunakan fungsi `get_elapsed_time` dari modul `game_stat`.
* Memeriksa apakah player telah mencapai pintu keluar level menggunakan fungsi `is_exit` dari modul `entity`. Jika ya, fungsi ini akan:
    * Mendapatkan renderer.
    * Menampilkan UI transisi level menggunakan fungsi `show_level_transition` dari modul `ui`.
    * Menaikkan nilai `current_level`.
    * Mengubah level game ke level berikutnya menggunakan fungsi `change_level`.
    * Menginisialisasi ulang posisi player berdasarkan level saat ini menggunakan fungsi `initiate_player` dari modul `player`.
* Memeriksa kondisi game over (belum ada implementasi spesifik dalam snippet ini, tetapi biasanya akan melibatkan pengecekan nyawa atau kondisi kegagalan lainnya). Jika game over, state game akan diubah ke state lain (`gameover_state`).

---

### **stage0_render**

```c title="stage0_state.h"
void stage0_render(SDL_Renderer *renderer);
```

Fungsi `stage0_render` dipanggil setiap frame untuk merender tampilan game dalam state `stage0_state`. Fungsi ini bertanggung jawab untuk:

* Membersihkan layar renderer.
* Merender level saat ini menggunakan fungsi `render_level` dari modul `level`.
* Merender player menggunakan fungsi `render_player` dari modul `player`.
* Memperbarui tampilan pada layar.

---

### **stage0_cleanup**

```c title="stage0_state.h"
void stage0_cleanup();
```

Fungsi `stage0_cleanup` dipanggil ketika state `stage0_state` akan diakhiri atau diganti dengan state lain. Fungsi ini bertanggung jawab untuk membersihkan sumber daya yang digunakan oleh state ini, meskipun dalam snippet ini implementasinya kosong.

```c title="stage0_state.c"
void stage0_cleanup()
{
  SDL_Log("Stage 0 State: Cleaned Up");
}
```

---

## Interaksi dengan modul lain

Modul `stage0_state` berinteraksi dengan modul lain sebagai berikut:

* **Modul `game`:** Modul `stage0_state` menggunakan fungsi `get_game_instance()` untuk mendapatkan pointer ke struct `Game` dan mengakses renderer.
* **Modul `game_state`:** Modul `stage0_state` menggunakan fungsi `change_game_state()` untuk mengubah state game ke state lain, seperti `menu_state`.
* **Modul `player`:** Modul `stage0_state` menggunakan fungsi `create_player` untuk membuat player, `handle_player_input` untuk menangani input player, `update_entity` untuk memperbarui status player, `render_player` untuk merender player, dan `initiate_player` serta `reinitiate_player` untuk mengatur posisi awal player.
* **Modul `level`:** Modul `stage0_state` menggunakan fungsi `change_level` untuk mengubah level yang sedang dimainkan dan `render_level` untuk merender level.
* **Modul `obstacles`:** Meskipun tidak ada interaksi eksplisit yang terlihat dalam snippet, ada interaksi melalui modul `level` dalam hal penanganan rintangan di dalam level.
* **Modul `entity`:** Modul `stage0_state` menggunakan fungsi `update_entity` untuk memperbarui entitas player dan fungsi `is_exit` untuk memeriksa apakah player telah mencapai pintu keluar.
* **Modul `game_stat`:** Modul `stage0_state` menggunakan fungsi `start_timer` untuk memulai timer game dan `get_elapsed_time` untuk mendapatkan waktu yang telah berlalu.
* **Modul `ui`:** Modul `stage0_state` menggunakan fungsi `show_stage_transition` dan `show_level_transition` untuk menampilkan UI transisi, serta `show_pause_ui` untuk menampilkan UI pause.
* **Modul `sfx`:** Modul `stage0_state` menggunakan fungsi `play_music` untuk memainkan musik latar belakang dan `stop_music` untuk menghentikannya.

---
