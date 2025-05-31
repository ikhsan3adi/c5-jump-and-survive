# Modul `leaderboard`

**Pembuat:** [Hanifidin Ibrahim (241511076)](https://github.com/Hanif13579)

**File:** `leaderboard.h` & `leaderboard.c`

## Struktur `LeaderboardNode`

```c title="leaderboard.h"
typedef struct LeaderboardNode {
    GameStat stat;
    struct LeaderboardNode* next;
} LeaderboardNode;
```

Struktur `LeaderboardNode` merepresentasikan sebuah entri dalam leaderboard, berfungsi sebagai node dalam sebuah linked list. Setiap node menyimpan statistik permainan (`GameStat`) dan sebuah pointer ke node berikutnya dalam daftar.

* `stat`: Berisi statistik permainan untuk entri leaderboard tertentu (misalnya, skor dan waktu yang berlalu).
* `next`: Pointer ke `LeaderboardNode` berikutnya dalam linked list, atau `NULL` jika ini adalah node terakhir.

---

## Variabel dan Konstanta

### **MAX_LEADERBOARD**

```c title="leaderboard.h"
#define MAX_LEADERBOARD 10
```

Konstanta `MAX_LEADERBOARD` mendefinisikan jumlah maksimum entri yang akan disimpan dalam leaderboard. Dalam kasus ini, leaderboard akan menyimpan hingga 10 entri skor tertinggi.

### **leaderboard_head**

```c title="leaderboard.h"
extern LeaderboardNode* leaderboard_head;
```

```c title="leaderboard.c"
LeaderboardNode *leaderboard_head = NULL;
```

Variabel global `leaderboard_head` adalah pointer yang menunjuk ke node pertama (head) dari linked list leaderboard. Variabel ini digunakan untuk mengelola akses ke seluruh data leaderboard. Ini diinisialisasi ke `NULL` yang menunjukkan leaderboard kosong pada awalnya.

---

## Penjelasan Setiap Fungsi

### **create_node**

```c title="leaderboard.h"
LeaderboardNode* create_node(GameStat stat);
```

```c title="leaderboard.c"
LeaderboardNode* create_node(GameStat stat) {
    LeaderboardNode* new_node = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    if (!new_node) return NULL;
    new_node->stat = stat;
    new_node->next = NULL;
    return new_node;
}
```

Fungsi `create_node` membuat dan menginisialisasi node `LeaderboardNode` baru. Fungsi ini menerima satu parameter `stat` (tipe `GameStat`) yang akan disimpan dalam node baru. Fungsi ini mengalokasikan memori untuk node baru, menetapkan statistik permainan yang diberikan, dan mengatur pointer `next` ke `NULL`. Mengembalikan pointer ke node yang baru dibuat, atau `NULL` jika alokasi memori gagal.

---

### **is_greater**

```c title="leaderboard.h"
bool is_greater(GameStat a, GameStat b);
```

Fungsi `is_greater` adalah fungsi pembanding yang menentukan apakah satu `GameStat` lebih unggul dari yang lain untuk tujuan peringkat leaderboard. Fungsi ini menerima dua parameter `a` dan `b`, keduanya bertipe `GameStat`. Prioritas pertama adalah skor yang lebih tinggi. Jika skornya sama, maka waktu yang lebih rendah (elapsed time) dianggap lebih baik. Mengembalikan `true` jika `a` lebih unggul dari `b`, `false` sebaliknya.

```c title="leaderboard.c"
bool is_greater(GameStat a, GameStat b) {
    return (a.score > b.score) ||
           (a.score == b.score && a.elapsed_time < b.elapsed_time);
}
```

---

### **insert_leaderboard**

```c title="leaderboard.h"
void insert_leaderboard(LeaderboardNode** head, GameStat stat);
```

Fungsi `insert_leaderboard` menyisipkan entri `GameStat` baru ke dalam leaderboard yang diurutkan secara menurun berdasarkan skor dan kemudian waktu yang berlalu. Fungsi ini menerima pointer ke pointer head leaderboard (`head`) dan statistik permainan (`stat`) yang akan disisipkan. Jika `nickname` kosong, akan diatur menjadi "Anonymous". Fungsi ini juga memastikan bahwa leaderboard tidak melebihi `MAX_LEADERBOARD` entri dengan menghapus node ke-11 jika ada.

---

### **free_leaderboard**

```c title="leaderboard.h"
void free_leaderboard(LeaderboardNode* head);
```

Fungsi `free_leaderboard` membebaskan semua memori yang dialokasikan untuk node-node dalam linked list leaderboard. Fungsi ini menerima pointer ke head leaderboard (`head`).

---

### **print_leaderboard**

```c title="leaderboard.h"
void print_leaderboard(const LeaderboardNode* head);
```

Fungsi `print_leaderboard` mencetak isi leaderboard ke konsol. Fungsi ini menerima pointer ke head leaderboard (`head`). Fungsi ini bersifat opsional dan berguna untuk debugging.

---

### **save_leaderboard**

```c title="leaderboard.h"
void save_leaderboard(const char* filename, LeaderboardNode* head);
```

Fungsi `save_leaderboard` menyimpan data leaderboard ke dalam file biner. Fungsi ini menerima nama file (`filename`) dan pointer ke head leaderboard (`head`). Hanya `MAX_LEADERBOARD` entri pertama yang disimpan.

---

### **load_leaderboard**

```c title="leaderboard.h"
LeaderboardNode* load_leaderboard(const char* filename);
```

Fungsi `load_leaderboard` memuat data leaderboard dari file biner. Fungsi ini menerima nama file (`filename`). Fungsi ini membaca setiap `GameStat` dari file dan menyisipkannya ke dalam linked list leaderboard menggunakan `insert_leaderboard`, sehingga memastikan urutan yang benar. Mengembalikan pointer ke head leaderboard yang dimuat, atau `NULL` jika file tidak dapat dibuka.

---

## Interaksi dengan modul lain

Modul `leaderboard` ini memiliki interaksi dengan modul lain sebagai berikut:

* **`game_stat.h`**: Modul `leaderboard` bergantung pada struktur `GameStat` yang didefinisikan dalam `game_stat.h` untuk menyimpan statistik pemain (skor dan waktu).

* **`leaderboard_state.h` dan `leaderboard_state.c`**: Kemungkinan besar, modul `leaderboard_state` akan menggunakan fungsi-fungsi dari `leaderboard.h` (seperti `load_leaderboard`, `insert_leaderboard`, dan `print_leaderboard` atau fungsi untuk rendering) untuk menampilkan dan mengelola data leaderboard di dalam state permainan leaderboard.

* **`main.c` (atau modul state game lainnya)**: Fungsi `insert_leaderboard` mungkin dipanggil setelah permainan berakhir untuk menyimpan skor pemain ke leaderboard. Fungsi `save_leaderboard` dan `load_leaderboard` kemungkinan akan dipanggil pada saat startup dan shutdown game untuk mempertahankan data leaderboard.
