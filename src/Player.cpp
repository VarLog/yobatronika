//
//  Player.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include "Player.h"

using namespace Yoba;

Player::Player(std::string name, const LoaderParams &params)
: SDLGameObject(params), m_sName(name)
{
    
}

Player::~Player() {
    
}
