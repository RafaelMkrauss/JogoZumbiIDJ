#include "Gun.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Bullet.h"
#include "Component.h"
#include "Game.h"
#include "State.h"

#include <string>

const float GUN_DISTANCE = 40.0f;

Gun::Gun(GameObject &associated, std::weak_ptr<GameObject> character)
    : Component(associated), character(character),
      shotSound("Recursos/audio/Range (3).wav"),
      reloadSound("Recursos/audio/PumpAction (3).wav"),
      cooldownState(0), cdTimer(), angle(0)
{
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Recursos/img/Gun (2).png", 3, 2);
    associated.AddComponent(spriteRenderer);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle", Animation(0, 0, 0));
    animator->AddAnimation("reloading", Animation(1, 5, 0.1f));
    animator->AddAnimation("idleFlipped", Animation(0, 0, 0, SDL_FLIP_VERTICAL));
    animator->AddAnimation("reloadingFlipped", Animation(1, 5, 0.1f, SDL_FLIP_VERTICAL));
    associated.AddComponent(animator);

    animator->SetAnimation("idle");
}

void Gun::Update(float dt) {
    std::shared_ptr<GameObject> charGo = character.lock();
    if (charGo == nullptr) {
        associated.RequestDelete();
        return;
    }

    cdTimer.Update(dt);

    Vec2 charCenter = charGo->box.Center();
    associated.box.x = charCenter.x - associated.box.w / 2;
    associated.box.y = charCenter.y - associated.box.h / 2;

    Vec2 offset = Vec2(GUN_DISTANCE, 0).Rotate(angle);
    associated.box.x += offset.x;
    associated.box.y += offset.y;

    associated.angleDeg = angle * 180.0f / SDL_PI_F;

    float charFeet = charGo->box.y + charGo->box.h;
    float gunFeet = associated.box.y + associated.box.h;
    associated.depthOffset = charFeet - gunFeet + 0.1f;

    switch (cooldownState) {
        case 1:
            if (cdTimer.Get() > 0.1f) {
                cooldownState = 2;
                reloadSound.Play(1);
                cdTimer.Restart();
            }
            break;
        case 2:
            if (cdTimer.Get() > 0.4f) {
                cooldownState = 3;
                cdTimer.Restart();
            }
            break;
        case 3:
            if (cdTimer.Get() > 0.1f) {
                cooldownState = 0;
                cdTimer.Restart();
            }
            break;
        default:
            break;
    }

    std::string animation = (cooldownState == 2) ? "reloading" : "idle";
    bool aimingLeft = angle > SDL_PI_F / 2 || angle < -SDL_PI_F / 2;
    if (aimingLeft) {
        animation += "Flipped";
    }
    associated.GetComponent<Animator>()->SetAnimation(animation);
}

void Gun::Render() {

}

void Gun::Shoot(Vec2 target) {
    if (cooldownState != 0) {
        return;
    }

    std::shared_ptr<GameObject> charGo = character.lock();
    if (charGo == nullptr) {
        return;
    }

    Vec2 charCenter = charGo->box.Center();
    angle = (target - charCenter).Angle();

    shotSound.Play(1);

    Vec2 muzzle = charCenter + Vec2(GUN_DISTANCE + associated.box.w / 2, 0).Rotate(angle);

    GameObject* bulletGo = new GameObject();
    Bullet* bullet = new Bullet(*bulletGo, angle, 500.0f, 10, 400.0f);
    bulletGo->AddComponent(bullet);
    bulletGo->box.x = muzzle.x - bulletGo->box.w / 2;
    bulletGo->box.y = muzzle.y - bulletGo->box.h / 2;
    Game::GetInstance().GetState().AddObject(bulletGo);

    cooldownState = 1;
    cdTimer.Restart();
}
