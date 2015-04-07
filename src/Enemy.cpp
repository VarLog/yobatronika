//
//  Enemy.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include "Enemy.h"

using namespace Yoba;

Enemy::Enemy(const LoaderParams &params)
: SDLGameObject(params)
{
    
}

Enemy::~Enemy() {
    
}

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::clean() {
    SDLGameObject::clean();
}

void Enemy::update()
{
    m_velocity.setX(-1);
    
    SDLGameObject::update();
}
