#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#include "SDL_include.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include <unordered_map>

class Resources {
public:
    static SDL_Texture* GetImage(std::string file);
    static void ClearImages();

    static MIX_Audio* GetMusic(std::string file);
    static void ClearMusics();

    static MIX_Audio* GetSound(std::string file);
    static void ClearSounds();

private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, MIX_Audio*> musicTable;
    static std::unordered_map<std::string, MIX_Audio*> soundTable;
};

#endif
