#include "Character.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Gun.h"
#include "Game.h"
#include "State.h"

Character* Character::player = nullptr;

Character::Command::Command(CommandType type, float x, float y) : type(type), pos(x, y) {}

Character::Character(GameObject& associated, std::string sprite)
    : Component(associated), speed(0, 0), linearSpeed(200), hp(100), deathTimer(), facingLeft(false)
{
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(spriteRenderer);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(6, 8, 0.2f));
    animator->AddAnimation("idleLeft", Animation(6, 8, 0.2f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("walking", Animation(0, 5, 0.1f));
    animator->AddAnimation("walkingLeft", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead", Animation(10, 10, 0));
    associated.AddComponent(animator);

    animator->SetAnimation("idle");

    player = this;
}

Character::~Character() {
    if (player == this) {
        player = nullptr;
    }
}

void Character::Start() {
    GameObject* gunGo = new GameObject();

    std::weak_ptr<GameObject> selfPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);
    Gun* gunCpt = new Gun(*gunGo, selfPtr);
    gunGo->AddComponent(gunCpt);

    gun = Game::GetInstance().GetState().AddObject(gunGo);
}

void Character::Update(float dt) {
    while (!taskQueue.empty()) {
        Command task = taskQueue.front();

        if (task.type == Command::MOVE) {
            speed = task.pos.Normalized() * linearSpeed;
        } else if (task.type == Command::SHOOT) {
            std::shared_ptr<GameObject> gunGoShared = gun.lock();
            if (gunGoShared != nullptr) {
                gunGoShared->GetComponent<Gun>()->Shoot(task.pos);
            }
        }

        taskQueue.pop();
    }

    if (hp <= 0) {
        associated.GetComponent<Animator>()->SetAnimation("dead");
        deathTimer.Update(dt);
        if (deathTimer.Get() > 2.0f) {
            associated.RequestDelete();
        }
        return;
    }

    associated.box += speed * dt;

    if (speed.x < 0) {
        facingLeft = true;
    } else if (speed.x > 0) {
        facingLeft = false;
    }

    Animator* animator = associated.GetComponent<Animator>();
    if (speed.Magnitude() > 0) {
        animator->SetAnimation(facingLeft ? "walkingLeft" : "walking");
    } else {
        animator->SetAnimation(facingLeft ? "idleLeft" : "idle");
    }
}

void Character::Render() {

}

void Character::Issue(Command task) {
    taskQueue.push(task);
}
