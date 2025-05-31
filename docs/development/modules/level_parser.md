# Modul `level_parser`

**Pembuat:** [Ikhsan Satriadi (241511080)](https://github.com/ikhsan3adi)

**File:** `level_parser.h` & `level_parser.c`

---

## Variabel dan Konstanta

### **MAX_LEVELS**

```c title="level_parser.h"
#define MAX_LEVELS 1000
```

Konstanta `MAX_LEVELS` mendefinisikan jumlah maksimum level yang dapat dimuat ke dalam game.

---

## Penjelasan Setiap Fungsi

### **get_filename_ext**

```c title="level_parser.h"
const char *get_filename_ext(const char *filename);
```

Fungsi ini mengembalikan pointer ke ekstensi nama file dari string `filename` yang diberikan.

### **get_json_string**

```c title="level_parser.h"
char *get_json_string(const char *file);
```

Fungsi ini membaca seluruh konten file yang ditentukan oleh `file` dan mengembalikan isinya sebagai string yang dialokasikan secara dinamis.

### **get_level_from_json**

```c title="level_parser.h"
LevelNode *get_level_from_json(const char *json_str);
```

Fungsi ini mengurai string JSON yang diberikan (`json_str`) dan mengisi struktur `LevelNode` dengan data yang relevan. Fungsi ini menggunakan array pointer fungsi untuk memanggil fungsi-fungsi `set_*_from_json` yang sesuai berdasarkan urutan kunci dalam file JSON.

### **load_json_levels**

```c title="level_parser.h"
void load_json_levels(LevelNode **head, const char *dir);
```

---

## Internal Functions

Fungsi untuk mengurai data dari objek JSON ke dalam struktur `LevelNode`. Setiap fungsi ini bertanggung jawab untuk mengisi bagian tertentu dari `LevelNode` berdasarkan data yang ditemukan dalam objek JSON.

### **set_level_name_from_json**

```c title="level_parser.c"
void set_level_name_from_json(LevelNode *node, cJSON *json);
```

Mengatur nama level dari objek JSON.

### **set_prev_level_from_json**

```c title="level_parser.c"
void set_prev_level_from_json(LevelNode *node, cJSON *json);
```

Mengatur nama level sebelumnya dari objek JSON.

### **set_next_level_from_json**

```c title="level_parser.c"
void set_next_level_from_json(LevelNode *node, cJSON *json);
```

Mengatur nama level berikutnya dari objek JSON.

### **set_player_spawn_from_json**

```c title="level_parser.c"
void set_player_spawn_from_json(LevelNode *node, cJSON *json);
```

Mengatur posisi spawn pemain dari objek JSON.

### **set_fg_color_from_json_array**

```c title="level_parser.c"
void set_fg_color_from_json_array(LevelNode *node, cJSON *json);
```

Mengatur warna foreground dari objek JSON array.

### **set_bg_color_from_json_array**

```c title="level_parser.c"
void set_bg_color_from_json_array(LevelNode *node, cJSON *json);
```

Mengatur warna background dari objek JSON array.

### **set_bg_image_from_json**

```c title="level_parser.c"
void set_bg_image_from_json(LevelNode *node, cJSON *json);
```

Mengatur nama file gambar background dari objek JSON.

### **set_bg_music_from_json**

```c title="level_parser.c"
void set_bg_music_from_json(LevelNode *node, cJSON *json);
```

Mengatur nama file musik background dari objek JSON.

### **set_switches_from_json**

```c title="level_parser.c"
void set_switches_from_json(LevelNode *node, cJSON *json);
```

Mengatur data switch dari objek JSON. Fungsi ini mengurai array JSON menjadi struktur `Switch` yang berisi posisi tombol dan daftar switch yang terhubung.

### **set_switch_obstacles_from_json**

```c title="level_parser.c"
void set_switch_obstacles_from_json(LevelNode *node, cJSON *json);
```

Mengatur data obstacle yang terhubung ke switch dari objek JSON. Fungsi ini mengurai array JSON menjadi struktur `Switch_Obstacles` yang berisi posisi tombol, daftar switch, dan daftar obstacle yang terhubung.

### **set_saws_from_json**

```c title="level_parser.c"
void set_saws_from_json(LevelNode *node, cJSON *json);
```

Mengatur data gergaji (saws) dari objek JSON. Fungsi ini mengurai array JSON menjadi struktur `Saw` yang berisi transformasi (posisi dan ukuran) dan fisika (kecepatan).

### **set_maps_from_json**

```c title="level_parser.c"
void set_maps_from_json(LevelNode *node, cJSON *json);
```

Mengatur data peta (map) dari objek JSON. Fungsi ini mengisi array 2D `node->map` dengan nilai integer dari array JSON.

Fungsi ini memuat semua file JSON dari direktori yang ditentukan (`dir`), mengurai setiap file menjadi `LevelNode`, dan membangun linked list dari level-level yang dimuat.
