//
//  Enemy.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include "Enemy.h"

using namespace Yoba;

Enemy::Enemy(int x, int y, int width, int height, std::string textureID)
: GameObject(x, y, width, height, textureID)
{
    
}

Enemy::~Enemy() {
    
}
