//
//  InputHandler.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 08.04.15.
//
//

#include <iostream>

#include "InputHandler.h"
#include "Game.h"

using namespace Yoba;

std::shared_ptr<InputHandler> InputHandler::m_spInstance = nullptr;

std::shared_ptr<InputHandler> InputHandler::Instance()
{
    if(m_spInstance == nullptr)
    {
        m_spInstance = std::shared_ptr<InputHandler>(new InputHandler());
    }
    return m_spInstance;
}

void InputHandler::DeleteInstance() {
    m_spInstance.reset();
}

InputHandler::InputHandler() {
    m_vMouseButtonStates.assign(3, false);
}

InputHandler::~InputHandler() {
    clean();
}

void InputHandler::update() {
    m_keystates = SDL_GetKeyboardState(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                Game::Instance()->quit();
                break;
            }
                
            case SDL_KEYDOWN: {
                onKeyDown(event);
                break;
            }
                
            case SDL_KEYUP: {
                onKeyUp(event);
                break;
            }
                
            case SDL_MOUSEMOTION:
            {
                onMouseMove(event);
                break;
            }
                
            case SDL_MOUSEBUTTONDOWN:
            {
                onMouseButtonDown(event);
                break;
            }
                
            case SDL_MOUSEBUTTONUP:
            {
                onMouseButtonUp(event);
                break;
            }
            
            case SDL_JOYBUTTONDOWN: {
                onJoystickButtonDown(event);
                break;
            }
            case SDL_JOYBUTTONUP: {
                onJoystickButtonUp(event);
                break;
            }
                
            case SDL_JOYAXISMOTION: {
                onJoystickAxisMove(event);
                break;
            }
                
            default:
                break;
        }
    }
}

void InputHandler::onKeyDown(SDL_Event& event) {

}

void InputHandler::onKeyUp(SDL_Event& event) {
    
}

void InputHandler::onMouseMove(SDL_Event& event) {
    m_mousePosition.setX(event.motion.x);
    m_mousePosition.setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event) {
    if(event.button.button == SDL_BUTTON_LEFT) {
        m_vMouseButtonStates[MOUSE_BUTTON_LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) {
        m_vMouseButtonStates[MOUSE_BUTTON_MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) {
        m_vMouseButtonStates[MOUSE_BUTTON_RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event) {
    if(event.button.button == SDL_BUTTON_LEFT) {
        m_vMouseButtonStates[MOUSE_BUTTON_LEFT] = false;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) {
        m_vMouseButtonStates[MOUSE_BUTTON_MIDDLE] = false;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) {
        m_vMouseButtonStates[MOUSE_BUTTON_RIGHT] = false;
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event& event) {
    int whichOne = event.jaxis.which;
    
    // left stick move left or right
    if(event.jaxis.axis == 0) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setX(1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setX(-1);
        } else {
            m_vJoystickValues[whichOne].first.setX(0);
        }
    }
    
    // left stick move up or down
    if(event.jaxis.axis == 1) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setY(1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setY(-1);
        } else {
            m_vJoystickValues[whichOne].first.setY(0);
        }
    }
    
    // right stick move left or right
    if(event.jaxis.axis == 3) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setX(1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setX(-1);
        } else {
            m_vJoystickValues[whichOne].first.setX(0);
        }
    }
    
    // right stick move up or down
    if(event.jaxis.axis == 4) {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setY(1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_vJoystickValues[whichOne].first.setY(-1);
        } else {
            m_vJoystickValues[whichOne].first.setY(0);
        }
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event& event) {
    int whichOne = event.jaxis.which;
    m_vJoystickButtonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event) {
    int whichOne = event.jaxis.which;
    m_vJoystickButtonStates[whichOne][event.jbutton.button] = false;
}

void InputHandler::clean() {
    if(m_bJoysticksInitialised) {
        for(auto joy : m_vJoysticks) {
            SDL_JoystickClose(joy);
        }
    }
}

void InputHandler::initialiseJoysticks() {
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
    if(SDL_NumJoysticks() > 0) {
        
        for(int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            
            if(joy && (SDL_JoystickGetAttached(joy) == SDL_TRUE)) {
                m_vJoysticks.push_back(joy);
                m_vJoystickValues.push_back(std::make_pair(Vector2D(0,0),Vector2D(0,0)));
                
                std::vector<bool> tempButtons;
                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
                    tempButtons.push_back(false);
                }
                m_vJoystickButtonStates.push_back(tempButtons);
                
            } else {
                /// \todo exception
                std::cout << SDL_GetError() << std::endl;
                return;
            }
        }
        
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        
        std::cout << "Initialised " << m_vJoysticks.size() << "joystick(s)";
    } else {
        m_bJoysticksInitialised = false;
    }
}

const Vector2D InputHandler::joystickValue(int joy, int stick) const {
    if(m_vJoystickValues.size() > 0) {
        if(stick == 1) {
            return m_vJoystickValues[joy].first;
        } else if(stick == 2) {
            return m_vJoystickValues[joy].second;
        }
    }
    /// \todo exception
    return Vector2D(0,0);
}

bool InputHandler::joystickButtonState(int joy, int buttonNumber) const {
    /// \todo error handle
    return m_vJoystickButtonStates[joy][buttonNumber];
}

bool InputHandler::mouseButtonState(MOUSE_BUTTONS button) const {
    return m_vMouseButtonStates[button];
}

const Vector2D InputHandler::mousePosition() const {
    return m_mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    if(m_keystates != nullptr) {
        if(m_keystates[key] == 1) {
            return true;
        } else {
            return false;
        }
    }
    /// \todo exception
    return false;
}

void InputHandler::resetMouseButtonStates() {
    m_vMouseButtonStates.assign(3, false);
}
