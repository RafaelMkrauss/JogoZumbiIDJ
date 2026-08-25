#include "Music.h"
#include "Game.h"
#include "Resources.h"

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
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);
    if (music == nullptr) {
        return;
    }

    if (track == nullptr) {
        track = MIX_CreateTrack(Game::GetInstance().GetMixer());
        if (track == nullptr) {
            std::cerr << "Erro ao criar track de audio: " << SDL_GetError() << "\n";
            return;
        }
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
