# Cara Menjalankan Program

> ⚠ _Baru teruji untuk platform Windows saja_

## Instal Persyaratan

Pastikan _compiler_ **GCC** dan **GNU Make** telah terinstal. Jika belum, instal menggunakan perintah berikut:

### Windows (menggunakan MSYS2)

1. Unduh dan instal [MSYS2](https://www.msys2.org/).
2. Buka shell/terminal MSYS2 dan jalankan:

```sh
pacman -S mingw-w64-x86_64-gcc make
```

> ⚠ Pastikan `gcc` dan `make` sudah terdaftar di environment variables di sistem Anda.

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
