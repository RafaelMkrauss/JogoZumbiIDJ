#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "Character.h"
#include "PlayerController.h"

#include <algorithm>

State::State() : music("Recursos/audio/BGM (3).wav") , started(false) {
    quitRequested = false;

    GameObject* go = new GameObject();
    SpriteRenderer* spriteRenderer = new SpriteRenderer(*go, "Recursos/img/Background (3).png");
    spriteRenderer->SetCameraFollower(true);
    go->AddComponent(spriteRenderer);
    go->z = -2;
    AddObject(go);

    GameObject* mapGo = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    TileMap* tileMap = new TileMap(*mapGo, "Recursos/map/map (2).txt", tileSet);
    tileMap->SetParallax(0, 0.5f);
    mapGo->AddComponent(tileMap);
    mapGo->box.x = 0;
    mapGo->box.y = 0;
    mapGo->z = -1;
    AddObject(mapGo);

    GameObject* characterGo = new GameObject();
    Character* character = new Character(*characterGo, "Recursos/img/Player (2).png");
    characterGo->AddComponent(character);
    PlayerController* playerController = new PlayerController(*characterGo);
    characterGo->AddComponent(playerController);
    characterGo->box.x = 1280;
    characterGo->box.y = 1280;
    AddObject(characterGo);

    Camera::Follow(characterGo);

    music.Play();
} 

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {

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
    std::vector<GameObject*> renderOrder;
    renderOrder.reserve(objectArray.size());
    for (auto& obj : objectArray) {
        renderOrder.push_back(obj.get());
    }

    std::stable_sort(renderOrder.begin(), renderOrder.end(), [](GameObject* a, GameObject* b) {
        if (a->z != b->z) {
            return a->z < b->z;
        }
        float depthA = a->box.y + a->box.h + a->depthOffset;
        float depthB = b->box.y + b->box.h + b->depthOffset;
        return depthA < depthB;
    });

    for (GameObject* go : renderOrder) {
        go->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Start() {
    LoadAssets();
    for (unsigned i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> sharedGo(go);
    objectArray.push_back(sharedGo);
    if (started) {
        go->Start();
    }
    return std::weak_ptr<GameObject>(sharedGo);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (auto& obj : objectArray) {
        if (obj.get() == go) {
            return std::weak_ptr<GameObject>(obj);
        }
    }
    return std::weak_ptr<GameObject>();
}
