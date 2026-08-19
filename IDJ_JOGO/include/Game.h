#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>

class State;
struct MIX_Mixer;

class Game {
public:
    ~Game();

    static Game& GetInstance();

    void Run();

    SDL_Renderer* GetRenderer();
    MIX_Mixer* GetMixer();
    State& GetState();

private:
    Game(std::string title, int width, int height);

    static Game* instance;

    SDL_Window* window;
    SDL_Renderer* renderer;
    MIX_Mixer* mixer;
    State* state;
};

#endif
