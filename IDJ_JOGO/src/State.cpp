#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"

State::State() : music("Recursos/audio/BGM (3).wav") {
    quitRequested = false;

    GameObject* go = new GameObject();
    SpriteRenderer* spriteRenderer = new SpriteRenderer(*go, "Recursos/img/Background (3).png");
    spriteRenderer->SetCameraFollower(true);
    go->AddComponent(spriteRenderer);
    AddObject(go);

    GameObject* mapGo = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    TileMap* tileMap = new TileMap(*mapGo, "Recursos/map/map (2).txt", tileSet);
    tileMap->SetParallax(0, 0.5f);
    mapGo->AddComponent(tileMap);
    mapGo->box.x = 0;
    mapGo->box.y = 0;
    AddObject(mapGo);

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
    Camera::Update(dt);

    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    if (input.KeyPress(SDLK_SPACE)) {
        GameObject* zb = new GameObject();
        Zombie* zombie = new Zombie(*zb);
        zb->AddComponent(zombie);
        zb->box.x = (float)input.GetMouseX() + Camera::pos.x;
        zb->box.y = (float)input.GetMouseY() + Camera::pos.y;
        AddObject(zb);
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
