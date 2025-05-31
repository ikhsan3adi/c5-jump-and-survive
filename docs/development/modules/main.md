# Main Program

**Pembuat:** [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `main.c`

## Penjelasan Setiap Fungsi

### **main**

```c title="main.c"
int main();
```

Fungsi `main` adalah titik masuk utama aplikasi. Fungsi ini menginisialisasi game, membuat instance game, memuat aset seperti font dan audio, dan memuat level dari direktori "assets/levels/". Kemudian, ia mengatur state game awal ke `menu_state`. Loop game utama berjalan hingga `game->is_exit` bernilai true. Dalam loop, ia menangani input dan event, menghitung `delta_time` untuk pembaruan fisika, memperbarui logika game, dan merender frame saat ini. Sebelum keluar, ia membersihkan state game saat ini dan memanggil `exit_game`.
