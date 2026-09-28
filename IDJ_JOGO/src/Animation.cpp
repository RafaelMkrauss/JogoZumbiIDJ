#include "Animation.h"

Animation::Animation(int frameStart, int frameEnd, float frameTime, SDL_FlipMode flip)
    : frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime), flip(flip) {}
