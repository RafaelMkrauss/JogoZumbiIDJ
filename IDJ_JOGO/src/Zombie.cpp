#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "Camera.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitpoints(100),
      deathSound("Recursos/audio/Dead (1).wav"),
      hitSound("Recursos/audio/Hit0 (3).wav"),
      hit(false)
{
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(spriteRenderer);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 0.33f));
    animator->AddAnimation("hit", Animation(4, 4, 0));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    associated.AddComponent(animator);

    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage) {
    if (hitpoints <= 0) {
        return;
    }

    hitpoints -= damage;
    hitSound.Play(1);

    if (hitpoints <= 0) {
        associated.GetComponent<Animator>()->SetAnimation("dead");
        deathSound.Play(1);
        deathTimer.Restart();
    } else {
        hit = true;
        hitTimer.Restart();
        associated.GetComponent<Animator>()->SetAnimation("hit");
    }
}

void Zombie::Update(float dt) {
    hitTimer.Update(dt);
    deathTimer.Update(dt);

    InputManager& input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        Vec2 mousePos((float)input.GetMouseX() + Camera::pos.x, (float)input.GetMouseY() + Camera::pos.y);
        if (associated.box.Contains(mousePos)) {
            Damage(34);
        }
    }

    if (hitpoints <= 0) {
        if (deathTimer.Get() > 5) {
            associated.RequestDelete();
        }
        return;
    }

    if (hit && hitTimer.Get() >= 0.5f) {
        associated.GetComponent<Animator>()->SetAnimation("walking");
        hit = false;
    }
}

void Zombie::Render() {

}
