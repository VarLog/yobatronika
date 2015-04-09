//
//  Player.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include "Player.h"

#include "InputHandler.h"

using namespace Yoba;

Player::Player(std::string name, const LoaderParams &params)
: SDLGameObject(params), m_sName(name)
{
    
}

Player::~Player() {
    
}

void Player::draw() {
    SDLGameObject::draw();
}

void Player::clean() {
    SDLGameObject::clean();
}

void Player::update() {
    m_velocity.setX(0);
    m_velocity.setY(0);
    
    handleInput();
    
    SDLGameObject::update();
}

void Player::handleInput() {
    if(InputHandler::Instance()->joysticksInitialised()) {
        Vector2D value(0,0);
        value += InputHandler::Instance()->joystickValue(0, 1);
        value += InputHandler::Instance()->joystickValue(0, 2);
        
        m_velocity = value * 1;
        
        // Yellow button on xbox360 gamepad
        if(InputHandler::Instance()->joystickButtonState(0, 3))
        {
            m_velocity.setX(10);
        }
    }
    
    if(InputHandler::Instance()->mouseButtonState(InputHandler::MOUSE_BUTTON_LEFT))
    {
        m_velocity.setY(1);
    }
    
    Vector2D vec = InputHandler::Instance()->mousePosition();
    m_acceleration = (vec - m_position) / 100;
}