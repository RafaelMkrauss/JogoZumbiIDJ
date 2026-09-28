#include "Bullet.h"
#include "SpriteRenderer.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), speed(Vec2(speed, 0).Rotate(angle)), distanceLeft(maxDistance), damage(damage) {
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Recursos/img/Bullet.png", 1, 1);
    associated.AddComponent(spriteRenderer);
    spriteRenderer->SetScale(0.5f, 0.5f);

    associated.angleDeg = angle * 180.0f / SDL_PI_F + 90.0f;
}

void Bullet::Update(float dt) {
    associated.box += speed * dt;

    distanceLeft -= speed.Magnitude() * dt;
    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {

}

int Bullet::GetDamage() {
    return damage;
}
