# Teknis Pengembangan

Halaman ini bertujuan untuk memberikan gambaran umum tentang pengembangan proyek, termasuk bagaimana proses pengembangan dilakukan, pembagian tugas antar anggota, branch-branch yang digunakan, struktur arsitektur proyek, dan teknologi yang digunakan.

---

## Gambaran Umum

### Pembagian Tugas Anggota Kelompok

1. [**Ikhsan Satriadi** (241511080)](https://github.com/ikhsan3adi)

     Mengembangkan core lifecycle game, seperti pengelolaan state, dan bertanggung jawab atas inisialisasi program menggunakan library SDL untuk membuat _window_ dan _renderer_. Ikut membantu dalam pengembangan entity dan level. Selain itu, juga membuat dokumentasi teknis proyek.

2. [**Muhamad Syahid** (241511081)](https://github.com/muhamadSyahid)

     Bertanggung jawab pada pengelolaan entity, seperti player, musuh, dan objek dinamis lainnya. Tanggung jawab juga meliputi pengembangan logika fisika untuk entitas, termasuk implementasi sistem tabrakan / collision dengan tile map.

3. [**Hisyam Khaeru Umam** (241511078)](https://github.com/Umeem26)

     Merancang dan mengimplementasikan level permainan, termasuk mendesain level-level dengan berbagai elemen seperti tata letak platform dan rintangan. Selain itu, juga mendesain bentuk dan tampilan player.

4. [**Helga Athifa Hidayat** (241511077)](https://github.com/helga1406)

     Mengembangkan antarmuka pengguna (UI), mencakup perancangan menu utama, game over, pause, navigasi antar halaman, serta elemen visual seperti indikator skor dan nyawa.

5. [**Hanifidin Ibrahim** (241511076)](https://github.com/Hanif13579)

     Mengelola sistem statistik permainan (_Game Stats_), termasuk mencatat dan menampilkan data seperti skor, jumlah nyawa yang tersisa, dan timer.

### Pembagian Branch

#### Branch program

- **`main`**: Menyimpan versi stabil dari program.
- **`feat/game-state`**: Berisi pengembangan state game, seperti menu state, stage state.
- **`feat/ui`**: Berisi pengembangan dan implementasi elemen UI, seperti teks dan HUD game.
- **`feat/main-menu`**: Berisi implementasi logika menu utama / start menu.
- **`feat/entity-and-physics`**: Mengembangkan logika _entity_ (player) dan modul fisika.
- **`feat/tile-system`**: Mengimplementasikan sistem tile untuk _level design_.
- **`feat/game-stat`**: Berisi pengembangan fitur terkait statistik game, seperti skor dan waktu bermain.
- **`feat/coins-and-other-obstacles`**: Mengembangkan fitur tambahan, seperti koin dan rintangan dalam permainan.

#### Branch dokumentasi

- **`docs`**: Branch khusus untuk dokumentasi proyek.
- **`gh-pages`**: Branch untuk memublikasi dokumentasi menggunakan GitHub Pages.

### Cara Kerja Pengembangan

- Setiap fitur baru dikembangkan di branch terpisah untuk menjaga kebersihan branch `main`.
- Setelah fitur selesai dan diuji, branch tersebut akan di-_merge_ ke `main` melalui pull request.
- Komunikasi dilakukan secara rutin (melalui WhatsApp group, GitHub atau Trello) untuk memastikan semua anggota tetap sinkron.

---

## Arsitektur

### State Pattern untuk Lifecycle Game

Logika siklus game ini dikelola melalui **state pattern**. Modul `game_state` bertindak sebagai antarmuka abstrak yang mengatur alur permainan melalui state konkrit, seperti `menu_state`, `stage0_state`, dan `stage1_state`. Dalam modul ini, fungsi-fungsi seperti inisialisasi (`init()`), pembaruan (`update()`), dan rendering (`render()`) didefinisikan sebagai kontrak yang harus diimplementasikan oleh state konkrit. State konkrit seperti `menu_state`, `stage0_state`, dan `stage1_state` masing-masing mengimplementasikan logika spesifik untuk menu utama, tahap pertama permainan, dan tahap lanjutan. Disediakan juga fungsi untuk berpindah state (`change_game_state`). Dengan pemisahan ini, setiap state dapat dikembangkan dan dimodifikasi secara independen tanpa memengaruhi alur logika state lainnya.

Definisi dan implementasi _game state_ dapat dilihat pada:

- [Modul `game_state`](./modules/game_state.md)
- [Main program `main.c`](./modules/main.md)

### Tile System untuk Map, Obstacle, dan Collision

_Tile system_ digunakan untuk mendesain map, rintangan, dan mendukung deteksi tabrakan (collision). Sistem ini memanfaatkan **array 2D** untuk merepresentasikan tata letak level secara grid, di mana setiap elemen array menunjukkan jenis tile, seperti platform, rintangan, atau ruang kosong.

Implementasi dan penggunaan _level_ dan _tile system_ dapat dilihat pada:

- [Modul `level`](./modules/level.md)
- [Modul `stage0_state`](./modules/stage0_state.md)
- [Modul `stage1_state`](./modules/stage1_state.md)

### Entity System untuk Player dan Objek dinamis lainnya

Entity system dikelola melalui modul `entity`, yang menangani semua objek dinamis seperti `player` dan enemy. Setiap entitas memiliki atribut seperti transformasi posisi yang dikelola melalui modul `transform` dan mengikuti aturan fisika yang ditentukan oleh modul `physics`.

Desain ini memastikan modularitas, memudahkan penambahan fitur baru, dan mendukung pengembangan yang efisien dengan pemisahan tanggung jawab yang jelas di setiap modul.

Implementasi _entity_, _player_ dan modul pendukungnya dapat dilihat pada:

- [Modul `entity`](./modules/entity.md)
- [Modul `player`](./modules/player.md)
- [Modul `transform`](./modules/transform.md)
- [Modul `physics`](./modules/physics.md)

---

## Teknologi yang Digunakan

- **Bahasa Pemrograman**:
    - **C** Programing Language (GCC v14.2.0)
- **Library**:
    - [**SDL3**](https://www.libsdl.org/) v3.3.0 untuk rendering grafis dan handling event.
        - [SDL_ttf](https://wiki.libsdl.org/SDL3_ttf/FrontPage) v3.2.0 untuk menangani teks dan font.
        - [SDL_mixer](https://wiki.libsdl.org/SDL3_mixer/FrontPage) v3.0.0 untuk menangani audio.

        Kami menggunakan build SDL dari: <https://github.com/mmozeiko/build-sdl3>

- **Build Tools**:
    - [**GNU Make**](https://www.gnu.org/software/make/) untuk otomatisasi proses build.
    - [**GCC**](https://packages.msys2.org/packages/mingw-w64-x86_64-gcc) v14.2.0 (MSYS2) untuk kompilasi _source code_.
- **Version Control System**:
    - [**Git**](https://git-scm.com/) untuk pengelolaan kode dan kolaborasi.
- **Dokumentasi**:
    - [**MkDocs Material**](https://squidfunk.github.io/mkdocs-material/) untuk pembuatan web dokumentasi teknis ini.
    - [**GitHub Pages**](https://pages.github.com/) untuk memublikasikan dokumentasi secara online.
- **Code Editor**:
    - [**Visual Studio Code**](https://code.visualstudio.com/) dengan extension C/C++ untuk pengembangan.
