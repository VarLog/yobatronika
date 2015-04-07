//
//  Player.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include "Player.h"

using namespace Yoba;

Player::Player(std::string name, int x, int y, int width, int height, std::string textureID)
: GameObject(x, y, width, height, textureID), m_sName(name)
{
    
}
