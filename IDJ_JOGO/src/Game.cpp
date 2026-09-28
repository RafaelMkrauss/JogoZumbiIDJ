#include "Game.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Rafael Mileo Moreira Krauss Guimaraes - 242024763", 1200, 900);
    }
    return *instance;
}

Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        std::cerr << "ERRO: tentando criar uma segunda instancia de Game\n";
        exit(1);
    }
    instance = this;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << "\n";
        exit(1);
    }

    frameStart = (int)SDL_GetTicks();
    dt = 0;


    if (!MIX_Init()) {
        std::cerr << "Erro ao inicializar SDL_mixer: " << SDL_GetError() << "\n";
        exit(1);
    }

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (mixer == nullptr) {
        std::cerr << "Erro ao abrir dispositivo de audio: " << SDL_GetError() << "\n";
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (window == nullptr) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << "\n";
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cerr << "Erro ao criar renderer: " << SDL_GetError() << "\n";
        exit(1);
    }

    state = new State();
}

Game::~Game() {
    delete state;

    MIX_DestroyMixer(mixer);
    MIX_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

MIX_Mixer* Game::GetMixer() {
    return mixer;
}

State& Game::GetState() {
    return *state;
}

void Game::CalculateDeltaTime() {
    int currentFrame = (int)SDL_GetTicks();
    dt = (currentFrame - frameStart) / 1000.0f;
    frameStart = currentFrame;
}

float Game::GetDeltaTime() {
    return dt;
}

void Game::Run() {
    state->Start();
    while (!state->QuitRequested()) {
        CalculateDeltaTime();
        InputManager::GetInstance().Update();

        state->Update(dt);
        state->Render();

        SDL_RenderPresent(renderer);

        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}
