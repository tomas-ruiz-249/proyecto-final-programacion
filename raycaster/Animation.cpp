#include "Animation.h"

bool Animation::isAnimationDone()
{
    return currentFrame == numFrames-1;
}
