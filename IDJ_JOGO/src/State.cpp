#include "State.h"

#define INCLUDE_SDL
#include "SDL_include.h"

State::State() : bg("Recursos/img/Background (3).png"), music("Recursos/audio/BGM (3).wav") {
    quitRequested = false;
    music.Play();
}

void State::LoadAssets() {
    
}

void State::Update(float dt) {
    (void)dt; 

    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            quitRequested = true;
        }
    }
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}
