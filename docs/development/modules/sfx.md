# Modul `SFX`

**Pembuat:** [Hisyam Khaeru Umam (241511078)](https://github.com/Umeem26)

**File:** `SFX.c` & `SFX.h`

## Variabel dan Konstanta

### **stage0_bgm**

```c
extern Mix_Music *stage0_bgm;
```

Variabel global untuk menyimpan musik latar belakang stage 0.

### **menu_bgm**

```c
extern Mix_Music *menu_bgm;
```

Variabel global untuk menyimpan musik latar belakang menu.

### **stage1_bgm**

```c
extern Mix_Music *stage1_bgm;
```

Variabel global untuk menyimpan musik latar belakang stage 1.

### **win_bgm**

```c
extern Mix_Music *win_bgm;
```

Variabel global untuk menyimpan musik kemenangan.

### **jump_sfx**

```c
extern Mix_Chunk *jump_sfx;
```

Variabel global untuk menyimpan efek suara lompatan.

### **gate_sfx**

```c
extern Mix_Chunk *gate_sfx;
```

Variabel global untuk menyimpan efek suara gerbang.

### **coin_sfx**

```c
extern Mix_Chunk *coin_sfx;
```

Variabel global untuk menyimpan efek suara koin.

### **dead_sfx**

```c
extern Mix_Chunk *dead_sfx;
```

Variabel global untuk menyimpan efek suara kematian.

### **gameover_sfx**

```c
extern Mix_Chunk *gameover_sfx;
```

Variabel global untuk menyimpan efek suara game over.

---

## Penjelasan Setiap Fungsi

### **init_audio**

```c title="SFX.h"
void init_audio();
```

Fungsi `init_audio` bertugas untuk menginisialisasi sistem audio menggunakan SDL Mixer, mengatur format audio, membuka audio device, dan memuat semua file musik dan efek suara yang akan digunakan dalam game.

```c title="SFX.c"
void init_audio()
{
    SDL_AudioSpec spec = {
        .format = SDL_AUDIO_S8,
        .freq = 44100,
        .channels = 2,
    };
    if (!Mix_Init(MIX_INIT_MP3) || !Mix_OpenAudio(0, &spec))
    {
        printf("Failed to initialize SDL3 Mixer: %s\n", SDL_GetError());
        return;
    }

    // Memuat musik dan efek suara
    stage0_bgm = load_music("assets/SFX/bg-music1.mp3");
    stage1_bgm = load_music("assets/SFX/bg-music2.mp3");
    menu_bgm = load_music("assets/SFX/bg-music-home1.mp3");
    win_bgm = load_music("assets/SFX/champion.mp3");
    jump_sfx = load_sound("assets/SFX/jump.wav");
    gate_sfx = load_sound("assets/SFX/exit-gate.wav");
    coin_sfx = load_sound("assets/SFX/coin.wav");
    dead_sfx = load_sound("assets/SFX/dead.wav");
    gameover_sfx = load_sound("assets/SFX/game-over.wav");
}
```

---

### **load_sound**

```c title="SFX.h"
Mix_Chunk *load_sound(const char *file);
```

Fungsi `load_sound` menerima path file audio dan memuatnya sebagai efek suara (chunk).

```c title="SFX.c"
Mix_Chunk *load_sound(const char *file)
{
    Mix_Chunk *sound = Mix_LoadWAV(file);
    if (!sound)
    {
        printf("Failed to load sound %s: %s\n", file, SDL_GetError());
    }
    return sound;
}
```

---

### **load_music**

```c title="SFX.h"
Mix_Music *load_music(const char *file);
```

Fungsi `load_music` menerima path file audio dan memuatnya sebagai musik.

```c title="SFX.c"
Mix_Music *load_music(const char *file)
{
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music)
    {
        printf("Failed to load music %s: %s\n", file, SDL_GetError());
    }
    return music;
}
```

---

### **play_sound**

```c title="SFX.h"
void play_sound(Mix_Chunk *sound, int channel, int loops);
```

Fungsi `play_sound` digunakan untuk memainkan efek suara pada channel tertentu dengan jumlah loop yang ditentukan.

```c title="SFX.c"
void play_sound(Mix_Chunk *sound, int channel,int loops)
{
    if (sound)
    {
        Mix_PlayChannel(channel, sound, loops);
    }
}
```

---

### **play_music**

```c title="SFX.h"
void play_music(Mix_Music *sound, int loops);
```

Fungsi `play_music` digunakan untuk memainkan musik dengan jumlah loop yang ditentukan.

```c title="SFX.c"
void play_music(Mix_Music *sound, int loops)
{
    if (sound)
    {
        Mix_PlayMusic(sound, loops);
    }
}
```

---

### **stop_music**

```c title="SFX.h"
void stop_music();
```

Fungsi `stop_music` digunakan untuk menghentikan musik yang sedang diputar.

```c title="SFX.c"
void stop_music()
{
    Mix_HaltMusic();
}
```

---

### **stop_sound**

```c title="SFX.h"
void stop_sound(int channel);
```

Fungsi `stop_sound` digunakan untuk menghentikan efek suara yang sedang diputar pada channel tertentu.

```c title="SFX.c"
void stop_sound(int channel)
{
    Mix_HaltChannel(channel);
}
```

---

### **cleanup_audio**

```c title="SFX.h"
void cleanup_audio();
```

Fungsi `cleanup_audio` bertugas untuk membersihkan semua sumber daya audio yang telah dialokasikan dengan menutup audio device dan keluar dari sistem Mixer.

```c title="SFX.c"
void cleanup_audio()
{
    Mix_CloseAudio();
    Mix_Quit();
}
```

---

## Interaksi dengan modul lain

Modul `SFX` memiliki interaksi yang luas dengan modul lain dalam game. Fungsi-fungsi seperti `play_sound` dan `play_music` dipanggil dari berbagai tempat di kode yang membutuhkan pemutaran audio. Beberapa contoh interaksi meliputi:

* Pemanggilan `play_sound(jump_sfx, ...)` di modul player ketika karakter melompat.
* Pemanggilan `play_music(stage0_bgm, -1)` di modul stage 0 untuk memulai musik latar belakang.
* Pemanggilan `play_music(menu_bgm, -1)` di modul menu state untuk memulai musik latar belakang menu.
* Pemanggilan `stop_music()` ketika terjadi transisi antar state atau kondisi tertentu dalam game.

Secara umum, modul `SFX` menyediakan layanan audio yang dapat digunakan oleh hampir semua bagian game yang memerlukan efek suara atau musik.

---
