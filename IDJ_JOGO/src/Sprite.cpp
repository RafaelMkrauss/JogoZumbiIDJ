#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite() {
    texture = nullptr;
    width = 0;
    height = 0;
    frameCountW = 1;
    frameCountH = 1;
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) {
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

void Sprite::Render(int x, int y, int w, int h) {
    SDL_FRect srcRect;
    srcRect.x = (float)clipRect.x;
    srcRect.y = (float)clipRect.y;
    srcRect.w = (float)clipRect.w;
    srcRect.h = (float)clipRect.h;

    SDL_FRect dstRect;
    dstRect.x = (float)x;
    dstRect.y = (float)y;
    dstRect.w = (float)w;
    dstRect.h = (float)h;

    SDL_RenderTexture(Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect);
}

int Sprite::GetWidth() {
    return width / frameCountW;
}

int Sprite::GetHeight() {
    return height / frameCountH;
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
