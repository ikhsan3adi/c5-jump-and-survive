# Struktur Kode

Halaman ini menjelaskan struktur kode pada proyek game 2D platformer sederhana, termasuk organisasi file dan modul-modul utama yang membentuk alur kerja game.

## Organisasi Direktori

Proyek ini memiliki struktur direktori berikut:

```txt
📂assets/
  ├─ 📂fonts/
  ├─ 📂images/
  ├─ 📂levels/
  └─ 📂SFX/

📂include/
  ├─ 📂SDL3/
  ├─ 📂cJSON/
  ├─ SFX.h
  ├─ entity.h
  ├─ game.h
  ├─ game_stat.h
  ├─ game_state.h
  ├─ leaderboard.h
  ├─ leaderboard_state.h
  ├─ level.h
  ├─ level_parser.h
  ├─ menu_state.h
  ├─ obstacle.h
  ├─ physics.h
  ├─ player.h
  ├─ stage0_state.h
  ├─ transform.h
  ├─ ui.h
  ├─ util.h
  └─ vector.h

📂src/
  ├─ SFX.c
  ├─ entity.c
  ├─ game.c
  ├─ game_stat.c
  ├─ game_state.c
  ├─ leaderboard.c
  ├─ leaderboard_state.c
  ├─ level.c
  ├─ level_parser.c
  ├─ main.c
  ├─ menu_state.c
  ├─ obstacle.c
  ├─ physics.c
  ├─ player.c
  ├─ stage0_state.c
  ├─ ui.c
  └─ util.c

📂bin/
📂build/
📂lib/

leaderboard.dat

.gitignore
Makefile
README.md
```

Berikut adalah penjelasan untuk setiap folder dan file:

---

### **📂 assets/**

Folder ini menyimpan semua aset yang digunakan dalam game, seperti font, gambar, dan suara.

- **📂 fonts/**: Berisi font yang digunakan untuk teks dalam game, misalnya judul di menu, skor, atau elemen UI lainnya.

- **📂 SFX/**: Berisi file suara (*.wav &*.mp3) yang digunakan dalam game, seperti jump, gate, coin, dead, dan gameover.

- **📂 images/**: Berisi gambar yang digunakan dalam game, seperti latar belakang level.

- **📂 levels/**: Berisi file JSON yang mendeskripsikan level dalam game. Setiap file berisi informasi tentang posisi pemain, jebakan, dan properti lainnya yang diperlukan untuk membangun level.

---

### **📂 include/**

Berisi header file (`*.h`) yang mendefinisikan fungsi, struktur, dan konstanta yang digunakan oleh berbagai modul dalam proyek.

- **📂 SDL3/**:

    Berisi file header dari library SDL3. Sudah termasuk library SDL_ttf, dan SDL_mixer.

- **📂 cJSON/**:

    Berisi file header dari library cJSON, yang digunakan untuk parsing JSON.

- **SFX.h** & **SFX.c**:

    Berisi kode yang menangani musik dan sound effect.

- **entity.h** & **entity.c**:

    Mengatur entitas dalam game, seperti pemain, musuh, atau objek lain. Berisi fungsi untuk pembuatan,
    pembaruan, dan pembersihan entitas.

- **game.h** & **game.c**:

    Berisi struktur game yang terdiri dari window dan renderer, serta prosedur untuk inisialisasi game.

- **game_state.h** & **game_state.c**:

    State management dari game. Berisi deklarasi struktur GameState, yang merupakan blueprint dari state-state game (cth. `menu_state`, `stage0_state`). Terdapat fungsi untuk berpindah state.

- **game_stat.h** & **game_stat.c**:

    Memuat fungsi-fungsi terkait statistik, seperti skor, nyawa dan waktu bermain.

- **leaderboard.h** & **leaderboard.c**:

    Berisi fungsi untuk mengelola leaderboard, termasuk menyimpan dan memuat skor tertinggi.

- **level.h** & **level.c**:

    Berisi definisi level dalam game, termasuk memuat data level dan perpindahan antar level.

- **level_parser.h** & **level_parser.c**:
  
    Berisi fungsi untuk mem-parsing file level yang ditulis dalam format JSON. Menggunakan library cJSON untuk membaca data level.

- **menu_state.h** & **menu_state.c**:

    Mengatur tampilan start menu. Implementasi dari `game_state`.

- **obstacle.h** & **obstacle.c**:

    Mengatur tampilan dan logika obstacles, contohnya *saw*, *spike*, *fake coins*, dan lainnya.

- **physics.h** & **physics.c**:

    Menangani simulasi fisika sederhana seperti gravitasi dan tabrakan(collision).

- **player.h** & **player.c**:

    Mengatur logika perilaku pemain, seperti kontrol, pergerakan, atau interaksi dengan entitas lainnya.

- **stage0_state.h** & **stage0_state.c**:

    Logika untuk level atau stage awal dari game. Implementasi dari `game_state`.

- **transform.h**:

    Berisi struktur transformasi seperti posisi dan ukuran.

- **vector.h**:

    Berisi struktur sederhana vector, yang memuat 2 buah angka, yaitu x dan y.

- **ui.h** & **ui.c**:

    Berisi fungsi untuk menampilkan UI, seperti game UI (skor, nyawa dan timer), render teks, tampilan
    transisi level, pause, game over, dan lainnya.

- **util.h** & **util.c**:

    Berisi fungsi utilitas/helper yang digunakan di berbagai bagian game.

- **main.c**:

    Program utama yang menjalankan game. Inisialisasi game, memuat state awal (`menu_state`), dan menjalankan loop game.

---

### **📂 src/**

Folder ini berisi semua file implementasi (`*.c`) dari proyek. Penjelasan fungsionalitas setiap file telah dikelompokkan bersama header-nya di bagian sebelumnya.

---

### **📂 bin/**

Folder ini menyimpan file biner dari library, yang nantinya akan disalin ke folder build setelah proses build selesai.

---

### **📂 build/**

Folder ini menyimpan file biner hasil kompilasi program dan file sementara yang dihasilkan selama proses kompilasi, seperti file objek (`*.o`) atau cache build lainnya.

---

### **📂 lib/**

Folder ini berisi library eksternal yang dibutuhkan oleh proyek, seperti SDL3.

---

### File di Root Directory

- **leaderboard.dat**:

    File biner yang menyimpan data leaderboard, berisi skor tertinggi yang dicapai pemain.

- **.gitignore**:

    Berisi aturan untuk menentukan file atau folder yang harus diabaikan oleh Git, seperti file build atau cache.

- **Makefile**:

    File konfigurasi untuk alat build make, digunakan untuk mempermudah proses kompilasi game. Berisi aturan untuk mengompilasi, membersihkan, dan menjalankan program.

- **README.md**:

    Berisi deskripsi, informasi kelompok, pembagian tugas dan informasi tambahan lainnya.
