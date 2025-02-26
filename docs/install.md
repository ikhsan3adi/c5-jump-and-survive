# How to Run

> ⚠ _Baru teruji untuk platform Windows saja_

## Install Requirements

Pastikan compiler **GCC** dan **GNU Make** telah terinstal. Jika belum, install menggunakan perintah berikut:

### Ubuntu/Debian

```sh
sudo apt update && sudo apt install build-essential -y
```

### MacOS (menggunakan Homebrew)

```sh
brew install gcc make
```

### Windows (menggunakan MSYS2)

1. Unduh dan instal [MSYS2](https://www.msys2.org/).
2. Buka MSYS2 dan jalankan:

```sh
pacman -S mingw-w64-x86_64-gcc make
```

> Pastikan `gcc` dan `make` sudah terdaftar di environment variables di sistem Anda

## Download Proyek

Clone repository proyek menggunakan Git:

```sh
git clone https://github.com/ikhsan3adi/c5-jump-and-survive.git
cd c5-jump-and-survive
```

Atau, unduh ZIP dari repository dan ekstrak ke dalam folder yang diinginkan (Direkomendasikan).

## Build dan Jalankan Program

Gunakan perintah **make** untuk membangun dan menjalankan program:

```sh
make
```

## Membersihkan Folder Build

Untuk menghapus file hasil kompilasi dan membersihkan folder build, jalankan:

```sh
make clean
```
