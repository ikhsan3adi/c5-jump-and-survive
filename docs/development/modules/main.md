# Main Program

**Pembuat:** [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `main.c`

## Penjelasan Setiap Fungsi

### **SDL_AppInit()**

```c title="main.c"
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) { ... }
```

Fungsi `SDL_AppInit` adalah titik awal aplikasi, dipanggil hanya sekali saat program dimulai. Fungsi ini bertugas untuk melakukan inisialisasi awal, termasuk memanggil fungsi `initialize()` untuk inisialisasi permainan dan mengatur metadata. Selanjutnya, fungsi `create_game_instance()` dipanggil untuk membuat window dan renderer game. Terakhir, `change_game_state()` digunakan untuk mengatur state awal permainan ke `menu_state`, yang berarti layar menu akan ditampilkan pertama kali saat aplikasi dijalankan.

---

### **SDL_AppEvent()**

```c title="main.c"
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) { ... }
```

Dipanggil setiap kali ada event terjadi, seperti input dari keyboard atau mouse. Pertama, fungsi ini memeriksa apakah event tersebut adalah SDL_EVENT_QUIT, yang menandakan permintaan untuk menutup aplikasi. Jika ya, aplikasi akan keluar. Jika tidak, fungsi ini akan mengambil state permainan saat ini. Kemudian, fungsi `handle_input()` dari state permainan saat ini dipanggil, dan event yang diterima diteruskan ke fungsi tersebut.

```c
  GameState *current_state = get_current_game_state();
  current_state->handle_input(event);

```

---

### **SDL_AppIterate()**

```c title="main.c"
SDL_AppResult SDL_AppIterate(void *appstate) { ... }
```

Fungsi `SDL_AppIterate` adalah jantung dari loop permainan, dipanggil setiap frame untuk memperbarui dan merender permainan. Pertama, fungsi ini menghitung **_delta time_**, yaitu selisih waktu antara frame saat ini dan frame sebelumnya, yang penting untuk pergerakan dan animasi yang halus.

```c
  Uint64 current_time = SDL_GetTicks();
  double delta_time = ((current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency());
  last_time = current_time;
```

Kemudian, fungsi ini mengambil `renderer` dari instance permainan, yang digunakan untuk menggambar elemen-elemen permainan ke layar. Selanjutnya, fungsi `update()` dari state permainan saat ini dipanggil untuk memperbarui logika permainan, diikuti oleh fungsi `render()` untuk menggambar frame saat ini ke layar.

```c
  GameState *current_state = get_current_game_state();

  current_state->update(delta_time);
  current_state->render(renderer);
```

---

### **SDL_AppQuit()**

```c title="main.c"
void SDL_AppQuit(void *appstate, SDL_AppResult result) { ... }
```

Fungsi `SDL_AppQuit` dipanggil saat program akan ditutup. Fungsinya adalah untuk membersihkan semua sumber daya yang digunakan oleh program. Ketika fungsi ini dipanggil, SDL secara otomatis akan membersihkan `window`, `renderer` dan resource lain (misalnya font SDL_ttf), memastikan bahwa semua sumber daya yang dialokasikan oleh program dilepaskan dengan benar.

---
