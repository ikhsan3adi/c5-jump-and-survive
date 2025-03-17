# Struktur Kode

Halaman ini menjelaskan struktur kode pada proyek game 2D platformer sederhana, termasuk organisasi file dan modul-modul utama yang membentuk alur kerja game.

## Organisasi Direktori

Proyek ini memiliki struktur direktori berikut:

```txt
📂assets/
  ├─ 📂fonts/
  └─ 📂SFX/

📂include/
  ├─ 📂SDL3/
  ├─ SFX.h
  ├─ entity.h
  ├─ game.h
  ├─ game_stat.h
  ├─ game_state.h
  ├─ level.h
  ├─ menu_state.h
  ├─ obstacle.h
  ├─ physics.h
  ├─ player.h
  ├─ stage0_state.h
  ├─ stage1_state.h
  ├─ transform.h
  ├─ ui.h
  └─ vector.h

📂src/
  ├─ SFX.c
  ├─ entity.c
  ├─ game.c
  ├─ game_stat.c
  ├─ game_state.c
  ├─ level.c
  ├─ main.c
  ├─ menu_state.c
  ├─ obstacle.c
  ├─ physics.c
  ├─ player.c
  ├─ stage0_state.c
  ├─ stage1_state.c
  └─ ui.c

📂bin/
📂build/
📂lib/

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

---

### **📂 include/**

Berisi header file (`*.h`) yang mendefinisikan fungsi, struktur, dan konstanta yang digunakan oleh berbagai modul dalam proyek.

- **📂 SDL3/**:

    Berisi file header dari library SDL3. Sudah termasuk library SDL_ttf, dan SDL_mixer.

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

- **level.h** & **level.c**:

    Berisi definisi level dalam game, termasuk memuat data level dan perpindahan antar level.

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

- **stage1_state.h** & **stage1_state.c**:

    Logika untuk level atau stage berikutnya. Implementasi dari `game_state`.

- **transform.h**:

    Berisi struktur transformasi seperti posisi dan ukuran.

- **vector.h**:

    Berisi struktur sederhana vector, yang memuat 2 buah angka, yaitu x dan y.

- **ui.h** & **ui.c**:

    Berisi fungsi untuk menampilkan UI, seperti game UI (skor, nyawa dan timer), render teks, tampilan
    transisi level, pause, game over, dan lainnya.

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

- **.gitignore**:

    Berisi aturan untuk menentukan file atau folder yang harus diabaikan oleh Git, seperti file build atau cache.

- **Makefile**:

    File konfigurasi untuk alat build make, digunakan untuk mempermudah proses kompilasi game. Berisi aturan untuk mengompilasi, membersihkan, dan menjalankan program.

- **README.md**:

    Berisi deskripsi, informasi kelompok, pembagian tugas dan informasi tambahan lainnya.
