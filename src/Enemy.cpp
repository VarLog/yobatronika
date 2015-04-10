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
    clean();
}

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::clean() {
    SDLGameObject::clean();
}

void Enemy::update()
{
    SDLGameObject::update();
}
