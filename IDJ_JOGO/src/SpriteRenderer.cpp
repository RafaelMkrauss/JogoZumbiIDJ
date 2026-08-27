#include "SpriteRenderer.h"

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

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::SetCameraFollower(bool value) {
    sprite.cameraFollower = value;
}

void SpriteRenderer::Update(float dt) {
    (void)dt;
}

void SpriteRenderer::Render() {
    sprite.Render((int)associated.box.x, (int)associated.box.y, (int)associated.box.w, (int)associated.box.h);
}
