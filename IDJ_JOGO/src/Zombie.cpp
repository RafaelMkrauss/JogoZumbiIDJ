#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitpoints(100), deathSound("Recursos/audio/Dead (1).wav")
{
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(spriteRenderer);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    associated.AddComponent(animator);

    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage) {
    if (hitpoints <= 0) {
        return;
    }

    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.GetComponent<Animator>()->SetAnimation("dead");
        deathSound.Play(1);
    }
}

void Zombie::Update(float dt) {
    (void)dt;
    Damage(1);
}

void Zombie::Render() {

}
