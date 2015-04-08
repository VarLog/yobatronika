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

}

InputHandler::~InputHandler() {

}

void InputHandler::update() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                Game::Instance()->quit();
                break;
            }
                
            case SDL_KEYDOWN: {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Game::Instance()->quit();
                        break;
                }
                break;
            }
            
            case SDL_JOYBUTTONDOWN: {
                int whichOne = event.jaxis.which;
                m_vJoystickButtonStates[whichOne][event.jbutton.button] = true;
                break;
            }
            case SDL_JOYBUTTONUP: {
                int whichOne = event.jaxis.which;
                m_vJoystickButtonStates[whichOne][event.jbutton.button] = false;
                break;
            }
                
            case SDL_JOYAXISMOTION: {
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
                
                break;
            }
                
            default:
                break;
        }
    }
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
        
        std::cout << "Initialised  "<< m_vJoysticks.size() << "joystick(s)";
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