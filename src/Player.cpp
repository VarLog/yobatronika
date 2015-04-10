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

Player::Player(const LoaderParams &params, std::string name)
: SDLGameObject(params), m_sName(name)
{
    
}

Player::~Player() {
    clean();
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
    
    if (m_velocity.getX() < 0) {
        m_renderFlip = SDL_FLIP_HORIZONTAL;
    } else {
        m_renderFlip = SDL_FLIP_NONE;
    }
    
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
        Vector2D vec = InputHandler::Instance()->mousePosition();
        
        Vector2D center(m_position.getX()+m_width/2, m_position.getY()+m_height/2);
        
        m_velocity = (vec - center) / 50;
    }
    
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        m_velocity.setX(2);
    }
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        m_velocity.setX(-2);
    }
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        m_velocity.setY(-2);
    }
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        m_velocity.setY(2);
    }
}
