#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include "Vec2.h"
#include <string>

class Sprite
{
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(std::string file);

    void SetClip(int x, int y, int w, int h);

    void Render(int x, int y, int w, int h, float angle = 0);

    void SetFrame(int frame);

    void SetFrameCount(int frameCountW, int frameCountH);

    void SetScale(float scaleX, float scaleY);

    Vec2 GetScale();

    void SetFlip(SDL_FlipMode flip);

    int GetWidth();
    int GetHeight();

    bool IsOpen();

    bool cameraFollower;

private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;

    SDL_FlipMode flip;
    Vec2 scale;
};

#endif
