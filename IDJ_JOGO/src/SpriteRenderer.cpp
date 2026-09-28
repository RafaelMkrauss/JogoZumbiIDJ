#include "SpriteRenderer.h"

#include <cmath>

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH) {
    associated.box.w = (float)sprite.GetWidth();
    associated.box.h = (float)sprite.GetHeight();
    sprite.SetFrame(0);
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    associated.box.w = (float)sprite.GetWidth();
    associated.box.h = (float)sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame, SDL_FlipMode flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}

void SpriteRenderer::SetCameraFollower(bool value) {
    sprite.cameraFollower = value;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    Vec2 center = associated.box.Center();

    sprite.SetScale(scaleX, scaleY);
    associated.box.w = (float)sprite.GetWidth();
    associated.box.h = (float)sprite.GetHeight();

    associated.box.x = center.x - associated.box.w / 2;
    associated.box.y = center.y - associated.box.h / 2;
}

void SpriteRenderer::Update(float dt) {
    (void)dt;
}

void SpriteRenderer::Render() {
    Vec2 scale = sprite.GetScale();
    int unscaledW = (int)std::round(associated.box.w / scale.x);
    int unscaledH = (int)std::round(associated.box.h / scale.y);

    sprite.Render((int)associated.box.x, (int)associated.box.y, unscaledW, unscaledH, (float)associated.angleDeg);
}
