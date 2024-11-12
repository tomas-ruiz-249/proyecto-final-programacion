#include "Animation.h"

int Animation::getCurrentFrame()
{
    return currentFrame;
}

bool Animation::isAnimationDone()
{
    return currentFrame == numFrames-1;
}

void Animation::resetAnimation()
{
    currentFrame = 0;
}

void Animation::nextFrame()
{
    if (currentFrame + 1 == numFrames) {
        currentFrame = 0;
    }
    else {
		currentFrame++;
    }
}
