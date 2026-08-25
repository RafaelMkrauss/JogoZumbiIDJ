#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"

#define INCLUDE_SDL
#include "SDL_include.h"

State::State() : music("Recursos/audio/BGM (3).wav") {
    quitRequested = false;

    GameObject* go = new GameObject();
    SpriteRenderer* spriteRenderer = new SpriteRenderer(*go, "Recursos/img/Background (3).png");
    go->AddComponent(spriteRenderer);
    AddObject(go);

    GameObject* mapGo = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    TileMap* tileMap = new TileMap(*mapGo, "Recursos/map/map (2).txt", tileSet);
    mapGo->AddComponent(tileMap);
    mapGo->box.x = 0;
    mapGo->box.y = 0;
    AddObject(mapGo);

    GameObject* zb = new GameObject();
    Zombie* zombie = new Zombie(*zb);
    zb->AddComponent(zombie);
    zb->box.x = 600;
    zb->box.y = 450;
    AddObject(zb);

    GameObject* zb2 = new GameObject();
    Zombie* zombie2 = new Zombie(*zb2);
    zb2->AddComponent(zombie2);
    zb2->box.x = 800;
    zb2->box.y = 300;
    AddObject(zb2);

    GameObject* zb3 = new GameObject();
    Zombie* zombie3 = new Zombie(*zb3);
    zb3->AddComponent(zombie3);
    zb3->box.x = 400;
    zb3->box.y = 600;
    AddObject(zb3);

    music.Play();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {

}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}

void State::Update(float dt) {
   
    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            quitRequested = true;
        }
    }

    
    for (int i = (int)objectArray.size() - 1; i >= 0; i--) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render() {
    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}
