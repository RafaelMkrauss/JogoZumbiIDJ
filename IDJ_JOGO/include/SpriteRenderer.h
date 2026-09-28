#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

#include <string>

class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);

    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrame(int frame, SDL_FlipMode flip);
    void SetCameraFollower(bool value);

    void SetScale(float scaleX, float scaleY);

    void Update(float dt) override;
    void Render() override;

private:
    Sprite sprite;
};

#endif
