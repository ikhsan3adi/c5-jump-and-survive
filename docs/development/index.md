# Teknis Pengembangan

Halaman ini bertujuan untuk memberikan gambaran umum tentang pengembangan proyek, termasuk bagaimana proses pengembangan dilakukan, pembagian tugas antar anggota, branch-branch yang digunakan, struktur arsitektur proyek, dan teknologi yang digunakan.

---

## Gambaran Umum

### Pembagian Tugas Anggota Kelompok

1. [**Ikhsan Satriadi** (241511080)](https://github.com/ikhsan3adi)

    Bertugas mengelola _Game State_ dan mengembangkan _Game Manager_ serta _Main Driver/Game Loop_ utama permainan. Ikhsan juga bertanggung jawab atas pembuatan dokumentasi web proyek, merancang struktur data untuk _node level_, dan mengimplementasikan mekanisme _parsing_ berkas level dari format JSON ke dalam struktur data tersebut.

2. [**Muhamad Syahid** (241511081)](https://github.com/muhamadSyahid)

    Fokus pada pengembangan logika _entity_, khususnya untuk _player_, serta menangani aspek fisika (_physics_) yang berlaku pada setiap entitas dalam game. Syahid juga mengembangkan logika untuk berbagai rintangan (_obstacles_) dan melakukan manajemen data level menggunakan struktur data _doubly linked list_.

3. [**Hisyam Khaeru Umam** (241511078)](https://github.com/Umeem26)

    Bertanggung jawab atas pembuatan _stage_ dan desain _level/map_ permainan secara keseluruhan. Hisyam juga mengerjakan aspek visual untuk karakter _player_, manajemen _audio_ dan _sound effects_ (SFX), serta pembuatan berkas-berkas level dalam format JSON.

4. [**Helga Athifa Hidayat** (241511077)](https://github.com/helga1406)

    Mengembangkan berbagai antarmuka pengguna (UI), termasuk _menu interface_ dan _game interface_ yang interaktif. Helga juga bertugas melakukan manajemen _assets_ grafis yang digunakan dalam permainan dan merancang antarmuka untuk sistem _leaderboard_.

5. [**Hanifidin Ibrahim** (241511076)](https://github.com/Hanif13579)

    Bertugas mengelola dan menampilkan statistik permainan (_Game Stats_) kepada pemain. Hanifidin juga merancang tampilan visual untuk rintangan (_visual obstacle_) dan mengimplementasikan fungsionalitas sistem _leaderboard_ dengan menggunakan struktur data _singly linked list_.

### Pembagian Branch

#### Branch program

- **`main`**: Menyimpan versi stabil dari program.
- **`feat/game-state`**: Berisi pengembangan state game, seperti menu state, stage state.
- **`feat/ui`**: Berisi pengembangan dan implementasi elemen UI, seperti teks dan HUD game.
- **`feat/main-menu`**: Berisi implementasi logika menu utama / start menu.
- **`feat/entity-and-physics`**: Mengembangkan logika _entity_ (player) dan modul fisika.
- **`feat/tile-system`**: Mengimplementasikan sistem tile untuk _level design_.
- **`feat/game-stat`**: Berisi pengembangan fitur terkait statistik game, seperti skor dan waktu bermain. Juga mengelola leaderboard.
- **`feat/coins-and-other-obstacles`**: Mengembangkan fitur koin dan rintangan dalam permainan.
- **`feat/Audio_SFX`**: Berisi pengembangan fitur audio dan efek suara (SFX) dalam permainan.
- **`feat/parsing-level-json`**: Mengimplementasikan mekanisme parsing berkas level dari format JSON ke dalam struktur data yang digunakan dalam permainan.
- **`feat/linked-list-map`**: Berisi pengembangan struktur data _doubly linked list_ untuk manajemen level dalam permainan.
- **`integration`**: Branch untuk mengintegrasikan semua fitur yang telah dikembangkan ke dalam branch `main`.

#### Branch dokumentasi

- **`docs`**: Branch khusus untuk dokumentasi proyek.
- **`gh-pages`**: Branch untuk memublikasi dokumentasi menggunakan GitHub Pages.

### Cara Kerja Pengembangan

- Setiap fitur baru dikembangkan di branch terpisah untuk menjaga kebersihan branch `main`.
- Setelah fitur selesai dan diuji, branch tersebut akan di-_merge_ ke `integration` melalui pull request. Setelah itu, branch `integration` akan diuji dan di-_merge_ ke `main`.
- Komunikasi dilakukan secara rutin (melalui WhatsApp group, GitHub atau Trello) untuk memastikan semua anggota tetap sinkron.

---

## Arsitektur

### State Pattern untuk Lifecycle Game

Logika siklus game ini dikelola melalui **state pattern**. Modul `game_state` bertindak sebagai antarmuka abstrak yang mengatur alur permainan melalui state konkrit, seperti `menu_state`, `stage0_state`, dan `leadrboard_state`. Dalam modul ini, fungsi-fungsi seperti inisialisasi (`init()`), pembaruan (`update()`), dan rendering (`render()`) didefinisikan sebagai kontrak yang harus diimplementasikan oleh state konkrit. State konkrit seperti `menu_state`, `stage0_state`, dan `leadrboard_state` masing-masing mengimplementasikan logika spesifik untuk menu utama, tahap pertama permainan, dan tahap lanjutan. Disediakan juga fungsi untuk berpindah state (`change_game_state`). Dengan pemisahan ini, setiap state dapat dikembangkan dan dimodifikasi secara independen tanpa memengaruhi alur logika state lainnya.

Definisi dan implementasi _game state_ dapat dilihat pada:

- [Modul `game_state`](./modules/game_state.md)
- [Main program `main.c`](./modules/main.md)

### Tile System untuk Map, Obstacle, dan Collision

_Tile system_ digunakan untuk mendesain map, rintangan, dan mendukung deteksi tabrakan (collision). Sistem ini memanfaatkan **array 2D** untuk merepresentasikan tata letak level secara grid, di mana setiap elemen array menunjukkan jenis tile, seperti platform, rintangan, atau ruang kosong.

Implementasi dan penggunaan _level_ dan _tile system_ dapat dilihat pada:

- [Modul `level`](./modules/level.md)
- [Modul `stage0_state`](./modules/stage0_state.md)

### Level Modular dengan JSON

Level permainan didefinisikan dalam format JSON, yang memungkinkan desainer untuk membuat dan mengedit level dengan mudah tanpa perlu mengubah kode sumber. Modul `level_parser` bertanggung jawab untuk membaca berkas JSON, mem-parsing data, dan mengonversinya menjadi struktur data yang digunakan dalam permainan. Ini memungkinkan fleksibilitas dalam desain level dan memudahkan penambahan atau perubahan level di masa depan.
Implementasi _level_ dan _parsing_ berkas JSON dapat dilihat pada:

- [Modul `level`](./modules/level.md)
- [Modul `level_parser`](./modules/level_parser.md)

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
    - [**SDL3**](https://www.libsdl.org/) untuk rendering grafis dan handling event.
        - [SDL_ttf](https://wiki.libsdl.org/SDL3_ttf/FrontPage) untuk menangani teks dan font.
        - [SDL_mixer](https://wiki.libsdl.org/SDL3_mixer/FrontPage) untuk menangani audio.

        Kami menggunakan build SDL dari: <https://github.com/mmozeiko/build-sdl3>

    - [**cJSON**](https://github.com/DaveGamble/cJSON) untuk parsing file JSON, digunakan untuk menyimpan data level.

- **Build Tools**:
    - [**GNU Make**](https://www.gnu.org/software/make/) untuk otomatisasi proses build.
    - [**GCC**](https://packages.msys2.org/packages/mingw-w64-x86_64-gcc) (MSYS2) untuk kompilasi _source code_.
- **Version Control System**:
    - [**Git**](https://git-scm.com/) untuk pengelolaan kode dan kolaborasi.
- **Dokumentasi**:
    - [**MkDocs Material**](https://squidfunk.github.io/mkdocs-material/) untuk pembuatan web dokumentasi teknis ini.
    - [**GitHub Pages**](https://pages.github.com/) untuk memublikasikan dokumentasi secara online.
- **Code Editor**:
    - [**Visual Studio Code**](https://code.visualstudio.com/) dengan extension C/C++ untuk pengembangan.
