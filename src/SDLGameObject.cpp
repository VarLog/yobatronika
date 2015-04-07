//
//  SDLGameObject.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 08.04.15.
//
//

#include "Game.h"
#include "TextureManager.h"
#include "SDLGameObject.h"

using namespace Yoba;

SDLGameObject::SDLGameObject(const LoaderParams &params) :
GameObject(params), m_position(params.getX(), params.getY()), m_velocity(0,0)
{
    m_width = params.getWidth();
    m_height = params.getHeight();
    
    m_textureID = params.getTextureID();
    
    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(),
                                          m_width, m_height, m_currentRow, m_currentFrame,
                                          Game::Instance()->getRenderer());
}

void SDLGameObject::update() {
    m_position += m_velocity;
}

void SDLGameObject::clean() {
    
}

