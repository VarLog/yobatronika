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
GameObject(params)
{
    m_x = params.getX();
    m_y = params.getY();
    
    m_width = params.getWidth();
    m_height = params.getHeight();
    
    m_textureID = params.getTextureID();
    
    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y,
                                          m_width, m_height, m_currentRow, m_currentFrame,
                                          Game::Instance()->getRenderer());
}

void SDLGameObject::update() {
    
}

void SDLGameObject::clean() {
    
}

