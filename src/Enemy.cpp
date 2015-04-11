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
    m_velocity.setY(2);
    m_velocity.setX(0.001);
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
    if(m_position.getY() <= 0)
    {
        m_position = Vector2D(m_position.getX(), 0);
        m_velocity.setY(2);
    }
    else if(m_position.getY() >= 400)
    {
        m_position = Vector2D(m_position.getX(), 400);
        m_velocity.setY(-2);
    }
    
    if(m_position.getX() <= 0)
    {
        m_velocity.setX(0.1);
    }
    else if(m_position.getX() >= 400)
    {
        m_velocity.setX(-0.1);
    }
    
    SDLGameObject::update();
}
