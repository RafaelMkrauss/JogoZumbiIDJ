#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

#include <cmath>

Sprite::Sprite() : cameraFollower(false), flip(SDL_FLIP_NONE), scale(1, 1) {
    texture = nullptr;
    width = 0;
    height = 0;
    frameCountW = 1;
    frameCountH = 1;
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH)
    : cameraFollower(false), flip(SDL_FLIP_NONE), scale(1, 1) {
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    if (texture == nullptr) {
        return;
    }

    width = texture->w;
    height = texture->h;

    SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h, float angle) {
    SDL_FRect srcRect;
    srcRect.x = (float)clipRect.x;
    srcRect.y = (float)clipRect.y;
    srcRect.w = (float)clipRect.w;
    srcRect.h = (float)clipRect.h;

    SDL_FRect dstRect;
    if (cameraFollower) {
        dstRect.x = (float)x;
        dstRect.y = (float)y;
    } else {
        dstRect.x = (float)x - Camera::pos.x;
        dstRect.y = (float)y - Camera::pos.y;
    }
    dstRect.w = (float)w * scale.x;
    dstRect.h = (float)h * scale.y;

    SDL_RenderTextureRotated(Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect, angle, nullptr, flip);
}

int Sprite::GetWidth() {
    return (int)std::round((width / frameCountW) * scale.x);
}

int Sprite::GetHeight() {
    return (int)std::round((height / frameCountH) * scale.y);
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::SetFrame(int frame) {
    int frameWidth = width / frameCountW;
    int frameHeight = height / frameCountH;

    int frameX = (frame % frameCountW) * frameWidth;
    int frameY = (frame / frameCountW) * frameHeight;

    if (frameX + frameWidth > width || frameY + frameHeight > height) {
        return;
    }

    SetClip(frameX, frameY, frameWidth, frameHeight);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) {
        scale.x = scaleX;
    }
    if (scaleY != 0) {
        scale.y = scaleY;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFlip(SDL_FlipMode flip) {
    this->flip = flip;
}
