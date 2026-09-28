#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "Rect.h"

#include <vector>

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();

    bool IsDead();
    void RequestDelete();

    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);

    template <class T>
    T *GetComponent()
    {
        for (Component *cpt : components)
        {
            T *castedCpt = dynamic_cast<T *>(cpt);
            if (castedCpt != nullptr)
            {
                return castedCpt;
            }
        }
        return nullptr;
    }

    void Start();

    Rect box;
    double angleDeg;
    int z;
    float depthOffset;

private:
    std::vector<Component *> components;
    bool isDead;
    bool started;
};

#endif
