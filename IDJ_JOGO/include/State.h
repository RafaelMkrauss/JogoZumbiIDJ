#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "GameObject.h"

#include <vector>
#include <memory>

class State {
public:
    State();
    ~State();

    void AddObject(GameObject* go);

    bool QuitRequested();

    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    Music music;

    bool quitRequested;

    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif
