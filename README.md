# Jump & Survive

## Proyek 2: Pengembangan Aplikasi Berbasis Library

![Preview](https://github.com/ikhsan3adi/c5-jump-and-survive/blob/docs/docs/image/how-to-play/menu.png?raw=true)

Jump & Survive adalah game 2D platformer sederhana yang dibuat menggunakan bahasa pemrograman C dan library SDL3. Dalam game ini, pemain mengendalikan karakter utama yang harus melompat dan menghindari rintangan untuk mencapai tujuan akhir.

---

**Kelompok** : C5

**Jurusan** : Teknik Komputer dan Informatika

**Prodi** : D3 Teknik Informatika

**Manager Proyek** : Yudi Widhiyasana, S.Si., MT

---

## Anggota Kelompok

| No  | Anggota                                                                 | NIM       |
| --- | ----------------------------------------------------------------------- | --------- |
| 1   | **Hanifidin Ibrahim** ([@Hanif13579](https://github.com/Hanif13579))    | 241511076 |
| 2.  | **Helga Athifa Hidayat** ([@helga1406](https://github.com/helga1406))   | 241511077 |
| 3.  | **Hisyam Khaeru Umam** ([@Umeem26](https://github.com/Umeem26))         | 241511078 |
| 4.  | **Ikhsan Satriadi** ([@ikhsan3adi](https://github.com/ikhsan3adi))      | 241511080 |
| 5.  | **Muhamad Syahid** ([@muhamadSyahid](https://github.com/muhamadSyahid)) | 241511081 |

---

## Pembagian Roles

- ### Ikhsan Satriadi ([@ikhsan3adi](https://github.com/ikhsan3adi))

  - Game State
  - Game Manager & Main Driver/Game Loop
  - Web dokumentasi
  - Struktur data node level
  - Urai(Parsing) file level JSON ke struktur data node level

- ### Muhamad Syahid ([@muhamadSyahid](https://github.com/muhamadSyahid))

  - Entity/player logic
  - Physics entity
  - Obstacles logic
  - Manajemen level dengan doubly linked list

- ### Hisyam Khaeru Umam ([@Umeem26](https://github.com/Umeem26))

  - Pembuatan stage
  - Pembuatan level/map
  - Tampilan player
  - Manajemen audio/sfx
  - Pembuatan file level JSON

- ### Helga Athifa Hidayat ([@helga1406](https://github.com/helga1406))

  - Menu interface
  - Game interface
  - Manajemen assets
  - Manajemen interface leaderboard

- ### Hanifidin Ibrahim ([@Hanif13579](https://github.com/Hanif13579))

  - Game Stats
  - Visual obstacle
  - Sistem leaderboard dengan singly linked list

---

## Instalasi

### Instal Persyaratan

Pastikan _compiler_ **GCC** dan **GNU Make** telah terinstal. Jika belum, instal menggunakan perintah berikut:

#### Windows (menggunakan MSYS2)

1. Unduh dan instal [MSYS2](https://www.msys2.org/).
2. Buka shell/terminal MSYS2 dan jalankan:

```sh
pacman -S mingw-w64-x86_64-gcc make
```

> ⚠ Pastikan `gcc` dan `make` sudah terdaftar di environment variables di sistem Anda.

#### Linux

1. Install _compiler_ GCC, GNU Make, `SDL3`, `SDL3_ttf`, `SDL3_mixer`, dan `SDL3_image`  menggunakan manajer paket distribusi Linux Anda.

    - Untuk Debian/Ubuntu, gunakan:

        ```sh
        sudo apt install build-essential libsdl3-dev libsdl3-ttf-dev libsdl3-mixer-dev libsdl3-image-dev
        ```

    - Untuk Arch Linux, gunakan:

        ```sh  
        sudo pacman -S base-devel sdl3 sdl3_ttf sdl3_mixer sdl3_image
        ```

    Untuk distribusi lain, silakan sesuaikan dengan manajer paket yang digunakan.

### Download Proyek

Clone repository proyek menggunakan Git:

```sh
git clone https://github.com/ikhsan3adi/c5-jump-and-survive.git
cd c5-jump-and-survive
```

Atau, unduh ZIP dari repositori dan ekstrak ke dalam folder yang diinginkan (Direkomendasikan).

### Build dan Jalankan Program

Gunakan perintah **make** untuk mem-build dan menjalankan program:

```sh
make
```

Jika _build_ berhasil, folder build dan file program (contoh `main.exe` untuk windows) akan muncul.

### Membersihkan Folder Build

Untuk menghapus file hasil kompilasi dan membersihkan folder build, jalankan:

```sh
make clean
```

## Dokumentasi Lebih Lanjut

[Jump &amp; Survive Documentation](https://ikhsan3adi.github.io/c5-jump-and-survive/)
