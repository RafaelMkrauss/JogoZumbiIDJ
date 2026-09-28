#include "Animator.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated)
    : Component(associated), frameStart(0), frameEnd(0), frameTime(0), currentFrame(0), timeElapsed(0), flip(SDL_FLIP_NONE) {}

void Animator::Update(float dt) {
    if (frameTime == 0) {
        return;
    }

    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        currentFrame++;
        timeElapsed -= frameTime;

        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }

        associated.GetComponent<SpriteRenderer>()->SetFrame(currentFrame, flip);
    }
}

void Animator::Render() {

}

void Animator::SetAnimation(std::string name) {
    if (name == current) {
        return;
    }

    std::unordered_map<std::string, Animation>::iterator it = animations.find(name);
    if (it != animations.end()) {
        Animation animation = it->second;
        frameStart = animation.frameStart;
        frameEnd = animation.frameEnd;
        frameTime = animation.frameTime;
        flip = animation.flip;
        currentFrame = frameStart;
        timeElapsed = 0;

        associated.GetComponent<SpriteRenderer>()->SetFrame(currentFrame, flip);

        current = name;
    }
}

void Animator::AddAnimation(std::string name, Animation animation) {
    std::unordered_map<std::string, Animation>::iterator it = animations.find(name);
    if (it == animations.end()) {
        animations.insert({name, animation});
    }
}
