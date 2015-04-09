//
//  MenuButton.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include "MenuButton.h"
#include "InputHandler.h"

using namespace Yoba;

MenuButton::MenuButton(const LoaderParams &params)
: SDLGameObject(params)
{
    m_currentFrame = BUTTON_STATE_MOUSE_OUT;
}

MenuButton::MenuButton(const LoaderParams &params, std::function<void()> callback)
: SDLGameObject(params), m_callback(callback)
{
    m_currentFrame = BUTTON_STATE_MOUSE_OUT;
}

MenuButton::~MenuButton() {
    clean();
}

void MenuButton::draw() {
    SDLGameObject::draw();
}

void MenuButton::update() {
    Vector2D pMousePos = InputHandler::Instance()->mousePosition();
    
    /// \todo use frame and intersection
    if(pMousePos.getX() < (m_position.getX() + m_width)
       && pMousePos.getX() > m_position.getX()
       && pMousePos.getY() < (m_position.getY() + m_height)
       && pMousePos.getY() > m_position.getY())
    {
        
        if(InputHandler::Instance()->mouseButtonState(InputHandler::MOUSE_BUTTON_LEFT) && m_bReleased) {
            m_currentFrame = BUTTON_STATE_CLICKED;
            
            if (m_callback) {
                m_callback();
            }
            m_bReleased = false;
        }
        else if(!InputHandler::Instance()->mouseButtonState(InputHandler::MOUSE_BUTTON_LEFT)) {
            m_bReleased = true;
            m_currentFrame = BUTTON_STATE_MOUSE_OVER;
        }
        
    } else {
        m_currentFrame = BUTTON_STATE_MOUSE_OUT;
    }
}

void MenuButton::clean() {
    SDLGameObject::clean();
}