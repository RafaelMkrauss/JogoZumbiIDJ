#ifndef CHARACTER_H
#define CHARACTER_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

#include <memory>
#include <queue>
#include <string>

class Character : public Component {
    public:
        class Command {
            public:
                enum CommandType {
                    MOVE,
                    SHOOT
                };

                Command(CommandType type, float x, float y);

                CommandType type;
                Vec2 pos;
        };

        Character(GameObject& associated, std::string sprite);
        ~Character();

        void Start() override;
        void Update(float dt) override;
        void Render() override;

        void Issue(Command task);

        static Character* player;

    private:
        std::weak_ptr<GameObject> gun;
        std::queue<Command> taskQueue;
        Vec2 speed;
        float linearSpeed;
        int hp;
        Timer deathTimer;
        bool facingLeft;
};

#endif
