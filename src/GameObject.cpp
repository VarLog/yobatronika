//
//  GameObject.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include <iostream>

#include <SDL.h>

#include "GameObject.h"
#include "TextureManager.h"

using namespace Yoba;

GameObject::GameObject(int x, int y, int width, int height, std::string textureID) {
    load(x, y, width, height, textureID);
}

GameObject::~GameObject() {
    clean();
}

void GameObject::load(int x, int y, int width, int height, std::string textureID) {
    m_x = x;
    m_y = y;
    
    m_width = width;
    m_height = height;
    
    m_textureID = textureID;
    
    m_currentRow = 1;
    m_currentFrame = 1;    
}

void GameObject::draw(SDL_Renderer* pRenderer) {
    TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height,
                                          m_currentRow, m_currentFrame, pRenderer);
}

void GameObject::update() {

}

void GameObject::clean() {
    std::cout << "GameObject::clean()" << std::endl;
}