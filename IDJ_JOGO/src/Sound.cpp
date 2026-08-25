#include "Sound.h"
#include "Game.h"
#include "Resources.h"

#include <iostream>

Sound::Sound() {
    chunk = nullptr;
    track = nullptr;
}

Sound::Sound(std::string file) {
    chunk = nullptr;
    track = nullptr;
    Open(file);
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Stop();
        MIX_DestroyTrack(track);
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
    if (chunk == nullptr) {
        return;
    }

    if (track == nullptr) {
        track = MIX_CreateTrack(Game::GetInstance().GetMixer());
        if (track == nullptr) {
            std::cerr << "Erro ao criar track de audio: " << SDL_GetError() << "\n";
            return;
        }
    }

    MIX_SetTrackAudio(track, chunk);
}

void Sound::Play(int times) {
    if (chunk == nullptr) {
        return;
    }

    MIX_SetTrackLoops(track, times - 1);
    MIX_PlayTrack(track, 0);
}

void Sound::Stop() {
    if (chunk != nullptr) {
        MIX_StopTrack(track, 0);
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}
