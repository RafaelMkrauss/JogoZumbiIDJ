#include "GameObject.h"

#include <algorithm>

GameObject::GameObject() : angleDeg(0), z(0), depthOffset(0), isDead(false), started(false) {}

GameObject::~GameObject() {
    
    for (int i = (int)components.size() - 1; i >= 0; i--) {
        delete components[i];
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for (Component* cpt : components) {
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for (Component* cpt : components) {
        cpt->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
    if (started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    std::vector<Component*>::iterator it = std::find(components.begin(), components.end(), cpt);
    if (it != components.end()) {
        delete *it;
        components.erase(it);
    }
}

void GameObject::Start() {
    
    for (unsigned i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}
