#include "Resources.h"
#include "Game.h"

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, MIX_Audio*> Resources::musicTable;
std::unordered_map<std::string, MIX_Audio*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        std::cerr << "Erro ao carregar imagem '" << file << "': " << SDL_GetError() << "\n";
        return nullptr;
    }
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    imageTable.insert({file, texture});
    return texture;
}

void Resources::ClearImages() {
    for (auto& pair : imageTable) {
        SDL_DestroyTexture(pair.second);
    }
    imageTable.clear();
}

MIX_Audio* Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    }

    MIX_Audio* music = MIX_LoadAudio(Game::GetInstance().GetMixer(), file.c_str(), false);
    if (music == nullptr) {
        std::cerr << "Erro ao carregar musica '" << file << "': " << SDL_GetError() << "\n";
        return nullptr;
    }

    musicTable.insert({file, music});
    return music;
}

void Resources::ClearMusics() {
    for (auto& pair : musicTable) {
        MIX_DestroyAudio(pair.second);
    }
    musicTable.clear();
}

MIX_Audio* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    }

    MIX_Audio* chunk = MIX_LoadAudio(Game::GetInstance().GetMixer(), file.c_str(), true);
    if (chunk == nullptr) {
        chunk = MIX_LoadAudio(Game::GetInstance().GetMixer(), file.c_str(), false);
    }
    if (chunk == nullptr) {
        std::cerr << "Erro ao carregar som '" << file << "': " << SDL_GetError() << "\n";
        return nullptr;
    }

    soundTable.insert({file, chunk});
    return chunk;
}

void Resources::ClearSounds() {
    for (auto& pair : soundTable) {
        MIX_DestroyAudio(pair.second);
    }
    soundTable.clear();
}
