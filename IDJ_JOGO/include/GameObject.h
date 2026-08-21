#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "Rect.h"

#include <vector>

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();

    bool IsDead();
    void RequestDelete();

    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);

    template <class T>
    T* GetComponent() {
        for (Component* cpt : components) {
            T* castedCpt = dynamic_cast<T*>(cpt);
            if (castedCpt != nullptr) {
                return castedCpt;
            }
        }
        return nullptr;
    }

    Rect box;

private:
    std::vector<Component*> components;
    bool isDead;
};

#endif
