#include "Music.h"
#include "Game.h"

#include <iostream>

Music::Music() {
    music = nullptr;
    track = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
    track = nullptr;
    Open(file);
}

Music::~Music() {
    Stop();

    if (track != nullptr) {
        MIX_DestroyTrack(track);
    }
    if (music != nullptr) {
        MIX_DestroyAudio(music);
    }
}

void Music::Open(std::string file) {
    if (music != nullptr) {
        MIX_DestroyAudio(music);
        music = nullptr;
    }

    MIX_Mixer* mixer = Game::GetInstance().GetMixer();

    music = MIX_LoadAudio(mixer, file.c_str(), false);
    if (music == nullptr) {
        std::cerr << "Erro ao carregar musica '" << file << "': " << SDL_GetError() << "\n";
        return;
    }

    track = MIX_CreateTrack(mixer);
    if (track == nullptr) {
        std::cerr << "Erro ao criar track de audio: " << SDL_GetError() << "\n";
        return;
    }

    MIX_SetTrackAudio(track, music);
}

void Music::Play(int times) {
    if (music == nullptr || track == nullptr) {
        return;
    }

    if (times == 0) {
        return;
    }

    MIX_SetTrackLoops(track, times == -1 ? -1 : times - 1);
    MIX_PlayTrack(track, 0);
}

void Music::Stop(int msToStop) {
    if (track == nullptr) {
        return;
    }

    Sint64 fadeFrames = MIX_TrackMSToFrames(track, msToStop);
    MIX_StopTrack(track, fadeFrames);
}

bool Music::IsOpen() {
    return music != nullptr;
}
