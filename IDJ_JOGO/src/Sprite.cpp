#include "Sprite.h"
#include "Game.h"

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

Sprite::Sprite() {
    texture = nullptr;
    width = 0;
    height = 0;
}

Sprite::Sprite(std::string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        return;
    }

    width = texture->w;
    height = texture->h;

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_FRect srcRect;
    srcRect.x = (float)clipRect.x;
    srcRect.y = (float)clipRect.y;
    srcRect.w = (float)clipRect.w;
    srcRect.h = (float)clipRect.h;

    SDL_FRect dstRect;
    dstRect.x = (float)x;
    dstRect.y = (float)y;
    dstRect.w = (float)clipRect.w;
    dstRect.h = (float)clipRect.h;

    SDL_RenderTexture(Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}
