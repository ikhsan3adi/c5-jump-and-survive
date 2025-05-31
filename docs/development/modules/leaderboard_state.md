# Modul `leaderboard_state`

**Pembuat:** [Helga Athifa Hidayat (241511077)](https://github.com/helga1406)

**File:** `leaderboard_state.c` & `leaderboard_state.h`

## Variabel dan Konstanta

### **leaderboard_state**

```c
GameState leaderboard_state = {
    .init = leaderboard_init,
    .handle_input = leaderboard_handle_input,
    .update = leaderboard_update,
    .render = leaderboard_render,
    .cleanup = leaderboard_cleanup,
};
```

---

## Penjelasan Setiap Fungsi

### **leaderboard_init**

```c title="leaderboard_state.h"
void leaderboard_init();
```

Fungsi `leaderboard_init` dipanggil ketika game memasuki state `leaderboard_state`. Fungsi ini bertanggung jawab untuk melakukan inisialisasi yang diperlukan untuk stage 0, termasuk:

---

### **leaderboard_handle_input**

```c title="leaderboard_state.h"
void leaderboard_handle_input(SDL_Event *event);
```

Fungsi `leaderboard_handle_input` dipanggil setiap kali ada event input dari pengguna saat state `leaderboard_state` aktif.

---

### **leaderboard_update (tidak digunakan)**

```c title="leaderboard_state.h"
void leaderboard_update(double delta_time);
```

Fungsi `leaderboard_update` dipanggil setiap frame untuk memperbarui logika game dalam state `leaderboard_state`.

---

### **leaderboard_render**

```c title="leaderboard_state.h"
void leaderboard_render(SDL_Renderer *renderer);
```

Fungsi `leaderboard_render` dipanggil setiap frame untuk merender tampilan game dalam state `leaderboard_state`.

---

### **leaderboard_cleanup**

```c title="leaderboard_state.h"
void leaderboard_cleanup();
```

Fungsi `leaderboard_cleanup` dipanggil ketika state `leaderboard_state` akan diakhiri atau diganti dengan state lain. Fungsi ini bertanggung jawab untuk membersihkan sumber daya yang digunakan oleh state ini.

---

## Interaksi dengan modul lain

Modul `leaderboard_state` berinteraksi dengan modul lain sebagai berikut:

* **Modul `ui`:** Modul `leaderboard_state` menggunakan fungsi `show_leaderboard_ui` untuk menampilkan UI leaderboard.
* **Modul `menu_state`:** Modul `leaderboard_state` dapat diakses dari state menu ketika pengguna memilih opsi leaderboard.

---
