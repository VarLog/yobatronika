//
//  AnimatedGraphic.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 11.04.15.
//
//

#include "AnimatedGraphic.h"

using namespace Yoba;

AnimatedGraphic::AnimatedGraphic(const LoaderParams &params, const int animSpeed)
: SDLGameObject(params), m_animSpeed(animSpeed)
{
    
}

AnimatedGraphic::~AnimatedGraphic() {
    clean();
}

void AnimatedGraphic::draw() {
    SDLGameObject::draw();
}

void AnimatedGraphic::clean() {
    SDLGameObject::clean();
}

void AnimatedGraphic::update() {
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames)) + 1;
}
