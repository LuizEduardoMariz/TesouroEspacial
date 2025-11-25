#include "audio.h"

static Music music;  // variável interna para armazenar a música (LEMBRAR DE SUBSTITUIR STATIC)

void InitAudio() {
    InitAudioDevice();
    music = LoadMusicStream("assets/audio/heavy_battle.ogg");
    PlayMusicStream(music);
}

void UpdateAudio() {
    UpdateMusicStream(music);
}

void CloseAudio() {
    UnloadMusicStream(music);
    CloseAudioDevice();
}
