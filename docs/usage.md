# Cara Menjalankan Program

> ⚠ _Baru teruji untuk platform Windows & Linux saja_

## Instal Persyaratan

Pastikan _compiler_ **GCC** dan **GNU Make** telah terinstal. Jika belum, instal menggunakan perintah berikut:

### Windows (menggunakan MSYS2)

1. Unduh dan instal [MSYS2](https://www.msys2.org/).
2. Buka shell/terminal MSYS2 dan jalankan:

```sh
pacman -S mingw-w64-x86_64-gcc make
```

> ⚠ Pastikan `gcc` dan `make` sudah terdaftar di environment variables di sistem Anda.

### Linux

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

## Download Proyek

Clone repository proyek menggunakan Git:

```sh
git clone https://github.com/ikhsan3adi/c5-jump-and-survive.git
cd c5-jump-and-survive
```

Atau, unduh ZIP dari repositori dan ekstrak ke dalam folder yang diinginkan (Direkomendasikan).

## Build dan Jalankan Program

Gunakan perintah **make** untuk mem-build dan menjalankan program:

```sh
make
```

Jika _build_ berhasil, folder build dan file program (contoh `main.exe` untuk windows) akan muncul.

## Membersihkan Folder Build

Untuk menghapus file hasil kompilasi dan membersihkan folder build, jalankan:

```sh
make clean
```
