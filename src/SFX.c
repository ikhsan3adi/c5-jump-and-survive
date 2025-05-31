#include <stdio.h>
#include "SFX.h"

Mix_Music *stage0_bgm;
Mix_Music *menu_bgm;
Mix_Music *stage1_bgm;
Mix_Music *win_bgm;
Mix_Chunk *jump_sfx;
Mix_Chunk *gate_sfx;
Mix_Chunk *coin_sfx;
Mix_Chunk *dead_sfx;
Mix_Chunk *gameover_sfx;

Mix_Music *current_bgm = NULL;

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

Mix_Chunk *load_sound(const char *file)
{
    Mix_Chunk *sound = Mix_LoadWAV(file);
    if (!sound)
    {
        printf("Failed to load sound %s: %s\n", file, SDL_GetError());
    }
    return sound;
}

Mix_Music *load_music(const char *file)
{
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music)
    {
        printf("Failed to load music %s: %s\n", file, SDL_GetError());
    }
    return music;
}

void play_sound(Mix_Chunk *sound, int channel, int loops)
{
    if (sound)
    {
        Mix_PlayChannel(channel, sound, loops);
    }
}

void play_music(Mix_Music *sound, int loops)
{
    if (sound)
    {
        Mix_PlayMusic(sound, loops);
    }
}

void pause_music()
{
    Mix_PauseMusic();
}

void resume_music()
{
    Mix_ResumeMusic();
}

void stop_music()
{
    Mix_HaltMusic();
}

void stop_sound(int channel)
{
    Mix_HaltChannel(channel);
}

void cleanup_audio()
{
    Mix_CloseAudio();
    Mix_Quit();
}
